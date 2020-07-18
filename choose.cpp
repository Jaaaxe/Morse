#include "choose.h"
#include "MicroBit.h"
#include "defs.h"
#include "MicroBit.h"
MicroBitPin P0B(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL);
bool sender, receiver, senderChosen;

void chooseSender(){

    while(!senderChosen){
        if(uBit.buttonA.isPressed()){
            senderChosen = true;
            sender = true;
        }
        if(uBit.buttonB.isPressed()){
            senderChosen = true;
            receiver = true;
        }
    }
}
