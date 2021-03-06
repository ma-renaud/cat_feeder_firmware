#include "serial_parser_states.h"
#include "simple_protocol_parser.h"

void WaitForStart::receiveChar(char received)
{
	if(received == '<')
	{
		_context->receptionStart();
		_context->setState( std::make_shared<ReceiveData>(_context));
	}
}

void ReceiveData::receiveChar(char received)
{
	if(received == '>')
	{
        _context->appendReceivedData();
		_context->receptionCompleted();
		_context->setState( std::make_shared<WaitForStart>(_context));
	}
	else if(received == ':')
        _context->appendReceivedData();
	else
		_context->receiveData(received);
}




