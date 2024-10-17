> [libemqtt github](https://github.com/fcvarela/liblwmqtt)
>
> [liblwmqtt](https://code.google.com/archive/p/liblwmqtt/)

`libemqtt` 是一个轻量级的 MQTT 客户端库，用于嵌入式设备和资源受限的系统。根据 `libemqtt` 的文档和常见使用情况，它主要支持 **MQTT v3.1** 协议。

### 具体说明

- **MQTT 版本支持**: `libemqtt` 主要支持 MQTT v3.1 协议。这意味着它适用于基于 MQTT v3.1 标准的通信需求。如果你需要支持 MQTT v3.1.1 或更高版本，可能需要做一些手动修改或使用其他支持更新协议版本的库。
- **功能特点**:
  - 轻量级设计，适合嵌入式系统。
  - 支持基本的 MQTT 功能，如连接、订阅、发布和保持连接等。
  - 使用 C 语言编写，易于集成到嵌入式项目中。

### 如果需要支持 MQTT v3.1.1 或更高版本：

- **代码修改**: 虽然 `libemqtt` 支持 v3.1，但你可以通过调整 `CONNECT` 报文中的协议版本号和相关标志来尝试支持 v3.1.1，但这可能需要一些对 MQTT 协议的深刻理解和代码修改。
- **其他库选项**: 如果你需要一个更全面支持 MQTT v3.1.1 或更高版本的库，可以考虑使用其他 MQTT 客户端库，如 Paho MQTT、[mosquitto](https://mosquitto.org/) 等，它们支持更新的协议版本和更丰富的功能。

### 总结

`libemqtt` 支持的是 MQTT v3.1 版本。如果你的项目需要支持 MQTT v3.1.1 或更高版本，建议考虑修改代码或选择其他支持更新协议版本的 MQTT 客户端库。

MQTT v3.1 和 v3.1.1 是两个不同版本的 MQTT 协议，虽然它们在核心功能上非常相似，但 v3.1.1 引入了一些改进和修正。以下是它们之间的主要区别：