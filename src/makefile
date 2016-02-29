CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=Agent.cpp Controller.cpp Log.cpp Main.cpp signalHandler.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
EXEC=quadcopter

all: $(EXEC)

$(EXEC): $(OBJS)
    $(CXX) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
    rm -f ./.depend
    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
    $(RM) $(OBJS)

dist-clean: clean
    $(RM) *~ .depend

include .depend