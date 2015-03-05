/*
	RackAFX(TM)
	Applications Programming Interface
	Derived Class Object Implementation
*/


#include "ModMedFilt.h"


/* constructor()
	You can initialize variables here.
	You can also allocate memory here as long is it does not
	require the plugin to be fully instantiated. If so, allocate in init()

*/
CModMedFilt::CModMedFilt()
{
	// Added by RackAFX - DO NOT REMOVE
	//
	// initUI() for GUI controls: this must be called before initializing/using any GUI variables
	initUI();
	// END initUI()

	// built in initialization
	m_PlugInName = "ModMedFilt";

	// Default to Stereo Operation:
	// Change this if you want to support more/less channels
	m_uMaxInputChannels = 2;
	m_uMaxOutputChannels = 2;

	// use of MIDI controllers to adjust sliders/knobs
	m_bEnableMIDIControl = true;		// by default this is enabled

	// custom GUI stuff
	m_bLinkGUIRowsAndButtons = false;	// change this if you want to force-link

	// DO NOT CHANGE let RackAFX change it for you; use Edit Project to alter
	m_bUseCustomVSTGUI = true;

	// for a user (not RackAFX) generated GUI - advanced you must compile your own resources
	// DO NOT CHANGE let RackAFX change it for you; use Edit Project to alter
	m_bUserCustomGUI = false;

	// output only - SYNTH - plugin DO NOT CHANGE let RackAFX change it for you; use Edit Project to alter
	m_bOutputOnlyPlugIn = false;

	// change to true if you want all MIDI messages
	m_bWantAllMIDIMessages = false;

	// un-comment this for VST/AU Buffer-style processing
	// m_bWantVSTBuffers = true;

	// Finish initializations here

}


/* destructor()
	Destroy variables allocated in the contructor()

*/
CModMedFilt::~CModMedFilt(void)
{


}

/*
initialize()
	Called by the client after creation; the parent window handle is now valid
	so you can use the Plug-In -> Host functions here (eg sendUpdateUI())
	See the website www.willpirkle.com for more details
*/
bool __stdcall CModMedFilt::initialize()
{
	// Add your code here

	return true;
}



/* prepareForPlay()
	Called by the client after Play() is initiated but before audio streams

	You can perform buffer flushes and per-run intializations.
	You can check the following variables and use them if needed:

	m_nNumWAVEChannels;
	m_nSampleRate;
	m_nBitDepth;

	NOTE: the above values are only valid during prepareForPlay() and
		  processAudioFrame() because the user might change to another wave file,
		  or use the sound card, oscillators, or impulse response mechanisms

    NOTE: if you allocte memory in this function, destroy it in ::destroy() above
*/
bool __stdcall CModMedFilt::prepareForPlay()
{
	// Add your code here:



	return true;
}


