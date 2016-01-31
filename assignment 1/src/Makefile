#DONT USE THIS FILE FOR MAKE: INCOMPLETE

#Makefile for Compilers Lab project
#Author: Karthik Duddu

IDIR=include
CC=g++
CFLAGS=-I $(IDIR)
ODIR=obj

LDFLAGS=
LIBS=-lm
LIB_PATH=

SOURCES= lex.cpp basic_parser.cpp modified_parser.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=trial_compiler

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(ODIR)/$(OBJECTS) -o $@

.cpp:
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@