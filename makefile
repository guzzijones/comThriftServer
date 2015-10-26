###########
#add new depend files below 
#add new ones here object files relating to .cpp files
DEPS=distDataServer.o dir.o

EXE=driver

#######################
#DO NOT EDIT BELOW
#######################

###########
#variables
###########
CC=g++
CPPFLAGS= -Wall -g -c -I./include/  -I/usr/local/include -I/opt/comThrift/include -I/usr/local/include/thrift -I/usr/share/boost_1_58_0/ 
CPPFLAGS+= -MD -MP -std=c++0x
LFLAGS= -Wall -L/opt/comThrift/ -lutils  -L/usr/local/lib -lthrift -L/usr/share/boost_1_58_0/lib/ -lboost_system -lboost_filesystem
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

