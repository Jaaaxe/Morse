/********************************************************
  *                MORSE CODE COMMUNICATORS              *
  Internet of Things | Challenge 02
  Student Name: Aishath Nahidha
  Student ID: S1900136
  
  *******************************************************/


#include "MicroBit.h"
#include "choose.h"
#include "defs.h"
#include "message.h"
#include "morseCharacter.h"

#include <vector>

MicroBit uBit;
extern bool sender, receiver;

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.display.scroll("MORSE");
    chooseSender();

    if(sender){
        uBit.display.print('S');
        
        bool receiverReady = false;
        int signalLength = 0;
        while (!receiverReady) {
            signalLength = signalReader();
            if(rangeChecker(signalLength, 100, 25)){
                uBit.display.scroll("1");
                receiverReady = true;
                generateCipherKey();
                sendMorse(cipherKey);
            }
        }

        bool morseEntered;
        int initialTime, deltaTime, row;
        std::vector<char> morseLetter;

        while(true){
            uBit.display.clear();
            //read current system time
            initialTime = system_timer_current_time();
            //Loop while button is is pressed
            while(uBit.buttonA.isPressed()){
                morseEntered = true;
            }
            //Calculate how long the button was pressed for, i.e. how long the loop executed for
            deltaTime = system_timer_current_time() - initialTime;
            //change this if condition to if(deltaTime > 50)
            if(morseEntered){
                if(deltaTime > 1000){
                    //todo, noise?
                }
                //dash
                else if(deltaTime > DASHPRESS){
                    for(int i = 0; i < 3; i++){
                        uBit.display.image.setPixelValue(i, row, 255);
                    }
                    row++;
                    morseLetter.push_back('-');
                }
                //dot
                else if(deltaTime > DOTPRESS){
                    uBit.display.image.setPixelValue(0, row, 255);
                    row++;
                    morseLetter.push_back('.');
                }
                morseEntered = false;

                if(uBit.buttonB.isPressed()){
                    morseLetter.push_back('|');
                    sendMorse(cipher(morseLetter));
                    morseLetter.clear();
                    uBit.display.clear();
                    row = 0;
                    uBit.display.print('>');
                    uBit.sleep(5000);
                }
                if(uBit.buttonAB.isPressed()){
                    sendSignal(SPACESIGNAL);
                }
            }
        }
    }

    if(receiver){
        uBit.display.print('R');
        sendSignal(100);

        int signalLength;
        bool cipherReceived = false;
        while(!cipherReceived){
            signalLength = signalReader();
            if(rangeChecker(signalLength, DOTSIGNAL, 25)){
                cipherKey.push_back('.');
            }else if(rangeChecker(signalLength, DASHSIGNAL, 25)){
                cipherKey.push_back('-');
            }else if(rangeChecker(signalLength, ENDMORSESIGNAL, 25)){
                cipherKey.push_back('|');
                cipherReceived = true;
                uBit.display.scroll("READY");
                uBit.display.clear();
            }
        } 

        std::vector<char> morseLetter;\
        while(true){
            signalLength = signalReader();
            if(rangeChecker(signalLength, SPACESIGNAL, 25)){
                uBit.display.clear();
                uBit.display.printChar('_');
            }else if(rangeChecker(signalLength, DOTSIGNAL, 25)){
                morseLetter.push_back('.');
            }else if(rangeChecker(signalLength, DASHSIGNAL, 25)){
                morseLetter.push_back('-');
            }else if(rangeChecker(signalLength, ENDMORSESIGNAL, 25)){
                char ASCII = morseToASCII(cipher(morseLetter));
                uBit.display.clear();
                uBit.display.printChar(ASCII);
                morseLetter.clear();
            }
        }          
    }

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    //release_fiber();
}

