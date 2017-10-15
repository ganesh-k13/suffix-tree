CHECK := $(shell which clang++)

ifeq ($(CHECK),)
$(warning No clang++ found, consider apt-get install clang, using g++ now)
CC = g++
else
$(info using clang++ over g++)
CC = clang++
endif

IDIR=include
ODIR=obj
SRCDIR=src
LDIR=lib

test:	$(ODIR)/test.o $(ODIR)/Node.o $(ODIR)/SuffixTree.o $(ODIR)/utils.o
		$(CC) -std=c++11 -o test -g $(ODIR)/test.o $(ODIR)/SuffixTree.o $(ODIR)/Node.o $(ODIR)/utils.o

$(ODIR)/test.o:	test.cpp 
	$(CC) -std=c++11 -w -o $(ODIR)/test.o -c test.cpp

$(ODIR)/Node.o:	$(SRCDIR)/Node.cpp $(IDIR)/Node.h
	$(CC) -std=c++11 -w -o $(ODIR)/Node.o -c $(SRCDIR)/Node.cpp
	
$(ODIR)/SuffixTree.o: $(SRCDIR)/SuffixTree.cpp $(IDIR)/SuffixTree.h $(ODIR)/Node.o
	$(CC) -std=c++11 -w -o $(ODIR)/SuffixTree.o  -g $(ODIR)/Node.o -c $(SRCDIR)/SuffixTree.cpp

$(ODIR)/utils.o: $(SRCDIR)/utils.cpp $(IDIR)/utils.h
	$(CC) -std=c++11 -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.cpp

clean:
	rm -f $(ODIR)/*.o
	rm test
	
slib: $(ODIR)/Node.o $(ODIR)/SuffixTree.o
	ar rcs $(LDIR)/libsuffix.a $(ODIR)/Node.o $(ODIR)/SuffixTree.o
