# Vigenere cipher 

### Target platform: Ubuntu 16.04

Language: C++11 compiled under GCC 5.4.0 using CMake 3.5.2

## Installing

In bash:

```
    cmake ./CMakeLists.txt
    make
```

The executable will be placed in "build" folder.

## Brief description

Works only with Russian characters (lowercase without spaces and punctuation marks).
Letter 'ё' was replaced with letter 'е'.

Features: 1. enciphering, 2. deciphering, 3. cryptanalysis.

Cryptanalysis consists of 2 steps.

First - uses the index of coincidence to calculate the key length.

Second - uses frequency analysis to calculate symbols of the key.

## Installing

### First step:

In bash:

```
    cmake CMakeLists.txt
```

Output (approximately):

```
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: pathToFolder
```

### Second step:

```
    make
```

Output (approximately):

```
[ 33%] Building CXX object CMakeFiles/Vigenere.dir/src/main.cpp.o
[ 66%] Building CXX object CMakeFiles/Vigenere.dir/src/functions.cpp.o
[100%] Linking CXX executable build/Vigenere
[100%] Built target Vigenere
```
Executable will be placed in build folder.

## How to work with the program

Put enciphered text in resources/encipheredText.txt

Run executable.

The decrypted text will be placed in resources/output.txt

## Author

* **Taras Koval** - *All work* - [TarasKoval](https://github.com/TarasKoval)

## License

No license - do what you want
