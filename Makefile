# Makefile for fswatch
# --------------------

SRC     = $(wildcard *.cc)
OBJ     = $(patsubst %.cc, %.o, $(SRC))
PRG     = fswatch
BINDIR ?= $$HOME/bin
TAR    ?= /tmp/fswatch.tar.gz
AUTHOR  = "Karel Kubat <karel@kubat.nl>"
URL     = "http://www.kubat.nl/pages/fswatch"
YEARS   = "2015 ff."
VER     = "1.12"

$(PRG): $(OBJ)
	c++ -g -o $(PRG) $(OBJ)
clean:
	rm -f $(OBJ) $(PRG)

dist: clean
	(cd .. && tar -c -v -z -f $(TAR) --exclude .git fswatch/)
	@echo
	@echo "Distribution ready as $(TAR)"

install: $(BINDIR)/$(PRG)

$(BINDIR)/$(PRG): $(PRG)
	mv $(PRG) $(BINDIR)/$(PRG)
	strip $(BINDIR)/$(PRG)

%.o: %.cc
	c++ -std=c++11 -g -c -Werror -Wall -DAUTHOR=\"$(AUTHOR)\" \
	    -DYEARS=\"$(YEARS)\" -DVER=\"$(VER)\" -DURL=\"$(URL)\" $<

usage.o: usage.cc Makefile

me:
	@true
a:
	@true
sandwich: install
