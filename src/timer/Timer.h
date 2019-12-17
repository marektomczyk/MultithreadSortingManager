//============================================================================
// Name        : Timer.h
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Timer header file
//============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <sstream>
#include <mutex>

class Timer
{
public:
	/// @brief Timer record class
	class TimeRecord
	{
	public:
		enum class eRecordType
		{
			RT_Sorting,
			RT_Merging,
			RT_ReadData,
			RT_WriteData,
			RT_All
		};

		/// @brief Class constructor
		TimeRecord(eRecordType type)
		{
			m_threadId = std::this_thread::get_id();
			m_recordType = type;
			m_start = std::chrono::high_resolution_clock::now();
			m_end = m_start;
			m_durationInMs = 0.0f;
		}
		/// @brief Stop time measuring method
		void Stop()
		{
			m_end = std::chrono::high_resolution_clock::now();
			m_durationInMs = (float)std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();
		}
		/// @brief Get type method
		eRecordType GetRecordType() const
		{
			return m_recordType;
		}
		/// @brief Get duration
		float GetDuration() const
		{
			return m_durationInMs;
		}
		/// @brief ToString method
		std::string ToString()
		{
			std::stringstream stream;
			stream << "ThreadId: " << m_threadId << " | Duration: " << m_durationInMs << "ms\n";
			return stream.str();
		}

	private:
		/// @brief Thread unique ID
		std::thread::id m_threadId;
		/// @brief Record type
		eRecordType m_recordType;
		/// @brief Start point of measuring time
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		/// @brief End point of measuring time
		std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
		/// @brief Duration in milliseconds
		float m_durationInMs;
	};

	/// @brief Add new timer record
	static void AddRecord(TimeRecord& record);
	/// @brief Get time by type
	static float GetTime(TimeRecord::eRecordType recordType);

private:
	Timer() = delete;
	~Timer() = delete;

	/// @biref List of time measurements of worker threads
	static std::list<TimeRecord> m_records;
	/// @brief Access control mutex
	static std::recursive_mutex m_mutex;
};

#endif /* TIMER_TIMER_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
