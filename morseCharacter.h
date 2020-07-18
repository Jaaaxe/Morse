#ifndef MORSECHARACTER_H
#define MORSECHARACTER_H

#include <vector>
 extern std::vector<char> cipherKey;
 
 void generateCipherKey();
 std::vector<char> cipher(std::vector<char> morseInput);
 char morseToASCII(std::vector<char> morse);

#endif
