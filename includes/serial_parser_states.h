#ifndef INCLUDE_SERIALPARSERSTATES_H_
#define INCLUDE_SERIALPARSERSTATES_H_

#include "processor_state.h"
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



#endif /* INCLUDE_SERIALPARSERSTATES_H_ */
