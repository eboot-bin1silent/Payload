  GNU nano 8.7.1                            Makefile                            Modified
CC      := gcc
AR      := ar
ODIR    := build
SDIR    := source
IDIR    := include
CFLAGS  := -I$(IDIR) -Os -std=c11 -ffunction-sections -fdata-sections -fno-builtin -nosta>
CFILES  := $(wildcard $(SDIR)/*.c)
SFILES  := $(wildcard $(SDIR)/*.s)
OBJS    := $(patsubst $(SDIR)/%.c, build/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, build/%.>

TARGET = libPS4.a

$(TARGET): $(ODIR) $(OBJS)
        $(AR) rcs $@ $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.c
        $(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s
        $(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
        @mkdir $@

.PHONY: clean

clean:
        rm -rf $(TARGET) $(ODIR)
