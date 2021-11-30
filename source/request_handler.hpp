#pragma once
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "predef.hpp"

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#define ENCODING_TYPE "ISO-8859-1"

#else
#error "Writer or output support for libXML2 not compiled in"
#endif

namespace ssor::boss::detail {
inline std::string write_xml_document() {
	// TODO: throw exception and catch.

  int rc = 0;
  xmlTextWriterPtr writer;
	xmlBufferPtr buffer;
  xmlChar* temp;

	buffer = xmlBufferCreate();
	if (buffer == nullptr) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to create XML memory buffer.";
		std::exit(EXIT_FAILURE);
	}

	writer = xmlNewTextWriterMemory(buffer, 0);
	if (writer == nullptr) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to create XML document writer.";
		std::exit(EXIT_FAILURE);
	}

	rc = xmlTextWriterStartDocument(writer, nullptr, ENCODING_TYPE, nullptr);
	if (rc < 0) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to start writing document ("
			<< std::hex << rc << std::dec << ")";
		std::exit(EXIT_FAILURE);
	}

	rc = xmlTextWriterStartElement(writer, BAD_CAST "body");
	if (rc < 0) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to start writing element ("
			<< std::hex << rc << std::dec << ")";
		std::exit(EXIT_FAILURE);
	}

	rc = xmlTextWriterWriteElement(writer, BAD_CAST "data", BAD_CAST "Hello, World!");
	if (rc < 0) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to write data to element ("
			<< std::hex << rc << std::dec << ")";
		std::exit(EXIT_FAILURE);
	}

	rc = xmlTextWriterEndElement(writer);
	if (rc < 0) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to end writing element ("
			<< std::hex << rc << std::dec << ")";
		std::exit(EXIT_FAILURE);
	}

	rc = xmlTextWriterEndDocument(writer);
	if (rc < 0) {
		BOOST_LOG_TRIVIAL(fatal) << "Failed to end writing document ("
			<< std::hex << rc << std::dec << ")";
		std::exit(EXIT_FAILURE);
	}

	const std::string result { reinterpret_cast<const char*>(buffer->content) };
	xmlFreeTextWriter(writer);
	xmlBufferFree(buffer);

	return result;
}
}  // namespace ssor::boss::detail

namespace ssor::boss {

struct request_handler {
  template <typename TBody, typename TAllocator>
  using http_request = http::request<TBody, http::basic_fields<TAllocator>>;

 public:
  template <typename TBody, typename TAllocator, typename TSend>
  static void handle(http_request<TBody, TAllocator>&& request,
                     TSend&& sender) {
    using status = http::status;

    BOOST_LOG_TRIVIAL(trace) << "Received request:\n" << request;

    /// Returns a bad request response.
    const auto bad_request = [&request](beast::string_view why) {
      auto res{create_response(status::bad_request, request.version(),
                               request.keep_alive())};

      res.body() = std::string(why);
      res.prepare_payload();
      return res;
    };

    // Returns a not found response.
    const auto not_found = [&request](beast::string_view target) {
      auto res{create_response(status::not_found, request.version(),
                               request.keep_alive())};

      res.body() = "The resource '" + std::string(target) + "' was not found.";
      res.prepare_payload();
      return res;
    };

    // Returns a internal server error response.
    const auto server_error = [&request](beast::string_view why) {
      auto res{create_response(status::internal_server_error, request.version(),
                               request.keep_alive())};

      res.body() = "An error occurred: '" + std::string(why) + "'";
      res.prepare_payload();
      return res;
    };

    if (request.method() != http::verb::get)
      return sender(bad_request("Unknown HTTP-method"));

    const auto target{request.target()};
    if (target.empty() || target[0] != '/' ||
        target.find("..") != beast::string_view::npos)
      return sender(bad_request("Illegal request-target"));
    if (target != "/") return sender(not_found(target));

    http::string_body::value_type body{ detail::write_xml_document() };
    const auto length = body.length();
    http::response<http::string_body> res{
        std::piecewise_construct, std::make_tuple(std::move(body)),
        std::make_tuple(http::status::ok, request.version())};

    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.content_length(length);
    res.keep_alive(request.keep_alive());

    BOOST_LOG_TRIVIAL(trace) << "Writing response to stream:\n" << res;
    return sender(std::move(res));
  }

 private:
  static http::response<http::string_body> create_response(http::status s,
                                                           unsigned v,
                                                           bool ka) {
    http::response<http::string_body> res{s, v};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "application/xml");
    res.keep_alive(ka);
    return res;
  }
};
}  // namespace ssor::boss
