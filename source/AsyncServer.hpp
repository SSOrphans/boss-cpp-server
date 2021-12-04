#pragma once
#include "predef.hpp"
#include "ServerConfig.hpp"
#include "Book.grpc.pb.h"

namespace ssor::boss {

struct AsyncServer final {
	AsyncServer(const ServerConfig& config)
		: m_config{ config }
	{ }

	~AsyncServer() {
		m_server->Shutdown();
		m_queue->Shutdown();
	}

	void run() {
		std::string server_address{ m_config.address };
		server_address += ":";
		server_address += std::to_string(m_config.port);

		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
		builder.RegisterService(&m_service);

		m_queue = builder.AddCompletionQueue();
		m_server = builder.BuildAndStart();

		BOOST_LOG_TRIVIAL(trace) << "Server listening on " << server_address;
		handle_rpcs();
	}

private:
	struct call_data {
		// TODO: call child events.
		virtual void proceed() = 0;

	protected:
		call_data(BookService::AsyncService* service, grpc::ServerCompletionQueue* queue)
			: m_service{ service }
			, m_queue{ queue }
			, m_status{ call_status::create }
		{
			Book book1;
			book1.set_name("Moby-Dick");
			book1.set_author("Herman Melville");

			Book book2;
			book2.set_name("Jane Eyre");
			book2.set_author("Charlotte Brontë");

			m_books.push_back(book1);
			m_books.push_back(book2);
		}

	protected:
		enum struct call_status {
			create, process, finish
		};

	protected:
		std::vector<Book> m_books;
		grpc::ServerContext m_context;
		BookService::AsyncService* m_service;
		grpc::ServerCompletionQueue* m_queue;
		call_status m_status;
	};

	struct get_book_call_data : public call_data {
		get_book_call_data(BookService::AsyncService* service, grpc::ServerCompletionQueue* queue)
			: call_data(service, queue)
			, m_responder{ &m_context }
		{ }

		void proceed() override {
			if (m_status == call_status::create) {
				m_status = call_status::process;
				m_service->RequestGetBook(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
			} else if (m_status == call_status::process) {
				// spawn new one for other requests.
				(new get_book_call_data(m_service, m_queue))->proceed();

				BOOST_LOG_TRIVIAL(trace) << "Received request for book " << m_request.value();
				m_status = call_status::finish;
				m_responder.Finish(m_books[0], grpc::Status::OK, this);
			} else {
				GPR_ASSERT(m_status == call_status::finish);
				delete this;
			}
		}

	private:
		grpc::ServerAsyncResponseWriter<Book> m_responder;
		google::protobuf::UInt32Value m_request;
	};

	struct list_books_call_data : public call_data {
		list_books_call_data(BookService::AsyncService* service, grpc::ServerCompletionQueue* queue)
			: call_data(service, queue)
			, m_responder{ &m_context }
		{ }

		void proceed() override {
			if (m_status == call_status::create) {
				m_status = call_status::process;
				m_service->RequestListBooks(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
			} else if (m_status == call_status::process) {
				// spawn new one for other requests.
				(new list_books_call_data(m_service, m_queue))->proceed();

				BOOST_LOG_TRIVIAL(trace) << "Received request for all books";
				m_status = call_status::finish;
				for (const auto& b : m_books)
					m_responder.Write(b, this);
				m_responder.Finish(grpc::Status::OK, this);
			}
		}

	private:
		grpc::ServerAsyncWriter<Book> m_responder;
		google::protobuf::Empty m_request;
	};

private:
	void handle_rpcs() {
		(new get_book_call_data(&m_service, m_queue.get()))->proceed();
		(new list_books_call_data(&m_service, m_queue.get()))->proceed();

		void* tag;
		bool ok;
		while (true) {
			GPR_ASSERT(m_queue->Next(&tag, &ok));
			GPR_ASSERT(ok);
			static_cast<call_data*>(tag)->proceed();
		}
	}

private:
	ServerConfig m_config;
	BookService::AsyncService m_service;
	std::unique_ptr<grpc::Server> m_server;
	std::unique_ptr<grpc::ServerCompletionQueue> m_queue;
};

} // namespace ssor::boss
