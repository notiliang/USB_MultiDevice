# USB 复合设备设计

一个基于 STM32H7 的 USB 复合设备项目，实现通过单一 USB 接口同时进行设备操作和硬件调试。

---

## 目录

- [项目初衷](#项目初衷)
- [功能特性](#功能特性)
- [硬件平台](#硬件平台)
- [软件架构](#软件架构)
- [USB 复合设备实现](#usb-复合设备实现)
- [项目结构](#项目结构)
- [开发环境](#开发环境)
- [快速开始](#快速开始)
- [开发进度](#开发进度)
- [技术文档](#技术文档)
- [许可证](#许可证)

---

## 项目初衷

笔者工作之初曾收到一个需求，即需要在上位机操作产品的同时可以通过同一个接口去调试硬件，但一直没空去搞。后面离职后正好有空研究一下USB相关的技术。

本项目旨在实现一个 USB 复合设备，能够：
- 同时提供多个虚拟串口（CDC ACM）用于数据通信
- 提供自定义 HID 接口用于人机交互
- 通过单一 USB 接口实现设备操作和调试功能

---

## 功能特性

| 功能 | 状态 | 说明 |
|------|------|------|
| 双串口通信 | ✅ 已实现 | UART4 和 UART5 硬件串口配置 |
| USB 复合设备 | ✅ 已实现 | 使用 I-CUBE-USBD-Composite 构建 |
| CDC ACM | ✅ 已实现 | 2 个虚拟串口接口 |
| 自定义 HID | ✅ 已配置 | 自定义 HID 设备支持 |
| 串口回环测试 | ⚠️ 部分完成 | 基础测试已完成 |
| USB 数据传输 | 🚧 进行中 | USB 与串口数据转发 |

---

## 硬件平台

- **MCU**: STM32H7 系列微控制器
- **主频**: 最高 480MHz
- **USB 接口**: USB OTG HS（高速）
- **调试接口**: UART4、UART5

---

## 软件架构

### 技术栈

```
┌─────────────────────────────────────┐
│         应用层 (Application)         │
├─────────────────────────────────────┤
│   USB 复合设备中间件 (Composite)     │
│  ┌─────────┐  ┌─────────┐           │
│  │ CDC ACM │  │   HID   │           │
│  │  x2     │  │ Custom  │           │
│  └─────────┘  └─────────┘           │
├─────────────────────────────────────┤
│   ST USB 设备库 (USB Device Lib)    │
├─────────────────────────────────────┤
│        HAL 驱动层 (HAL Drivers)      │
├─────────────────────────────────────┤
│       CMSIS / 硬件层 (Hardware)      │
└─────────────────────────────────────┘
```

### 依赖库

- **STM32_USB_Device_Library**: ST 官方 USB 设备库
- **AL94_USB_Composite**: 第三方 USB 复合设备构建库（CubeMX可配）

---

## USB 复合设备实现

本项目使用 **AL94 I-CUBE-USBD-Composite** 库构建 USB 复合设备。该库通过模块化设计，支持多种 USB 功能类的灵活组合。

### 实现原理

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         USB Composite Device                            │
├─────────────────────────────────────────────────────────────────────────┤
│  Interface 0              │  Interface 1              │  Interface 2    │
│  CDC ACM (COM1)           │  CDC ACM (COM2)           │  Custom HID     │
│  ├─ CDC Command (EP2)     │  ├─ CDC Command (EP4)     │  ├─ Interrupt   │
│  └─ CDC Data (EP1 IN/OUT)│  └─ CDC Data (EP3 IN/OUT)│                  │
└─────────────────────────────────────────────────────────────────────────┘
```

### 核心文件说明

| 文件 | 说明 |
|------|------|
| [AL94.I-CUBE-USBD-COMPOSITE_conf.h](Composite/AL94.I-CUBE-USBD-COMPOSITE_conf.h) | 功能类开关配置 |
| [usbd_composite.c](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Src/usbd_composite.c) | 复合设备核心实现 |
| [usb_device.c](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usb_device.c) | USB 设备初始化 |

### 配置步骤

#### 1. 功能类配置

编辑 [AL94.I-CUBE-USBD-COMPOSITE_conf.h](Composite/AL94.I-CUBE-USBD-COMPOSITE_conf.h:1)，启用需要的功能类：

```c
// 启用 USB 高速模式
#define _USBD_USE_HS                  true

// 启用 CDC ACM（虚拟串口）
#define _USBD_USE_CDC_ACM             true
#define _USBD_CDC_ACM_COUNT           2        // 2 个虚拟串口

// 启用自定义 HID
#define _USBD_USE_HID_CUSTOM          true
```

#### 2. 自动描述符构建

库会根据配置自动构建完整的 USB 配置描述符：

```c
// usbd_composite.c:893 - USBD_COMPOSITE_Mount_Class()
void USBD_COMPOSITE_Mount_Class(void)
{
  // 端点号跟踪器
  uint8_t in_ep_track = 0x81;      // IN 端点从 0x81 开始
  uint8_t out_ep_track = 0x01;     // OUT 端点从 0x01 开始
  uint8_t interface_no_track = 0x00;  // 接口号从 0 开始

  // 按配置顺序挂载各功能类描述符
  // ... 每个 class 自动分配接口号和端点号
}
```

#### 3. 设备初始化

在 [main.c](Core/Src/main.c:102) 中初始化 USB 设备：

```c
int main(void)
{
  // ... 系统初始化

  MX_USB_DEVICE_Init();  // 初始化 USB 复合设备

  while (1) {
    // 主循环
  }
}
```

#### 4. 初始化流程

[usb_device.c:62](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usb_device.c:62) 中的 `MX_USB_DEVICE_Init()` 函数：

```c
void MX_USB_DEVICE_Init(void)
{
  // 1. 挂载所有启用的功能类
  USBD_COMPOSITE_Mount_Class();

  // 2. 初始化 USB 核心
  USBD_Init(&hUsbDevice, &USBD_Desc, DEVICE_HS);

  // 3. 注册复合设备类
  USBD_RegisterClass(&hUsbDevice, &USBD_COMPOSITE);

  // 4. 注册各功能类接口
  USBD_CDC_ACM_RegisterInterface(...);      // CDC ACM
  USBD_CUSTOM_HID_RegisterInterface(...);   // 自定义 HID

  // 5. 启动 USB 设备
  USBD_Start(&hUsbDevice);
}
```

### 支持的功能类

| 功能类 | 宏定义 | 说明 |
|--------|--------|------|
| CDC ACM | `_USBD_USE_CDC_ACM` | 虚拟串口（支持多个实例） |
| CDC RNDIS | `_USBD_USE_CDC_RNDIS` | 网络适配器（RNDIS） |
| CDC ECM | `_USBD_USE_CDC_ECM` | 网络适配器（ECM） |
| HID Mouse | `_USBD_USE_HID_MOUSE` | 鼠标 |
| HID Keyboard | `_USBD_USE_HID_KEYBOARD` | 键盘 |
| HID Custom | `_USBD_USE_HID_CUSTOM` | 自定义 HID |
| UAC Mic | `_USBD_USE_UAC_MIC` | 麦克风 |
| UAC Speaker | `_USBD_USE_UAC_SPKR` | 扬声器 |
| UVC | `_USBD_USE_UVC` | 视频设备 |
| MSC | `_USBD_USE_MSC` | 大容量存储 |
| DFU | `_USBD_USE_DFU` | 固件升级 |
| Printer | `_USBD_USE_PRNTR` | 打印机 |

### 端点与接口分配

复合设备库会自动管理端点和接口号分配：

```
功能类              接口号          IN端点        OUT端点      CMD端点
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CDC ACM #1          IF0, IF1        EP1           EP1          EP2
CDC ACM #2          IF2, IF3        EP3           EP3          EP4
Custom HID          IF4             EP5           EP6          -
```

> 注：CDC ACM 每个实例占用 2 个接口号（通信接口 + 数据接口）

### 数据流向

```
主机                     STM32
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
COM1 ←── CDC ACM #1 ←→ 端点1 (IN/OUT)
                          ↓
                      应用层处理
                          ↑
COM2 ←── CDC ACM #2 ←→ 端点3 (IN/OUT)

HID ←── Custom HID  ←→ 端点5/6 (IN/OUT)
```

---

### USB 枚举与描述符设计

理解 USB 复合设备的关键在于理解 USB 设备的枚举过程。主机通过一系列标准请求（GET_DESCRIPTOR）来识别设备的类型和功能。

#### 枚举流程图

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           USB 设备枚举流程                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│  ① 上电复位                                                                 │
│     └── 主机检测到设备连接，发出 RESET 信号                                   │
│                                                                             │
│  ② 获取设备描述符 (GET_DESCRIPTOR - DEVICE)                                 │
│     └── 确定设备类型（复合设备：bDeviceClass = 0xEF）                        │
│                                                                             │
│  ③ 设置地址 (SET_ADDRESS)                                                   │
│     └── 分配唯一 USB 地址                                                   │
│                                                                             │
│  ④ 获取配置描述符 (GET_DESCRIPTOR - CONFIGURATION)                          │
│     └── 获取完整的配置描述符，包含所有接口和端点信息                           │
│                                                                             │
│  ⑤ 获取字符串描述符 (GET_DESCRIPTOR - STRING)                               │
│     └── 获取厂商、产品、序列号等字符串                                        │
│                                                                             │
│  ⑥ 设置配置 (SET_CONFIGURATION)                                            │
│     └── 激活配置，设备进入配置状态                                           │
│                                                                             │
│  ⑦ 设备枚举完成，开始正常通信                                                │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

#### 描述符层次结构

USB 复合设备的描述符按以下层次组织：

```
┌───────────────────────────────────────────────────────────────────────────────┐
│                          USB 描述符层次结构                                     │
├───────────────────────────────────────────────────────────────────────────────┤
│                                                                               │
│  ┌─────────────────┐                                                          │
│  │ 设备描述符 (18B) │ ←─ [usbd_desc.c:152] 定义设备基本信息                      │
│  │  - bDeviceClass │     0xEF (复合设备)                                       │
│  │  - idVendor/pid │     VID/PID                                              │
│  └────────┬────────┘                                                          │
│           │                                                                   │
│           ▼                                                                   │
│  ┌─────────────────┐                                                          │
│  │ 配置描述符 (9B)  │ ←─ 总长度 = 所有接口描述符之和                            │
│  │  - wTotalLength │     由 USBD_COMPOSITE_Mount_Class() 自动计算              │
│  │  - bNumInterfaces│    5 个接口（2 CDC ACM × 2接口 + 1 HID）                 │
│  └────────┬────────┘                                                          │
│           │                                                                   │
│           ├──► ┌──────────────┐                                               │
│           │    │ IAD 描述符    │ ←─ Interface Association Descriptor            │
│           │    │ (8B)          │    关联 CDC 的控制接口和数据接口                │
│           │    └──┬───────────┘                                               │
│           │       │                                                           │
│           │       ▼                                                           │
│           │    ┌──────────────────────────────────────────────────────────┐    │
│           │    │ CDC ACM #1 接口组 (66B)                                   │    │
│  [usbd_cdc_acm.c:173]                                                     │    │
│           │    │  ┌─ IAD (8B)                                            │    │
│           │    │  │  ┌─ 接口描述符 (9B) - 通信接口 (IF0)                   │    │
│           │    │  │  │  ├─ Header Functional Desc (5B)                    │    │
│           │    │  │  │  ├─ Call Management Desc (5B)                      │    │
│           │    │  │  │  ├─ ACM Functional Desc (4B)                        │    │
│           │    │  │  │  ├─ Union Functional Desc (5B)                     │    │
│           │    │  │  │  └─ 端点描述符 (7B) - EP2 (Interrupt IN)           │    │
│           │    │  │  └─ 接口描述符 (9B) - 数据接口 (IF1)                   │    │
│           │    │  │     ├─ 端点描述符 (7B) - EP1 (Bulk OUT)               │    │
│           │    │  │     └─ 端点描述符 (7B) - EP1 (Bulk IN)                │    │
│           │    │  └─ 总计: 66 字节                                         │    │
│           │    └──────────────────────────────────────────────────────────┘    │
│           │                                                                   │
│           ├──► ┌──────────────┐                                               │
│           │    │ IAD 描述符    │                                                 │
│           │    └──┬───────────┘                                               │
│           │       │                                                           │
│           │       ▼                                                           │
│           │    ┌──────────────────────────────────────────────────────────┐    │
│           │    │ CDC ACM #2 接口组 (66B) - 结构同上                         │    │
│           │    │  - IF2 (通信接口) + EP4 (Interrupt IN)                    │    │
│           │    │  - IF3 (数据接口) + EP3 (Bulk IN/OUT)                     │    │
│           │    └──────────────────────────────────────────────────────────┘    │
│           │                                                                   │
│           └──► ┌──────────────────────────────────────────────────────────┐    │
│                │ Custom HID 接口组                                         │    │
│                │  ┌─ 接口描述符 (9B) - IF4                                 │    │
│                │  │  ├─ HID 描述符                                         │    │
│                │  │  └─ 端点描述符 - EP5/EP6 (Interrupt IN/OUT)             │    │
│                │  └─ 总计: ~XX 字节                                         │    │
│                └──────────────────────────────────────────────────────────┘    │
│                                                                               │
└───────────────────────────────────────────────────────────────────────────────┘
```

#### 设备描述符详解

[usbd_desc.c:152](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_desc.c#L152) 中定义的设备描述符：

```c
__ALIGN_BEGIN uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
{
  0x12,                       // bLength: 18 字节
  USB_DESC_TYPE_DEVICE,       // bDescriptorType: 0x01 (设备描述符)
  0x00, 0x02,                 // bcdUSB: USB 2.0
  0xEF,                       // bDeviceClass: 0xEF = 复合设备
  0x02,                       // bDeviceSubClass: 0x02
  0x01,                       // bDeviceProtocol: 0x01
  USB_MAX_EP0_SIZE,           // bMaxPacketSize0: EP0 最大包大小（64）
  LOBYTE(USBD_VID),           // idVendor: 0x0483 (ST)
  HIBYTE(USBD_VID),
  LOBYTE(USBD_PID),           // idProduct: 0x52A4
  HIBYTE(USBD_PID),
  0x00, 0x02,                 // bcdDevice: 2.00
  USBD_IDX_MFC_STR,           // iManufacturer: 厂商字符串索引
  USBD_IDX_PRODUCT_STR,       // iProduct: 产品字符串索引
  USBD_IDX_SERIAL_STR,        // iSerialNumber: 序列号字符串索引
  USBD_MAX_NUM_CONFIGURATION  // bNumConfigurations: 配置数量
};
```

**关键字段说明：**

| 字段 | 值 | 说明 |
|------|-----|------|
| `bDeviceClass` | `0xEF` | **复合设备标识**，告诉主机这是一个多功能设备 |
| `bDeviceSubClass` | `0x02` | 子类代码 |
| `bDeviceProtocol` | `0x01` | 协议代码 |

#### 配置描述符详解

配置描述符由 [USBD_COMPOSITE_Mount_Class()](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Src/usbd_composite.c#L893) 动态构建：

```c
// usbd_composite.c:1119 - 计算总长度并更新配置描述符头
uint16_t CFG_SIZE = sizeof(USBD_COMPOSITE_CFG_DESC_t);
ptr = USBD_COMPOSITE_HSCfgDesc.CONFIG_DESC;

ptr[0] = 0x09;                        // bLength: 9 字节
ptr[1] = USB_DESC_TYPE_CONFIGURATION; // bDescriptorType: 0x02 (配置描述符)
ptr[2] = LOBYTE(CFG_SIZE);            // wTotalLength: 总长度（包含所有接口）
ptr[3] = HIBYTE(CFG_SIZE);
ptr[4] = interface_no_track;          // bNumInterfaces: 接口总数（5个）
ptr[5] = 0x01;                        // bConfigurationValue: 配置值
ptr[6] = 0x00;                        // iConfiguration: 配置字符串索引
ptr[7] = 0xC0;                        // bmAttributes: 自供电
ptr[8] = USBD_MAX_POWER;              // MaxPower: 最大功耗（100mA）
```

#### CDC ACM 接口描述符详解

每个 CDC ACM 实例占用 **66 字节**，包含一个 IAD 描述符和两个接口：

```c
// usbd_cdc_acm.c:190 - CDC ACM #0 描述符结构
/* ========== IAD (Interface Association Descriptor) ========== */
0x08,             // bLength: 8 字节
0x0B,             // bDescriptorType: 0x0B (IAD)
0x00,             // bFirstInterface: 第一个接口号 (IF0)
0x02,             // bInterfaceCount: 关联 2 个接口
0x02,             // bFunctionClass: CDC Control
0x02,             // bFunctionSubClass: Abstract Control Model
0x01,             // bFunctionProtocol: V.25ter protocol
0x00,             // iFunction: 字符串索引

/* ========== 接口 0: 通信接口 (Communication Interface) ========== */
/* Interface Descriptor */
0x09,             // bLength: 9 字节
0x04,             // bDescriptorType: Interface
0x00,             // bInterfaceNumber: IF0
0x00,             // bAlternateSetting: 0
0x01,             // bNumEndpoints: 1 个端点（EP2）
0x02,             // bInterfaceClass: CDC Control
0x02,             // bInterfaceSubClass: ACM
0x01,             // bInterfaceProtocol: AT commands
0x00,             // iInterface

/* Header Functional Descriptor (CDC 类特定) */
0x05, 0x24, 0x00, 0x10, 0x01

/* Call Management Functional Descriptor */
0x05, 0x24, 0x01, 0x00, 0x01  // bDataInterface = IF1

/* ACM Functional Descriptor */
0x04, 0x24, 0x02, 0x02        // 支持 SET_LINE_CODING

/* Union Functional Descriptor */
0x05, 0x24, 0x06, 0x00, 0x01  // 主接口=IF0, 从接口=IF1

/* Endpoint 2 Descriptor (Command) */
0x07,             // bLength: 7 字节
0x05,             // bDescriptorType: Endpoint
0x82,             // bEndpointAddress: EP2 IN (中断端点)
0x03,             // bmAttributes: Interrupt
0x08, 0x00,       // wMaxPacketSize: 8 字节
0x10,             // bInterval: 16ms

/* ========== 接口 1: 数据接口 (Data Interface) ========== */
/* Interface Descriptor */
0x09,             // bLength
0x04,             // bDescriptorType: Interface
0x01,             // bInterfaceNumber: IF1
0x00,             // bAlternateSetting
0x02,             // bNumEndpoints: 2 个端点
0x0A,             // bInterfaceClass: CDC Data
0x00,             // bInterfaceSubClass
0x00,             // bInterfaceProtocol
0x00,             // iInterface

/* Endpoint 1 Descriptor (OUT) */
0x07, 0x05, 0x01, 0x02, 0x00, 0x02, 0x00  // EP1 OUT, Bulk, 512B

/* Endpoint 1 Descriptor (IN) */
0x07, 0x05, 0x81, 0x02, 0x00, 0x02, 0x00  // EP1 IN, Bulk, 512B
```

#### 动态描述符构建机制

[usbd_composite.c:893](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Src/usbd_composite.c#L893) 中的 `USBD_COMPOSITE_Mount_Class()` 负责动态构建复合设备描述符：

```c
void USBD_COMPOSITE_Mount_Class(void)
{
  uint8_t in_ep_track = 0x81;      // IN 端点跟踪器
  uint8_t out_ep_track = 0x01;     // OUT 端点跟踪器
  uint8_t interface_no_track = 0x00;  // 接口号跟踪器

  // 按配置顺序挂载各功能类描述符
#if (USBD_USE_CDC_ACM == 1)
  // 获取 CDC ACM 描述符模板
  ptr = USBD_CDC_ACM.GetFSConfigDescriptor(&len);

  // 更新描述符中的动态字段（接口号、端点号等）
  USBD_Update_CDC_ACM_DESC(ptr,
                           interface_no_track,      // cmd_itf: IF0
                           interface_no_track + 1,  // com_itf: IF1
                           in_ep_track,             // in_ep: EP1
                           in_ep_track + 1,         // cmd_ep: EP2
                           out_ep_track,           // out_ep: EP1
                           USBD_Track_String_Index);

  // 复制到复合设备描述符中
  memcpy(USBD_COMPOSITE_FSCfgDesc.USBD_CDC_ACM_DESC, ptr + 0x09, len - 0x09);

  // 更新跟踪器
  in_ep_track += 2;      // 下一个 IN 端点: EP3
  out_ep_track += 1;     // 下一个 OUT 端点: EP2
  interface_no_track += 2;  // 下一个接口: IF2
  USBD_Track_String_Index += 1;
#endif

#if (USBD_USE_HID_CUSTOM == 1)
  // HID 描述符挂载...
#endif

  // 最后更新配置描述符头部
  ptr = USBD_COMPOSITE_HSCfgDesc.CONFIG_DESC;
  ptr[2] = LOBYTE(CFG_SIZE);     // wTotalLength
  ptr[3] = HIBYTE(CFG_SIZE);
  ptr[4] = interface_no_track;   // bNumInterfaces: 总接口数
}
```

[usbd_cdc_acm.c:2158](Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ACM/Src/usbd_cdc_acm.c#L2158) 中的 `USBD_Update_CDC_ACM_DESC()` 负责更新 CDC 描述符中的动态字段：

```c
void USBD_Update_CDC_ACM_DESC(uint8_t *desc,
                              uint8_t cmd_itf,    // 命令接口号
                              uint8_t com_itf,    // 数据接口号
                              uint8_t in_ep,      // IN 端点
                              uint8_t cmd_ep,     // 命令端点
                              uint8_t out_ep,     // OUT 端点
                              uint8_t str_idx)    // 字符串索引
{
  desc += 9;  // 跳过配置描述符头部
  for (uint8_t i = 0; i < NUMBER_OF_CDC; i++)
  {
    // 更新 IAD 描述符
    desc[2] = cmd_itf;           // bFirstInterface

    // 更新接口描述符
    desc[10] = cmd_itf;          // 通信接口号
    desc[16] = str_idx;          // iInterface

    // 更新 Union 功能描述符
    desc[34] = cmd_itf;          // bMasterInterface
    desc[35] = com_itf;          // bSlaveInterface

    // 更新端点描述符
    desc[38] = cmd_ep;           // 命令端点
    desc[54] = out_ep;           // OUT 端点
    desc[61] = in_ep;            // IN 端点

    // 更新 Call Management 描述符
    desc[26] = com_itf;          // bDataInterface

    // 保存到全局变量供运行时使用
    CDC_CMD_ITF_NBR[i] = cmd_itf;
    CDC_COM_ITF_NBR[i] = com_itf;
    CDC_IN_EP[i] = in_ep;
    CDC_OUT_EP[i] = out_ep;
    CDC_CMD_EP[i] = cmd_ep;

    // 更新下一个 CDC 的参数
    in_ep += 2;
    cmd_ep = in_ep + 1;
    out_ep++;
    cmd_itf += 2;
    com_itf = cmd_itf + 1;
    str_idx++;

    desc += 66;  // 移动到下一个 CDC 描述符块
  }
}
```

#### 复合设备的关键点

1. **IAD (Interface Association Descriptor)**: 将多个接口关联为一个功能组，使操作系统能正确识别并加载对应的驱动程序。

2. **动态端点/接口分配**: AL94 库通过跟踪器自动分配连续的端点号和接口号，避免冲突。

3. **描述符拼接**: 将各功能类的描述符模板拼接成完整的配置描述符，然后更新其中的动态字段。

4. **复合设备标识**: 设备描述符中 `bDeviceClass = 0xEF` 表示这是一个复合设备。

---

## 项目结构

```
USB_MultiDevice/
├── Core/                           # 核心应用代码
│   ├── Src/
│   │   ├── main.c                  # 主程序入口
│   │   ├── gpio.c                  # GPIO 配置
│   │   ├── usart.c                 # 串口配置 (UART4/5)
│   │   ├── usb_otg.c               # USB OTG 配置
│   │   └── ...
│   └── Inc/                        # 头文件
├── Middlewares/
│   ├── ST/                         # ST 官方 USB 库
│   │   └── STM32_USB_Device_Library/
│   └── Third_Party/
│       └── AL94_USB_Composite/     # 复合设备库
├── Composite/                      # 复合设备配置
├── Drivers/                        # 硬件驱动库
│   ├── CMSIS/                      # CMSIS 标准
│   └── STM32H7xx_HAL_Driver/       # HAL 驱动
├── build/                          # 构建输出目录
├── CMakeLists.txt                  # CMake 构建配置
└── README.md                       # 项目说明
```

---

## 开发环境

### 工具链

| 工具 | 版本/说明 |
|------|----------|
| IDE | VSCode + STM32CubeIDE |
| 代码生成 | STM32CubeMX |
| 编译器 | ARM GCC |
| 构建系统 | CMake |
| 代码分析 | ClangD |

### VSCode 扩展推荐

- C/C++ (Microsoft)
- Cortex-Debug (marus25)
- CMake (twxs)

---

## 快速开始

### 前置要求（也可直接安装STM32CubeIDE for VS Code 扩展）

```bash
# 安装 ARM GCC 工具链
# 安装 CMake
# 安装 STM32CubeMX
```

### 构建项目

```bash
# 创建构建目录
mkdir build && cd build

# 配置 CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 编译
cmake --build .
```

### 烧录

使用 STM32CubeIDE 或通过 ST-Link Utility 烧录生成的固件。

---

## 开发进度

### Git 提交历史

| 提交 | 描述 |
|------|------|
| a9483d6 | 更新 README |
| 0342fd8 | 创建 README |
| 0323510 | 测试：两个虚拟串口的回环通信 |
| fe634ba | 添加：CubeMX USB COMPOSITE pack 注释 |
| e386a01 | 修改：USB 设备初始化方式 |

### 待办事项

- [ ] 完善 USB 与串口数据转发功能
- [ ] 添加自定义 HID 报告描述符
- [ ] 实现完整的串口回环测试
- [ ] 编写用户使用文档
- [ ] 添加错误处理机制

---

## 技术文档

### 配置文件

- **AL94.I-CUBE-USBD-COMPOSITE_conf.h**: USB 复合设备配置
  - CDC ACM 接口数量: 2
  - 自定义 HID 接口: 1

### 参考资源

- [STM32 USB 设备库](https://github.com/STMicroelectronics/stm32_usb_device_library)
- [USB Composite Device Specification](https://www.usb.org/documents)
- [I-CUBE-USBD-Composite](https://github.com/STMicroelectronics/STM32Cube_USB)

---

## 许可证

本项目仅供学习和研究使用。

---

## 贡献

欢迎提交 Issue 和 Pull Request！

---

## 联系方式

如有问题或建议，欢迎通过 Issue 联系。
