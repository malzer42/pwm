# ----------------------------------------------------------------
# Makefile : for pos_weight_mat Cpp-src
#
# The CURSES variable defines the BSD curses library is being used.
# The LIBS variable defines the C libraries to link with.
# The SOURCES variable defines the C sources
# The OBJS variables define the object files.
#
# The C sources are compiled with flags as described by CFLAGS.
# ----------------------------------------------------------------

LIBS = -lstdc++ # OS/2

WITH_CURSES = no

ifeq ($(WITH_CURSES),yes)
  LIBS = -lstdc++ -lcurses -ltermcap
else
  LIBS = -lstdc++
endif

# ------- Source Files are Listed Here ---------------------------

SOURCES = pos_weight_mat.cpp argument.cpp sum.pp site_spec.cpp \
		  title.cpp message.cpp printVector.cpp matrix.cpp split.cpp \
		  print.cpp pwm.cpp position.cpp threshold.cpp factor.cpp version.cpp

# ------- Object Files are the same as Sources -------------------

OBJS    = pos_weight_mat.o argument.o sum.o title.o message.o split.o site_spec.o \
	      printVector.o matrix.o print.o pwm.o position.o threshold.o factor.o version.o

# ------- Compiler flags and things ------------------------------

FLAGS = 2>>err
DEBUG =    -ggdb
WARNINGS = -Wall
         # -W -Wcast-qual -Wcast-align \
         # -Wmissing-prototypes \
         # -Wmissing-declarations \
         # -Wnested-externs \
         # -Wstrict-prototypes
         # -Wconversion \
         # -Wredundant-decls
OPTIMIZE =   -O0
PROFILE  = # -pg
BOUNDS   = # -fbounds-checking
FLOAT0   = # -ffloat-store
           # Do not store floating point variables in registers, and
           # inhibit other options that might change whether a floating
           # point value is taken from a register or memory.
FLOAT1   = # -mieee-fp
           # Control whether or not the compiler uses IEEE floating
           # point comparisons.  These handle correctly the case where
           # the result of a comparison is unordered.
FLOAT2   = # -mwide-multiply
           # Control whether GNU CC uses the @code{mul} and @code{imul}
           # that produce 64 bit results in @code{eax:edx} from 32 bit
           # operands to do @code{long long} multiplies and 32-bit
           # division by constants.
FAST     = # -ffast-math
           # This option allows GCC to violate some ANSI or IEEE rules
           # and/or specifications in the interest of optimizing code
           # for speed.  For example, it allows the compiler to assume
           # arguments to the @code{sqrt} function are non-negative
           # numbers and that no floating-point values are NaNs.
CODE0    = # -mcpu=pentium
CODE1    = # -march=pentium
CFLAGS =  ${OPTIMIZE} ${DEBUG}  ${WARNINGS} ${BOUNDS} ${PROFILE} \
          ${FLOAT0}   ${FLOAT1} ${FLOAT2}   ${CODE0}  ${CODE1} ${FAST}
# CC = gcc-3.3 -Wno-deprecated # -fguiding-decls
CC = g++-7 -std=c++17 -Wno-deprecated # -fguiding-decls
O  = .o

%.o: %.cpp
	$(CC) -c $(FLAGS) $(CFLAGS) $<

# ------- The real makecoy ---------------------------------------
all: clean drop
	@echo Done
	@echo Congratulation the program has been created successfully
	@echo Weldone

clean:
	rm -f err

# ---------------------------------------------------------------
# Compile sources
# ---------------------------------------------------------------

drop: ${OBJS}
	${CC} -o xpos_weight_mat ${CFLAGS} ${FLAGS} ${OBJS} ${LIBS}

pos_weight_mat$(O) : pos_weight_mat.cpp pos_weight_mat.h

sum$(O) : sum.cpp sum.h 

title$(O) : title.cpp title.h 

message$(O) : message.cpp message.h 

printVector$(O) : printVector.cpp  printVector.h 

argument$(O) : argument.cpp argument.h

matrix$(O) : matrix.cpp matrix.h

print$(O) : print.cpp print.h

pwm$(O) : pwm.cpp pwm.h

position$(O): position.cpp position.h

threshold$(O): threshold.cpp threshold.h

factor$(O): factor.cpp factor.h

version$(O): version.cpp version.h

split$(O): split.cpp split.h

site_spec$(O): site_spec.cpp site_spec.h
