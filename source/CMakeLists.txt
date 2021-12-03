add_executable(${PROJECT_NAME} main.cpp book.grpc.pb.cc book.pb.cc)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE LIBXML_WRITER_ENABLED
	PRIVATE LIBXML_OUTPUT_ENABLED
)

target_precompile_headers(${PROJECT_NAME} PRIVATE predef.hpp)

# Link all required interface libraries.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE Boost::Boost
	PRIVATE gRPC::gRPC
	PRIVATE LibXml2::LibXml2
	PRIVATE OpenSSL::OpenSSL
)
