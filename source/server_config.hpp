#pragma once
#include <sstream>
#include <string>

#include "predef.hpp"

namespace ssor::boss {
/**
 * @brief Contains the configuration settings for the server.
 */
struct server_config {
  // Rule of 0.
  std::string address;
  std::uint16_t port;
  std::int32_t threads;

  /**
   * @brief Converts this object into a string that can be printed.
   * @return The server configuation as a string.
   */
  std::string to_string() {
    std::ostringstream oss;
    oss << "{ "
        << "Address: " << address << ", "
        << "Port: " << port << ", "
        << "Threads: " << threads << " }";
    return oss.str();
  }
};

inline void tag_invoke(json::value_from_tag, json::value& jv,
                       const server_config& config) {
  jv = {{"address", config.address},
        {"port", config.port},
        {"threads", config.threads}};
}

inline server_config tag_invoke(json::value_to_tag<server_config>,
                                const json::value& jv) {
  const auto& obj = jv.as_object();
  return server_config{json::value_to<std::string>(obj.at("address")),
                       json::value_to<std::uint16_t>(obj.at("port")),
                       json::value_to<std::int32_t>(obj.at("threads"))};
}
}  // namespace ssor::boss
