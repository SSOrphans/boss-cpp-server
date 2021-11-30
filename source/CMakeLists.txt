add_executable(${PROJECT_NAME} main.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE LIBXML_WRITER_ENABLED
	PRIVATE LIBXML_OUTPUT_ENABLED
)

target_precompile_headers(${PROJECT_NAME} PRIVATE predef.hpp)
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE Boost::filesystem
	PRIVATE Boost::json
	PRIVATE Boost::log
	PRIVATE Boost::log_setup
	PRIVATE LibXml2::LibXml2
	PRIVATE OpenSSL::SSL
	PRIVATE OpenSSL::Crypto
)
