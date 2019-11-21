//============================================================================
// Name        : SortingManager.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager source file
//============================================================================

#include "SortingManager.h"
#include "../tools/ToolSet.h"
#include "../timer/Timer.h"
#include "../log/Logger.h"
#include <filesystem>

/*****************************************************************************
 *	@brief Class constructor
 *
 ****************************************************************************/
SortingManager::SortingManager(const std::shared_ptr<SortAlgorithmBase>& pSortAlgorithm,
															 std::string const& fileName, 
															 const unsigned int threadCount)
	: m_sortAlgorithm(pSortAlgorithm),
		m_threadCount(threadCount),
		m_chunkCount(0),
		m_chunkSize(0)
{
	if ( !fileName.empty() )
	{
		m_file.open(fileName, std::ios::binary);
		if ( m_file.is_open() )
		{
			auto fileSize = std::filesystem::file_size(fileName);

			if ( fileSize < MAX_RAM_USAGE )
			{
				m_chunkCount = 1u;
				m_chunkSize = (unsigned int) fileSize;
			}
			else
			{
				m_chunkSize = (unsigned int) MAX_RAM_USAGE / m_threadCount;
				m_chunkCount = (unsigned int) fileSize / m_chunkSize;
			}

			ToolSet::CreateTmpDirectory();
		}
		else
		{
			LOG_TRACE("Could not open file {0}", fileName);
		}
	}
}

/*****************************************************************************
 *	@brief Class destructor
 *
 ****************************************************************************/
SortingManager::~SortingManager()
{
	if ( m_file.is_open() )
	{
		m_file.close();
	}
}

/*****************************************************************************
 *	@brief Perform all steps needed to sort data:
 *				 1) Start timer
 *				 2) Sort data in parallel
 *			   3) Merge sorted chunks into one output file
 *			   4) Stop timer
 *         5) Show results on the console screen
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::Run()
{
	beforeRun();
	sort();
	merge();
	afterRun();
}

/*****************************************************************************
 *	@brief Method called before sorting
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::beforeRun()
{
	Timer::StartTimer();
	LOG_INFO("Sorting manager start working...");
}

/*****************************************************************************
 *	@brief Method called after sorting
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::afterRun()
{
	LOG_INFO("Sorting manager finished");
	Timer::StopTimer();
	Timer::ShowRecords();
}

/*****************************************************************************
 *	@brief Sort data method
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::sort()
{
	auto sortedChunkCounter = 0u;
	ThreadPool threadPool{ m_threadCount };

	while ( sortedChunkCounter < m_chunkCount )
	{
		while ( !threadPool.IsAnyThreadIdle() )
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		if ( threadPool.IsAnyThreadIdle() )
		{
			std::vector<std::byte>* chunk = new std::vector<std::byte>();
						
			if ( chunk != nullptr )
			{
				if ( ToolSet::ReadChunkFromFile(m_file, *chunk, m_chunkSize) )
				{
					(void)threadPool.AddTask(&SortAlgorithmBase::Sort, m_sortAlgorithm, chunk, sortedChunkCounter);
					++sortedChunkCounter;
				}
			}
		}
	}
}

/*****************************************************************************
 *	@brief Merge sorted chunks into one output file
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::merge()
{
	auto mergedChunksCounter = 0u;
	ThreadPool threadPool{ m_threadCount };
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
