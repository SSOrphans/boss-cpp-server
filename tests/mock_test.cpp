#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/test/mock_stream.h>

#include "Book_mock.grpc.pb.h"

struct FakeClient {
	explicit FakeClient(ssor::boss::BookService::StubInterface* stub)
		: m_stub{ stub }
	{ }

	void DoGetBook() {
		grpc::ClientContext context;
		google::protobuf::UInt32Value request;
		ssor::boss::Book response;

		request.set_value(1);
		grpc::Status s = m_stub->GetBook(&context, request, &response);
		EXPECT_EQ(response.name(), "Moby-Dick");
		EXPECT_EQ(response.author(), "Herman Melville");
		EXPECT_TRUE(s.ok());
	}

	void DoListBooks() {
		grpc::ClientContext context;
		google::protobuf::Empty request;
		ssor::boss::Book response;

		auto cstream = m_stub->ListBooks(&context, request);
		EXPECT_TRUE(cstream->Read(&response));
		EXPECT_EQ(response.name(), "Moby-Dick");
		EXPECT_EQ(response.author(), "Herman Melville");

		EXPECT_TRUE(cstream->Read(&response));
		EXPECT_EQ(response.name(), "Jane Eyre");
		EXPECT_EQ(response.author(), "Charlotte Bronte");

		// Finish stream.
		EXPECT_FALSE(cstream->Read(&response));
		grpc::Status s = cstream->Finish();
		EXPECT_TRUE(s.ok());
	}

	void ResetStub(ssor::boss::BookService::StubInterface* stub) {
		m_stub = stub;
	}

private:
	ssor::boss::BookService::StubInterface* m_stub;
};

struct TestService : public ssor::boss::BookService::Service {
	TestService() {
		ssor::boss::Book book1;
		book1.set_name("Moby-Dick");
		book1.set_author("Herman Melville");

		ssor::boss::Book book2;
		book2.set_name("Jane Eyre");
		book2.set_author("Charlotte Bronte");

		m_books.push_back(book1);
		m_books.push_back(book2);
	}

	grpc::Status GetBook(grpc::ServerContext*,
	                     const google::protobuf::UInt32Value* request,
		                   ssor::boss::Book* response) override {
		response->set_name(m_books[0].name());
		response->set_author(m_books[0].author());
		return grpc::Status::OK;
	}

	grpc::Status ListBooks(grpc::ServerContext*,
	                       const google::protobuf::Empty*,
	                       grpc::ServerWriter<ssor::boss::Book>* writer) override {
		for (const auto& b : m_books)
			writer->Write(b);
		return grpc::Status::OK;
	}

private:
	std::vector<ssor::boss::Book> m_books;
};

struct MockTest : public ::testing::Test {
protected:
	MockTest() {}

	void SetUp() override {
		grpc::ServerBuilder builder;
		builder.AddListeningPort("localhost:9090", grpc::InsecureServerCredentials());
		builder.RegisterService(&m_service);
		m_server = builder.BuildAndStart();
	}

	void TearDown() override {
		m_server->Shutdown();
	}

	void ResetStub() {
		m_stub = ssor::boss::BookService::NewStub(
			grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));
	}

	std::unique_ptr<ssor::boss::BookService::Stub> m_stub;
	std::unique_ptr<grpc::Server> m_server;
	TestService m_service;
};

TEST_F(MockTest, GetBookTest) {
	ResetStub();

	// Real RPC.
	FakeClient client(m_stub.get());
	client.DoGetBook();

	ssor::boss::MockBookServiceStub stub;
	ssor::boss::Book resp;
	resp.set_name("Moby-Dick");
	resp.set_author("Herman Melville");

	// Mock RPC.
	using namespace testing;
	EXPECT_CALL(stub, GetBook(_, _, _))
		.Times(AtLeast(1)).WillOnce(DoAll(SetArgPointee<2>(resp), Return(grpc::Status::OK)));
	client.ResetStub(&stub);
	client.DoGetBook();
}

TEST_F(MockTest, ListBooksTest) {
	ResetStub();

	// Real RPC.
	FakeClient client(m_stub.get());
	client.DoListBooks();

	ssor::boss::MockBookServiceStub stub;
	auto reader = new grpc::testing::MockClientReader<ssor::boss::Book>();

	ssor::boss::Book response1;
	response1.set_name("Moby-Dick");
	response1.set_author("Herman Melville");

	ssor::boss::Book response2;
	response2.set_name("Jane Eyre");
	response2.set_author("Charlotte Bronte");

	// Mock RPC.
	using namespace testing;
	EXPECT_CALL(*reader, Read(_))
		.WillOnce(DoAll(SetArgPointee<0>(response1), Return(true)))
		.WillOnce(DoAll(SetArgPointee<0>(response2), Return(true)))
		.WillOnce(Return(false));
	EXPECT_CALL(*reader, Finish())
		.WillOnce(Return(grpc::Status::OK));
	EXPECT_CALL(stub, ListBooksRaw(_, _))
		.WillOnce(Return(reader));

	client.ResetStub(&stub);
	client.DoListBooks();
}
