#
# The following environment variable(s) should be predefined:
#
# CXX
# CXX_OPTS

#
# The following environment variable(s) can be predefined
#
# DEBUG: run in debug mode, printing additional information

#
# Set paths for various files
#

ST = sparsetiling
LIB = lib
OBJ = obj
DEMOS = demos
BIN = bin

ST_SRC = $(ST)/src
ST_INC = $(ST)/include
ST_BIN = $(BIN)/sparsetiling
ST_DEMOS = $(DEMOS)/sparsetiling

#
# Compiler settings
#

CXX      := $(CXX)
CXXFLAGS := -O3 -std=c++0x $(VTK_ON) $(CXX_OPTS)


.PHONY: clean mklib

all: clean mklib sparsetiling demos

mklib:
	@mkdir -p $(LIB) $(OBJ) $(ST_BIN)/airfoil

sparsetiling: mklib
	@echo "Compiling the library"
	$(CXX) $(CXXFLAGS) -I$(ST_INC) -c $(ST_SRC)/inspector.cpp -o $(OBJ)/inspector.o
	ar -r $(LIB)/libst.a $(OBJ)/inspector.o
	ranlib $(LIB)/libst.a

demos: mklib
	@echo "Compiling demos"
	$(CXX) $(CXXFLAGS) -I$(ST_INC) $(ST_DEMOS)/airfoil/airfoil.cpp -o $(ST_BIN)/airfoil/airfoil -lrt

clean:
	-rm -if $(OBJ)/*.o
	-rm -if $(OBJ)/*~
	-rm -if $(LIB)/*.a
	-rm -if $(LIB)/*.so
	-rm -if $(ST_SRC)/*~
	-rm -if $(ST_INC)/*~
	-rm -if $(ST_DEMOS)/airfoil/*~
	-rm -if $(ST_BIN)/airfoil_*
