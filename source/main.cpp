#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <boost/json.hpp>

namespace json = boost::json;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	fs::path configFile { argv[0] };

	// Escape bin directory and enter the etc directory.
	configFile = configFile.parent_path().parent_path();
	configFile.append("etc/server-config.json");

	// Check file's existence.
	if (!fs::exists(configFile))
	{
		std::cerr << "No configuration file to load.\n";
		return EXIT_FAILURE;
	}

	// Read configuration file.
	std::ifstream file { configFile };
	std::string contents {
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};

	// Convert contents to parsed JSON value.
	json::error_code ec;
	json::value jv { json::parse(contents), ec };

	std::cout << configFile << std::endl;
	return EXIT_SUCCESS;
}
