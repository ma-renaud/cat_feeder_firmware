#include "waitForCommandStart.h"
#include "simpleProtocolParser.h"

#define UNUSED(expr) (void)(expr)

void WaitForCommandStart::receiveChar(char received)
{
	if(received == '<')
	{
		_context->waitForCommand();
		_context->setState( std::make_shared<WaitForCommand>(_context));
	}
}

void WaitForCommand::receiveChar(char received)
{
	UNUSED(received);
	cpt++;
	_context->saveCommand();
	if(cpt >= 3)
	{
		cpt = 0;
		_context->setState( std::make_shared<WaitForData>(_context));
	}
}

void WaitForData::receiveChar(char received)
{
	if(received == '>')
	{
		_context->executeCommand();
		_context->setState( std::make_shared<WaitForCommandStart>(_context));
	}
	else
		_context->saveData();
}




