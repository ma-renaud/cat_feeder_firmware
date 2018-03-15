#include "gmock/gmock.h"
#include "simpleProtocolParser.h"

using namespace testing;

class SimpleProtocolParserStub : public SimpleProtocolParser
{
   public:
      SimpleProtocolParserStub() { trace = ""; }
      std::string getTrace() { return trace; }

   private:
      std::string trace;

      void receptionStart() override { trace += "S"; }
      void receiveData(char received) override { trace += "D"; }
      void appendReceivedData() override { trace += "A"; }
      void receptionCompleted() override { trace += "E"; }
};

class SimpleProtocolParserLogicGroup : public Test
{
   public:
      SimpleProtocolParserStub parser;
};

TEST_F(SimpleProtocolParserLogicGroup, test_start_char_state_change)
{
   parser.receiveChar('<');

   ASSERT_THAT(parser.getTrace().c_str(), StrEq("S"));
}

TEST_F(SimpleProtocolParserLogicGroup, test_receive_four_char_then_end)
{
   parser.receiveChar('<');
   parser.receiveChar('a');
   parser.receiveChar('a');
   parser.receiveChar('a');
   parser.receiveChar('a');
   parser.receiveChar('>');

   ASSERT_THAT(parser.getTrace().c_str(), StrEq("SDDDDAE"));
}

TEST_F(SimpleProtocolParserLogicGroup, test_receive_three_data)
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

  ASSERT_THAT(parser.getTrace().c_str(), StrEq("SDDDDDADDADAE"));
}
