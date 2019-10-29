//============================================================================
// Name        : SortingManager.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager source file
//============================================================================

#include "SortingManager.h"

/*****************************************************************************
 *	@brief Class constructor
 *
 ****************************************************************************/
SortingManager::SortingManager(const std::shared_ptr<SortAlgorithmBase> &pSortAlgorithm, std::string fileName, const unsigned int threadCount)
	: m_sortAlgorithm(pSortAlgorithm),
		m_threadCount(threadCount)
{
	if ( !fileName.empty() )
	{
		m_file.open(fileName, std::ios::ate);
		unsigned long long int fileSize = m_file.tellg();

		if ( fileSize < CHUNK_SIZE )
		{
			m_chunkCount = fileSize;
		}
		else
		{
			m_chunkCount = fileSize / CHUNK_SIZE;
		}

		m_file.seekg(0, m_file.beg);
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
 *	@brief Perform all steps needed to sort data
 *
 *	@param None
 *
 *	@return None
 ****************************************************************************/
void SortingManager::Sort()
{
	{
		auto sortedChunkCounter = 0u;
		ThreadPool threadPool{ m_threadCount };

		while ( sortedChunkCounter < m_chunkCount )
		{
			while ( !threadPool.IsAnyThreadIdle() )
			{
				// TODO: logging
				//std::cout << "Waiting for idle thread (10ms)\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			if ( threadPool.IsAnyThreadIdle() )
			{
				auto chunk = readChunkFromFile();
				if ( chunk != nullptr )
				{
					threadPool.AddTask(&SortAlgorithmBase::Sort, m_sortAlgorithm, chunk, sortedChunkCounter);
				}
			}
		}
	}
}

/*****************************************************************************
 *	@brief Reads chunk of data from file
 *
 *	@param None
 *
 *	@return Chunk from file in bytes
 ****************************************************************************/
const char * SortingManager::readChunkFromFile()
{
	char * chunk = nullptr;

	if ( m_file.is_open() )
	{
		chunk = new char[CHUNK_SIZE + 1];
		if ( chunk != nullptr )
		{
			memset(chunk, '\0', CHUNK_SIZE);
			m_file.read(chunk, CHUNK_SIZE);

			std::cout << chunk << "\n";
		}
	}

	return chunk;
}

//============================================================================
// End of file
//============================================================================
