//============================================================================
// Name        : SortingManager.h
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager header file
//============================================================================

#ifndef _SORTINGMANAGER_H_
#define _SORTINGMANAGER_H_

#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>
#include <string.h>
#include "../algorithm/SortAlgorithmBase.h"
#include "../threadPool/ThreadPool.hpp"

#define CHUNK_SIZE 1000000

class SortingManager
{
public:
	/// @brief Class constructor
	SortingManager(const std::shared_ptr<SortAlgorithmBase>& pSortAlgorithm,
		std::string const& fileName,
		unsigned int threadCount = std::thread::hardware_concurrency());
	/// @brief Class destructor
	virtual ~SortingManager();
	/// @brief 
	void Run();

private:
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

	/// @brief Before sort
	void beforeRun();
	/// @brief Sorting method
	void sort();
	/// @brief Merge sorted chunks
	void merge();
	/// @brief After sort
	void afterRun();
};

#endif /* SORTINGMANAGER_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
