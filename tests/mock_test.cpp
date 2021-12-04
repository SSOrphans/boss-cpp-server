#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "book.grpc.pb.h"

namespace ssor::boss::testing {

struct FakeClient {
	explicit FakeClient(book_service::StubInterface* stub)
		: m_stub{ stub }
	{ }



	void reset_stub(book_service::StubInterface* stub) {
		m_stub = stub;
	}

private:
	book_service::StubInterface* m_stub;
};

}


