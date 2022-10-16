#######
# makefile for STM8*_StdPeriph_Lib and SDCC compiler
#
# note: paths in this Makefile assume unmodified SPL folder structure
#
# usage:
#   1. if SDCC not in PATH set path -> CC_ROOT
#   2. set correct STM8 device -> DEVICE
#   3. set project paths -> PRJ_ROOT, PRJ_SRC_DIR, PRJ_INC_DIR
#   4. set SPL root path -> SPL_ROOT
#   5. include required SPL modules -> SPL_SOURCE
#
#######

# STM8 device (doesn't matter here, just for Makefile)
DEVICE=STM8TL5x

# set compiler path & parameters 
CC_ROOT =
CC      = sdcc
CFLAGS  = -mstm8 -lstm8 --opt-code-size

# set output folder and target name
OUTPUT_DIR = ./$(DEVICE)
TARGET     = $(OUTPUT_DIR)/$(DEVICE).hex

# set project folder and files (all *.c)
PRJ_ROOT    = ..
PRJ_SRC_DIR = $(PRJ_ROOT)
PRJ_INC_DIR = $(PRJ_ROOT)
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# set SPL paths
SPL_ROOT    = ../../..
SPL_SRC_DIR = $(SPL_ROOT)/Libraries/STM8TL5x_StdPeriph_Driver/src
SPL_INC_DIR = $(SPL_ROOT)/Libraries/STM8TL5x_StdPeriph_Driver/inc
SPL_SOURCE  = stm8tl5x_gpio.c
SPL_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(SPL_SOURCE:.c=.rel))

# collect all include folders
INCLUDE = -I$(PRJ_SRC_DIR) -I$(SPL_INC_DIR)

# collect all source directories
VPATH=$(PRJ_SRC_DIR):$(SPL_SRC_DIR)

.PHONY: clean

all: $(OUTPUT_DIR) $(TARGET)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -D$(DEVICE) -c $?

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -D$(DEVICE) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS) $(SPL_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

clean: 
	rm -fr $(OUTPUT_DIR)

