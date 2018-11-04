/*
 * sequencer.h
 *
 *  Created on: Nov 4, 2018
 *      Author: Roman
 */

#ifndef SEQUENCER_HPP_
#define SEQUENCER_HPP_


#include <Globals.hpp>
#include "MIDIparser.hpp"

using namespace MIDI;

extern u32 millis;         // for time measurements

enum class SeqOptions {
	SIZE = 8
};

enum SeqStepAction {
		ADVANCE,
		SKIP,
		REPEAT,
		JUMP
	};

struct SeqStep {
	MIDImessage note;   // midi to send
	u32 length;         // in ms
	u8 repeats;         // how many repeats
	u16 jumpTo;         // jump to this step
};

class Sequencer {
public:
	Sequencer();
	void triggerStep(SeqStep step);
	void advanceStep(void);
	void start(void);
	void pause(void);
	void stop(void);
	u16 seqLength;                       // [1..SeqOptions::SIZE]
	SeqStep sequence[SeqOptions::SIZE];  // the greatest sequence ever)

private:
	u16 currStep;
	u32 prevTime;  //
};




#endif /* SEQUENCER_HPP_ */
