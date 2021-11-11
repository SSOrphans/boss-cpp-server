from conans import ConanFile, CMake, tools


class BossCppServerConan(ConanFile):
	name = "BossCppServer"
	version = "0.0.1"
	author = "John Christman john.christman@smoothstack.com"
	url = "https://github.com/SSOrphans/boss/cpp-server"
	description = "C++ based HTTP server proof of concept for SWIFT and Crabel position."
	settings = "os", "compiler", "build_type", "arch"
	options = {}
	default_options = {}
	requires = [
		"openssl/3.0.0",
		"boost/1.77.0",
		"libxml2/2.9.12",
		"gtest/1.11.0"
	]
	generators = "cmake_find_package"

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def package(self):
		self.copy("*.h", dst="include", src="source")
		self.copy("*hello.lib", dst="lib", keep_path=False)
		self.copy("BossCppServer", dst="bin", src="source", keep_path=False)
		self.copy("*.dll", dst="bin", keep_path=False)
		self.copy("*.so", dst="lib", keep_path=False)
		self.copy("*.dylib", dst="lib", keep_path=False)
		self.copy("*.a", dst="lib", keep_path=False)

	def package_info(self):
		self.cpp_info.libs = ["source"]
