# C++ Server using gRPC over HTTP/2

This project provides an implementation of a simple Book API that is accessed via gRPC over HTTP/2.
It has been dockerized so that it can run in an environment that it expects and can be isolated in
for it's own purposes. This proves useful in a cloud environment or standalone.

## Prerequisites

The project was built from an RHEL 8 environment and uses an RHEL 8 container. The decision to use
RHEL 8 for development was because of its stability and to be able to use RHEL 8 containers without
spending entitlements to RHEL 8 when building containers. It's recommended to use an RHEL system or
a compatible RHEL system unless you have unlimited entitlements.

## Building the server

The project provides a hand made command runner `run.sh`. It has a set of commands that you can poll
with `./run.sh help` but we'll discuss some of the most important ones. Keep in mind that all
commands will be ran from inside the development container, this tends to slow down operations
because the container will be writing cache files back to the host.

Also note that the project expects to be at `${HOME}/smoothstack/boss/cpp-server`. This is the
`PROJECT_ROOT_DIR` in the `./scripts/variables.sh` file. If this doesn't work for you, you are
welcome to change it for your purposes.

- `./run.sh fetch <profile>` will fetch and build all dependencies for the environment specified by
`<profile>` using Conan. The results of the dependencies will be written to a `.conan` cache folder
in the root of the project. If you're using Visual Studio Code for development, you may want to add
the include folders from each of the dependency packages to your `C_Cpp.default.includePath` so that
it registers properly with the editor.

- `./run.sh build <profile>` will first attempt to fetch all the dependencies if necessary, then it
will build the server itself using CMake. The build files will be directed to `./build/<profile>`.

- `./run.sh pack <profile>` will first attempt to build the project if necessary, then it will
package the server and all its dependencies. The package will be directed to
`./build/<profile>/package`. There will be a `bin` folder with the server application, a `lib`
folder with the required dynamic libraries.

- `./run.sh clean <profile>` will clean the build directory for the given profile using
`make clean`.

- `./run.sh purge <profile>` will completely remove the build directory for the given profile. Use
this is your experiencing segmentation faults with your program and debugging the program isn't able
to produce a root cause. This can happen when ABIs get mixed up, which can happen if you updated a
dependency and not everything was rebuilt properly.

- `./run.sh reset` will purge all builds and then remove the `.conan` cache to reset the entire
build system. Use this only if you're experiencing issues with your dependencies or your builds.

## Debugging the server

The server uses Boost::Log to output trace information in debug mode. Use this to debug internal
problems that aren't easily apparent. For more complicated issues such as segmentation fault or the
like, open the development container in interactive mode `./run.sh interactive` and then use `lldb`
to debug the application.

## Running the server

To run the application locally use `./run.sh local <profile>`. To run the application in server like
environment use `./run.sh server <profile>`.
