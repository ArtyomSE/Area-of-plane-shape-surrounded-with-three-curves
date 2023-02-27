CC = gcc
CFLAGS += -m32 -Wall -g -O2 -W
AS = nasm
ASMFLAGS += -g -f elf32

all: integral

integral: integral.o fp.o
    $(CC) $(CFLAGS) $^ -lm -o $@

integral.o: integral.c
    $(CC) $(CFLAGS) $^ -c -o $@

fp.o: fp.asm
    $(AS) $(ASMFLAGS) $^ -o $@

test:
    ./integral -R 1:2:-5.3:-0.2:0.0001:-0.371816
    ./integral -R 1:3:-7.91:3.23:0.003:-4.026748
    ./integral -R 2:3:-15.27:10.7:0.0002:-1.822875
    ./integral -I 1:-8.0:1.3:0.0005:22.269219
    ./integral -I 2:-6.0:-3.5:0.006:0.539014
    ./integral -I 3:-5.1:-1.2:0.0007:8.095331


clean:
    rm -rf *.o fp.o root.o integral.o
