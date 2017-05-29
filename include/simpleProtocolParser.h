#ifndef INCLUDE_SIMPLEPROTOCOLPARSER_H_
#define INCLUDE_SIMPLEPROTOCOLPARSER_H_

#include <memory>
#include "processorState.h"

class SimpleProtocolParser
{
	public:
		SimpleProtocolParser();
		virtual ~SimpleProtocolParser(){}

		void receiveChar(char received);
		void setState(std::shared_ptr<ProcessorState> state);

		virtual void waitForCommand() = 0;
		virtual void saveCommand() = 0;
		virtual void saveData() = 0;
		virtual void executeCommand() = 0;

	private:
		std::shared_ptr<ProcessorState> pState;
};


#endif /* INCLUDE_SIMPLEPROTOCOLPARSER_H_ */
