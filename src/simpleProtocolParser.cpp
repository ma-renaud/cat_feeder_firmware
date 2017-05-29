#include <simpleProtocolParser.h>
#include "waitForCommandStart.h"

SimpleProtocolParser::SimpleProtocolParser()
{
	pState = std::make_shared<WaitForCommandStart>(this);
}

void SimpleProtocolParser::receiveChar(char received)
{
	pState->receiveChar(received);
}

void SimpleProtocolParser::setState(std::shared_ptr<ProcessorState> state)
{
	pState = state;
}
