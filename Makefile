CC = gcc
CFLAGS += -m32 -Wall -g -O2 -W
AS = nasm
ASMFLAGS += -g -f elf32

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

.PHONY: all

all: integral

integral: integral.o fp.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

integral.o: integral.c
	$(CC) $(CFLAGS) $^ -c -o $@

fp.o: fp.asm
	$(AS) $(ASMFLAGS) $^ -o $@

test:
	./integral -R 1:2:-5.3:10.7:0.0001:-0.371818
	./integral --test-root 1:3:-7.91:3.23:0.003:-4.026682
	./integral -R 2:3:-15.27:10.7:0.0002:-1.822875
	./integral -I 1:-8.0:1.3:0.0005:22.269219
	./integral --test-integral 2:-6.0:-3.5:0.006:0.539014
	./integral -I 3:-5.1:-1.2:0.0007:8.095331


clean:
	rm -rf *.o ./integral
