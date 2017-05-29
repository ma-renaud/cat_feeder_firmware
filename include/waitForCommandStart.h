/*
 * WaitForCommandStart.h
 *
 *  Created on: 2016-03-29
 *      Author: Marco
 */

#ifndef INCLUDE_WAITFORCOMMANDSTART_H_
#define INCLUDE_WAITFORCOMMANDSTART_H_

#include "processorState.h"

class SimpleProtocolParser;

class WaitForCommandStart: public ProcessorState
{
	private:
		SimpleProtocolParser* _context;

	public:
		WaitForCommandStart(SimpleProtocolParser* context): _context(context) {}
		void receiveChar(char received);
};

class WaitForCommand: public ProcessorState
{
	private:
		SimpleProtocolParser* _context;

	public:
		WaitForCommand(SimpleProtocolParser* context)
		{
			_context = context;
		}
		void receiveChar(char received);
};

class WaitForData: public ProcessorState
{
	private:
		SimpleProtocolParser* _context;

	public:
		WaitForData(SimpleProtocolParser* context)
		{
			_context = context;
		}
		void receiveChar(char received);
};



#endif /* INCLUDE_WAITFORCOMMANDSTART_H_ */
