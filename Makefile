CC := clang
CFLAGS := -g -Wall -D IN_DEV

BUILDDIR := ./server/build
INCLUDE := ./server/include
SRC := ./server/src
OUTPUT := output

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
