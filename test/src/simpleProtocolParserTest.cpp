#include "gmock/gmock.h"
#include "serialParser.h"

using namespace testing;

class SimpleProtocolParserGroup : public Test
{
 public:
  SerialParser parser;
};


TEST_F(SimpleProtocolParserGroup, test_receive_three_data)
{
  parser.receiveChar('<');
  parser.receiveChar('a');
  parser.receiveChar('a');
  parser.receiveChar('a');
  parser.receiveChar('a');
  parser.receiveChar('a');
  parser.receiveChar(':');
  parser.receiveChar('a');
  parser.receiveChar('a');
  parser.receiveChar(':');
  parser.receiveChar('a');
  parser.receiveChar('>');

  ASSERT_THAT(parser.getDecoded(), ElementsAre("aaaaa", "aa", "a"));
}
