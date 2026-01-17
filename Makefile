# Makefile for building IncrediMail (cross-compile for classic Amiga m68k)
CC = /opt/m68k-amigaos/bin/m68k-amigaos-gcc
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
