#pragma once
#include <iostream>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/json.hpp>

namespace fs = boost::filesystem;
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace net = boost::asio;
namespace tls = boost::asio::ssl;
namespace json = boost::json;

using tcp = net::ip::tcp;
