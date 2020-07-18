#include "message.h"
#include "defs.h"

#include "MicroBit.h"
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL);
void sendSignal(int signalLength){
    P0.setDigitalValue(1);
    uBit.sleep(signalLength);
    P0.setDigitalValue(0);
    uBit.sleep(500);
}

int signalReader(){
  int initialTime, deltaTime;
    if(P0.getDigitalValue()){
        initialTime = uBit.systemTime();
        while(P0.getDigitalValue()){
            //Signal being received
        }
        deltaTime = uBit.systemTime() - initialTime;
        //todo specify constant NOISE = 10
        if(deltaTime > 10){
            return deltaTime;
        }
    }
}

bool rangeChecker(int incomingLength, int standard, int range){
  int rangeMax = standard + range;
  int rangeMin = standard - range;
  if(incomingLength < (rangeMax) && (incomingLength > (rangeMin))){
    return true;
  }else{
    return false;
  }
}

void sendMorse(std::vector<char> morse){
  for (int i = 0; i < morse.size(); i++){
    if(morse.at(i) == '.'){
      uBit.display.scroll(".", 100);
      sendSignal(DOTSIGNAL);
    }else if(morse.at(i) == '-'){
      uBit.display.scroll("-", 100);
      sendSignal(DASHSIGNAL);
    }else{
      uBit.display.scroll("E", 100);
      sendSignal(ENDMORSESIGNAL);
    }
  }
}
