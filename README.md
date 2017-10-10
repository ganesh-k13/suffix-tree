# Suffix Tree

Suffix Tree (Ukkonene's) implementation written in C++.

### Prerequisites

* g++ version 6.3.0 or higher
* clang++ version 4.0.0-1ubuntu1 or higher

### Installing

First compile the project in your local system by:

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
        [TODO]
    
```

## Deployment

For using the Suffix Tree:

* Copy SuffixTree.h and Node.h header files to the location of your source file.
* Include SuffixTree.h and Node.h to your source file.
* Use SuffixTree.o and Node.o object files and compile your program:
 

## Built With

* [C++](http://www.cplusplus.com/) - The main backend used
* [clang](https://docs.python.org/3/) - Used for testing

## Authors

* **Ganesh K.** - [DarkFate13](https://github.com/DarkFate13)

## Acknowledgments

This is developed as an assignment for Advanced Algorithms Course.
This code is completely based on Geeks For Geeks implementation of Suffix tree using C.
I would like to thank Tushar Roy for his vides on Ukkonens implementation of Suffix Tree.