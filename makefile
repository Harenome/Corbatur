CC = g++

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_ORB = orb
PATH_TEST = tests
PATH_INCLUDE = include

PATH_OMNIORB = omniORB-4.1.7
PATH_OMNIORB_LIB = $(PATH_OMNIORB)/lib
PATH_OMNIORB_INCLUDE = $(PATH_OMNIORB)/include

FLAGS_CC = std=c++11 -pedantic -Wall -g
FLAGS_LIB = -L$(PATH_OMNIORB_LIB) -lomniORB4 -lomnithread -lomniDynamic4
FLAGS_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_OMNIORB_INCLUDE)

OMNIIDL = $(PATH_OMNIORB)/bin/omniidl

vpath %.cpp $(PATH_SRC)
vpath %.hpp $(PATH_INCLUDE)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)
vpath %.hh $(PATH_ORB)
vpath %SK.cc $(PATH_ORB)

%.o: %.cpp | obj
		$(CC) $(FLAGS_CC) -o $(PATH_OBJ)/$@ -c $< $(FLAGS_INCLUDE)

%.hh: %.idl | orb
		$(OMNIIDL)

omniorb_extract:
		@tar -xf omniORB-4.1.7.tar.bz2

omniorb: omniorb_extract
		cd $(PATH_OMNIORB) && ./configure && make

doc: clean_doc
		@doxygen

orb:
		@mkdir -p $(PATH_ORB)

obj:
		@mkdir -p $(PATH_OBJ)

bin:
		@mkdir -p $(PATH_BIN)

lib:
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
