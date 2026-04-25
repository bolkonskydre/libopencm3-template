PROJECT = stm32-firmware
BUILD_DIR = bin

SHARED_DIR = ../inc
CFILES = firmware.c
CFILES += core/system.c

# TODO - you will need to edit these two lines!
DEVICE=stm32h743zit6
OOCD_FILE = board/stm32h743zit6.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
