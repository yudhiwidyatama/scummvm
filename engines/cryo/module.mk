MODULE := engines/cryo

MODULE_OBJS = \
	cryo.o \
	cryolib.o \
	detection.o \
	eden.o \
	sound.o \
	staticdata.o \
	video.o

# This module can be built as a plugin
ifeq ($(ENABLE_CRYO), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
