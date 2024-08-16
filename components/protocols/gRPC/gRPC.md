> [gRPC](https://grpc.io/)

### gRPC

gRPC（**g**oogle **R**emote **P**rocedure **C**all）是一个高性能、通用的开源远程过程调用 (RPC) 框架，由 Google 开发。它允许客户端和服务器之间的通信，并且支持多种编程语言。gRPC 基于 HTTP/2 协议，可以使用 Protocol Buffers (protobuf) 作为接口定义语言 (IDL) 和序列化格式。

#### gRPC 的关键特性：

1. **多语言支持**：gRPC 支持多种编程语言，包括 C++, Java, Python, Go, Ruby, C#, Node.js 等。
2. **高性能**：gRPC 使用 HTTP/2 协议，这使得它能够实现高效的双向流、多路复用连接、头部压缩等特性，减少了带宽的消耗和延迟。
3. **流式通信**：gRPC 支持客户端流、服务器流和双向流式 RPC，这使得在复杂场景中灵活实现数据流传输。
4. **代码生成**：gRPC 使用 Protocol Buffers 作为其接口定义语言，开发者可以通过定义 `.proto` 文件，自动生成客户端和服务器端代码，大大减少手动编码的工作量。

### gRPC定义

```protobuf
syntax = "proto3";
package hello;
// The greeter service definition.
service Greeter {
	// Sends a greeting
	rpc SayHello (HelloRequest) returns (HelloReply);
	rpc LotsOfReplies(HelloRequest) returns (stream HelloReply);
	rpc LotsOfGreetings(stream HelloRequest) returns (HelloReply);
} 

// The request message containing the user's name.
message HelloRequest {
	string name = 1;
}

// The response message containing the greetings
message HelloReply {
	string reply = 1;
}
```

使用了 service 和 rpc 关键字。 service 关键字后是具体的 RPC 内容， rpc 关键字定义的服务就类似于一般编程语言的函数，客户端向服务端发送 request ，服务端接收到后处理，并返回 response ，客户端接收。  

```
rpc FunctionName (request) returns (response)
```

除去单一 RPC 外，gRPC 还支持流式 RPC，使用 stream 关键字即可。这允许服务器和客户端在双方连接不中断的情况下发送多个消息。

例如，在游戏中，服务端经常要连续给客户端发送游戏当前的信息，而客户端经常要连续给服务端发送自己的操作，这时就比较适合流式服务

### gRPC 的基本工作流程

1. **定义服务**：在 `.proto` 文件中定义服务及其方法，以及消息的结构。
2. **生成代码**：使用 `protoc` 工具根据 `.proto` 文件生成客户端和服务器端的代码。
3. **实现服务**：在服务器端实现定义的服务逻辑。
4. **调用服务**：在客户端调用生成的存根（stub）进行远程调用。

### gRPC 的使用示例

#### 1. 安装所需工具

首先，确保你已经安装了 `grpcio` 和 `grpcio-tools`：

```bash
pip install grpcio grpcio-tools
```

#### 2. 定义 `.proto` 文件

创建一个简单的 `.proto` 文件，比如 `helloworld.proto`，内容如下：

```proto
syntax = "proto3";

package helloworld;

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}

service Greeter {
  // 简单 RPC
  rpc SayHello (HelloRequest) returns (HelloReply);

  // 服务器端流式 RPC
  rpc SayHelloServerStreaming (HelloRequest) returns (stream HelloReply);

  // 客户端流式 RPC
  rpc SayHelloClientStreaming (stream HelloRequest) returns (HelloReply);

  // 双向流式 RPC
  rpc SayHelloBiDiStreaming (stream HelloRequest) returns (stream HelloReply);
}

```

##### 关键点：

- **package**：指定包名，通常与代码生成的命名空间对应。

- **message**：定义消息类型，`HelloRequest` 和 `HelloReply` 是在 RPC 中传递的消息类型。

- service：定义服务接口，

  ```
  Greeter
  ```

   是我们定义的服务，里面包含四种 RPC 方法。

  - `SayHello` 是一个简单的 RPC，发送一个请求，接收一个响应。
  - `SayHelloServerStreaming` 是一个服务器端流式 RPC，客户端发送一个请求，服务器返回一个消息流。
  - `SayHelloClientStreaming` 是一个客户端流式 RPC，客户端发送一个消息流，服务器返回一个响应。
  - `SayHelloBiDiStreaming` 是一个双向流式 RPC，客户端和服务器可以同时发送和接收多个消息。

#### 3. 生成代码

使用 `grpc_tools.protoc` 工具生成 Python 代码：

```bash
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. helloworld.proto
```

这将生成两个文件：`helloworld_pb2.py` 和 `helloworld_pb2_grpc.py`。

#### 4. 实现服务器

创建一个 Python 文件 `server.py`，实现服务逻辑：

```python
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


```

##### 服务器端代码解析

```python
class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, context):
        return helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)
```

##### `SayHello` 方法

- **输入**：`HelloRequest` 对象。
- **输出**：`HelloReply` 对象。
- **解释**：这是一个简单的 RPC，服务器接收 `HelloRequest` 并返回一个 `HelloReply`。此方法没有流式处理，处理的是单个请求和响应。

```python
def SayHelloServerStreaming(self, request, context):
        for i in range(5):
            yield helloworld_pb2.HelloReply(message='Hello, %s! Number %d' % (request.name, i + 1))
```

##### `SayHelloServerStreaming` 方法

- **输入**：`HelloRequest` 对象。
- **输出**：`HelloReply` 对象流。
- **解释**：这是一个服务器端流式 RPC。服务器接收 `HelloRequest`，并返回一个消息流。`yield` 关键字用于生成流中的每个 `HelloReply`。在客户端接收完所有流消息之前，连接会保持打开状态。

```python
def SayHelloClientStreaming(self, request_iterator, context):
        names = []
        for request in request_iterator:
            names.append(request.name)
        return helloworld_pb2.HelloReply(message='Hello, %s!' % ', '.join(names))
```

##### `SayHelloClientStreaming` 方法

- **输入**：`HelloRequest` 对象流。
- **输出**：`HelloReply` 对象。
- **解释**：这是一个客户端流式 RPC。服务器接收一个包含多个 `HelloRequest` 消息的流，然后在处理完所有消息后，返回一个 `HelloReply` 响应。`request_iterator` 是一个迭代器，用于遍历客户端发送的流。

```python
def SayHelloBiDiStreaming(self, request_iterator, context):
        for request in request_iterator:
            yield helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)
```

##### `SayHelloBiDiStreaming` 方法

- **输入**：`HelloRequest` 对象流。
- **输出**：`HelloReply` 对象流。
- **解释**：这是一个双向流式 RPC。客户端和服务器都可以同时发送和接收消息流。服务器使用 `request_iterator` 接收来自客户端的流，并使用 `yield` 将响应消息流发送回客户端。每个请求对应一个响应。

#### 5. 实现客户端

创建一个 Python 文件 `client.py`，调用远程服务：

```python
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

```

#####  客户端代码解析

```python
def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        # 简单 RPC
        response = stub.SayHello(helloworld_pb2.HelloRequest(name='World'))
        print("Simple RPC: " + response.message)
```

##### 简单 RPC 调用

- **步骤**：创建一个 gRPC 渠道连接到服务器，然后使用存根（`stub`）调用 `SayHello` 方法。结果会打印到控制台。
- **解释**：这是一个标准的单向 RPC 调用，客户端发送一个请求并接收一个响应。

```python
        # 服务器端流式 RPC
        print("Server Streaming RPC:")
        for response in stub.SayHelloServerStreaming(helloworld_pb2.HelloRequest(name='World')):
            print(response.message)
```

##### 服务器端流式 RPC 调用

- **步骤**：客户端发送一个请求，并通过迭代接收服务器返回的消息流。
- **解释**：每次 `for` 循环迭代，客户端会接收服务器返回的一个 `HelloReply`，直到流结束。

```python
        # 客户端流式 RPC
        def request_generator():
            for name in ['Alice', 'Bob', 'Charlie']:
                yield helloworld_pb2.HelloRequest(name=name)

        response = stub.SayHelloClientStreaming(request_generator())
        print("Client Streaming RPC: " + response.message)

```

##### 客户端流式 RPC 调用

- **步骤**：客户端通过 `request_generator` 生成一个消息流，然后将该流发送到服务器。服务器接收完所有请求后，返回一个响应。
- **解释**：客户端流式 RPC 允许客户端发送多个请求，然后接收一个最终响应。

```python
        # 双向流式 RPC
        def bidi_request_generator():
            for name in ['Dave', 'Eve', 'Frank']:
                yield helloworld_pb2.HelloRequest(name=name)

        print("BiDi Streaming RPC:")
        for response in stub.SayHelloBiDiStreaming(bidi_request_generator()):
            print(response.message)
```

##### 双向流式 RPC 调用

- **步骤**：客户端通过 `bidi_request_generator` 生成一个消息流，并同时接收服务器发送的响应流。
- **解释**：双向流式 RPC 允许客户端和服务器在同一个连接上同时发送和接收多个消息。这种模式特别适合实时双向通信。



#### 6. 运行服务器和客户端

1. 启动服务器：

   ```bash
   python server.py
   ```

2. 在另一个终端窗口中启动客户端：

   ```bash
   python client.py
   ```

客户端将输出 `Greeter client received: Hello, World!`，表示 gRPC 调用成功。

### 总结

gRPC 是一个功能强大且高效的 RPC 框架，适用于需要高性能、低延迟的服务通信场景。通过使用 Protocol Buffers 进行消息定义和序列化，它提供了跨语言的支持和易于扩展的服务接口。