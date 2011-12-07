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

Install
-------

    cc [-o name] -lm spark.c
    
where cc is your C compiler command. Or use whatever C compiler option you want.
Tested under gcc 4.4.3 and clang 1.1 under Ubuntu 10.04.

TODO
----

* Use actual Unicode block fractions instead of numbers
* Proper error handling
* Tests
* Modularise code
* Help text
* Investigate locale dependency of strtod
* Investigate C99 effects to strtod (hexadecimal numbers + NaN + Infinity)
