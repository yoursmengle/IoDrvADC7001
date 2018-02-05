######################################################################################
######################################################################################
## Copyright:»··© 3S - Smart Software Solutions GmbH, Kempten                       ##
## Program: »···Linux dynamic linking makefile                                      ##
## Module: »····Makefile                                                            ##
## Version:»····0.1                                                                 ##
## Author:      3s-software. (PhB)                                                  ##
######################################################################################
#   ----------------------------------------------------------------------------
#   Included defined variables
#   ----------------------------------------------------------------------------
#include ../../Rules.make
ARCH=arm
CROSS_COMPILE=arm-linux-gnueabi-

TARGET = IoDrvADC7001
OTHER_SRC = ./axio/ai.c ./axio/gpio.c ./axio/gsensor.c ./axio/i2c.c ./axio/pwm.c
OTHER_SRC += ./axio/ao.c ./axio/ADC7001io.c ./axio/pi.c 
 
INCLUDE = -I./ -I./Components -I./Linux -I./codesys -I/home/jhzhou/sysroot-glibc-linaro-2.21-2017.10-arm-linux-gnueabi/usr/include/

CXX = $(CROSS_COMPILE)gcc
# TRG_X86 | TRG_PPC | TRG_ARM | TRG_CORTEX
CXXFLAGS = -DTRG_ARM

DEBFLAGS = -g
LDLIBS = -lpthread
CXXFLAGS += -DALIGNATTRIB= -DCDECL= -DHANDLE_WIN32_PRAGMA -DDLL_DECL= -D_REENTRANT= -DHUGEPTR= 
CXXFLAGS += -O0 -Wall -Wno-unused
CXXFLAGS += $(INCLUDE)
CXXFLAGS += -DLINUX
CXXFLAGS += $(DEBFLAGS)
CXXFLAGS += -fPIC
LDFLAGS += $(LDLIBS)

MAJORVER = 0
MINORVER = 1
SONAME = lib$(TARGET).so

SRC =  ./$(TARGET).c $(OTHER_SRC)
OBJ = $(SRC:.c=.o)

all: $(SONAME)

$(SONAME): ./$(TARGET)Dep.h ./$(TARGET)Itf.h $(OBJ)   
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $(OBJ) -lc -Wl,-soname,$(SONAME) -o $(SONAME)

.c.o: 
	$(CXX) -fPIC -c $(CXXFLAGS) -o $*.o $<
	

./$(TARGET)Itf.h: ./$(TARGET)Itf.m4
	rm -f $(OBJ)
	fromdos ./$(TARGET)Itf.m4
	m4 -I$(BUILDUTILS)/M4Defs Exports.m4 - < ./$(TARGET)Itf.m4 > ./$(TARGET)Itf.h

clean:
	rm -f $(OBJ) *~ core .depend $(SONAME)

cleanall: clean
	rm -f ./$(TARGET)Dep.h ./$(TARGET)Itf.h

.depend:
	$(CXX) $(CXXFLAGS) -M $(SRC) > $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif

