// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: book.proto

#include "book.pb.h"
#include "book.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace ssor {
namespace boss {

static const char* book_service_method_names[] = {
  "/ssor.boss.book_service/get_book",
  "/ssor.boss.book_service/list_books",
};

std::unique_ptr< book_service::Stub> book_service::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< book_service::Stub> stub(new book_service::Stub(channel, options));
  return stub;
}

book_service::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_get_book_(book_service_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_list_books_(book_service_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::Status book_service::Stub::get_book(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::ssor::boss::book* response) {
  return ::grpc::internal::BlockingUnaryCall< ::google::protobuf::UInt32Value, ::ssor::boss::book, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_get_book_, context, request, response);
}

void book_service::Stub::async::get_book(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::book* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::google::protobuf::UInt32Value, ::ssor::boss::book, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_book_, context, request, response, std::move(f));
}

void book_service::Stub::async::get_book(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::book* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_book_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ssor::boss::book>* book_service::Stub::PrepareAsyncget_bookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ssor::boss::book, ::google::protobuf::UInt32Value, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_get_book_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ssor::boss::book>* book_service::Stub::Asyncget_bookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncget_bookRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::ssor::boss::book>* book_service::Stub::list_booksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) {
  return ::grpc::internal::ClientReaderFactory< ::ssor::boss::book>::Create(channel_.get(), rpcmethod_list_books_, context, request);
}

void book_service::Stub::async::list_books(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::grpc::ClientReadReactor< ::ssor::boss::book>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::ssor::boss::book>::Create(stub_->channel_.get(), stub_->rpcmethod_list_books_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::ssor::boss::book>* book_service::Stub::Asynclist_booksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::ssor::boss::book>::Create(channel_.get(), cq, rpcmethod_list_books_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::ssor::boss::book>* book_service::Stub::PrepareAsynclist_booksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::ssor::boss::book>::Create(channel_.get(), cq, rpcmethod_list_books_, context, request, false, nullptr);
}

book_service::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      book_service_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< book_service::Service, ::google::protobuf::UInt32Value, ::ssor::boss::book, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](book_service::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::UInt32Value* req,
             ::ssor::boss::book* resp) {
               return service->get_book(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      book_service_method_names[1],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< book_service::Service, ::google::protobuf::Empty, ::ssor::boss::book>(
          [](book_service::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::Empty* req,
             ::grpc::ServerWriter<::ssor::boss::book>* writer) {
               return service->list_books(ctx, req, writer);
             }, this)));
}

book_service::Service::~Service() {
}

::grpc::Status book_service::Service::get_book(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::book* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status book_service::Service::list_books(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::grpc::ServerWriter< ::ssor::boss::book>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ssor
}  // namespace boss

