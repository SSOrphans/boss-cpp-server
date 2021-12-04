#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>

#include "AsyncServer.hpp"

namespace ssor::boss {
void init_logging() {
  using namespace boost::log;
  using namespace boost::log::trivial;

  static const auto COMMON_FMT{"[%TimeStamp%][%Severity%]: %Message%"};
  register_simple_formatter_factory<severity_level, char>("Severity");
  add_console_log(std::cout, keywords::format = COMMON_FMT,
                  keywords::auto_flush = true);
  add_common_attributes();

#ifdef _DEBUG
  core::get()->set_filter(severity >= trace);
#else
  core::get()->set_filter(severity >= warning);
#endif
}

ServerConfig load_config_file(const fs::path& path) {
  BOOST_LOG_TRIVIAL(info) << "Config file at path '" << path.c_str()
                          << "' loaded";

  // Read configuration file.
  std::ifstream file{path};
  json::value value{json::parse(std::string{
      std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()})};

  // Convert contents to parsed JSON value.
  return ssor::boss::ServerConfig{json::value_to<ServerConfig>(value)};
}
}  // namespace ssor::boss

int main(int argc, char** argv) {
	ssor::boss::init_logging();

  // Escape bin directory and enter the etc directory.
  fs::path configFile{argv[0]};
  configFile = configFile.parent_path().parent_path();
  configFile.append("etc/server-config.json");

  // Check file's existence.
  ssor::boss::ServerConfig config{"localhost", 8080, 2};
  if (!fs::exists(configFile))
    BOOST_LOG_TRIVIAL(warning)
        << "No configuration file found, loading default configuration";
  else
    config = ssor::boss::load_config_file(configFile);

 	BOOST_LOG_TRIVIAL(info) << "Server Config " << config.to_string();
  BOOST_LOG_TRIVIAL(info) << "Starting HTTP server...";

  //net::io_context ioc{config.threads};
  //tls::context ctx{tls::context::tlsv12};
  //std::uint16_t https_port{config.port};

  //net::ip::address addr{net::ip::make_address(config.address)};
  //net::ip::tcp::endpoint https{addr, https_port};
  //auto listener = std::make_shared<ssor::boss::listener>(ioc, ctx, https);
  //listener->run();

  //for (auto index = config.threads - 1; index > 0; --index)
  //  std::thread([&ioc] { ioc.run(); }).detach();
  //ioc.run();

	ssor::boss::AsyncServer srvr{ config };
	srvr.run();

	return EXIT_SUCCESS;
}
