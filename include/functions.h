#ifndef CHARACTER_PROCESSING_FUNCTIONS_H
#define CHARACTER_PROCESSING_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstring>

const int alphabetLength = 32;
const int doubledAlphabetLength = alphabetLength * 2;

const std::array<double, alphabetLength> perfectLetterFrequency = {0.0750, 0.0201, 0.0433, 0.0172,
                                                                   0.0309, 0.0870, 0.0101, 0.0148,
                                                                   0.0709, 0.0121, 0.0330, 0.0496,
                                                                   0.0310, 0.0670, 0.1107, 0.0247,
                                                                   0.0433, 0.0497, 0.0597, 0.0222,
                                                                   0.0021, 0.0095, 0.0039, 0.0140,
                                                                   0.0072, 0.0030, 0.0002, 0.0236,
                                                                   0.0184, 0.0036, 0.0047, 0.0196};

void readAbc(std::map<std::string, int> &renamingMap, const std::string &path);

void readAbcReverse(std::map<int, std::string> &renamingMap, const std::string &path);

std::string readRawData(const std::string &path);

void outputData(const std::vector<std::string> &finalData, const std::string &path);

std::vector<int> encrypt(const std::vector<int> &plainText, const std::vector<int> &key);

std::vector<int> decrypt(const std::vector<int> &plainText, const std::vector<int> &key);

std::vector<int> utf16ToInt(const std::string &rawData);

std::vector<std::string> intToUtf16(const std::vector<int> &vectorInt);

std::map<int, int> createCharMap(const std::vector<int> &inputData);

double calcIndexOfCoincidence(const std::vector<int> &inputData);

unsigned long calcKeyLength(const std::vector<int> &inputData);

std::vector<int> decryptKey(std::vector<int> &encryptedData, unsigned long keyLength);

int bestShift(const std::vector<int> &inputData);

template<typename T>
void outputVector(const std::vector<T> &data) {
    for (const auto &iter : data) {
        std::cout << iter;
    }
    std::cout << std::endl;
}

#endif //CHARACTER_PROCESSING_FUNCTIONS_H
