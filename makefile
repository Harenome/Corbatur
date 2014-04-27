CC = g++

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_ORB = orb
PATH_IDL = idl
PATH_LOG = logs
PATH_TEST = tests
PATH_INCLUDE = include

PATH_OMNIORB = omniORB-4.1.7
PATH_OMNIORB_LIB = $(PATH_OMNIORB)/lib
PATH_OMNIORB_INCLUDE = $(PATH_OMNIORB)/include

FLAGS_CC = -std=c++98 -pedantic -Wall -g
FLAGS_LIB = -L$(PATH_OMNIORB_LIB) -L$(PATH_LIB) -lomniORB4 -lomnithread -lomniDynamic4
FLAGS_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_OMNIORB_INCLUDE) -I$(PATH_ORB)

OMNIIDL = $(PATH_OMNIORB)/bin/omniidl

vpath %.idl $(PATH_IDL)
vpath %.hpp $(PATH_INCLUDE)
vpath %.cpp $(PATH_SRC)
vpath %.hh $(PATH_ORB)
vpath %SK.cc $(PATH_ORB)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)

all: client server main

%.hh: %.idl | orb_dir
		$(OMNIIDL) -bcxx -C $(PATH_ORB) $<

%.o: %.cpp | obj_dir
		$(CC) $(FLAGS_CC) $(FLAGS_INCLUDE) -o $(PATH_OBJ)/$@ -c $<

corbatur.hh: corbatur.idl

corbaturSK.o: corbatur.hh | obj_dir
		$(CC) $(FLAGS_CC) $(FLAGS_INCLUDE) -o $(PATH_OBJ)/$@ -c $(PATH_ORB)/corbaturSK.cc

contact.o: contact.cpp contact.hpp
contact_manager.o: contact_manager.cpp contact_manager.hpp
corbatur_impl.o: corbatur_impl.cpp corbatur_impl.hpp contact_manager.hpp corbatur.hh
server.o: server.cpp server.hpp contact.hpp contact_manager.hpp corbatur.hh corbatur_impl.hpp
client.o: client.cpp client.hpp corbatur.hh
parser.o: parser.cpp parser.hpp
run_client.o: run_client.cpp
run_server.o: run_server.cpp
main.o: main.cpp

main: main.o libcorbatur.a | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o -lcorbatur

client: libcorbatur.a run_client.o | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/$@ $(PATH_OBJ)/run_client.o -lcorbatur

server: libcorbatur.a run_server.o | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/$@ $(PATH_OBJ)/run_server.o -lcorbatur
libcorbatur.a: parser.o contact.o contact_manager.o corbatur_impl.o server.o client.o corbaturSK.o | lib_dir
		ar -crv $(PATH_LIB)/libcorbatur.a $(PATH_OBJ)/parser.o $(PATH_OBJ)/contact.o $(PATH_OBJ)/contact_manager.o $(PATH_OBJ)/server.o $(PATH_OBJ)/corbatur_impl.o $(PATH_OBJ)/client.o $(PATH_OBJ)/corbaturSK.o
		ranlib $(PATH_LIB)/libcorbatur.a

omniorb_extract:
		@tar -xf omniORB-4.1.7.tar.bz2

omniorb: omniorb_extract
		cd $(PATH_OMNIORB) && ./configure && make

doc: clean_doc
		@doxygen

orb_dir:
		@mkdir -p $(PATH_ORB)

obj_dir:
		@mkdir -p $(PATH_OBJ)

bin_dir:
		@mkdir -p $(PATH_BIN)

lib_dir:
		@mkdir -p $(PATH_LIB)

clean:
		@rm -rf $(PATH_ORB) $(PATH_OBJ) $(PATH_LIB) $(PATH_BIN)

clean_doc:
		@rm -rf $(DPATH)

clean_omniorb:
		@cd $(PATH_OMNIORB)
		@make clean

clean_all: clean clean_doc clean_omniorb
		@echo "Clean."

archive:
		@tar -cvzf $(shell basename `pwd`).tar.gz $(PATH_SRC) $(PATH_INCLUDE) makefile AUTHORS COPYING LICENSE README README.md
