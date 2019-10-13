//============================================================================
// Name        : SortingManager.h
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager header file
//============================================================================

#ifndef _SORTINGMANAGER_H_
#define _SORTINGMANAGER_H_

#include "algorithm/AlgorithmBase.h"
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

#define CHUNK_SIZE 10

class SortingManager
{
public:
	/// @brief Class constructor
	SortingManager(AlgorithmBase *pSortAlgorithm,
								 std::string fileName,
								 unsigned int threadCount = std::thread::hardware_concurrency());
	/// @brief Class destructor
	virtual ~SortingManager();
	/// @brief Sorting method
	void Sort();

private:
	std::shared_ptr<AlgorithmBase>     m_sortAlgorithm;
	const unsigned int                 m_threadCount;
	std::ifstream 								     m_file;
	unsigned int 						           m_chunkCount;
	std::mutex							           m_mutex;
};

#endif /* SORTINGMANAGER_H_ */

//============================================================================
// End of file
//============================================================================
