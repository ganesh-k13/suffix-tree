# Suffix Tree

Suffix Tree (Ukkonen's) implementation written in C++.

### Prerequisites

* g++ version 6.3.0 or higher
* clang++ version 4.0.0-1ubuntu1 or higher

### Installing

First compile the project on your local system by:

```
make clean
make
```
For testing if it works, see Running tests below

## Running Tests

For manual tests, run:

``` 
./test [OPTION]... [PARAMETERS]...

OPTIONS:
    -1 [QUERY]...
        Get all occurences of the query in the document as [TITLE] ... <Sorrounding 80 characters> ... 
    -2 [QUERY]...
        Get first occurences of the query or it's Longest Common Subsequence(LCS) as [TITLE] ... <Sorrounding 80 characters> ... 
    -3 [QUERY]...
        Get the top 5 documents based on relevence with the query.
    
EXAMPLE:
	./test -3 cats in the cradle and the silver spoon
```

## Deployment

For using the Suffix Tree:

* Copy SuffixTree.h and Node.h header files to the location of your source file.
* Include SuffixTree.h and Node.h to your source file.
* Use SuffixTree.o and Node.o object files and compile your program:
 
Alternative (recommended):

```
make clean
make slib
```

Copy the libsuffix.a from lib folder and use it as static library.


## Built With

* [C++](http://www.cplusplus.com/) - The main backend used

## Authors

* **Ganesh K.** - [DarkFate13](https://github.com/DarkFate13)

## Acknowledgments

* This is developed as an assignment for Advanced Algorithms Course.
* I would like to thank my professors, Prof. NS Kumar and Prof. Channa Bankapur for their valuable advice.
* This code is based on Geeks For Geeks implementation of [Suffix tree](http://www.geeksforgeeks.org/generalized-suffix-tree-1/) using C.
* I would like to thank [Tushar Roy](https://www.youtube.com/user/tusharroy2525) for his [video](https://www.youtube.com/watch?v=aPRqocoBsFQ) on Ukkonens implementation of Suffix Tree.