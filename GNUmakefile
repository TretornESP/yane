override TARGET := yane.elf

CC := /usr/bin/gcc
LD := /usr/bin/ld

CFLAGS ?= -O0 -g -Wall -Wextra -pipe -pthread

ABSDIR := $(shell pwd)

SRCDIR := src
UTILDIR := util
BUILDHOME := build
BUILDDIR := build/bin
OBJDIR := build/lib

DIRS := $(wildcard $(SRCDIR)/*)
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Check that given variables are set and all have non-empty values,
# die with an error otherwise.
#
# Params:
#   1. Variable name(s) to test.
#   2. (optional) Error message to print.
check_defined = \
    $(strip $(foreach 1,$1, \
        $(call __check_defined,$1,$(strip $(value 2)))))
__check_defined = \
    $(if $(value $1),, \
      $(error Undefined $1$(if $2, ($2))))

override CFILES :=$(call rwildcard,$(SRCDIR),*.c)        
override OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CFILES))
override OBJS += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%_s.o, $(ASFILES))
override OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(NASMFILES))

.PHONY: clean test all run gdb debug log terminal rterminal kterminal

all:
	@echo "Building yane..."
	@make yane
	@make run
	@make clean
	@echo "Done."

debug:
	@echo "Building yane..."
	@make yane
	@make gdb
	@make clean
	@echo "Done."

yane: $(OBJS)
	@ echo !==== LINKING $^
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) $^ -o $(BUILDDIR)/$(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

run:
	@echo "Running yane..."
	@$(BUILDDIR)/$(TARGET)

gdb:
	@echo "Running yane in gdb..."
	@gdb --nx $(BUILDDIR)/$(TARGET)

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJDIR)/*
	@rm -rf $(OBJS)
	@rm -f $(BUILDDIR)/$(TARGET)
	@rm -f $(ABSDIR)/log.txt
	@rm -f $(ABSDIR)/terminal

log:
	@echo "Building yane..."
	@make yane
	@make run > $(ABSDIR)/log.txt
	@make clean
	@echo "Done."

terminal:
	@echo "Building terminal..."
	@$(CC) $(UTILDIR)/terminal.c -o $(ABSDIR)/terminal

rterminal:
	@echo "Running terminal..."
	@$(ABSDIR)/terminal

kterminal:
	@echo "Killing terminal..."
	@pkill -f 'make rterminal'

push:
	@echo "Cleaning up..."
	@make clean
	@echo "Pushing to git..."
	@git add .
	@git commit
	@git push origin main
	@echo "Done..."