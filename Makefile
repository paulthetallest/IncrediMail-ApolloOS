# Makefile for building IncrediMail (cross-compile for classic Amiga m68k)
CC := $(shell if /opt/m68k-amigaos/bin/m68k-amigaos-gcc --version >/dev/null 2>&1; then echo /opt/m68k-amigaos/bin/m68k-amigaos-gcc; elif command -v m68k-elf-gcc >/dev/null 2>&1 && m68k-elf-gcc --version >/dev/null 2>&1; then echo m68k-elf-gcc; else echo ""; fi)
ifeq ($(strip $(CC)),)
$(warning No m68k cross-compiler found in /opt/m68k-amigaos or PATH.)
$(warning Install m68k-amigaos-gcc or m68k-elf-gcc, or set CC env var.)
CC = gcc
endif
AMIGA_SDK ?= /Users/paulbertelink/Desktop/NDK3.2R4
CFLAGS ?= -m68040 -O2 -Wall -Wextra \
	-idirafter $(shell pwd)/compat \
	-I$(AMIGA_SDK)/Include_H -I$(AMIGA_SDK)/Include_H/proto \
	-I$(AMIGA_SDK)/Include_H/exec -I$(AMIGA_SDK)/Include_I
LDFLAGS ?= -lamiga
SRC = IncrediMail.c
TARGET = IncrediMail

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
