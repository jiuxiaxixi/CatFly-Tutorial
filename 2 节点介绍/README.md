# 节点介绍

测试平台中的物联网节点是由我们设计并请代工厂制造的IEEE 802.15.4兼容设备。每个节点配备了一个STM32F103RCT6微控制器、2.4 GHz AT86RF231无线射频模块、72MHz 32位CPU、256K指令存储器、96K RAM和USB接口，同时每个节点包含一个内置温度传感器和光线传感器，2个LED灯和预留的拓展接口。当放置在室内环境中时，加上3DB的衰减器之后，无线射频模块的可靠传输范围大约在1m至30m之间。节点上运行Contiki OS 3.0，一个具有轻量级和事件驱动并且具有适合嵌入式的网络协议栈uIP的操作系统。

 

