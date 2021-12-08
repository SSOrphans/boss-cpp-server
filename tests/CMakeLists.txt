include(GoogleTest)

add_executable(mock_test
	mock_test.cpp
	${CMAKE_SOURCE_DIR}/source/Book.grpc.pb.cc
	${CMAKE_SOURCE_DIR}/source/Book.pb.cc)

target_include_directories(mock_test
	PRIVATE ${CMAKE_SOURCE_DIR}/source)

target_link_libraries(mock_test
	PRIVATE gRPC::gRPC
	PRIVATE GTest::gmock
	PRIVATE GTest::gtest
	PRIVATE GTest::gtest_main)

gtest_discover_tests(mock_test)
