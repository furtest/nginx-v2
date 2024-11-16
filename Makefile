BUILDDIR := ./server/build
INCLUDE := ./server/include
SRC := ./server/src
OUTPUT := output

CC := clang
CFLAGS := -g -Wall -I $(INCLUDE) -D IN_DEV

SRCFILES := $(shell ls $(SRC))
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRCFILES))

all: $(BUILDDIR) $(OUTPUT)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -f $(BUILDDIR)/*.o
	rm -rf $(BUILDDIR)
	rm -f $(OUTPUT)
