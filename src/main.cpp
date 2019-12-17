//============================================================================
// Name        : main.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Main function
//============================================================================

#include "sortingManager/SortingManager.h"
#include "tools/ToolSet.h"
#include "log/Logger.h"

// Algorithm's
#include "algorithm/QuickSort/QuickSortAlgorithm.h"
#include "algorithm/BitonicSort/BitonicSortAlgorithm.h"
#include "algorithm/MergeSort/MergeSortAlgorithm.h"

/// @brief Main function
int main(int argc, char* argv[])
{
	// Init logger
	Logger::Init();
	// Create sorting manager
	SortingManager sortingManager(std::make_shared<MergeSortAlgorithm>(), "in-512mb.bin", 4u);
	// Run sorting manager
	sortingManager.Run();

	// Verify sorted file
	if ( ToolSet::CheckIfIsSortedProperly("output.bin") )
	{
		LOG_INFO("File was sorted properly!");
	}
	else
	{
		LOG_ERROR("File was not sorted properly!");
	}
	return 0;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
