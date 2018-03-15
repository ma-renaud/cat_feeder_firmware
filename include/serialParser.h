#ifndef _serialParser_H_
#define _serialParser_H_

#include "simpleProtocolParser.h"

class SerialParser: public SimpleProtocolParser
{
 public:
  SerialParser();
  ~SerialParser();

  void receptionStart() override ;
  void receiveData(char received) override ;
  void appendReceivedData() override ;
  void receptionCompleted() override ;

};

#endif
