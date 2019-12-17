//============================================================================
// Name        : Timer.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Timer source file
//============================================================================

#include "Timer.h"
#include "../log/Logger.h"

/// @biref List of time measurements of worker threads
std::list<Timer::TimeRecord> Timer::m_records;
/// @brief Access control mutex
std::recursive_mutex  Timer::m_mutex;

void Timer::AddRecord(TimeRecord& record)
{
	std::lock_guard<std::recursive_mutex> lock{ m_mutex };
	m_records.push_back(record);
}

float Timer::GetTime(TimeRecord::eRecordType recordType)
{
	float time = 0.0f;

	for ( auto record : m_records )
	{
		if ( ( record.GetRecordType() == recordType ) || 
			   ( recordType == TimeRecord::eRecordType::RT_All ) )
		{
			time += record.GetDuration();
		}
	}

	return time;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------

