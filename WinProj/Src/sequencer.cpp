/*
 * sequencer.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: Roman
 */

#include <Sequencer.hpp>

Sequencer::Sequencer() : prevTime(0), currStep(0), seqLength(SeqOptions::SIZE) { };

void triggerStep(SeqStep step) {
	SendNoteOn( &(step.note) );
	HAL_Delay(step.length);       // ?? stupid
	SendNoteOff( &(step.note) );  // noteOff with same velocity
	HAL_Delay(step.length);       // stupid monophonic
}

void Sequencer::advanceStep(void) {
	if(sequence[currStep].jumpTo != NULL)  // jump to hidden steps? Fun)
		currStep = sequence[currStep].jumpTo;
	else
		currStep++;

	if(currStep >= seqLength)
		currStep = 0;

	if (sequence[currStep].repeats)
		for(u8 i = 0; i < sequence[currStep].repeats; i++) {
			triggerStep(sequence[currStep]);
		}
	else
		triggerStep(sequence[currStep]);
}

void Sequencer::start(void) {
	triggerStep(sequence[currStep]);
	while(1)         // ?? stuupid
		Sequencer::advanceStep();
}
