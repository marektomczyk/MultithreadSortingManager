//============================================================================
// Name        : SortingManager.h
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager header file
//============================================================================

#ifndef _SORTINGMANAGER_H_
#define _SORTINGMANAGER_H_

#include "ThreadPool.hpp"
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>
#include <string.h>
#include "algorithm/SortAlgorithmBase.h"

#define CHUNK_SIZE 10

class SortingManager
{
public:
	/// @brief Class constructor
	SortingManager(const std::shared_ptr<SortAlgorithmBase> &pSortAlgorithm,
								 std::string fileName,
								 unsigned int threadCount = std::thread::hardware_concurrency());
	/// @brief Class destructor
	virtual ~SortingManager();
	/// @brief Sorting method
	void Sort();

private:
	/// @brief Returns read chunk from input file
	const char *  readChunkFromFile();

	/// @brief Pointer to sort algorithm
	std::shared_ptr<SortAlgorithmBase>     m_sortAlgorithm;
	/// @brief Count of worker thread
	const unsigned int                 		 m_threadCount;
	/// @brief Input file stream
	std::ifstream 								     		 m_file;
	/// @brief Count of chunk to sort
	unsigned int 						           		 m_chunkCount;
	/// @brief Access control mutex
	std::mutex							           		 m_mutex;
};

#endif /* SORTINGMANAGER_H_ */

//============================================================================
// End of file
//============================================================================
