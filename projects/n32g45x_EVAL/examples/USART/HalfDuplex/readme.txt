1、功能说明

    该测例演示了USARTy与USARTz间通过查询检测标识，实现半双工模式的
基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz接收数据存至RxBuffer2。
    随后，USARTz发送TxBuffer2数据至USARTy，USARTy接收数据存至RxBuffer1。
    最后，分别比较两组接收数据与发送数据，比较结果存入TransferStatus1变量
和TransferStatus2变量。
    USARTy和USARTz可以是USART1和USART2、USART3和UART4或UART6和UART7。


2、使用环境

    软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32G45XV-STB_V1.1


3、使用说明
    
    系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 144MHz
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - 半双工模式使能
    
    USART引脚连接如下：
    - USART1_Tx.PA9    <------->   USART2_Tx.PA2
    或
    - USART3_Tx.PB10   <------->   UART4_Tx.PC10
    或
    - UART6_Tx.PE2    <------->    UART7_Tx.PC4

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行后，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项
    USART_Tx需外接上拉电阻。
    使用PA9，PA10需要把开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开

1. Function description

    This test example demonstrates that the half-duplex mode can be realized by querying the detection mark between USARTy and USARTz.
Basic communication.
    First, USARTy sends TxBuffer1 data to USARTz, and USARTz receives data and stores it in RxBuffer2.
    Subsequently, USARTz sends TxBuffer2 data to USARTy, and USARTy receives data to RxBuffer1.
    Finally, compare the two groups of received data and sent data respectively, and store the comparison results in the TransferStatus1 variable
And the TransferStatus2 variable.
    USARTy and USARTz can be USART1 and USART2, USART3 and UART4 or UART6 and UART7.


2. Use environment

    Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

    Hardware environment: minimum system board N32G45XV-STB_V1.1


3. Instructions for use
    
    The system clock configuration is as follows:
    -Clock source = HSE + PLL
    -System clock = 144MHz
    
    The USART configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 8 data bits
    -1 stop bit
    -Parity control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    -Half-duplex mode enabled
    
    The USART pin connections are as follows:
    -USART1_Tx.PA9 <-------> USART2_Tx.PA2
    or
    -USART3_Tx.PB10 <-------> UART4_Tx.PC10
    or
    -UART6_Tx.PE2 <-------> UART7_Tx.PC4

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -After resetting the operation, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal


4. Matters needing attention
    USART_Tx requires an external pull-up resistor.
    To use PA9/PA10, disconnect the jumper cap of MCU_TX/MCU_RX on NS-LINK