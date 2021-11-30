#pragma once
#include "request_handler.hpp"

namespace ssor::boss {
struct session : std::enable_shared_from_this<session> {
  explicit session(tcp::socket&& socket, tls::context& ctx)
      : m_stream{std::move(socket)}, m_sender{*this} {}

  void run() {
    BOOST_LOG_TRIVIAL(trace) << "Starting session";
    net::dispatch(
        m_stream.get_executor(),
        beast::bind_front_handler(&session::on_run, shared_from_this()));
  }

 private:
  struct response_handler {
    explicit response_handler(session& session) : m_session{session} {}

    template <bool is_request, typename TBody, typename TFields>
    void operator()(http::message<is_request, TBody, TFields>&& msg) const {
      using http_message = http::message<is_request, TBody, TFields>;
      auto sp = std::make_shared<http_message>(std::move(msg));

      m_session.m_response = sp;
      BOOST_LOG_TRIVIAL(trace) << "Data written to stream";
      http::async_write(m_session.m_stream, *sp,
                        beast::bind_front_handler(&session::on_write,
                                                  m_session.shared_from_this(),
                                                  sp->need_eof()));
    }

   private:
    session& m_session;
  };

 private:
  static void fail(const beast::error_code& ec, const char* what) {
    // no close_notify case.
    if (ec == tls::error::stream_truncated) return;

    BOOST_LOG_TRIVIAL(error) << what << ": " << ec.message() << "\n";
  }

  static void set_connection_expiration(session* self) {
    constexpr auto expiry{std::chrono::seconds(30)};
    self->m_stream.expires_after(expiry);
    // beast::get_lowest_layer(self->m_stream).expires_after(expiry);
  }

  void close() {
    set_connection_expiration(this);

    beast::error_code ec;
    m_stream.socket().shutdown(tcp::socket::shutdown_send, ec);
    // m_stream.async_shutdown(beast::bind_front_handler(&session::on_shutdown,
    // shared_from_this()));
  }

  void read() {
    m_request = {};
    set_connection_expiration(this);
    http::async_read(
        m_stream, m_buffer, m_request,
        beast::bind_front_handler(&session::on_read, shared_from_this()));
  }

  void on_handshake(const beast::error_code& ec) {
    if (static_cast<bool>(ec)) return fail(ec, "session handshake");
    read();
  }

  void on_read(beast::error_code ec, std::size_t bytes) {
    boost::ignore_unused(bytes);
    if (static_cast<bool>(ec)) {
      if (ec == http::error::end_of_stream) return close();
      return fail(ec, "session read");
    }

    BOOST_LOG_TRIVIAL(trace) << "Handling request";
    request_handler::handle(std::move(m_request), m_sender);
  }

  void on_run() {
    set_connection_expiration(this);
    read();
    // m_stream.async_handshake(tls::stream_base::server,
    // 	beast::bind_front_handler(&session::on_handshake, shared_from_this()));
  }

  void on_shutdown(const beast::error_code& ec) {
    if (static_cast<bool>(ec)) return fail(ec, "session shutdown");
  }

  void on_write(bool close, beast::error_code ec, std::size_t bytes) {
    boost::ignore_unused(bytes);
    if (static_cast<bool>(ec)) return fail(ec, "session write");

    if (close) return this->close();

    m_response = nullptr;
    read();
  }

 private:
  // beast::ssl_stream<beast::tcp_stream> m_stream;
  beast::tcp_stream m_stream;
  beast::flat_buffer m_buffer;
  http::request<http::string_body> m_request;
  std::shared_ptr<void> m_response;
  response_handler m_sender;
};
}  // namespace ssor::boss
