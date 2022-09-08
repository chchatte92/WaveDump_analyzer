
EXE	=	wavedump_read

#CC	=	gcc
CC	=	g++

#COPTS	=	
COPTS	=	-fPIC -DLINUX -mavx -Wall
#COPTS	=	-g -fPIC -DLINUX -Wall

FLAGS	=	-Wall -s
#FLAGS	=	-Wall

# DEPLIBS	=       -l CAENVME -l CAENComm -l ncurses -lc -lm
# DEPLIBS	=       -L/usr/lib -L/usr/local/linuxvmeen/cct_modules -lvmedriver26 -lcctvmeen  -lpthread -lncurses -lc -lm
# DEPLIBS	=       -L/usr/local/linuxvmeen_util -lcctvmeen -L/usr/lib -lpthread -lncurses -lc -lm
#DEPLIBS	=       -L/usr/lib -lpthread -lrt -lncurses -lc -lm
# DEPLIBS	=       -L/usr/lib64 -lncurses -lc -lm
DEPLIBS	=       -L/usr/lib64 -lc -lm

LIBS	=	

INCLUDEDIR =	-I. -I/usr/include

# OBJS	=	uti.o daqsrt.o eeprom93C56.o spi_setup.o tdc_setup.o io_manager.o buffer_manager.o mydaq_sis3305.o
OBJS	=	uti.o adc_histos.o save_histos.o analyze_adc.o wavedump_read.o

#INCLUDES =	CAENVMElib.h CAENVMEtypes.h CAENVMEoslib.h console.h
#INCLUDES =	CAENComm.h

COPTS   += $(shell root-config --cflags)
DEPLIBS += $(shell root-config --glibs)

#########################################################################

all	:	$(EXE)

clean	:
		/bin/rm -f $(OBJS) $(EXE)

$(EXE)	:	$(OBJS)
		/bin/rm -f $(EXE)
		$(CC) $(FLAGS) -o $(EXE) $(OBJS) $(DEPLIBS)

$(OBJS)	:	$(INCLUDES) Makefile

%.o	:	%.cc
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

