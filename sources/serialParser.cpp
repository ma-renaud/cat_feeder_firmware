#include "serialParser.h"
#include "serialParserStates.h"

SerialParser::SerialParser() {
  setState(std::make_shared<WaitForStart>(this));
  completed = false;
  receptionBuffer = "";
  decoded.clear();
}

bool SerialParser::isCompleted() {
  return completed;
}

std::vector<std::string> SerialParser::getDecoded() {
  return decoded;
}

void SerialParser::receptionStart() {
  completed = false;
  receptionBuffer = "";
  decoded.clear();
}

void SerialParser::receiveData(char received) {
  receptionBuffer += received;
}

void SerialParser::appendReceivedData() {
  decoded.push_back(receptionBuffer);
  receptionBuffer = "";
}

void SerialParser::receptionCompleted() {
  completed = true;
}
