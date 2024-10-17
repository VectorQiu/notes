from concurrent import futures
import grpc
import helloworld_pb2
import helloworld_pb2_grpc

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, context):
        return helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)

    def SayHelloServerStreaming(self, request, context):
        for i in range(5):
            yield helloworld_pb2.HelloReply(message='Hello, %s! Number %d' % (request.name, i + 1))

    def SayHelloClientStreaming(self, request_iterator, context):
        names = []
        for request in request_iterator:
            names.append(request.name)
        return helloworld_pb2.HelloReply(message='Hello, %s!' % ', '.join(names))

    def SayHelloBiDiStreaming(self, request_iterator, context):
        for request in request_iterator:
            yield helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started on port 50051.")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
