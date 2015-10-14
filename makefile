###########
#add new depend files below 
#add new ones here object files relating to .cpp files
DEPS=distDataServer.o

EXE=driver

#######################
#DO NOT EDIT BELOW
#######################

###########
#variables
###########
CC=g++
CPPFLAGS= -Wall -g -c -I./include/  -I/opt/comThrift/include -I/usr/local/include/thrift
CPPFLAGS+= -MD -MP -std=c++0x
LFLAGS= -Wall -L/opt/comThrift/ -lutils  -L/usr/local/lib -lthrift
VPATH=src

all: $(EXE)

debug: CC+= -DDEBUG -g 
debug: $(EXE)
###########
#linker
###########
$(EXE): $(DEPS)
	$(CC)  $(DEPS) $(LFLAGS) -o $(EXE).exe

##########
#implicit calls for all object file builds
#########

###########
#include dependency files 
###########
-include $(DEPS:%.o=%.d)

