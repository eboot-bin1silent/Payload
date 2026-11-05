TARGET = custom_payload
OBJS = main.o

CFLAGS = -Os -std=c11 -ffunction-sections -fdata-sections -fno-builtin -nostartfiles -nostdlib
LDFLAGS = -T linker.x -nostdlib -nodefaultlibs

all: $(TARGET).bin

$(TARGET).bin: $(OBJS)
	ld $(LDFLAGS) -o $(TARGET).elf $(OBJS)
	objcopy -O binary $(TARGET).elf $(TARGET).bin

clean:
	rm -f *.bin *.elf *.o
