COMPILER    = gnu

program = wracer

source = \
main.c \
Faddeeva.c \
FNF.c 

obj = $(source:.c=.o)

# Standard Flags
CFLAGS := -std=gnu99

# Linker Flags
LDFLAGS = -lm

# Regular gcc Compiler
ifeq ($(COMPILER),gnu)
  CC = gcc
  LDFLAGS += 
  CFLAGS += -Ofast -ffast-math
endif

# intel Compiler
ifeq ($(COMPILER),intel)
  CC = icc
  LDFLAGS += 
  CFLAGS += -O3 -xhost -ansi-alias -no-prec-div -DINTEL -vec-report6
endif

$(program): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f wracer *.dat main.o Faddeeva.o FNF.o
run:
	./wracer
graph:
	gnuplot graph.gp
edit:
	vim -p main.c FNF.c
