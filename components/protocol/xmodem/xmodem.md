> [ymodem](https://pauillac.inria.fr/~doligez/zmodem/ymodem.txt)
>
> [zmodem](https://pauillac.inria.fr/~doligez/zmodem/zmodem.txt)
>
> [wiki xmodem](https://en.wikipedia.org/wiki/XMODEM)

modem、Ymodem 和 Zmodem 是三种经典的文件传输协议，它们在串行通信和远程文件传输中广泛使用。以下是对这三种协议的详细介绍和协议细节。

## **1. Xmodem 协议**

Xmodem 是由 Ward Christensen 于 1977 年开发的早期文件传输协议之一。它设计简单、可靠，但在效率和错误恢复方面存在局限性。

### Xmodem**协议细节**

**控制字符**

| 控制字符 | 值       | 说明                                        |
| -------- | -------- | ------------------------------------------- |
| SOH      | 0x01     | Xmodem数据头                                |
| STX      | 0x02     | 1K-Xmodem数据头                             |
| EOT      | 0x04     | 发送结束                                    |
| ACK      | 0x06     | 应答                                        |
| NAK      | 0x15     | 非应答                                      |
| ETB      | 0x17     | 数据块结束 （多文件传输，消息或日志的传输） |
| CAN      | 0x18     | 终止发送                                    |
| CTRL-Z   | 0x1A     | 填充数据包                                  |
| 'C'      | 0x43 'C' | CRC校验方式数据头                           |

对于标准Xmodem协议来说，如果传送的文件不是128的整数倍，那么最后一个数据包的有效内容肯定小于帧长，不足的部分需要用CTRL-Z(0x1A)来填充。

- **数据包格式**：
  - `SOH (1 字节)`：报头开始标志，表示数据包的开始。
  - `块编号 (1 字节)`：数据包的编号，从 1 到 255。
  - `块编号补码 (1 字节)`：块编号的补码，用于校验。
  - `数据 (128 字节)`：固定长度的 128 字节数据段。
  - `校验和 (1 字节)`：对数据段的所有字节进行 8 位累加得到的校验和。
- **数据传输流程**：
  1. **握手**：接收方发送 `NAK`，表示准备接收数据。
  2. **数据包传输**：发送方发送一个包含 128 字节数据的数据包。
  3. **数据包确认**：接收方校验数据包后，返回 `ACK`（确认）或 `NAK`（否认）。
  4. **传输完成**：所有数据包传输完毕后，发送方发送 `EOT`（传输结束）信号，接收方确认后传输结束。

### Xmodem-Check Sum

**帧格式**	

| Byte1       | Byte2  | Byte3      | Byte4~131 | Byte132             |
| ----------- | ------ | ---------- | --------- | ------------------- |
| 数据头`SOH` | 序列号 | 序列号补码 | 128位数据 | Byte4~131 Check Sum |

```
------------------------------------------------------------------------------
|               SENDER                |          |          RECIEVER         |
|                                     |  <---    |  NAK                      |
|                                     |          |  Time out after 3 second  |
|                                     |  <---    |  NAK                      |
| SOH|0x01|0xFE|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CheckSum| |  --->    |                           |
|                                     |  <---    |  ACK                      |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
| .                                   |          |  .                        |
|                                     |  <---    |  ACK                      |
| EOT                                 |  --->    |                           |
|                                     |  <---    |  ACK                      |
------------------------------------------------------------------------------
```

### Xmodem-CRC16

**帧格式**	

| Byte1       | Byte2  | Byte3      | Byte4~131 | Byte132~133           |
| ----------- | ------ | ---------- | --------- | --------------------- |
| 数据头`SOH` | 序列号 | 序列号补码 | 128位数据 | Byte4~131 CRC16校验码 |

```
---------------------------------------------------------------------------
|               SENDER             |          |           RECIEVER        |
|                                  |  <---    |  'C'                      |
|                                  |          |  Time out after 3 second  |
|                                  |  <---    |  'C'                      |
| SOH|0x01|0xFE|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| SOH|0x02|0xFD|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  NAK                      |
| SOH|0x02|0xFD|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| SOH|0x03|0xFC|Data[0~127]|CRC16| |  --->    |                           |
|                                  |  <---    |  ACK                      |
| .                                |          |  .                        |
| .                                |          |  .                        |
| .                                |          |  .                        |
|                                  |  <---    |  ACK                      |
| EOT                              |  --->    |                           |
|                                  |  <---    |  ACK                      |
---------------------------------------------------------------------------
```



## **2. Ymodem 协议**

Ymodem 是 Xmodem 协议的改进版，由 Chuck Forsberg 开发，目的是解决 Xmodem 协议的局限性，特别是在文件传输效率和多文件传输方面。Ymodem 采用了更大的数据包，支持批量文件传输，并提供了更强的错误处理机制。以下是 Ymodem 协议的详细介绍。

Ymodem 基于 Xmodem，但引入了几个重要的改进：

- **支持 1024 字节的数据包**：相比 Xmodem 的 128 字节，Ymodem 支持更大的数据包，从而提高了传输效率。
- **文件头传输**：Ymodem 支持文件头信息的传输，包括文件名、文件大小等元数据。
- **多文件传输**：Ymodem 允许一次传输多个文件，这对于批量传输非常有用。
- **增强的错误处理**：通过 CRC 校验，Ymodem 提供了更可靠的错误检测能力。

### **Ymodem 协议的详细结构**

#### **数据包格式**

- **文件头包**：
  - `SOH (1 Byte)`：表示 128 字节数据包的开始（或 `STX (1 Byte)` 表示 1024 字节数据包的开始）。
  - `块编号 (1 Byte)`：文件头包的块编号通常为 `0`。
  - `块编号补码 (1 Byte)`：块编号的补码。
  - `文件名和文件大小信息 (128 Bytes)`：包含文件名、文件大小和其他元数据。
  - `CRC 或校验和 (2 Bytes)`：文件头的校验和或 CRC。
- **数据包**：
  - `SOH 或 STX (1 Byte)`：`SOH` 表示 128 字节数据包，`STX` 表示 1024 字节数据包。
  - `块编号 (1 Byte)`：数据包的编号，从 `1` 开始递增。
  - `块编号补码 (1 Byte)`：块编号的补码。
  - `数据字段 (128 或 1024 Bytes)`：实际传输的数据，长度为 128 或 1024 字节。
  - `CRC 或校验和 (2 Bytes)`：对数据字段的 CRC 或校验和。
- **结束包**：
  - 文件传输完成后，发送一个空数据包（只有 `EOT` 字符）表示传输结束。

#### **文件头包内容**

文件头包包含以下内容（假设是 128 字节的文件头包）：

- 文件名和扩展名：例如 `example.txt`。
- 文件大小：以 ASCII 码形式表示的文件大小（字节数）。
- 文件的时间戳信息：包括创建日期和时间。
- 其他元数据：例如文件权限或类型。

这些信息填充到 128 字节的文件头包中，未使用的字节填充为 `0x00`。

------

### Ymodem 数据传输过程**

1. **握手**：
   - 接收方准备接收数据，发送 `NAK` 信号给发送方，表示准备好接收。
2. **文件头传输**：
   - 发送方首先发送一个包含文件头信息的数据包（块编号为 `0`）。
   - 接收方接收到文件头后，检查 CRC 或校验和，并返回 `ACK` 表示确认接收。
3. **数据传输**：
   - 发送方按顺序发送数据包，块编号从 `1` 开始递增。
   - 接收方逐个接收数据包，并对数据进行 CRC 校验。如果校验成功，返回 `ACK`，否则返回 `NAK` 请求重传。
4. **文件传输完成**：
   - 当所有数据包传输完毕后，发送方发送 `EOT` 信号表示传输结束。
   - 接收方收到 `EOT` 后，返回 `ACK` 以确认整个文件传输完成。
5. **多文件传输**：
   - 如果有多个文件需要传输，发送方会在完成一个文件传输后，继续发送下一个文件的文件头包。
   - 当所有文件都传输完毕后，发送方发送一个空的文件头包（只有文件名为空的包）来标识传输的结束。

**起始帧**

| Byte1       | Byte2      | Byte3          | Byte4~131                    | Byte132~133          |
| ----------- | ---------- | -------------- | ---------------------------- | -------------------- |
| 数据头`SOH` | 序列号(00) | 序列号补码(FF) | filename+" "+filesize+" "NUL | Byte4~131CRC16校验码 |

**数据帧**

| Byte1       | Byte2  | Byte3      | Byte4~131 | Byte132~133           |
| ----------- | ------ | ---------- | --------- | --------------------- |
| 数据头`SOH` | 序列号 | 序列号补码 | 128位数据 | Byte4~131 CRC16校验码 |

| Byte1       | Byte2  | Byte3      | Byte4~1027 | Byte1028~1029          |
| ----------- | ------ | ---------- | ---------- | ---------------------- |
| 数据头`STX` | 序列号 | 序列号补码 | 1024位数据 | Byte4~1027 CRC16校验码 |

**结束帧**

| Byte1       | Byte2      | Byte3          | Byte4~131 | Byte132~133          |
| ----------- | ---------- | -------------- | --------- | -------------------- |
| 数据头`SOH` | 序列号(00) | 序列号补码(FF) | 128位NUL  | Byte4~131CRC16校验码 |

YMODEM Batch Transmission Session

```
SENDER                                  RECEIVER
                                       "sb foo.*<CR>"
"sending in batch mode etc."
                                        C (command:rb)
SOH 00 FF foo.c NUL[123] CRC CRC
                                        ACK
                                        C
SOH 01 FE Data[128] CRC CRC
                                        ACK
SOH 02 FC Data[128] CRC CRC
                                        ACK
SOH 03 FB Data[100] CPMEOF[28] CRC CRC
                                        ACK
EOT
                                        NAK
EOT
                                        ACK
                                        C
SOH 00 FF NUL[128] CRC CRC
                                        ACK
```

YMODEM Batch Transmission Session (2 files)

```
SENDER                                  RECEIVER
                                        "sb foo.c baz.c<CR>"
"sending in batch mode etc."
                                        C (command:rb)
SOH 00 FF foo.c NUL[123] CRC CRC
                                        ACK
                                        C
SOH 01 FE Data[128] CRC CRC
                                        ACK
SOH 02 FC Data[128] CRC CRC
                                        ACK
SOH 03 FB Data[100] CPMEOF[28] CRC CRC
                                        ACK
EOT
                                        NAK
EOT
                                        ACK
                                        C
SOH 00 FF baz.c NUL[123] CRC CRC
                                        ACK
                                        C
SOH 01 FB Data[100] CPMEOF[28] CRC CRC
                                        ACK
EOT
                                        NAK
EOT
                                        ACK
                                        C
SOH 00 FF NUL[128] CRC CRC
                                        ACK      
```

YMODEM Batch Transmission Session-1k Blocks

```
SENDER                                  RECEIVER
                                        "sb -k foo.*<CR>"
"sending in batch mode etc."
                                         C (command:rb)
SOH 00 FF foo.c NUL[123] CRC CRC
                                         ACK
                                         C
STX 01 FD Data[1024] CRC CRC
                                         ACK
SOH 02 FC Data[128] CRC CRC
                                         ACK
SOH 03 FB Data[100] CPMEOF[28] CRC CRC
                                         ACK
EOT
                                         NAK
EOT
```

## **3. Zmodem 协议**

Zmodem 是由 Chuck Forsberg 开发的文件传输协议，是 Xmodem 和 Ymodem 的改进版。Zmodem 协议以其高效、可靠、灵活的传输特点在许多应用中得到了广泛的应用。相比于 Xmodem 和 Ymodem，Zmodem 引入了流模式传输、错误恢复、自动速度调整等新特性，极大地提高了文件传输的效率和稳定性。

Zmodem 通过以下特性改进了文件传输：

- **流模式传输**：Zmodem 支持连续的数据流传输，而不是逐个数据块的传输，这大大提高了传输效率。
- **错误恢复**：在传输过程中，如果遇到传输错误或中断，Zmodem 可以从中断点恢复传输，而不需要重新传输整个文件。
- **自动速度调整**：Zmodem 会根据链路质量自动调整传输速度，确保最佳的传输性能。
- **批量文件传输**：类似 Ymodem，Zmodem 支持一次传输多个文件。
- **自动启动**：Zmodem 支持接收方自动启动传输，简化了传输过程。

