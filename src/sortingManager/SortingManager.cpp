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
#include <queue>

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
			if ( !ToolSet::CheckIfIsPowerOfTwo(fileSize) )
			{
				LOG_ERROR("Filesize is not power of two! Could not sort this file.");
				m_file.close();
				return;
			}

			if ( fileSize < MAX_RAM_USAGE )
			{
				m_chunkCount = 1u;
				m_chunkSize = (unsigned int) fileSize;
			}
			else
			{
				m_chunkSize = (MAX_RAM_USAGE / m_threadCount) / sizeof(int);
				m_chunkCount = (fileSize / (m_chunkSize * (std::uintmax_t) sizeof(int)));

				if ( m_chunkCount > _getmaxstdio() )
				{
					auto maxstdio = _getmaxstdio();
					_setmaxstdio((int) m_chunkCount + maxstdio);
				}
			}

			ToolSet::CreateTmpDirectory();
		}
		else
		{
			LOG_ERROR("Could not open file {0}", fileName);
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
	if ( !m_file.is_open() )
		return;

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
			std::vector<int>* chunk = new std::vector<int>();
						
			if ( chunk != nullptr )
			{
				if ( ToolSet::ReadChunkFromFile(m_file, *chunk, m_chunkSize) )
				{
					(void)threadPool.AddTask(&SortAlgorithmBase::Sort, m_sortAlgorithm, chunk, sortedChunkCounter);
					++sortedChunkCounter;
				}
				else
				{
					delete chunk;
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
	LOG_INFO("Merge temporary files started");

	auto comparator = [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) { return p1.first > p2.first; };
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, decltype(comparator)> minHeap(comparator);

	std::unique_ptr<std::ifstream[]> handles = std::make_unique<std::ifstream[]>(m_chunkCount);
	if (handles == nullptr)
		LOG_ERROR("No enough memory!");

	for ( unsigned int i = 0; i < m_chunkCount; i++ )
	{
		std::string sortedInputFileName = "tmp//" + std::to_string(i) + ".bin";
		handles[i].open(sortedInputFileName.c_str(), std::ios::binary);
		if ( handles[i].is_open() )
		{
			int firstValue;
			handles[i].read((char*) &firstValue, sizeof(firstValue));
			if ( handles[i] )
				minHeap.push(std::pair<int, int>(firstValue, i));
		}
		else
			LOG_ERROR("Could not open {0} file", sortedInputFileName);
	}

	std::ofstream outputFile("output.bin", std::ios::binary);
	if ( outputFile.is_open() )
	{
		while ( minHeap.size() > 0 )
		{
			auto minPair = minHeap.top();
			minHeap.pop();
			outputFile.write((char*) &minPair.first, sizeof(minPair.first));
			int nextValue;
			flush(outputFile);
			handles[minPair.second].read((char*) &nextValue, sizeof(nextValue));

			if ( handles[minPair.second] )
				minHeap.push(std::pair <int, int>(nextValue, minPair.second));
		}
		outputFile.close();
	}
	else
		LOG_ERROR("Could not create output file!");

	for (unsigned int i = 0; i < m_chunkCount; ++i)
		handles[i].close();

	LOG_INFO("Merge temporary files finished");
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------