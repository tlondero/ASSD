

#ifndef _MIDIEVENT_H_INCLUDED
#define _MIDIEVENT_H_INCLUDED

#include "MidiMessage.h"
#include <vector>

namespace smf {

class MidiEvent : public MidiMessage {
	public:
		           MidiEvent             (void);
		           MidiEvent             (int command);
		           MidiEvent             (int command, int param1);
		           MidiEvent             (int command, int param1, int param2);
		           MidiEvent             (const MidiMessage& message);
		           MidiEvent             (const MidiEvent& mfevent);
		           MidiEvent             (int aTime, int aTrack,
		                                  std::vector<uchar>& message);

		          ~MidiEvent             ();

		MidiEvent& operator=             (const MidiEvent& mfevent);
		MidiEvent& operator=             (const MidiMessage& message);
		MidiEvent& operator=             (const std::vector<uchar>& bytes);
		MidiEvent& operator=             (const std::vector<char>& bytes);
		MidiEvent& operator=             (const std::vector<int>& bytes);

		void       clearVariables        (void);

		// functions related to event linking (note-ons to note-offs).
		void       unlinkEvent           (void);
		void       unlinkEvents          (void);
		void       linkEvent             (MidiEvent* mev);
		void       linkEvents            (MidiEvent* mev);
		void       linkEvent             (MidiEvent& mev);
		void       linkEvents            (MidiEvent& mev);
		int        isLinked              (void) const;
		MidiEvent* getLinkedEvent        (void);
		const MidiEvent* getLinkedEvent  (void) const;
		int        getTickDuration       (void) const;
		double     getDurationInSeconds  (void) const;

		int        tick;     // delta or absolute MIDI ticks
		int        track;    // [original] track number of event in MIDI file
		double     seconds;  // calculated time in sec. (after doTimeAnalysis())
		int        seq;      // sorting sequence number of event

	private:
		MidiEvent* m_eventlink;  // used to match note-ons and note-offs

};

} // end of namespace smf

#endif /* _MIDIEVENT_H_INCLUDED */



