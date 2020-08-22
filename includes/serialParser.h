#ifndef _serialParser_H_
#define _serialParser_H_

#include <vector>
#include "simpleProtocolParser.h"

class SerialParser: public SimpleProtocolParser
{
 public:
  SerialParser();
  ~SerialParser() = default;

  bool isCompleted();
  std::vector<std::string> getDecoded();

  void receptionStart() override ;
  void receiveData(char received) override ;
  void appendReceivedData() override ;
  void receptionCompleted() override ;

 private:
  std::vector<std::string> decoded;
  std::string receptionBuffer;
  bool completed;


};

#endif
