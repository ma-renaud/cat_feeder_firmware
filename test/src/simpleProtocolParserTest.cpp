#include "gmock/gmock.h"
#include "serialParser.h"

using namespace testing;

class SimpleProtocolParserGroup : public Test
{
 public:
  SerialParser parser;
};

TEST_F(SimpleProtocolParserGroup, test_start_char_state_change)
{
  parser.receiveChar('<');

  ASSERT_THAT(parser.getTrace().c_str(), StrEq("S"));
}