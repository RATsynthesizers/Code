/*
 * MIDIparser.hpp
 *
 *  Created on: Nov 3, 2018
 *      Author: Roman
 */

#ifndef MIDIPARSER_HPP_
#define MIDIPARSER_HPP_

#include <stdint.h>

namespace MIDI {
	enum CommandTypes {
		NOTE_OFF = 0x80,
		NOTE_ON = 0x90,
		AFTERTOUCH = 0xA0,
		CONT_CONTROLLER = 0xB0,
		PATCH_CHANGE = 0xC0,
		CHANNEL_PRES = 0xD0,
		PITCH_BEND = 0xE0,
		SYS_EX_START = 0xF0,
		MIDI_TCQF,
		SONG_POS_POINTER,
		SONG_SELECT,
		TUNE_REQUEST = 0xF6,
		SYS_EX_END,
		TIMING_CLOCK,
		START = 0xFA,
		CONTINUE,
		STOP,
		ACTIVE_SENSING = 0xFE,
		SYSTEM_RESET
	};

//	struct MIDImessage {
//	private:
//		uint8_t parameter1;
//		uint8_t parameter2;
//
//	public:
//		uint8_t command;
//		uint8_t& key = parameter1;
//		uint8_t& controller = parameter1;
//		uint8_t& instrument = parameter1;
//		uint8_t& pressure = parameter1;
//		uint8_t& lsb = parameter1;
//
//		uint8_t& velocity = parameter2;
//		uint8_t& touch = parameter2;
//		uint8_t& controllerVal = parameter2;
//		uint8_t& msb = parameter2;
//	};

	uint8_t CheckChannel(uint8_t channel);

	class MIDIparser {
	public:
		MIDIparser();
		void PushByte(uint8_t byte);

	private:
		uint8_t running_status_;
		uint8_t data_[3];
		uint8_t data_size_;  		  // Number of non-status byte received.
		uint8_t expected_data_size_;  // Expected number of non-status bytes.

		void MessageReceived(uint8_t status);
	};
};



#endif /* MIDIPARSER_HPP_ */