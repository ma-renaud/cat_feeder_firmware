#ifndef INCLUDE_PROCESSORSTATE_H_
#define INCLUDE_PROCESSORSTATE_H_

class ProcessorState
{
	public :
		virtual ~ProcessorState(){};
		virtual void receiveChar(char received) = 0;
};

#endif /* INCLUDE_PROCESSORSTATE_H_ */
