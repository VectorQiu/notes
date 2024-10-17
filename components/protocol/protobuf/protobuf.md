> [**Protocol Buffers Documentation**](https://protobuf.dev/)
>
> 

Protocol Buffers 3（简称 protobuf3）是由 Google 开发的一种语言中立、平台中立、可扩展的序列化数据格式，主要用于高效传输结构化数据。protobuf3 的目标是提供一种简洁、性能优越的数据交换机制，广泛应用于 RPC（远程过程调用）系统、数据存储、网络通信等领域。

# protobuf3 的主要特点：

1. **跨语言支持**：支持多种编程语言，包括 C++, Java, Python, Go 等。开发者可以在不同语言之间轻松交换数据。
2. **高效的序列化与反序列化**：相比于 XML 和 JSON，protobuf3 序列化后的数据更加紧凑，占用的空间更小，序列化和反序列化速度也更快。
3. **向后兼容性**：protobuf3 支持向后兼容，即你可以在不影响旧版本客户端的情况下，给数据结构添加新的字段。

## 定义消息类型

首先我们来看一个非常简单的例子。假设您想要定义一个搜索请求消息格式，其中每个搜索请求都有一个查询字符串、您感兴趣的特定结果页面以及每页的结果数量。这是`.proto`您用来定义消息类型的文件。

```protobuf
syntax = "proto3";

message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 results_per_page = 3;
}
```

- 文件的第一行指定您正在使用的`proto3`语法：如果您不这样做，协议缓冲区编译器将假定您正在使用 [proto2](https://protobuf.dev/programming-guides/proto2)。这必须是文件的第一个非空、非注释行。
- 消息`SearchRequest`定义指定了三个字段（名称/值对），每个字段对应一个要包含在此类消息中的数据。每个字段都有一个名称和一个类型。

### 指定字段类型

在前面的例子中，所有字段都是[标量类型](https://protobuf.dev/programming-guides/proto3/#scalar)：两个整数（`page_number`和`results_per_page`）和一个字符串（`query`）。您还可以像其他消息类型一样为字段指定[枚举和复合类型。](https://protobuf.dev/programming-guides/proto3/#enum)

### 分配字段编号

您必须为消息定义中的每个字段赋予一个介于和之间的数字`1`，并 `536,870,911`具有以下限制：

- 给定的数字在该消息的所有字段中**必须是唯一的。**
- 字段编号`19,000`为`19,999`Protocol Buffers 实现保留。如果您在消息中使用这些保留字段编号之一，Protocol Buffers 编译器将会报错。
- 您不能使用任何先前[保留的](https://protobuf.dev/programming-guides/proto3/#fieldreserved)字段编号或任何已分配给[扩展的](https://protobuf.dev/programming-guides/proto3/#extensions)字段编号。

**一旦您的消息类型正在使用，**此编号就无法更改，因为它会以[消息线格式](https://protobuf.dev/programming-guides/encoding)标识字段 。“更改”字段编号相当于删除该字段并创建具有相同类型但新编号的新字段。请参阅[删除字段](https://protobuf.dev/programming-guides/proto3/#deleting) 以了解如何正确执行此操作。

字段编号**绝不应重复使用**。切勿将字段编号从 [保留](https://protobuf.dev/programming-guides/proto3/#fieldreserved)列表中取出，以便用新字段定义重复使用。请参阅 [重复使用字段编号的后果](https://protobuf.dev/programming-guides/proto3/#consequences)。

您应该将字段编号 1 到 15 用于最常设置的字段。较低的字段编号值在线路格式中占用的空间较少。例如，1 到 15 范围内的字段编号需要一个字节进行编码。16 到 2047 范围内的字段编号需要两个字节。您可以在 [Protocol Buffer 编码](https://protobuf.dev/programming-guides/encoding#structure)中找到有关此内容的更多信息。

#### 重复使用字段编号的后果

重复使用字段编号会导致解码线路格式消息变得模糊不清。

protobuf 连接格式很精简，并且不提供检测使用一个定义编码并使用另一个定义解码的字段的方法。

使用一个定义对一个字段进行编码，然后使用不同的定义对同一字段进行解码可能会导致：

- 开发人员在调试上浪费的时间
- 解析/合并错误（最佳情况）
- 泄露的 PII/SPII
- 数据损坏

字段编号重用的常见原因：

- 重新编号字段（有时这样做是为了使字段的数字顺序更美观）。重新编号实际上会删除并重新添加涉及重新编号的所有字段，从而导致不兼容的线路格式更改。
- 删除一个字段并且不[保留](https://protobuf.dev/programming-guides/proto3/#fieldreserved)该号码以防止将来重复使用。

最大字段为 29 位，而不是更典型的 32 位，因为三个低位用于线路格式。有关更多信息，请参阅 [编码主题](https://protobuf.dev/programming-guides/encoding#structure)。

### 指定字段标签

消息字段可以是下列之一：

- `optional`：`optional`字段可能处于以下两种状态之一：

  - 字段已设置，且包含从线路中显式设置或解析的值。它将被序列化到线路中。
  - 字段未设置，将返回默认值。它不会被序列化到线路中。

  您可以检查该值是否已明确设置。

- `repeated`：此字段类型可以在格式良好的消息中重复零次或多次。重复值的顺序将被保留。

- `map`：这是成对的键/值字段类型。 有关此字段类型的更多信息，请参阅[Maps 。](https://protobuf.dev/programming-guides/encoding#maps)

- 如果未应用显式字段标签，则假定使用默认字段标签，即“隐式字段存在”。（您无法显式将字段设置为此状态。）格式正确的消息可以有零个或一个此字段（但不能超过一个）。您也无法确定此类型的字段是否从线路中解析。除非隐式存在字段是默认值，否则它将被序列化到线路中。有关此主题的更多信息，请参阅 [字段存在](https://protobuf.dev/programming-guides/field_presence)。

在 proto3 中，`repeated`标量数字类型的字段`packed`默认使用编码。您可以在[Protocol Buffer Encoding](https://protobuf.dev/programming-guides/encoding#packed)`packed`中找到有关编码的 更多信息。

#### 格式正确的消息

术语“格式良好”在应用于 protobuf 消息时，指的是序列化/反序列化的字节。protoc 解析器验证给定的 proto 定义文件是否可解析。

如果`optional`字段有多个值，协议解析器将接受输入，但只使用最后一个字段。因此，“字节”可能不是“格式良好的”，但生成的消息只有一个，并且是“格式良好的”（但不会往返相同）。

#### 消息类型字段具有字段存在

在 proto3 中，消息类型字段已经具有字段存在。因此，添加修饰符`optional`不会改变字段的字段存在。

`Message2`以下代码示例中的和的定义`Message3`对于所有语言都会生成相同的代码，并且在二进制、JSON 和 TextFormat 中的表示形式没有区别：

```proto
syntax="proto3";

package foo.bar;

message Message1 {}

message Message2 {
  Message1 foo = 1;
}

message Message3 {
  optional Message1 bar = 1;
}
```

### 添加更多消息类型

可以在单个`.proto`文件中定义多种消息类型。如果您要定义多个相关消息，这很有用 - 例如，如果您想要定义与您的`SearchResponse` 消息类型相对应的回复消息格式，您可以将其添加到相同的`.proto`：

```proto
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 results_per_page = 3;
}

message SearchResponse {
 ...
}
```

**合并消息会导致文件膨胀**虽然可以在单个文件中定义多种消息类型（例如消息、枚举和服务） ，但当在单个文件中定义大量具有不同依赖关系的消息时，也会导致依赖关系膨胀。建议每个文件包含尽可能`.proto`少的消息类型。`.proto`

### 添加评论

要向您的文件添加注释`.proto`，请使用 C/C++ 风格`//`和`/* ... */` 语法。

```proto
/* SearchRequest represents a search query, with pagination options to
 * indicate which results to include in the response. */

message SearchRequest {
  string query = 1;
  int32 page_number = 2;  // Which page number do we want?
  int32 results_per_page = 3;  // Number of results to return per page.
}
```

### 删除字段

如果操作不当，删除字段可能会导致严重问题。

当您不再需要某个字段并且所有引用都已从客户端代码中删除时，您可以从消息中删除该字段定义。但是，您 **必须** [保留已删除的字段编号](https://protobuf.dev/programming-guides/proto3/#fieldreserved)。如果您不保留字段编号，开发人员将来可能会重新使用该编号。

您还应该保留字段名称，以允许消息的 JSON 和 TextFormat 编码继续解析。

#### 保留字段编号

如果您通过完全删除字段或注释掉字段来 [更新消息类型，则未来的开发人员可以在对该类型进行自己的更新时重复使用字段编号。这可能会导致严重问题，如](https://protobuf.dev/programming-guides/proto3/#updating)[重复使用字段编号的后果](https://protobuf.dev/programming-guides/proto3/#consequences)中所述。为确保不会发生这种情况，请将您删除的字段编号添加到列表中`reserved`。

如果未来的开发人员尝试使用这些保留字段编号，protoc 编译器将生成错误消息。

```proto
message Foo {
  reserved 2, 15, 9 to 11;
}
```

保留字段编号范围包括（`9 to 11`与 相同`9, 10, 11`）。

#### 保留字段名称

稍后重用旧字段名称通常是安全的，除非使用 TextProto 或 JSON 编码（其中字段名称已序列化）。为了避免这种风险，您可以将已删除的字段名称添加到列表中`reserved`。

保留名称仅影响 protoc 编译器行为，而不影响运行时行为，但有一个例外：TextProto 实现可以在解析时丢弃具有保留名称的未知字段（不会像其他未知字段一样引发错误）（目前只有 C++ 和 Go 实现这样做）。运行时 JSON 解析不受保留名称的影响。

```proto
message Foo {
  reserved 2, 15, 9 to 11;
  reserved "foo", "bar";
}
```

请注意，不能在同一个`reserved` 语句中混合字段名称和字段编号

## 标量值类型

标量消息字段可以具有以下类型之一 - 表格显示了文件中指定的类型`.proto`以及自动生成的类中的对应类型：

| .proto Type | Notes                                                        | C++ Type | Java/Kotlin Type[1] | Python Type[3]                  | Go Type | Ruby Type                      | C# Type | PHP Type          | Dart Type | Rust Type   |
| ----------- | ------------------------------------------------------------ | -------- | ------------------- | ------------------------------- | ------- | ------------------------------ | ------- | ----------------- | --------- | ----------- |
| double      |                                                              | double   | double              | float                           | float64 | Float                          | double  | float             | double    | f64         |
| float       |                                                              | float    | float               | float                           | float32 | Float                          | float   | float             | double    | f32         |
| int32       | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint32 instead. | int32    | int                 | int                             | int32   | Fixnum or Bignum (as required) | int     | integer           | int       | i32         |
| int64       | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint64 instead. | int64    | long                | int/long[4]                     | int64   | Bignum                         | long    | integer/string[6] | Int64     | i64         |
| uint32      | Uses variable-length encoding.                               | uint32   | int[2]              | int/long[4]                     | uint32  | Fixnum or Bignum (as required) | uint    | integer           | int       | u32         |
| uint64      | Uses variable-length encoding.                               | uint64   | long[2]             | int/long[4]                     | uint64  | Bignum                         | ulong   | integer/string[6] | Int64     | u64         |
| sint32      | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int32s. | int32    | int                 | int                             | int32   | Fixnum or Bignum (as required) | int     | integer           | int       | i32         |
| sint64      | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int64s. | int64    | long                | int/long[4]                     | int64   | Bignum                         | long    | integer/string[6] | Int64     | i64         |
| fixed32     | Always four bytes. More efficient than uint32 if values are often greater than 228. | uint32   | int[2]              | int/long[4]                     | uint32  | Fixnum or Bignum (as required) | uint    | integer           | int       | u32         |
| fixed64     | Always eight bytes. More efficient than uint64 if values are often greater than 256. | uint64   | long[2]             | int/long[4]                     | uint64  | Bignum                         | ulong   | integer/string[6] | Int64     | u64         |
| sfixed32    | Always four bytes.                                           | int32    | int                 | int                             | int32   | Fixnum or Bignum (as required) | int     | integer           | int       | i32         |
| sfixed64    | Always eight bytes.                                          | int64    | long                | int/long[4]                     | int64   | Bignum                         | long    | integer/string[6] | Int64     | i64         |
| bool        |                                                              | bool     | boolean             | bool                            | bool    | TrueClass/FalseClass           | bool    | boolean           | bool      | bool        |
| string      | A string must always contain UTF-8 encoded or 7-bit ASCII text, and cannot be longer than 232. | string   | String              | str/unicode[5]                  | string  | String (UTF-8)                 | string  | string            | String    | ProtoString |
| bytes       | May contain any arbitrary sequence of bytes no longer than 232. | string   | ByteString          | str (Python 2) bytes (Python 3) | []byte  | String (ASCII-8BIT)            | By      |                   |           |             |

[1] Kotlin 使用 Java 中的相应类型，即使是无符号类型，以确保混合 Java/Kotlin 代码库的兼容性。

[2]在 Java 中，无符号的 32 位和 64 位整数使用它们的有符号对应项来表示，其中最高位仅存储在符号位中。

[3]在所有情况下，设置字段的值都会执行类型检查以确保其有效。

[4] 64 位或无符号 32 位整数在解码时始终表示为 long，但如果在设置字段时指定了 int，则可以为 int。在所有情况下，值都必须符合设置时所表示的类型。请参阅 [2]。

[5] Python 字符串在解码时表示为 unicode，但如果给定的是 ASCII 字符串，则可以表示为 str（这可能会发生变化）。

[6] 64 位机器上使用整数，32 位机器上使用字符串。

[您可以在协议缓冲区编码](https://protobuf.dev/programming-guides/encoding)中找到有关在序列化消息时如何编码这些类型的更多信息 。

## 默认值

解析消息时，如果编码消息不包含特定的隐式存在元素，则访问解析对象中的相应字段将返回该字段的默认值。这些默认值是特定于类型的：

- 对于字符串，默认值是空字符串。
- 对于字节，默认值是空字节。
- 对于布尔值，默认值为 false。
- 对于数字类型，默认值为零。
- 对于枚举，默认值是**第一个定义的枚举值**，必须为 0。
- 对于消息字段，该字段未设置。其确切值取决于语言。有关详细信息，请参阅 [生成的代码指南](https://protobuf.dev/reference/)。

重复字段的默认值为空（通常是相应语言中的空列表）。

请注意，对于标量消息字段，一旦解析了消息，就无法判断字段是否明确设置为默认值（例如，布尔值是否设置为）或根本没有设置：定义消息类型时应牢记这一点。例如，如果您不希望默认情况下也发生该行为，则 `false`不要使用在设置为时打开某些行为的布尔值。另请注意，如果标量消息字段**设置**为其默认值，则该值将不会在线上序列化。如果将浮点值或双精度值设置为 +0，则不会序列化，但 -0 被视为不同值并将被序列化。`false`

有关默认在生成代码中如何工作的更多详细信息，请参阅您选择的语言的[生成代码指南。](https://protobuf.dev/reference/)

## 枚举

定义消息类型时，您可能希望其中一个字段仅具有预定义值列表中的一个值。例如，假设您想`corpus`为每个添加一个字段`SearchRequest`，其中语料库可以是`UNIVERSAL`, `WEB`, `IMAGES`, `LOCAL`, `NEWS`, `PRODUCTS` or `VIDEO`。您可以通过在消息定义中添加一个`enum`，为每个可能的值添加一个常量，非常简单地做到这一点。

在以下示例中，我们添加了一个包含所有可能值的`enum`调用`Corpus`，以及一个类型为的字段：`Corpus`

```proto
enum Corpus {
  CORPUS_UNSPECIFIED = 0;
  CORPUS_UNIVERSAL = 1;
  CORPUS_WEB = 2;
  CORPUS_IMAGES = 3;
  CORPUS_LOCAL = 4;
  CORPUS_NEWS = 5;
  CORPUS_PRODUCTS = 6;
  CORPUS_VIDEO = 7;
}

message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 results_per_page = 3;
  Corpus corpus = 4;
}
```

如您所见，`Corpus`枚举的第一个常量映射到零：每个枚举定义都**必须**包含一个映射到零的常量作为其第一个元素。这是因为：

- 必须有一个零值，这样我们可以使用 0 作为数字 [默认值](https://protobuf.dev/programming-guides/proto3/#default)。
- 零值需要是第一个元素，为了与 [proto2](https://protobuf.dev/programming-guides/proto2)语义兼容，其中第一个枚举值是默认值，除非明确指定不同的值。

您可以通过将相同的值分配给不同的枚举常量来定义别名。为此，您需要将选项设置`allow_alias`为`true`。否则，当发现别名时，协议缓冲区编译器会生成警告消息。虽然所有别名值在反序列化期间都是有效的，但序列化时始终使用第一个值。

```proto
enum EnumAllowingAlias {
  option allow_alias = true;
  EAA_UNSPECIFIED = 0;
  EAA_STARTED = 1;
  EAA_RUNNING = 1;
  EAA_FINISHED = 2;
}

enum EnumNotAllowingAlias {
  ENAA_UNSPECIFIED = 0;
  ENAA_STARTED = 1;
  // ENAA_RUNNING = 1;  // Uncommenting this line will cause a warning message.
  ENAA_FINISHED = 2;
}
```

枚举器常量必须在 32 位整数范围内。由于`enum` 值在传输过程中使用 [varint 编码](https://protobuf.dev/programming-guides/encoding)，因此负值效率低下，因此不推荐使用。您可以 `enum`在消息定义中定义 s（如前面的示例所示），也可以在消息定义之外定义 s — 这些`enum`s 可以在`.proto`文件中的任何消息定义中重复使用。您还可以使用`enum`语法 ，将一条消息中声明的类型用作另一条消息中字段的类型`_MessageType_._EnumType_`。

`.proto`当您在使用的上运行协议缓冲区编译器时`enum`，生成的代码将具有`enum`与 Java、Kotlin 或 C++ 对应的代码，或与`EnumDescriptor`Python 对应的特殊类，该类用于在运行时生成的类中创建一组具有整数值的符号常量。

> #### 重要的
>
> 生成的代码可能会受到特定语言的枚举器数量的限制（一种语言的枚举器数量低于数千个）。请查看您计划使用的语言的限制。

在反序列化过程中，无法识别的枚举值将保留在消息中，但在反序列化消息时如何表示这些值取决于语言。在支持开放枚举类型（其值超出指定符号范围）的语言（如 C++ 和 Go）中，未知枚举值仅存储为其底层整数表示形式。在具有封闭枚举类型的语言（如 Java）中，枚举中的案例用于表示无法识别的值，并且可以使用特殊访问器访问底层整数。在任一情况下，如果消息被序列化，则无法识别的值仍将与消息一起序列化。

> #### 重要的
>
> 有关枚举应如何工作（与当前不同语言中的工作方式相比）的信息，请参阅 [枚举行为](https://protobuf.dev/programming-guides/enum)。
>
> `enum`有关如何在应用程序中处理消息的更多信息，请参阅 您选择的语言的[生成代码指南。](https://protobuf.dev/reference/)

### 保留值

如果通过完全删除或注释掉某个枚举条目来[更新](https://protobuf.dev/programming-guides/proto3/#updating)`.proto`枚举类型，则未来的用户在对该类型进行自己的更新时可以重用该数值。 如果他们以后加载相同的旧版本，这可能会导致严重问题，包括数据损坏、隐私错误等。 确保不会发生这种情况的一种方法是指定已删除条目的数值（和/或名称，这也可能导致 JSON 序列化问题）为`reserved`。 如果任何未来的用户尝试使用这些标识符，协议缓冲区编译器将会抱怨。 您可以使用关键字指定保留的数值范围达到最大可能值 `max`。

```proto
enum Foo {
  reserved 2, 15, 9 to 11, 40 to max;
  reserved "FOO", "BAR";
}
```

请注意，不能在同一个`reserved` 语句中混合字段名称和数值

## 使用其他消息类型

您可以使用其他消息类型作为字段类型。例如，假设您想`Result`在每条消息中包含消息`SearchResponse`- 为此，您可以`Result`在其中定义一个消息类型，然后在`SearchResponse`中`.proto`指定类型的字段：`Result`

```proto
message SearchResponse {
  repeated Result results = 1;
}

message Result {
  string url = 1;
  string title = 2;
  repeated string snippets = 3;
}
```

### 导入定义[ ](https://protobuf.dev/programming-guides/proto3/#importing)

在前面的例子中，`Result`消息类型在同一个文件中定义 `SearchResponse`——如果您想用作字段类型的消息类型已经在另一个`.proto`文件中定义，该怎么办？

您可以`.proto`通过*导入来*使用其他文件的定义。要导入另一个文件`.proto`的定义，请在文件顶部添加导入语句：

```proto
import "myproject/other_protos.proto";
```

默认情况下，您只能使用直接导入`.proto`文件中的定义。但是，有时您可能需要将文件移动到新位置。您可以将占位符文件放在旧位置，以便使用 notion 将所有导入转发到新位置，`.proto`而不是`.proto`直接移动文件并在一次更改中更新所有调用站点。`.proto``import public`

**请注意，公共导入功能在 Java、Kotlin、TypeScript、JavaScript、GCL 以及使用 protobuf 静态反射的 C++ 目标中不可用。**

`import public`任何导入包含该语句的 proto 的代码都可以传递依赖`import public`。例如：

```proto
// new.proto
// All definitions are moved here
// old.proto
// This is the proto that all clients are importing.
import public "new.proto";
import "other.proto";
// client.proto
import "old.proto";
// You use definitions from old.proto and new.proto, but not other.proto
```

`-I`协议编译器使用/标志在协议编译器命令行上指定的一组目录中搜索导入的文件`--proto_path` 。如果没有指定标志，它会在调用编译器的目录中查找。通常，您应该将标志设置`--proto_path`为项目的根目录，并对所有导入使用完全限定名称。

### 使用 proto2 消息类型

可以导入 [proto2](https://protobuf.dev/programming-guides/proto2)消息类型并在 proto3 消息中使用它们，反之亦然。但是，proto2 枚举不能直接在 proto3 语法中使用（如果导入的 proto2 消息使用它们则没问题）。

## 嵌套类型

您可以在其他消息类型中定义和使用消息类型，如下例所示 - 这里的`Result`消息是在 `SearchResponse`消息内部定义的：

```proto
message SearchResponse {
  message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
  }
  repeated Result results = 1;
}
```

如果要在它的父消息类型之外重用此消息类型，可以这样引用它`_Parent_._Type_`：

```proto
message SomeOtherMessage {
  SearchResponse.Result result = 1;
}
```

您可以根据需要嵌套任意深度的消息。在下面的示例中，请注意，命名的两个嵌套类型`Inner`完全独立，因为它们是在不同的消息中定义的：

```proto
message Outer {       // Level 0
  message MiddleAA {  // Level 1
    message Inner {   // Level 2
      int64 ival = 1;
      bool  booly = 2;
    }
  }
  message MiddleBB {  // Level 1
    message Inner {   // Level 2
      int32 ival = 1;
      bool  booly = 2;
    }
  }
}
```





## 命名规则

为了便于阅读，protobuf 规定了一系列命名法：

- message、enum 采用大驼峰命名法，如 message StudentInfo 。
- 字段采用下划线分割法，且全部小写，如 string student_name 。
- 枚举值采用下划线分割法，且全部大写，如 FIRST_VALUE 。



# Python使用示例 

在 Windows 上使用 Python 操作 protobuf3，可以按照以下步骤进行安装和使用示例。

## 1. 安装 Protocol Buffers

首先需要安装 Protocol Buffers 的编译器 `protoc` 和 Python 的 `protobuf` 包。

### 安装 `protoc` 编译器：

1. 访问 [Protocol Buffers Releases](https://github.com/protocolbuffers/protobuf/releases) 页面。
2. 下载最新版本的 `protoc` 预编译二进制文件，选择适用于 Windows 的 zip 包，例如 `protoc-XX.X.X-win64.zip`。
3. 解压该 zip 包，将其中的 `bin` 目录添加到系统的 PATH 环境变量中，确保 `protoc` 命令可以在命令提示符下运行。

### 安装 Python 的 `protobuf` 包：

打开命令提示符，运行以下命令安装 Python 的 protobuf 库：

```bash
pip install protobuf
```

## 2. 创建 `.proto` 文件

创建一个简单的 `.proto` 文件来定义消息格式。例如，创建一个名为 `addressbook.proto` 的文件，内容如下：

```proto
syntax = "proto3";

message Person {
    string name = 1;
    int32 id = 2;
    string email = 3;
}

message AddressBook {
    repeated Person people = 1;
}
```

## 3. 使用 `protoc` 编译 `.proto` 文件

在命令提示符下，进入 `.proto` 文件所在的目录，运行以下命令生成 Python 代码：

```bash
protoc --python_out=. addressbook.proto
```

这会在当前目录下生成一个 `addressbook_pb2.py` 文件。

## 4. 编写 Python 代码进行序列化和反序列化

创建一个 Python 脚本文件，例如 `main.py`，并编写如下代码：

```python
import addressbook_pb2

# 创建一个 Person 对象
person = addressbook_pb2.Person()
person.name = "John Doe"
person.id = 1234
person.email = "johndoe@example.com"

# 将 Person 对象添加到 AddressBook
address_book = addressbook_pb2.AddressBook()
address_book.people.append(person)

# 序列化到二进制格式
with open("addressbook.bin", "wb") as f:
    f.write(address_book.SerializeToString())

# 从二进制文件反序列化
address_book_read = addressbook_pb2.AddressBook()
with open("addressbook.bin", "rb") as f:
    address_book_read.ParseFromString(f.read())

# 打印读取的数据
for person in address_book_read.people:
    print(f"Name: {person.name}, ID: {person.id}, Email: {person.email}")
```

## 5. 运行 Python 脚本

在命令提示符下运行以下命令执行脚本：

```bash
python main.py
```

这将生成一个 `addressbook.bin` 文件，并从中读取数据并打印出来。

## 总结

1. 安装 `protoc` 编译器和 Python 的 `protobuf` 库。
2. 创建 `.proto` 文件并使用 `protoc` 编译生成 Python 代码。
3. 编写 Python 脚本来序列化和反序列化 protobuf 消息。
4. 在 Windows 下运行 Python 脚本进行测试。

# C++使用示例

## 1. 安装 Protocol Buffers 编译器和库

### 安装 `protoc` 编译器：

1. 下载 `protoc`:
   - 访问 [Protocol Buffers Releases](https://github.com/protocolbuffers/protobuf/releases) 页面。
   - 下载最新的 `protoc-XX.X.X-win64.zip`（选择适合您的系统版本）。
2. 解压并配置环境:
   - 将下载的 zip 文件解压到一个方便的位置，例如 `C:\Program Files\protoc\`。
   - 将解压目录中的 `bin` 文件夹路径添加到系统的 PATH 环境变量中，以便全局访问 `protoc` 命令。

### 安装 Protocol Buffers C++ 库：

1. **安装 Visual Studio**:

   - 如果尚未安装 Visual Studio，请从 [Visual Studio 官方网站](https://visualstudio.microsoft.com/) 下载并安装 Visual Studio 2019 或更新版本，确保选择“使用 C++ 的桌面开发”工作负载。

2. **构建 Protocol Buffers C++ 库**:

   - 从 GitHub克隆 Protocol Buffers 的源码库：

     ```bash
     git clone https://github.com/protocolbuffers/protobuf.git
     cd protobuf
     git submodule update --init --recursive
     ```

   - 生成 Visual Studio 项目文件：

     ```bash
     mkdir cmake_build
     cd cmake_build
     cmake -G "Visual Studio 16 2019" -A x64 ..
     cmake -G "Visual Studio 17 2022" -A x64 ..
     ```

   - 配置完成后，CMake 会生成一个 `protobuf.sln` 文件。你可以通过以下步骤打开和构建这个解决方案：

     1. **打开解决方案**：
        - 在命令行中输入 `explorer .` 打开当前目录的文件资源管理器，找到 `protobuf.sln` 文件。
        - 双击 `protobuf.sln` 文件，Visual Studio 2022 会自动打开这个解决方案。
     2. **选择生成配置**：
        - 在 Visual Studio 中，选择 `Release` 或 `Debug` 作为生成配置（通常选择 `Release` 以便生成优化后的库）。
     3. **生成解决方案**：
        - 在菜单栏中，点击 `生成` > `生成解决方案`。
        - Visual Studio 会开始编译项目，生成所需的库文件和 `protoc` 编译器。

     #### 4. 查找生成的文件

     构建完成后，你可以在解决方案的输出目录中找到生成的库文件和 `protoc` 编译器。这些文件通常位于以下路径：

     ```
     protobuf/cmake/build/Release/
     ```

     其中 `Release` 是你选择的生成配置，可能会有所不同。

## 2.proto文件

```proto
// import语句引入其他protobuf文件
// import "other_portos.porto";

// 指定protobuf遵循的语法格式
syntax = "proto3";

// 包名声明 proto文件生成的类都会在此namespace student中，防止命名冲突
package student;


enum Sex // 自定义枚举类型
{
    MALE = 0;
    FEMALE = 1;
}

message Course // message定义数据结构
{
    int32 credit = 1;
    string name = 2;
}

message StudentInfo {
    // 变量声明格式 <限定修饰符> <数据类型> <变量名> = id;
    int32 age = 1;
    string name = 2;
    Sex sex = 3;
    // repeated 表示重复(数组), message可嵌套message
    repeated Course course = 4;
}
```

## 3. 使用 `protoc` 编译 `.proto` 文件

在命令提示符下，进入 `.proto` 文件所在的目录，运行以下命令生成 Python 代码：

```bash
protoc student.proto --cpp_out=.
```

在当前目录下生成.cpp文件和.h文件 

## 4.编写 CPP代码进行序列化和反序列化

```cpp
#include <google/protobuf/message.h>  // for protobuf

#include <fstream>
#include <iostream>
#include <vector>

#include "Example.pb.h"  // for protobuf source file
int main() {
    // 可以看到，protobuf文件中的信息都被封装在namespace
    // student中，这是之前protobuf中的`package`语法所规定的。
    // 1. 如何实例化一个proto文件中定义的类
    student::StudentInfo student1;
    // 2. 如何设置类的各个属性
    // a. 添加单一字段：使用set_<xxx>()语句
    student1.set_age(18);
    student1.set_name("Alice");
    student1.set_sex(student::Sex::FEMALE);
    // b. 添加repeated字段：使用add_<xxx>()语句
    student::Course *course1 = student1.add_courses();
    course1->set_name("calculus");
    course1->set_credit(5);
    student::Course *course2 = student1.add_courses();
    course2->set_name("Fundamentals of Electronic Circuits and System");
    course2->set_credit(2);
    // 3. 如何使用类的各个属性：使用<xxx>()语句
    std::cout << "----------------student info----------------" << std::endl
              << "age: " << student1.age() << std::endl
              << "name: " << student1.name() << std::endl
              << "sex (0:male, 1:female): " << (int)student1.sex() << std::endl
              << "courses: " << std::endl;
    for (int i = 0; i < student1.courses_size(); i++) {
        std::cout << " " << i << ". "
                  << "name: " << student1.courses(i).name() << " "
                  << "credit: " << student1.courses(i).credit() << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    // 4. 序列化
    std::cout << "serialize to file." << std::endl;
    std::fstream output("./output", std::ios::out | std::ios::binary);
    student1.SerializeToOstream(&output);  // 序列化为流
    output.close();
    std::cout << "serialize to array." << std::endl;
    size_t size = student1.ByteSizeLong();
    unsigned char *data = new unsigned char[size];
    student1.SerializeToArray(data, student1.ByteSizeLong());  // 序列化为数组
    // 5. 反序列化和debug
    std::cout << "deserialize from array." << std::endl;
    student::StudentInfo studentInfoFromArray;
    std::cout << std::endl;
    studentInfoFromArray.ParseFromArray(data, size);
    std::cout << studentInfoFromArray.DebugString()
              << std::endl;  // 输出字符串化的信息
    // 此处有大坑：需要开着 -pthread，否则会报错
}
```

## 5. 配置 Visual Studio 项目

1. **创建一个新的 C++ 项目**：在 Visual Studio 中创建一个新的控制台应用程序。
2. **添加生成的 `.h` 和 `.cc` 文件**：将 `addressbook.pb.h` 和 `addressbook.pb.cc` 添加到项目中。
3. 配置包含目录和库目录：
   - 在项目属性中，添加 Protocol Buffers 头文件的路径（`include` 文件夹）。
   - 添加 Protocol Buffers 库文件的路径（`libprotobuf.lib`）。
4. **编译项目**：确保项目可以正常编译并运行。

## 6. 运行程序

编译并运行项目后，程序将提示输入 `Person` 对象的信息，输入后会将数据序列化到 `addressbook.bin` 文件中，然后从该文件读取并打印出来。

## 总结

1. 安装并配置 `protoc` 编译器和 C++ 库。
2. 编写 `.proto` 文件并生成相应的 C++ 代码。
3. 在 Visual Studio 中编写 C++ 程序，使用 Protocol Buffers 进行序列化和反序列化操作。
4. 运行并测试程序的功能。

这样，您就可以在 Windows 上使用 Protocol Buffers 和 C++ 进行数据序列化和反序列化操作