
ARCH=arm
CROSS_COMPILE=arm-linux-gnueabi-

TARGET = test_nbIot
OTHER_SRC = ./test_uart.c ./app_config.c ./nbxx_01_app.c  ./lierda_server.c ./nbxx_01_udp.c

INCLUDE += -I./ -I/home/jhzhou/sysroot-glibc-linaro-2.21-2017.10-arm-linux-gnueabi/usr/include/
INCLUDE += -I../kernel_am437x/include/

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

SRC =  $(OTHER_SRC)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET):  $(OBJ)   
	$(CXX) -static $(CXXFLAGS) $(LDFLAGS) $(OBJ) -lc -o $(TARGET)

.c.o: 
	$(CXX) -fPIC -c $(CXXFLAGS) -o $*.o $<
	

clean:
	rm -f $(OBJ) *~ core .depend $(TARGET)

.depend:
	$(CXX) $(CXXFLAGS) -M $(SRC) > $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif

