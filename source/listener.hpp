#pragma once
#include "session.hpp"

namespace ssor::boss {
struct listener : std::enable_shared_from_this<listener> {
  explicit listener(net::io_context& ioc, tls::context& ctx,
                    const tcp::endpoint& endpoint)
      : m_ioc{ioc}, m_ctx{ctx}, m_acceptor{ioc} {
    beast::error_code ec;
    m_acceptor.open(endpoint.protocol(), ec);
    if (static_cast<bool>(ec)) {
      fail(ec, "listener open");
      return;
    }

    m_acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if (static_cast<bool>(ec)) {
      fail(ec, "listener set option reuse address");
      return;
    }

    m_acceptor.bind(endpoint, ec);
    if (static_cast<bool>(ec)) {
      fail(ec, "listener bind");
      return;
    }

    m_acceptor.listen(net::socket_base::max_listen_connections, ec);
    if (static_cast<bool>(ec)) {
      fail(ec, "listener listen");
      return;
    }
  }

  void run() {
    BOOST_LOG_TRIVIAL(trace) << "Running Listener";
    accept();
  }

 private:
  void accept() {
    BOOST_LOG_TRIVIAL(trace) << "Accepting connections";
    m_acceptor.async_accept(
        net::make_strand(m_ioc),
        beast::bind_front_handler(&listener::on_accept, shared_from_this()));
  }

  static void fail(const beast::error_code& ec, const char* what) {
    // no close_notify case.
    if (ec == tls::error::stream_truncated) return;

  	BOOST_LOG_TRIVIAL(error) << what << ": " << ec.message() << "\n";
  }

  void on_accept(const beast::error_code& ec, tcp::socket socket) {
    if (static_cast<bool>(ec)) {
      fail(ec, "listener accept");
      return;
    }

    std::make_shared<session>(std::move(socket), m_ctx)->run();
    BOOST_LOG_TRIVIAL(trace) << "Connection accepted";
    accept();  // TODO: remove recursion!
  }

 private:
  net::io_context& m_ioc;
  tls::context& m_ctx;
  tcp::acceptor m_acceptor;
};
}  // namespace ssor::boss
