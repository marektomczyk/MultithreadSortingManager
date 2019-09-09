//============================================================================
// Name        : main.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Main function
//============================================================================

#include <iostream>
#include "SortingManager.h"
#include "algorithm/QuickSortAlgorithm.h"

int main( int argc, char* argv[] )
{
	SortingManager sortingManager(new QuickSortAlgorithm, "in.txt", 1u);
	sortingManager.Sort();

	return 0;
}
