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

## How to work with the program

Put enciphered text in resources/encipheredText.txt

Run executable.

The decrypted text will be placed in resources/output.txt

## Author

* **Taras Koval** - *All work* - [TarasKoval](https://github.com/TarasKoval)

## License

No license - do what you want
