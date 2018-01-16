OPT?=-O3
all: main.bin

main.s: main.c
	arm-unknown-eabi-gcc $(OPT) -S main.c -mcpu=cortex-m4 -mthumb -g

main.elf: main.c
	arm-unknown-eabi-gcc $(OPT) main.c -mcpu=cortex-m4 -mthumb -g -lgcc -T linker_script.ld -Xlinker --cref -Xlinker -Map -Xlinker main.map -nostartfiles -o main.elf

main.bin: main.elf
	arm-unknown-eabi-objcopy -O binary main.elf main.bin

flash: main.bin
	st-flash write main.bin 0x8000000

clean:
	rm -f *.elf *.bin
