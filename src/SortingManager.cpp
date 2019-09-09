//============================================================================
// Name        : SortingManager.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager source file
//============================================================================

#include "SortingManager.h"

SortingManager::SortingManager(AlgorithmBase *pSortAlgorithm, std::string fileName, const unsigned int threadCount)
	: m_threadCount(threadCount)
{
	if( pSortAlgorithm != nullptr )
	{
		m_sortAlgorithm.reset( pSortAlgorithm );
	}

	if( !fileName.empty() )
	{
		m_file.open(fileName, std::ios::binary | std::ios::ate);
		unsigned long long int fileSize = m_file.tellg();

		if( fileSize < CHUNK_SIZE )
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

SortingManager::~SortingManager()
{
	if( m_file.is_open() )
	{
		m_file.close();
	}
}

void SortingManager::Sort()
{
	{
		auto sortedChunkCounter = 0u;
		ThreadPool threadPool{ m_threadCount };

		while( sortedChunkCounter < m_chunkCount )
		{
			while( !threadPool.IsAnyThreadIdle() )
			{
				// TODO: logging
				//std::cout << "Waiting for idle thread (10ms)\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			if( threadPool.IsAnyThreadIdle() )
			{
				auto chunk = "";
				if( chunk != nullptr )
				{
					threadPool.AddTask(&AlgorithmBase::Sort, m_sortAlgorithm.get(), chunk, sortedChunkCounter);
				}
			}
		}
	}
}



