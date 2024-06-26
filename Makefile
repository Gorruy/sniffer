CC = gcc

CFLAGS = -O2 -Wall

SNFRLDFLAGS = -lpthread -lrt
RPSTLDFLAGS = -lrt

SRCDIR = src/
RPSTSRCDIR = src/representer/
BINDIR = bin/
TESTDIR = tests/
BUILDDIR = build/
INCLDIR = include/

prefix = /usr/local

SNFRSRCS = $(wildcard $(SRCDIR)sniffer/*.c)
RPSTSRCS = $(wildcard $(SRCDIR)representer/*.c)
TESTSRCS = $(wildcard $(TESTDIR)*.c)

SNFROBJS := $(SNFRSRCS:$(SRCDIR)sniffer/%.c=$(BUILDDIR)sniffer/%.o)
RPSTOBJS := $(RPSTSRCS:$(SRCDIR)representer/%.c=$(BUILDDIR)representer/%.o)
TESTOBJS := $(TESTSRCS:$(TESTDIR)%.c=$(BUILDDIR)tests/%.o)

all: build

build: $(BUILDDIR) $(BINDIR) sniffer representer

sniffer: $(SNFROBJS)
	$(CC) $(CFLAGS) -I./$(INCLDIR) $^ -o $(BINDIR)$@ $(SNFRLDFLAGS)

representer: $(RPSTOBJS)
	$(CC) $(CFLAGS) -I./$(INCLDIR) $^ -o $(BINDIR)$@ $(RPSTLDFLAGS)

$(BUILDDIR)sniffer/%.o: $(SRCDIR)sniffer/%.c
	$(CC) $(CFLAGS) -I./$(INCLDIR) -c $< -o $@
$(BUILDDIR)representer/%.o: $(SRCDIR)representer/%.c
	$(CC) $(CFLAGS) -I./$(INCLDIR) -c $< -o $@
$(BUILDDIR)tests/%.o: $(TESTDIR)%.c
	$(CC) $(CFLAGS) -I./$(INCLDIR) -c $< -o $@

$(BINDIR):
	@mkdir -p $(BINDIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)sniffer $(BUILDDIR)representer $(BUILDDIR)tests

install: build
	install -D $(BINDIR)sniffer \
		$(DESTDIR)$(prefix)/bin/sniffer & \
	install -D $(BINDIR)representer \
		$(DESTDIR)$(prefix)/bin/representer

load: CFLAGS += -DLOAD
load: tests

tests: clean CFLAGS += -DDEBUG -ggdb3 -fno-omit-frame-pointer
tests: build $(TESTOBJS)
	$(CC) -I./$(INCLDIR) $(CFLAGS) $(TESTOBJS) $(filter-out $(BUILDDIR)sniffer/main.o, $(SNFROBJS)) \
		$(SNFRLDFLAGS) -o $(BINDIR)$@;
	./tests/run_tests.sh;

clean:
	rm -rf ${BUILDDIR}

trueclean: clean
	rm -rf $(BINDIR)

.PHONY: clean trueclean all install build tests load
	