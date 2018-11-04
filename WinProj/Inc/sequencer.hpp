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

enum SeqOptions {
	SIZE = 8
};

enum SeqStepAction {  // action bit mask
		//ADVANCE = 0x1,
		SKIP = 0x2,        // -> on advance
		//REPEAT = 0x4,    // -> on trig  ?? no need when we can check if repeats==1 or >1
		MUTE = 0x8,        // -> on trig
		JUMP = 0x20        // -> on advance
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
