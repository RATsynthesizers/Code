/*
 * sequencer.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: Roman
 */

#include <Sequencer.hpp>

using namespace SEQ_SPACE;

Sequencer::Sequencer(u16 size) : seqLength(size), seqSize(size), currStep(0), prevTime(0) { };

void triggerStep(SeqStep step) {  // TODO: think about timing, initialise all steps in ktor
	// if (step.action & REPEAT)
		for (u8 i = 0; i < step.repeats; i++) { // ?? behavior for repeats = 0 (ktor)
			if (step.action & MUTE)               // if muted - no sound, just wait
				HAL_Delay(step.length * 2);       // ?? stupid
			else {                                // else play
				SendNoteOn(step.note.key, step.note.velocity);
				HAL_Delay(step.length);                          // ?? stupid
				SendNoteOff(step.note.key, step.note.velocity);  // noteOff with same velocity
				HAL_Delay(step.length);                          // stupid monophonic
			}
		}
//	else                           // or play once
//		SendNoteOn( &(step.note) );
//		HAL_Delay(step.length);       // ?? stupid
//		SendNoteOff( &(step.note) );  // noteOff with same velocity
//		HAL_Delay(step.length);       // stupid monophonic
}

void Sequencer::advanceStep(void) {
	if(sequence[currStep].action & JUMP)     // if current step is set to JUMP - jump to the step specified
		currStep = sequence[currStep].jumpTo;   // jump to hidden steps? Fun)
	else
		currStep++;  // else simply advance step

	while ( (sequence[currStep].action & SKIP) && (currStep < seqLength))  // if the next step is SKIP - advannce more
		 currStep++;                                                        // until the next step is not SKIP

	if(currStep >= seqLength) {  // cycle steps
		currStep = 0;
		while ( (sequence[currStep].action & SKIP) && (currStep < seqLength))  // SKIP check again
				 currStep++;

	}

}

void Sequencer::continueSeq(void) {
	while(1) {         // ?? stuupid
		Sequencer::advanceStep();
		triggerStep(sequence[currStep]);
	}
}

void Sequencer::pauseSeq(void) {

}

void Sequencer::resetSeq(void) {
	currStep = 0;
}
