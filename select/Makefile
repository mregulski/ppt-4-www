CC = gcc
CFLAGS = -Wall -c -g
OBJDIR = bin
SRCDIR = src
OBJS = $(addprefix $(OBJDIR)/, test.o select.o sort.o median.o)
UTIL = $(OBJDIR)/util.o
SORT = $(OBJDIR)/sort.o

all: $(OBJS) $(UTIL)
	$(CC) $(OBJS) $(UTIL) -o $(OBJDIR)/select

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(UTIL): ../sort/src/util.c
	$(CC) $(CFLAGS) $< -c -o $(UTIL)

$(SORT): ../sort/src/quickSort.c
	$(CC) $(CFLAGS) -c ../sort/src/quickSort.c -o $(OBJDIR)/sort.o

$(OBJS): $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*
