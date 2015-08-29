/////////////////////////////////////////////////////////////////////////////////
// High Resolution Timer.																											 //
// This timer is able to measure the elapsed time with 1 micro-second accuracy //
// in both Windows, Linux and Unix system                                      //
//                                                                             //
// AUTHOR: Song Ho Ahn (song.ahn@gmail.com)                                    //
// CREATED: 2003-01-13                                                         //
// UPDATED: 2006-01-13                                                         //
// UPDATED: 2011-08-15 by Maxim Bilan (maximb.mail@gmail.com)                  //
//                                                                             //
// Copyright (c) 2003 Song Ho Ahn                                              //
/////////////////////////////////////////////////////////////////////////////////

#ifndef _Timer_H_
#define _Timer_H_

#ifdef WIN32
	#include <windows.h>
#else
	#include <sys/time.h>
#endif

#include <stdlib.h>

class Timer
{
	
	private:
		double startTimeInMicroSec;               // starting time in micro-second
		double endTimeInMicroSec;                 // ending time in micro-second
		bool stopped;                             // stop flag 
#ifdef WIN32
		LARGE_INTEGER frequency;                  // ticks per second
		LARGE_INTEGER startCount;
		LARGE_INTEGER endCount;
#else
		timeval startCount;
		timeval endCount;
#endif

	public:
		Timer();                                    // default constructor
		~Timer();                                   // default destructor

		void start();                               // start timer
		void stop();                                // stop the timer
		
		double getElapsedTime();                    // get elapsed time in second
		double getElapsedTimeInSec();               // get elapsed time in second (same as getElapsedTime)
		double getElapsedTimeInMilliSec();          // get elapsed time in milli-second
		double getElapsedTimeInMicroSec();          // get elapsed time in micro-second
	
};

#endif
