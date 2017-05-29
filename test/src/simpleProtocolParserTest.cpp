#include <simpleProtocolParser.h>
#include "CppUTest/TestHarness.h"
#include <string>

class SimpleProtocolParserStub : public SimpleProtocolParser
{
	public:
		SimpleProtocolParserStub()
		{
			trace = "";
		}

		std::string getTrace()
		{
			return trace;
		}

	private:
		std::string trace;

		virtual void waitForCommand()
		{
			trace += "W";
		}

		virtual void saveCommand()
		{
			trace += "C";
		}

		virtual void saveData()
		{
			trace += "D";
		}

		virtual void executeCommand()
		{
			trace += "E";
		}
};

TEST_GROUP(SimpleProtocolParserGroup)
{
	SimpleProtocolParserStub parser;
};

TEST(SimpleProtocolParserGroup, ChangeStateToWaitForCommandOnStartChar)
{
	parser.receiveChar('<');

	STRCMP_EQUAL("W", parser.getTrace().c_str());
}

TEST(SimpleProtocolParserGroup, StayInWaitForCommandWaitingThreeCommandChar)
{
	parser.receiveChar('<');
	parser.receiveChar('a');

	STRCMP_EQUAL("WC", parser.getTrace().c_str());
}

TEST(SimpleProtocolParserGroup, ChangeStateToWaitingForDataAfterThreeCommandChar)
{
	parser.receiveChar('<');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');

	STRCMP_EQUAL("WCCCD", parser.getTrace().c_str());
}

TEST(SimpleProtocolParserGroup, CallExecuteCommandOnEndChar)
{
	parser.receiveChar('<');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('a');
	parser.receiveChar('>');

	STRCMP_EQUAL("WCCCDE", parser.getTrace().c_str());
}
