//============================================================================
// Name        : Timer.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Timer source file
//============================================================================

#include "Timer.h"
#include "../log/Logger.h"

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
	if (m_mainThreadRecord != nullptr)
	{
		m_mainThreadRecord->Stop();
	}
}

void Timer::AddRecord(const TimeRecord& record)
{
	std::lock_guard<std::recursive_mutex> lock{ m_mutex };
	m_threadsRecords.push_back(record);
}

void Timer::ShowRecords()
{
	if (m_mainThreadRecord != nullptr)
	{
		LOG_INFO("=========================================");
		LOG_INFO("Main thread:");
		LOG_INFO("{0}", m_mainThreadRecord->ToString());
	}

	for (auto record : m_threadsRecords)
	{
		LOG_INFO("Worker threads:");
		LOG_INFO("{0}", record.ToString());
	}
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------

