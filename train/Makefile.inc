mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += util.o timer.o horn.o drive_unit.o signal_reader.o emergency_stopper.o train.o 

SRCLANG := c

# APPL_DIR += $(mkfile_path)app $(mkfile_path)../utils

# INCLUDES += \
# 	-I$(mkfile_path)app \
# 	-I$(mkfile_path)../utils
