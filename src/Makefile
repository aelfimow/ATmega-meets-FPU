MCU = atmega644

CFLAGS = -mmcu=$(MCU)
CFLAGS += -g0
CFLAGS += -DF_CPU=20000000UL
CFLAGS += -Os
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -Wstrict-prototypes
CFLAGS += -std=gnu99

all:
	avr-gcc -c main.c -o main.o $(CFLAGS)
	avr-gcc -c npe.c -o npe.o $(CFLAGS)
	avr-gcc -c fpu_instr.c -o fpu_instr.o $(CFLAGS)
	avr-gcc -c UsartDriver.c -o UsartDriver.o $(CFLAGS)
	avr-gcc main.o npe.o fpu_instr.o UsartDriver.o -o main.elf -Wl,-u,vfprintf -lprintf_flt -lm $(CFLAGS)
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature main.elf main.hex
	avr-size --mcu=$(MCU) --format=avr main.elf
