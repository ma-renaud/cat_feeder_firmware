#include "gtest/gtest.h"
#include "simpleProtocolParser.h"
using namespace testing;

class SimpleProtocolParserStub : public SimpleProtocolParser
{
	public:
		SimpleProtocolParserStub() { trace = ""; }
		std::string getTrace() { return trace; }

	private:
		std::string trace;

		virtual void waitForCommand(){ trace += "W"; }
		virtual void saveCommand() { trace += "C"; }
		virtual void saveData() { trace += "D";	}
		virtual void executeCommand() {	trace += "E"; }
};

class SimpleProtocolParserGroup : public Test
{
	public:
		SimpleProtocolParserStub parser;
};

TEST_F(SimpleProtocolParserGroup, ChangeStateToWaitForCommandOnStartChar)
{
	parser.receiveChar('<');

	ASSERT_STREQ("W", parser.getTrace().c_str());
}

TEST_F(SimpleProtocolParserGroup, StayInWaitForCommandWaitingThreeCommandChar)
{
    parser.receiveChar('<');
    parser.receiveChar('a');

    ASSERT_STREQ("WC", parser.getTrace().c_str());
}

TEST_F(SimpleProtocolParserGroup, ChangeStateToWaitingForDataAfterThreeCommandChar)
{
    parser.receiveChar('<');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');
    parser.receiveChar('a');

    ASSERT_STREQ("WCCCD", parser.getTrace().c_str());
}

TEST_F(SimpleProtocolParserGroup, CallExecuteCommandOnEndChar)
{
	parser.receiveChar('<');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('>');

    ASSERT_STREQ("WCCCDE", parser.getTrace().c_str());
}
