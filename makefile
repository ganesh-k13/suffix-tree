CC=clang++

IDIR=include
ODIR=obj
SRCDIR=src

test:	$(ODIR)/test.o $(ODIR)/Node.o $(ODIR)/SuffixTree.o $(ODIR)/utils.o
		$(CC) -o test -g $(ODIR)/test.o $(ODIR)/SuffixTree.o $(ODIR)/Node.o $(ODIR)/utils.o

$(ODIR)/test.o:	test.cpp 
	$(CC) -w -o $(ODIR)/test.o -c test.cpp

$(ODIR)/Node.o:	$(SRCDIR)/Node.cpp $(IDIR)/Node.h
	$(CC) -w -o $(ODIR)/Node.o -c $(SRCDIR)/Node.cpp
	
$(ODIR)/SuffixTree.o: $(SRCDIR)/SuffixTree.cpp $(IDIR)/SuffixTree.h $(ODIR)/Node.o
	$(CC) -w -o $(ODIR)/SuffixTree.o  -g $(ODIR)/Node.o -c $(SRCDIR)/SuffixTree.cpp

$(ODIR)/utils.o: $(SRCDIR)/utils.cpp $(IDIR)/utils.h
	$(CC) -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.cpp

clean:
	rm -f $(ODIR)/*.o
	rm test
