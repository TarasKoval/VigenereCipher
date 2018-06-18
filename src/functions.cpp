#include "../include/functions.h"

void readAbc(std::map<std::string, int> &renamingMap, const std::string &path) {

    std::string rawData = readRawData(path);
    unsigned long dataLength = rawData.length();

    if (dataLength != doubledAlphabetLength) {
        std::cerr << "dataLength is not " << doubledAlphabetLength << " (size of russian abc x2)" << std::endl;
        exit(3);
    }

    std::string tempStr;
    int tempInt = 0;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        renamingMap.emplace(tempStr, tempInt++);
    }
}

void readAbcReverse(std::map<int, std::string> &renamingMap, const std::string &path) {

    std::string rawData = readRawData(path);
    unsigned long dataLength = rawData.length();

    if (dataLength != doubledAlphabetLength) {
        std::cerr << "dataLength is not " << doubledAlphabetLength << " (size of russian abc x2)" << std::endl;
        exit(3);
    }

    std::string tempStr;
    int tempInt = 0;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        renamingMap.emplace(tempInt++, tempStr);
    }
}

std::string readRawData(const std::string &path) {
    std::ifstream inputStream(path, std::ios::binary);
    if (!inputStream.is_open()) {
        std::cerr << "error opening text file" << std::endl;
        exit(1);
    }

    std::string rawData((std::istreambuf_iterator<char>(inputStream)),
                        std::istreambuf_iterator<char>());

    char charsToDelete[] = "\n\t";
    for (unsigned int i = 0; i < strlen(charsToDelete); ++i) {
        rawData.erase(std::remove(rawData.begin(), rawData.end(), charsToDelete[i]), rawData.end());
    }

    inputStream.close();
    return rawData;
}

void outputData(const std::vector<std::string> &finalData, const std::string &path) {
    std::ofstream outputStream(path, std::ios::binary);
    if (!outputStream.is_open()) {
        std::cerr << "error opening output file" << std::endl;
        exit(1);
    }

    for (const auto &iter : finalData) {
        outputStream << iter;
    }

    outputStream.close();
}

std::vector<int> encrypt(const std::vector<int> &plainText, const std::vector<int> &key) {
    std::vector<int> outputVector;
    unsigned long keyLength = key.size();

    int i = 0;
    for (auto iter : plainText) {
        outputVector.push_back((iter + key[i++ % keyLength]) % alphabetLength);
    }
    return outputVector;
}

std::vector<int> decrypt(const std::vector<int> &plainText, const std::vector<int> &key) {
    std::vector<int> tempKey;
    for (auto iter : key) {
        tempKey.push_back(iter);
    }

    for (auto &tempIter : tempKey) {
        tempIter = alphabetLength - tempIter;
    }

    return encrypt(plainText, tempKey);
}

std::vector<int> utf16ToInt(const std::string &rawData) {
    unsigned long dataLength = rawData.length();

    if (dataLength % 2 != 0) {
        std::cerr << "data is not %2" << std::endl;
        exit(2);
    }

    std::vector<int> outputVector;
    std::map<std::string, int> renamingMap;
    readAbc(renamingMap, "../resources/abc.txt");

    std::string tempStr;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        if (tempStr == "ё") {
            tempStr = "е";
        }
        auto findIter = renamingMap.find(tempStr);
        if (findIter == renamingMap.end()) {
            // not found
            std::cerr << "didn't find string in renamingMap: " << tempStr << std::endl;
        } else {
            // found
            outputVector.push_back(findIter->second);
        }
    }
    return outputVector;
}

std::vector<std::string> intToUtf16(const std::vector<int> &vectorInt) {
    std::map<int, std::string> renamingMapReverse;
    readAbcReverse(renamingMapReverse, "../resources/abc.txt");

    std::vector<std::string> vectorDecryptedData;

    std::string tempStr;
    for (auto iter : vectorInt) {
        auto findIter = renamingMapReverse.find(iter);
        if (findIter == renamingMapReverse.end()) {
            // not found
            std::cerr << "didn't find string in renamingMapReverse: " << tempStr << std::endl;
        } else {
            // found
            vectorDecryptedData.push_back(findIter->second);
        }
    }
    return vectorDecryptedData;
}

std::map<int, int> createCharMap(const std::vector<int> &inputData) {
    std::map<int, int> charMap;

    for (auto iter : inputData) {
        auto findIter = charMap.find(iter);
        if (findIter == charMap.end()) {
            // not found
            charMap.emplace(iter, 1);
        } else {
            // found
            findIter->second++;
        }
    }
    return charMap;
}

double calcIndexOfCoincidence(const std::vector<int> &inputData) {
    double dataLength = inputData.size();
    if (dataLength <= 1) {
        std::cout << "from calcIndexOfCoincidence: data length <= 1: " << dataLength << std::endl;
        exit(4);
    }

    auto charMap = createCharMap(inputData);

    double sum = 0;
    for (auto &iter : charMap) {
        sum += iter.second * (iter.second - 1);
    }

    double matchingIndex = sum / dataLength / (dataLength - 1);
    return matchingIndex;
}

unsigned long calcKeyLength(const std::vector<int> &inputData) {
    std::vector<int> sliceVector;
    const unsigned long size = inputData.size();
    const auto russianIndexOfCoincidence = 0.056378;

    unsigned long closestKey = 0;
    double closestDifference = 1;
    for (unsigned long step = 2; step < 30; step++) {
        sliceVector.clear();
        for (unsigned long i = step; i < size; i += step) {
            sliceVector.push_back(inputData.at(i));
        }
        auto tempIndex = calcIndexOfCoincidence(sliceVector);
        auto difference = fabs(tempIndex - russianIndexOfCoincidence);
        if (difference < closestDifference) {
            closestKey = step;
            closestDifference = difference;
        }
    }

    return closestKey;
}

std::vector<int> decryptKey(std::vector<int> &encryptedData, unsigned long keyLength) {
    std::vector<int> mainKey;
    auto dataLength = encryptedData.size();
    for (unsigned long iter = 0; iter < keyLength; iter++) {
        std::vector<int> tempVector;
        for (unsigned long i = iter; i < dataLength; i += keyLength) {
            tempVector.push_back(encryptedData[i]);
        }
        auto tempKey = bestShift(tempVector);
        mainKey.push_back(tempKey);
    }
    return mainKey;
}

int bestShift(const std::vector<int> &inputData) {
    std::vector<unsigned int> localFrequency(alphabetLength, 0);

    for (auto iter : inputData) {
        localFrequency[iter]++;
    }

    double temp, fit, sum = 0, bestFit = std::numeric_limits<double>::max();
    int bestShift = 0;

    for (int i = 0; i < alphabetLength; i++) {
        sum += localFrequency[i];
    }

    for (int shift = 0; shift < alphabetLength; shift++) {
        fit = 0;
        for (int i = 0; i < alphabetLength; i++) {
            temp = localFrequency[(i + shift) % alphabetLength] / sum - perfectLetterFrequency[i];
            fit += temp * temp / perfectLetterFrequency[i];
        }

        if (fit < bestFit) {
            bestFit = fit;
            bestShift = shift;
        }
    }

    return bestShift;
}
