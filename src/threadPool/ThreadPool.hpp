//============================================================================
// Name        : ThreadPool.hpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Thread pool implementation
//============================================================================

#ifndef _THREADPOOL_HPP_
#define _THREADPOOL_HPP_

#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>
#include <memory>
#include <cassert>

class ThreadPool
{
public:
	using Task = std::function < void() >;

	/// @brief Class constructor
	ThreadPool(const unsigned int threadCount = std::thread::hardware_concurrency())
		: m_stopProcessing(false), m_isEmergencyStop(false), m_isPaused(false)
	{
		if (threadCount == 0)
			assert(false);

		m_workers.reserve(threadCount);

		for (unsigned int i = 0u; i < threadCount; ++i)
		{
			m_workers.emplace_back([this]() { run(); });
		}
	}

	/// @brief Class destructor
	virtual ~ThreadPool()
	{
		{
			std::unique_lock< std::recursive_mutex > lock{ m_mutex };
			m_stopProcessing = true;
		}

		m_notifier.notify_all();

		for (auto& thread : m_workers)
		{
			if (thread.joinable())
				thread.join();
		}
	}

	/// @brief Return worker threads count
	inline unsigned int GetThreadCount() const
	{
		return m_workers.size();
	}

	/// @brief Return true if is any worker thread idle
	bool IsAnyThreadIdle()
	{
		bool result = true;

		{
			std::unique_lock< std::recursive_mutex > lock{ m_mutex };
			if (m_pendingTask != nullptr)
				result = false;
		}

		return result;
	}

	/// @brief Emergency stop thread pool
	void EmergencyStop()
	{
		{
			std::unique_lock< std::recursive_mutex > lock{ m_mutex };
			m_isEmergencyStop = true;
		}

		m_notifier.notify_all();
	}

	/// @brief Pause thread pool
	void Pause()
	{
		{
			std::unique_lock< std::recursive_mutex > lock{ m_mutex };
			m_isPaused = true;
		}

		m_notifier.notify_all();
	}

	/// @brief Add pending task
	template < typename Function, typename... Args >
	auto AddTask(Function&& fun, Args&& ... args)
		-> std::future< typename std::result_of< Function(Args...) >::type >
	{
		using returnType = typename std::result_of< Function(Args...) >::type;

		auto task = std::make_shared< std::packaged_task< returnType() > >
			(
				std::bind
				(
					std::forward< Function >(fun),
					std::forward< Args >(args)...
				)
				);

		std::future< returnType > result = task->get_future();

		{
			std::unique_lock< std::recursive_mutex > lock{ m_mutex };

			if (m_stopProcessing || m_isEmergencyStop)
				assert(false);

			if (m_pendingTask == nullptr)
				m_pendingTask = std::make_unique< Task >([task]() { (*task)(); });
		}

		m_notifier.notify_one();

		return result;
	}


	ThreadPool(const ThreadPool& source) = delete;
	ThreadPool& operator= (const ThreadPool& source) = delete;

private:
	std::vector < std::thread >		  m_workers;
	std::recursive_mutex		  	    m_mutex;
	std::condition_variable_any     m_notifier;
	std::unique_ptr< Task >			    m_pendingTask;
	std::atomic < bool >						m_stopProcessing;
	std::atomic < bool >						m_isEmergencyStop;
	std::atomic < bool >            m_isPaused;

	/// @brief Worker thread method
	void run()
	{
		while (true)
		{
			std::unique_ptr<Task> task;

			{
				std::unique_lock< std::recursive_mutex > lock{ m_mutex };
				m_notifier.wait
				(
					lock,
					[this]()
					{
						return (m_pendingTask != nullptr && !m_isPaused)
							|| m_isEmergencyStop
							|| m_stopProcessing;
					}
				);

				if ((m_pendingTask == nullptr && m_stopProcessing) || m_isEmergencyStop)
					return;

				task = std::move(m_pendingTask);
			}

			(*task)();
		}
	}

};

#endif

//============================================================================
// End of file
//============================================================================
