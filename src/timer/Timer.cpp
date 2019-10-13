//============================================================================
// Name        : Timer.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Timer source file
//============================================================================

#include "Timer.h"
#include <iostream> // TODO: Change to logger

/// @brief Time measurement of the main thread
std::shared_ptr<Timer::TimeRecord> Timer::m_mainThreadRecord;
/// @biref List of time measurements of worker threads
std::list<Timer::TimeRecord> Timer::m_threadsRecords;
/// @brief Access control mutex
std::recursive_mutex  Timer::m_mutex;

void Timer::StartTimer()
{
	m_mainThreadRecord = std::make_shared<TimeRecord>();
}

void Timer::StopTimer()
{
	if ( m_mainThreadRecord != nullptr )
	{
		m_mainThreadRecord->Stop();
	}
}

void Timer::AddRecord(const TimeRecord &record)
{
	std::lock_guard<std::recursive_mutex> lock { m_mutex };
	m_threadsRecords.push_back(record);
}

void Timer::ShowRecords()
{
	// TODO: Logging (use spdlog or other logger)
	if ( m_mainThreadRecord != nullptr )
	{
		std::cout << "Main thread: \n";
		std::cout << m_mainThreadRecord->ToString();
	}

	for(auto record : m_threadsRecords)
	{
		std::cout << "Worker threads: \n";
		std::cout << record.ToString();
	}
}

//============================================================================
// End of file
//============================================================================

