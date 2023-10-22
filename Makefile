# The name of the source files
SOURCES := main.c
SOURCES += storage.c
SOURCES += symtable.c

SOURCES += lex.yy.c
SOURCES += y.tab.c

# The name of the executable
EXE = noematic

# Flags for compilation (adding warnings are always good)
CFLAGS = -Wall -Wno-unused-function -g -DYYDEBUG=1

# Flags for linking (none for the moment)
LDFLAGS =

# Libraries to link with (none for the moment)
LIBS =

# Use the GCC frontend program when linking
LD = gcc

# This creates a list of object files from the source files
OBJECTS = $(SOURCES:%.c=%.o)

# The first target, this will be the default target if none is specified
# This target tells "make" to make the "all" target
default: all

# Having an "all" target is customary, so one could write "make all"
# It depends on the executable program
all: $(EXE)

# This will link the executable from the object files
$(EXE): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o  $(EXE) $(LIBS)

# This is a target that will compiler all needed source files into object files
# We don't need to specify a command or any rules, "make" will handle it automatically
%.o: %.c
	$(CC) $(CFLAGS) -c $<

y.tab.c y.tab.h: dlg.y
	yacc -d $< -Wcounterexamples

lex.yy.c: dlg.l
	$(LEX) -d $<

# Target to clean up after us
clean:
	-rm -f $(EXE)      # Remove the executable file
	-rm -f $(OBJECTS)  # Remove the object files
	-rm -f y.tab.c y.tab.h # Remove yacc files
	-rm -f lex.yy.c    # Remove lex file

# Finally we need to tell "make" what source and header file each object file depends on
main.o: main.c storage.h y.tab.h
storage.o: storage.c storage.h
idtable.o: idtable.c idtable.h
lex.yy.c: y.tab.h
