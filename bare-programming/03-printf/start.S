/*
*轮询工作模式，串口需要配置的寄存器
* UART2 supports auto flow control if TxD3 and RxD3 are set as nRTS2 and nCTS2 by GPA1CON(GPIO SFR)
*/


.global _start					/* 声明一个全局的标号 */
_start:

	ldr r0, =0xE0200020		@config GPA1CON as UART2 TXD, RXD
	ldr r1, [r0]
	bic r1, r1, #0xFF
	orr r1, r1, #0x22
	str r1, [r0]
	
	ldr r0, =0xE2900800		@UART2 BASE
	ldr r1, =0x3			@ULCON2=0x3, 8bit/frame, 1bit stop, no parity
	str r1, [r0]
	
	ldr r1, =0x5			@UCON2=0x5, polling mode r/t
	str r1, [r0, #0x4]
	
	ldr r1, =0x0			@UFCON2=0x1, FIFO disable
	str r1, [r0, #0x8]
	
	ldr r1, =0x0			@UMCON2=0x0
	str r1, [r0, #0xC]
	
	ldr r1, =34				@UBRDIV2=34  66MHz
	str r1, [r0, #0x28]
	
	ldr r1, =0xDDDD			@UDIVSLOT2=0xDDDDD
	str r1, [r0, #0x2C]
	
	
	bl main
	
halt:
	b halt

uart_test:	
	ldr r0, =0xE2900820	
	ldr r1, =0xA				@UTH2 = '\r'
	str r1, [r0]
	ldr r1, =0xD				@UTH2 = '\n'
	str r1, [r0]	
	ldr r1, =0x55				@UTH2 = 'U'
	str r1, [r0]
	ldr r1, =0x61				@UTH2 = 'a'
	str r1, [r0]
	ldr r1, =0x72				@UTH2 = 'r'
	str r1, [r0]
	ldr r1, =0x74				@UTH2 = 't'
	str r1, [r0]
	ldr r1, =0xA				@UTH2 = '\r'
	str r1, [r0]
	ldr r1, =0xD				@UTH2 = '\n'
	str r1, [r0]
