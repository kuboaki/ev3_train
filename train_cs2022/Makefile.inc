mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

SRCLANG := c

APPL_COBJS += app_train.o util.o unit_timer.o unit_drive_unit.o \
unit_signal_reader.o unit_operation_switch.o

# unit_horn.o unit_status_indicator.o