// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Book.proto
#ifndef GRPC_Book_2eproto__INCLUDED
#define GRPC_Book_2eproto__INCLUDED

#include "Book.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace ssor {
namespace boss {

// enum ServiceErrors {
// 	OK,
// 	InvalidID
// }
//
// message BookResponse {
// 	optional Book book = 1;
// 	required ServiceErrors error = 2;
// }
//
class BookService final {
 public:
  static constexpr char const* service_full_name() {
    return "ssor.boss.BookService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::ssor::boss::Book* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>> AsyncGetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>>(AsyncGetBookRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>> PrepareAsyncGetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>>(PrepareAsyncGetBookRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderInterface< ::ssor::boss::Book>> ListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::ssor::boss::Book>>(ListBooksRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>> AsyncListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>>(AsyncListBooksRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>> PrepareAsyncListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>>(PrepareAsyncListBooksRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void ListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::grpc::ClientReadReactor< ::ssor::boss::Book>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>* AsyncGetBookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ssor::boss::Book>* PrepareAsyncGetBookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderInterface< ::ssor::boss::Book>* ListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>* AsyncListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::ssor::boss::Book>* PrepareAsyncListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::ssor::boss::Book* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>> AsyncGetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>>(AsyncGetBookRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>> PrepareAsyncGetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>>(PrepareAsyncGetBookRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReader< ::ssor::boss::Book>> ListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::ssor::boss::Book>>(ListBooksRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::ssor::boss::Book>> AsyncListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::ssor::boss::Book>>(AsyncListBooksRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::ssor::boss::Book>> PrepareAsyncListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::ssor::boss::Book>>(PrepareAsyncListBooksRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response, std::function<void(::grpc::Status)>) override;
      void GetBook(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response, ::grpc::ClientUnaryReactor* reactor) override;
      void ListBooks(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::grpc::ClientReadReactor< ::ssor::boss::Book>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>* AsyncGetBookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ssor::boss::Book>* PrepareAsyncGetBookRaw(::grpc::ClientContext* context, const ::google::protobuf::UInt32Value& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReader< ::ssor::boss::Book>* ListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) override;
    ::grpc::ClientAsyncReader< ::ssor::boss::Book>* AsyncListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::ssor::boss::Book>* PrepareAsyncListBooksRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetBook_;
    const ::grpc::internal::RpcMethod rpcmethod_ListBooks_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetBook(::grpc::ServerContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response);
    virtual ::grpc::Status ListBooks(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::grpc::ServerWriter< ::ssor::boss::Book>* writer);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetBook() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetBook(::grpc::ServerContext* context, ::google::protobuf::UInt32Value* request, ::grpc::ServerAsyncResponseWriter< ::ssor::boss::Book>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ListBooks() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListBooks(::grpc::ServerContext* context, ::google::protobuf::Empty* request, ::grpc::ServerAsyncWriter< ::ssor::boss::Book>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetBook<WithAsyncMethod_ListBooks<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetBook() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::google::protobuf::UInt32Value, ::ssor::boss::Book>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::google::protobuf::UInt32Value* request, ::ssor::boss::Book* response) { return this->GetBook(context, request, response); }));}
    void SetMessageAllocatorFor_GetBook(
        ::grpc::MessageAllocator< ::google::protobuf::UInt32Value, ::ssor::boss::Book>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::google::protobuf::UInt32Value, ::ssor::boss::Book>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetBook(
      ::grpc::CallbackServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ListBooks() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackServerStreamingHandler< ::google::protobuf::Empty, ::ssor::boss::Book>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::google::protobuf::Empty* request) { return this->ListBooks(context, request); }));
    }
    ~WithCallbackMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::ssor::boss::Book>* ListBooks(
      ::grpc::CallbackServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetBook<WithCallbackMethod_ListBooks<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetBook() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ListBooks() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetBook() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetBook(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ListBooks() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListBooks(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetBook() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetBook(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetBook(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ListBooks() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const::grpc::ByteBuffer* request) { return this->ListBooks(context, request); }));
    }
    ~WithRawCallbackMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* ListBooks(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetBook : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetBook() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::google::protobuf::UInt32Value, ::ssor::boss::Book>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::google::protobuf::UInt32Value, ::ssor::boss::Book>* streamer) {
                       return this->StreamedGetBook(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetBook() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetBook(::grpc::ServerContext* /*context*/, const ::google::protobuf::UInt32Value* /*request*/, ::ssor::boss::Book* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetBook(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::google::protobuf::UInt32Value,::ssor::boss::Book>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetBook<Service > StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_ListBooks : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_ListBooks() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::google::protobuf::Empty, ::ssor::boss::Book>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerSplitStreamer<
                     ::google::protobuf::Empty, ::ssor::boss::Book>* streamer) {
                       return this->StreamedListBooks(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_ListBooks() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ListBooks(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::ssor::boss::Book>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedListBooks(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::google::protobuf::Empty,::ssor::boss::Book>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_ListBooks<Service > SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetBook<WithSplitStreamingMethod_ListBooks<Service > > StreamedService;
};

}  // namespace boss
}  // namespace ssor


#endif  // GRPC_Book_2eproto__INCLUDED