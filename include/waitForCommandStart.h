#ifndef INCLUDE_WAITFORCOMMANDSTART_H_
#define INCLUDE_WAITFORCOMMANDSTART_H_

#include "processorState.h"
#include <cstdint>

class SimpleProtocolParser;

class WaitForStart: public ProcessorState
{
	private:
		SimpleProtocolParser* _context;

	public:
		WaitForStart(SimpleProtocolParser* context): _context(context) {}
		void receiveChar(char received);
};

class ReceiveData: public ProcessorState
{
	private:
		SimpleProtocolParser* _context;

	public:
  		ReceiveData(SimpleProtocolParser* context)
		{
			_context = context;
		}
		void receiveChar(char received);
};



#endif /* INCLUDE_WAITFORCOMMANDSTART_H_ */
