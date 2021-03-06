/*
 * MIDIparser.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: Roman
 */

#include <MIDIparser.hpp>

using namespace MIDI;

MIDIparser::MIDIparser() : running_status_(0),
		data_size_(0), expected_data_size_(0) { };

uint8_t MIDI::CheckChannel(uint8_t channel) {return 1;};

void MIDIparser::MessageReceived(uint8_t status) {
	 if (!status) {
	    //Device::BozoByte(data_[0]);
	  }

	  uint8_t hi = status & 0xf0;
	  uint8_t lo = status & 0x0f;

	  // If this is a channel-specific message, check first that the receiver is
	  // tuned to this channel.
	  if (hi != SYS_EX_START && !CheckChannel(lo)) {
	    //Device::RawMidiData(status, data_, data_size_, 0);
	    return;
	  }
	  if (status != SYS_EX_START && status != SYS_EX_END) {
	    //Device::RawMidiData(status, data_, data_size_, 1);
	  }
	  switch (hi) {
	    case NOTE_OFF:
	     // Device::NoteOff(lo, data_[0], data_[1]);
	    	while(1);
	      break;

	    case NOTE_ON:
	      if (data_[1]) {
	       // Device::NoteOn(lo, data_[0], data_[1]);
	      } else {
	        //Device::NoteOff(lo, data_[0], 0);
	      }
	      break;

	    case AFTERTOUCH:
	      //Device::Aftertouch(lo, data_[0], data_[1]);
	      break;

	    case CONT_CONTROLLER:
	      //Device::ControlChange(lo, data_[0], data_[1]);
	      break;

	    case PATCH_CHANGE:
	    //  Device::ProgramChange(lo, data_[0]);
	      break;

	    case CHANNEL_PRES:
	      //Device::Aftertouch(lo, data_[0]);
	      break;

	    case PITCH_BEND:
	      //Device::PitchBend(lo, (static_cast<uint16_t>(data_[1]) << 7) + data_[0]);
	      break;

	    case SYS_EX_START:
	      switch(status) {
	        case SYS_EX_START:
	        //  Device::SysExByte(data_[0]);
	          break;
	        case MIDI_TCQF:
	        case SONG_POS_POINTER:
	        case SONG_SELECT:
	        case 0xF4: //??
	        case 0xF5: //??
	        case TUNE_REQUEST:
	          // TODO(pichenettes): implement this if it makes sense.
	          break;
	        case TIMING_CLOCK:
	          //Device::Clock();
	          break;
	        case 0xF9: //??
	          break;
	        case START:
	         // Device::Start();
	          break;
	        case CONTINUE:
	        //  Device::Continue();
	          break;
	        case STOP:
	         // Device::Stop();
	          break;
	        case ACTIVE_SENSING:
	         // Device::ActiveSensing();
	          break;
	        case SYSTEM_RESET:
	          //Device::Reset();
	          break;
	      }
	      break;
	  }
}

void MIDIparser::PushByte(uint8_t byte) {
	// Realtime messages are immediately passed-through, and do not modify the
	  // state of the parser.
	  //Device::RawByte(byte);
	  if (byte >= 0xf8) {//If realtime
	    MessageReceived(byte);
	  } else {
	    if (byte >= 0x80) {
	      uint8_t hi = byte & 0xf0;
	      uint8_t lo = byte & 0x0f;
	      data_size_ = 0;
	      expected_data_size_ = 1;
	      switch (hi) {
	        case NOTE_OFF:
	        case NOTE_ON:
	        case AFTERTOUCH:
	        case CONT_CONTROLLER:
	          expected_data_size_ = 2;
	          break;
	        case PATCH_CHANGE:
	        case CHANNEL_PRES:
	          break;  // default data size of 1.
	        case PITCH_BEND:
	          expected_data_size_ = 2;
	          break;
	        case SYS_EX_START:
	          if (lo > 0 && lo < 3) {
	            expected_data_size_ = 2;
	          } else if (lo >= 4) {
	            expected_data_size_ = 0;
	          }
	          break;
	      }
	      if (byte == SYS_EX_END) {
	        if (running_status_ == SYS_EX_START) {
	          //Device::SysExEnd();
	        }
	        running_status_ = 0;
	      } else if (byte == SYS_EX_START) {
	        running_status_ = SYS_EX_START;
	        //Device::SysExStart();
	      } else {
	        running_status_ = byte;
	      }
	    } else {
	      data_[data_size_++] = byte; //??
	    }
	    if (data_size_ >= expected_data_size_) {
	      MessageReceived(running_status_);
	      data_size_ = 0;
	      if (running_status_ > SYS_EX_START) {
	        expected_data_size_ = 0;
	        running_status_ = 0;
	      }
	    }
	  }
};

// will we need this?
//void SendNoteOn(MIDImessage* msg) {
//	uint8_t tmp[3] = {NOTE_ON, msg->key, msg->velocity};
//	HAL_UART_Transmit_IT(&huart4, tmp, 3);
//}

// maybe just send message?
//void SendMeassage(MIDImessage* msg) {
//	uint8_t tmp[3] = {msg->command, msg->key, msg->velocity};
//	HAL_UART_Transmit_IT(&huart4, tmp, 3);  // tmp is a local buffer, ok?
//}


void MIDI::SendNoteOn(u8 key, u8 vel) {
	//uint8_t tmp[3] = {NOTE_ON, key, vel};
	buf[0] = NOTE_ON;
	buf[1] = key;
	buf[2] = vel;
	HAL_UART_Transmit_IT(&huart4, buf, 3);  // tmp is a local buffer, ok?
}

void MIDI::SendNoteOff(u8 key, u8 vel) {
	//uint8_t tmp[3] = {NOTE_OFF, key, vel};
	buf[0] = NOTE_OFF;
	buf[1] = key;
	buf[2] = vel;
	HAL_UART_Transmit_IT(&huart4, buf, 3);
}



