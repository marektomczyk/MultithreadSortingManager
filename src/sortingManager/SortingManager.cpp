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

/*****************************************************************************
 *	@brief Class constructor
 *
 ****************************************************************************/
SortingManager::SortingManager(const std::shared_ptr<SortAlgorithmBase>& pSortAlgorithm, std::string fileName, const unsigned int threadCount)
	: m_sortAlgorithm(pSortAlgorithm),
	m_threadCount(threadCount),
	m_chunkCount(0)
{
	if (!fileName.empty())
	{
		m_file.open(fileName, std::ios::ate);
		unsigned long long int fileSize = m_file.tellg();

		if (fileSize < CHUNK_SIZE)
		{
			m_chunkCount = (unsigned int) fileSize;
		}
		else
		{
			m_chunkCount = (unsigned int) fileSize / CHUNK_SIZE;
		}

		m_file.seekg(0, m_file.beg);
		ToolSet::CreateTmpDirectory();
	}
}

/*****************************************************************************
 *	@brief Class destructor
 *
 ****************************************************************************/
SortingManager::~SortingManager()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
}

/*****************************************************************************
 *	@brief Perform all steps needed to sort data
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::Sort()
{
	Timer::StartTimer();

	auto sortedChunkCounter = 0u;
	ThreadPool threadPool{ m_threadCount };

	while (sortedChunkCounter < m_chunkCount)
	{
		while (!threadPool.IsAnyThreadIdle())
		{
			// TODO: logging
			//std::cout << "Waiting for idle thread (10ms)\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		if (threadPool.IsAnyThreadIdle())
		{
			auto chunk = readChunkFromFile();
			if (chunk != nullptr)
			{
				(void)threadPool.AddTask(&SortAlgorithmBase::Sort, m_sortAlgorithm, chunk, sortedChunkCounter);
				++sortedChunkCounter;
			}
		}
	}

	Timer::StopTimer();
	Timer::ShowRecords();
}

/*****************************************************************************
 *	@brief Reads chunk of data from file
 *
 *	@param None
 *
 *	@return Chunk from file in bytes
 ****************************************************************************/
std::vector<int>* SortingManager::readChunkFromFile()
{
	std::vector<int>* chunk = nullptr;

	if (m_file.is_open())
	{
		chunk = new std::vector<int>();
		if (chunk != nullptr)
		{
			int number;
			int counter = 0;
			while ((counter < CHUNK_SIZE) && (m_file >> number))
			{
				++counter;
				chunk->push_back(number);
			}
		}
	}

	return chunk;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
