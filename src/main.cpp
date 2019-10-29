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
#include "timer/Timer.h"

int main( int argc, char* argv[] )
{
	Timer::StartTimer();

	SortingManager sortingManager(std::make_shared<QuickSortAlgorithm>(), "in.txt", 1u);
	sortingManager.Sort();


	Timer::StopTimer();
	Timer::ShowRecords();
	return 0;
}

//============================================================================
// End of file
//============================================================================
