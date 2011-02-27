# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

PROJDIRS:=src header
CFILES:=$(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.c")
SFILES:=$(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.s" )
ALLSRCFILES:=$(SFILES) $(CFILES)

SOBJFILES:= $(patsubst %.s, %.o, $(SFILES)) 
COBJFILES:= $(patsubst %.c, %.o, $(CFILES))

CC=@cc
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -I header
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf
AS=@nasm

all: $(SOBJFILES) $(COBJFILES) link
	
clean:
	

link:
	@ld $(LDFLAGS) -o kernel $(SOBJFILES) $(COBJFILES)
	-@rm TODOLIST
	-@for file in $(ALLSRCFILES); do fgrep -H -e TODO -e FIXME $$file >> TODOLIST; done; true
	@./build_tracker_script
	@./update_image.sh
	-@rm $(SOBJFILES) $(COBJFILES)
	
