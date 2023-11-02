# The name of the source files
SOURCES := main.c
SOURCES += action.c
SOURCES += expr.c
SOURCES += option.c
SOURCES += setter.c
SOURCES += when.c
SOURCES += strtable.c
SOURCES += symtable.c
SOURCES += utf8nop.c

SOURCES += lex_yy.c
SOURCES += y_tab.c

# The name of the executable
EXE = noematic

# Flags for compilation (adding warnings are always good)
CFLAGS := -Wall -Wno-unused-function -g

# Flags for linking (none for the moment)
LDFLAGS =

# Flags for lexer
LEXFLAGS =

# Libraries to link with (none for the moment)
LIBS =

# Use the GCC frontend program when linking
LD = gcc

ifeq ($(DEBUG), 1)
	CFLAGS += -DYYDEBUG=1
	LEXFLAGS += -d
endif

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

y_tab.c y_tab.h &: dlg.y
	yacc -d $< -Wcounterexamples -o y_tab.c

lex_yy.c: dlg.l
	$(LEX) $(LEXFLAGS) -t $< > $@

# Target to clean up after us
clean:
	-rm -f $(EXE)      # Remove the executable file
	-rm -f $(OBJECTS)  # Remove the object files
	-rm -f y_tab.c y_tab.h # Remove yacc files
	-rm -f lex_yy.c    # Remove lex file

# Finally we need to tell "make" what source and header file each object file depends on
main.o: main.c strtable.h symtable.h y_tab.h
action.o: action.h option.h setter.h when.h
expr.o: expr.c expr.h
option.o: option.c option.h action.h
setter.o: setter.c setter.h expr.h
when.o: when.c when.h action.h expr.h option.h
strtable.o: strtable.c strtable.h
symtable.o: symtable.c symtable.h
utf8nop.o: utf8.h
lex_yy.c: y_tab.h strtable.h symtable.h utf8.h
y_tab.c: when.h symtable.h
