#include "MicroBit.h"
#include "morseCharacter.h"
#include "defs.h"

#include <vector>


std::vector<char> cipherKey;

void generateCipherKey()
{
    uBit.display.scroll("2");
    cipherKey.clear();

    bool morseEntered;
    int initialTime, deltaTime;
    int row = 0;
    uBit.display.clear();
    
    uBit.display.scroll("5");
    while(row != 5) {
        //read current system time
        initialTime = system_timer_current_time();
        //Loop while button is is pressed
        while(uBit.buttonA.isPressed()) {
            morseEntered = true;
        }
        //Calculate how long the button was pressed for, i.e. how long the loop executed for
        deltaTime = system_timer_current_time() - initialTime;
        //change this if condition to if(deltaTime > 50)
        if(morseEntered) {
            if(deltaTime > 1000) {
                //todo, noise?
            }
            //dash
            else if(deltaTime > DASHPRESS) {
                for(int i = 0; i < 3; i++) {
                    uBit.display.scroll("7");
                    uBit.display.image.setPixelValue(i, row, 255);
                }
                row++;
                cipherKey.push_back('-');
            }
            //dot
            else if(deltaTime > DOTPRESS) {
                uBit.display.scroll("6");
                uBit.display.image.setPixelValue(0, row, 255);
                row++;
                cipherKey.push_back('.');
            }
            morseEntered = false;
        }
    }

    cipherKey.push_back('|');
    uBit.display.scroll("3");
    return;
}

std::vector<char> cipher(std::vector<char> morseInput)
{
    std::vector<char> morseOutput;
    for (int i = 0; i < morseInput.size(); i++) {
        if(morseInput.at(i) == '|') {
            morseOutput.at(i) = '|';
        } else if(morseInput.at(i) == cipherKey.at(i)) {
            morseOutput.at(i) = '.';
        } else {
            morseOutput.at(i) = '-';
        }
    }
    return morseOutput;
}

const char *ASCII = "##ETIANMSURWDKGOHVF#L#PJBXCYZQ##54#3###2##+####16=/#####7###8#90";

char morseToASCII(std::vector<char> morse)
{
    int index = 1;
    for(int i = 0; i < morse.size(); i++) {
        if(morse[i] == '.') {
            index = index<<1;
        } else if(morse[i] == '-') {
            index = index << 1;
            index = index | 1;
        }
    }
    return ASCII[index];
}
