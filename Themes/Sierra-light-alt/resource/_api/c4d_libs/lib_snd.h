/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_SND_H_
#define _LIB_SND_H_

#include "c4d_library.h"
#include "c4d_baseplugin.h"

struct GeSndInfoEx;	// deprecated

#ifndef _INTERNAL_DEF_SND_

class BaseSound;

class GeSndInfo
{
private:
	Int32	channel_cnt;
	Int32	bits_per_channel;
	Float	sample_rate;
	Int32	sample_cnt;  // number of samples per channel
	Char	*data;

public:
	GeSndInfo(void)
	{
		channel_cnt = 0;
		bits_per_channel = 0;
		sample_rate = 0.0;
		sample_cnt = 0;
		data = nullptr;
	}
	GeSndInfo(BaseSound *bs);

	// return the number of channels
	Int32	GetChannelCount( void ) const
	{
		return channel_cnt;
	}

	// return the number of bits per channel
	Int32	GetBitsPerChannel( void ) const
	{
		return bits_per_channel;
	}

	// return the sample rate in Hz
	Float GetSampleRate( void )
	{
		return sample_rate;
	}

	// return the duration/length of the sound in samples
	Int32	GetSampleCount( void ) const
	{
		return sample_cnt;
	}

	// return the length as BaseTime
	BaseTime	GetLength( void )
	{
		return BaseTime( GetSampleRate() != 0.0  ? (Float) sample_cnt / GetSampleRate() : 0.0 );
	}
};

class GePlaySnd
{

	private:
		GePlaySnd();
		~GePlaySnd();

	public:
		static GePlaySnd*		Alloc();
		static void					Free(GePlaySnd *&data);

		//----------------------------------------------------------------------------------------
		// Open audio device with a single BaseSound
		// The audio data referenced by the BaseSound will be kept in memory until you call Close()
		// Function result:		true if successful
		// snd:								BaseSound
		//----------------------------------------------------------------------------------------
		Bool	Open( const BaseSound *snd );

		//----------------------------------------------------------------------------------------
		// Open audio device with multiple BaseSounds that will be mixed
		// The audio data referenced by the BaseSounds will be kept in memory until you call Close()
		// Function result:		true if successful
		// stream_cnt:				number of BaseSounds to be mixed
		// streams:						array with BaseSound pointers
		// offsets:						array with start time offsets in seconds (this is the audible sound data when StartAt( 0 ) is called)
		// max_length:				maximum length of the audio data in seconds (relative to StartAt( 0 ))
		//----------------------------------------------------------------------------------------
		Bool	Open(  Int32 stream_cnt, const BaseSound **streams, const Float *start_offsets, Float max_length );

		//----------------------------------------------------------------------------------------
		// Close audio device
		// If the BaseSounds used for Open() have been deleted in the meantime, their audio data will be released
		// Function result:		-
		//----------------------------------------------------------------------------------------
		void	Close( void );

		//----------------------------------------------------------------------------------------
		// Start audio output
		// Function result:		-
		// start:							position relative to the start of the audio data in seconds
		//----------------------------------------------------------------------------------------
		void	StartAt( Float64 start );

		//----------------------------------------------------------------------------------------
		// Start audio scrubbing (this will automatically stop audio device after duration)
		// Function result:		-
		// start:							position relative to the start of the audio data in seconds
		// duration:					scrub duration in seconds after which the audio device will be stopped
		//----------------------------------------------------------------------------------------
		void	Scrub( Float64 start, Float64 duration );

		//----------------------------------------------------------------------------------------
		// Stop audio output
		// Function result:		-
		//----------------------------------------------------------------------------------------
		void	Stop( void );

		//----------------------------------------------------------------------------------------
		// Check if the audio device is running
		// Function result:		true if audio is playing
		//----------------------------------------------------------------------------------------
		Bool	IsPlaying( void );

		//----------------------------------------------------------------------------------------
		// Return an estimate audio position
		// Function result:		the currently audible position in seconds
		//----------------------------------------------------------------------------------------
		Float64	GetPositionEstimate( void );

		//----------------------------------------------------------------------------------------
		// Set playback time scale
		// Function result:		-
		// scale							2.0 means twice as fast, 0.5 means half the speed, 0.0 is invalid
		//----------------------------------------------------------------------------------------
		void	SetScale( Float64 scale );

		//----------------------------------------------------------------------------------------
		// Get playback time scale
		// Function result:		current playback time scale (1.0 means real time)
		//----------------------------------------------------------------------------------------
		Float64	GetScale( void );

};



#else

#define GePlaySnd		GeSndOut

#endif

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#define LIB_SND 1000496

struct GeSndLib : public C4DLibrary
{
		GePlaySnd*	(*Alloc)									();
		void				(*Free)										(GePlaySnd *&data);

		// dummy audio methods
		Bool				(GePlaySnd::*OpenEx)			(const GeSndInfoEx &si);
		void				(GePlaySnd::*CloseEx)			();
		void				(GePlaySnd::*StartEx)			(Int32 start, Int32 count);
		void				(GePlaySnd::*StopEx)			();
		Bool				(GePlaySnd::*IsPlayingEx)	();
		Int32				(GePlaySnd::*GetPositionEx)();

		// new audio stuff
		Bool				(GePlaySnd::*Open)				( Int32 stream_cnt, const BaseSound **streams, const Float *start_offsets, Float max_length );
		void				(GePlaySnd::*Close)				();
		void				(GePlaySnd::*StartAt)			( Float64 start );
		void				(GePlaySnd::*Scrub)				( Float64 start, Float64 duration );
		void				(GePlaySnd::*Stop)				();
		Bool				(GePlaySnd::*IsPlaying)		();
		Float64				(GePlaySnd::*GetPositionEstimate)	();

		void				(GePlaySnd::*SetScale)		( Float64 scale );
		Float64				(GePlaySnd::*GetScale)		( void );
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif
