/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <time.h>
#include <iomanip>
#include <iostream>
#include <iomanip>

/*
		CLOCK_REALTIME
              System-wide  realtime clock.  Setting this clock requires appro-
              priate privileges.

       CLOCK_MONOTONIC
              Clock that cannot be set and  represents  monotonic  time  since
              some unspecified starting point.

       CLOCK_PROCESS_CPUTIME_ID
              High-resolution per-process timer from the CPU.

       CLOCK_THREAD_CPUTIME_ID

*/
template <int clock = CLOCK_THREAD_CPUTIME_ID >
class Time	{
template <int C> friend std::ostream& operator << (std::ostream& cout, Time<C>& time);
	struct timespec t;
public:
	Time()	{
		clock_gettime(clock, &t);
	}
	
	Time(__time_t s, long int ns)	{
		t.tv_sec = s;
		t.tv_nsec = ns;
	}
	
	Time operator -(const Time& time)	{
		Time result;
		result.t.tv_sec = t.tv_sec - time.t.tv_sec;
		result.t.tv_nsec = t.tv_nsec - time.t.tv_nsec;
		if (result.t.tv_nsec<0)	{
			result.t.tv_sec--;
			result.t.tv_nsec += 1000000000;
		}
		return result;
	}
	
};

template <int C>
std::ostream& operator << (std::ostream& cout, Time<C>& time)
{
	cout << time.t.tv_sec  << ':';
	cout << std::setfill('0') << std::setw(9) << time.t.tv_nsec;
    return cout;
}


