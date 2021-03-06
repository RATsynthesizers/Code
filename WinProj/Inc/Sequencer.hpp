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

namespace SEQ_SPACE {
using namespace MIDI;

extern u32 millis;         // for time measurements

enum SeqOptions {      // ?? class? global scope is bad
	SIZE = 8
};

enum SeqStepAction {  // action bit mask
	SKIP = 0x1,        // -> on advance
	MUTE = 0x2,        // -> on trig
	JUMP = 0x4        // -> on advance
};

struct SeqStep {
	MIDImessage note;     // midi to send
	u32 length;           // in ms
	u8 action;            // what to do
	u8 repeats;           // how many repeats
	u16 jumpTo;           // jump to this step
};

class Sequencer {
public:
	Sequencer(u16 size);
	void triggerStep(SeqStep step);
	void advanceStep(void);
	void continueSeq(void);
	void pauseSeq(void);
	void resetSeq(void);
	u16 seqLength;                       // [1..SeqOptions::SIZE]
	SeqStep sequence[SeqOptions::SIZE];  // the greatest sequence ever)

private:
	// seq options
	u16 const seqSize;
	u16 currStep;
	u32 prevTime;  //
};

}

#endif /* SEQUENCER_HPP_ */
