import grpc
import helloworld_pb2
import helloworld_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        # 简单 RPC
        response = stub.SayHello(helloworld_pb2.HelloRequest(name='World'))
        print("Simple RPC: " + response.message)

        # 服务器端流式 RPC
        print("Server Streaming RPC:")
        for response in stub.SayHelloServerStreaming(helloworld_pb2.HelloRequest(name='World')):
            print(response.message)

        # 客户端流式 RPC
        def request_generator():
            for name in ['Alice', 'Bob', 'Charlie']:
                yield helloworld_pb2.HelloRequest(name=name)

        response = stub.SayHelloClientStreaming(request_generator())
        print("Client Streaming RPC: " + response.message)

        # 双向流式 RPC
        def bidi_request_generator():
            for name in ['Dave', 'Eve', 'Frank']:
                yield helloworld_pb2.HelloRequest(name=name)

        print("BiDi Streaming RPC:")
        for response in stub.SayHelloBiDiStreaming(bidi_request_generator()):
            print(response.message)

if __name__ == '__main__':
    run()
