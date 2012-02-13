spark.c
=======

A C implementation of [spark](https://github.com/holman/spark). Very much work
in progress.

Usage
-----

./spark NUMBERS

NUMBERS is a list of decimal numbers (or hexadecimal if compiled with
C99) with arbitrary seperators. Anything can be used to seperate items in the
list as long as it is not a digit, "+", "-", "e", "E" or your locales decimal
point ("." in English ones).

The two following examples give the same result:

    ./spark 2 3 1 12
    ./spark 2.00fgt+3,1 1.2e1

Build
-----

    make  # will run something like cc -o spark -lm spark.c

where cc is your C compiler command. Or use whatever C compiler option you want.
Tested under:

  - gcc 4.4.3 and clang 1.1 (Ubuntu 10.04)
  - gcc 4.6.2 and clang 2.9 (Fedora 16)

TODO
----

* Proper error handling
* Tests
* Help text
* Investigate locale dependency of strtod
* Investigate C99 effects to strtod (hexadecimal numbers + NaN + Infinity)