/* processAudioFrame

// ALL VALUES IN AND OUT ON THE RANGE OF -1.0 TO + 1.0

LEFT INPUT = pInputBuffer[0];
RIGHT INPUT = pInputBuffer[1]

LEFT OUTPUT = pInputBuffer[0]
RIGHT OUTPUT = pOutputBuffer[1]

*/
bool __stdcall CModMedFilt::processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels)
{
	// output = input -- change this for meaningful processing
	//
	// Do LEFT (MONO) Channel; there is always at least one input/one output
	// (INSERT Effect)
	pOutputBuffer[0] = pInputBuffer[0];

	// Mono-In, Stereo-Out (AUX Effect)
	if(uNumInputChannels == 1 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[0];

	// Stereo-In, Stereo-Out (INSERT Effect)
	if(uNumInputChannels == 2 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[1];


	return true;
}


/* ADDED BY RACKAFX -- DO NOT EDIT THIS CODE!!! ----------------------------------- //
   	**--0x2983--**

		Assignable Buttons               Index
	-----------------------------------------------
		B1		                          50
		B2		                          51
		B3		                          52

	-----------------------------------------------


	**--0xFFDD--**
// ------------------------------------------------------------------------------- */
// Add your UI Handler code here ------------------------------------------------- //
//
bool __stdcall CModMedFilt::userInterfaceChange(int nControlIndex)
{
	// decode the control index, or delete the switch and use brute force calls
	switch(nControlIndex)
	{
		case 0:
		{
			break;
		}

		default:
			break;
	}

	return true;
}


/* joystickControlChange

	Indicates the user moved the joystick point; the variables are the relative mixes
	of each axis; the values will add up to 1.0

			B
			|
		A -	x -	C
			|
			D

	The point in the very center (x) would be:
	fControlA = 0.25
	fControlB = 0.25
	fControlC = 0.25
	fControlD = 0.25

	AC Mix = projection on X Axis (0 -> 1)
	BD Mix = projection on Y Axis (0 -> 1)
*/
bool __stdcall CModMedFilt::joystickControlChange(float fControlA, float fControlB, float fControlC, float fControlD, float fACMix, float fBDMix)
{
	// add your code here

	return true;
}



/* processAudioBuffer

	// ALL VALUES IN AND OUT ON THE RANGE OF -1.0 TO + 1.0

	The I/O buffers are interleaved depending on the number of channels. If uNumChannels = 2, then the
	buffer is L/R/L/R/L/R etc...

	if uNumChannels = 6 then the buffer is L/R/C/Sub/BL/BR etc...

	It is up to you to decode and de-interleave the data.

	To use this function set m_bWantBuffers = true in your constructor.

	******************************
	********* IMPORTANT! *********
	******************************
	If you are going to ultimately make this a VST Compatible Plug-In and you want to process
	buffers, you need to override the NEXT function below:

	processVSTAudioBuffer()


	This function (processRackAFXAudioBuffer) is not supported in the VST wrapper because
	the VST buffer sizes no maximum value. This would require the use of dynamic buffering
	in the callback which is not acceptable for performance!
*/
bool __stdcall CModMedFilt::processRackAFXAudioBuffer(float* pInputBuffer, float* pOutputBuffer,
													   UINT uNumInputChannels, UINT uNumOutputChannels,
													   UINT uBufferSize)
{

	for(UINT i=0; i<uBufferSize; i++)
	{
		// pass through code
		pOutputBuffer[i] = pInputBuffer[i];
	}


	return true;
}



/* processVSTAudioBuffer

	// ALL VALUES IN AND OUT ON THE RANGE OF -1.0 TO + 1.0

	NOTE: You do not have to implement this function if you don't want to; the processAudioFrame()
	will still work; however this using function will be more CPU efficient for your plug-in, and will
	override processAudioFrame().

	To use this function set m_bWantVSTBuffers = true in your constructor.

	The VST input and output buffers are pointers-to-pointers. The pp buffers are the same depth as uNumChannels, so
	if uNumChannels = 2, then ppInputs would contain two pointers,

		inBuffer[0] = a pointer to the LEFT buffer of data
		inBuffer[1] = a pointer to the RIGHT buffer of data

	Similarly, outBuffer would have 2 pointers, one for left and one for right.

	For 5.1 audio you would get 6 pointers in each buffer.

*/
bool __stdcall CModMedFilt::processVSTAudioBuffer(float** inBuffer, float** outBuffer, UINT uNumChannels, int inFramesToProcess)
{
	// PASS Through example
	// MONO First
	float* pInputL  = inBuffer[0];
	float* pOutputL = outBuffer[0];
	float* pInputR  = NULL;
	float* pOutputR = NULL;

	// if STEREO,
	if(inBuffer[1])
		pInputR = inBuffer[1];

	if(outBuffer[1])
		pOutputR = outBuffer[1];

	// Process audio by de-referencing ptrs
	// this is siple pass through code
	while (--inFramesToProcess >= 0)
	{
		// Left channel processing
		*pOutputL = *pInputL;

		// If there is a right channel
		if(pInputR)
			*pOutputR = *pInputR;

		// advance pointers
		pInputL++;
		pOutputL++;
		if(pInputR) pInputR++;
		if(pOutputR) pOutputR++;
	}
	// all OK
	return true;
}

bool __stdcall CModMedFilt::midiNoteOn(UINT uChannel, UINT uMIDINote, UINT uVelocity)
{
	return true;
}

bool __stdcall CModMedFilt::midiNoteOff(UINT uChannel, UINT uMIDINote, UINT uVelocity, bool bAllNotesOff)
{
	return true;
}

// uModValue = 0->127
bool __stdcall CModMedFilt::midiModWheel(UINT uChannel, UINT uModValue)
{
	return true;
}

// nActualPitchBendValue 		= -8192 -> +8191, 0 at center
// fNormalizedPitchBendValue 	= -1.0  -> +1.0,  0 at center
bool __stdcall CModMedFilt::midiPitchBend(UINT uChannel, int nActualPitchBendValue, float fNormalizedPitchBendValue)
{
	return true;
}

// MIDI Clock
// http://home.roadrunner.com/~jgglatt/tech/midispec/clock.htm
/* There are 24 MIDI Clocks in every quarter note. (12 MIDI Clocks in an eighth note, 6 MIDI Clocks in a 16th, etc).
   Therefore, when a slave device counts down the receipt of 24 MIDI Clock messages, it knows that one quarter note
   has passed. When the slave counts off another 24 MIDI Clock messages, it knows that another quarter note has passed.
   Etc. Of course, the rate that the master sends these messages is based upon the master's tempo.

   For example, for a tempo of 120 BPM (ie, there are 120 quarter notes in every minute), the master sends a MIDI clock
   every 20833 microseconds. (ie, There are 1,000,000 microseconds in a second. Therefore, there are 60,000,000
   microseconds in a minute. At a tempo of 120 BPM, there are 120 quarter notes per minute. There are 24 MIDI clocks
   in each quarter note. Therefore, there should be 24 * 120 MIDI Clocks per minute.
   So, each MIDI Clock is sent at a rate of 60,000,000/(24 * 120) microseconds).
*/
bool __stdcall CModMedFilt::midiClock()
{

	return true;
}

// any midi message other than note on, note off, pitchbend, mod wheel or clock
bool __stdcall CModMedFilt::midiMessage(unsigned char cChannel, unsigned char cStatus, unsigned char
						   				  cData1, unsigned char cData2)
{
	return true;
}


// DO NOT DELETE THIS FUNCTION --------------------------------------------------- //
bool __stdcall CModMedFilt::initUI()
{
	// ADDED BY RACKAFX -- DO NOT EDIT THIS CODE!!! ------------------------------ //
	if(m_UIControlList.count() > 0)
		return true;

// **--0xDEA7--**


// **--0xEDA5--**
// ------------------------------------------------------------------------------- //

	return true;

}

