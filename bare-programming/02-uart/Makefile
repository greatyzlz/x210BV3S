CROSS_COMPILE=arm-linux-gnueabihf-

BINARY		?=	../../binary
PROJECT		?=	led_stream

SRCS		+=	$(wildcard	*.S *.c)
OBJS    	:=	$(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
PRES    	:=	$(patsubst %.c,%.i,$(patsubst %.cpp,%.i,$(SRCS)))
ENV			?=	MEM

CROSS_COMPILE	?=		
CC			:=	$(CROSS_COMPILE)gcc
LD			:=	$(CROSS_COMPILE)ld
OBJCOPY		:=	$(CROSS_COMPILE)objcopy
OBJDUMP		:=	$(CROSS_COMPILE)objdump

INCLUDE		+=	-I./
LIBS		+=	.
libs		+=	
DEFINES		+=	

CFLAGS		:=	-Wall
ifeq ($(ENV), SD)
LDFLAGS		:=	-Ttext 0xD0020010
else
LDFLAGS		:=	-Ttext 0x30008000
endif

TARGET		?=	$(PROJECT).bin
ELF			?=	$(PROJECT).elf
DIS			?=	$(PROJECT).dis


all : $(TARGET)


$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(ELF) $^
	$(OBJCOPY) -O binary $(ELF) $(BINARY)/$@
	$(OBJDUMP) -D $(ELF) > $(DIS)
	#cp ../addheader ./
	#./addheader $(TARGET) 210.bin
	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< -fno-builtin
	
%.o : %.S
	$(CC) $(CFLAGS) -c -o $@ $<
	
#w2sd:
#	sudo dd iflag=dsync oflag=dsync if=210.bin of=/dev/sdb seek=1
	
clean:
	rm *.o *.elf $(BINARY)/$(TARGET) *.dis
