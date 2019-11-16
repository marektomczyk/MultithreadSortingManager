//============================================================================
// Name        : main.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Main function
//============================================================================

#include <iostream>
#include "sortingManager/SortingManager.h"
#include "algorithm/QuickSort/QuickSortAlgorithm.h"
#include "tools/ToolSet.h"

/// @brief Main function
int main(int argc, char* argv[])
{
	SortingManager sortingManager(std::make_shared<QuickSortAlgorithm>(), "in.txt", 1u);
	sortingManager.Sort();

	return 0;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
