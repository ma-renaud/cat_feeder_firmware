#include <simple_protocol_parser.h>
#include "serial_parser_states.h"

SimpleProtocolParser::SimpleProtocolParser()
{
	pState = std::make_shared<WaitForStart>(this);
}

void SimpleProtocolParser::receiveChar(char received)
{
	pState->receiveChar(received);
}

void SimpleProtocolParser::setState(std::shared_ptr<ProcessorState> state)
{
	pState = state;
}
