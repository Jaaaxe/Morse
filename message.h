#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
 void sendSignal(int signalLength);
 int signalReader();
 bool rangeChecker(int incomingLength, int standard, int range);
 void sendMorse(std::vector<char> morse);

#endif
