from conans import ConanFile, CMake, tools


class BossCppServerConan(ConanFile):
	name = "BossCppServer"
	version = "0.0.1"
	author = "John Christman john.christman@smoothstack.com"
	url = "https://github.com/SSOrphans/boss/cpp-server"
	description = "C++ based HTTP server proof of concept for SWIFT and Crabel position."
	settings = "os", "compiler", "build_type", "arch"
	options = {"shared": [True, False], "fPIC": [True, False]}
	default_options = {"shared": False, "fPIC": True}
	generators = "cmake"

	def config_options(self):
		if self.settings.os == "Windows":
			del self.options.fPIC

#     def source(self):
#         self.run("git clone https://github.com/conan-io/hello.git")
#         # This small hack might be useful to guarantee proper /MT /MD linkage
#         # in MSVC if the packaged project doesn't have variables to set it
#         # properly
#         tools.replace_in_file("hello/CMakeLists.txt", "PROJECT(HelloWorld)",
#                               '''PROJECT(HelloWorld)
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()''')

	def build(self):
		cmake = CMake(self)
		cmake.configure(source_folder="source")
		cmake.build()

		# Explicit way:
		# self.run('cmake %s/hello %s'
		#          % (self.source_folder, cmake.command_line))
		# self.run("cmake --build . %s" % cmake.build_config)

	def package(self):
		self.copy("*.h", dst="include", src="source")
		self.copy("*hello.lib", dst="lib", keep_path=False)
		self.copy("Project", dst="bin", keep_path=False)
		self.copy("*.dll", dst="bin", keep_path=False)
		self.copy("*.so", dst="lib", keep_path=False)
		self.copy("*.dylib", dst="lib", keep_path=False)
		self.copy("*.a", dst="lib", keep_path=False)

	def package_info(self):
		self.cpp_info.libs = ["hello"]
