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
#include "argParser/ArgParser.hpp"

// Algorithm's
#include "algorithm/QuickSort/QuickSortAlgorithm.h"
#include "algorithm/BitonicSort/BitonicSortAlgorithm.h"
#include "algorithm/MergeSort/MergeSortAlgorithm.h"

/// @brief Main function
int main(int argc, char* argv[])
{
	// Init logger
	Logger::Init();
	// Parse arguments
	auto parseRes = ArgParser::GetInstance().ParseArguments(argc, argv);
	auto showHelpRequest = false;

	if ( parseRes == ArgParser::eParseResult::PARSE_OK )
	{
		auto inFileName        = ArgParser::GetInstance().GetInputFileName();
		auto outFileName       = ArgParser::GetInstance().GetOutputFileName();
		auto logFileName       = ArgParser::GetInstance().GetLogFileName();
		auto sortAlgorithmName = ArgParser::GetInstance().GetSortAlgorithmName();
		auto threadCount       = ArgParser::GetInstance().GetThreadCount();
		auto withComparison    = ArgParser::GetInstance().IsWithComparison();
		auto withVerify        = ArgParser::GetInstance().VerifyAfterSortEnabled();
		showHelpRequest        = ArgParser::GetInstance().ShowHelpRequest();

		// Create log file and init file logger
		if ( !logFileName.empty() && Logger::CreateLogFile(logFileName) )
		{
			LOG_INFO("Log file created");
		}
		
		std::list< std::shared_ptr<SortAlgorithmBase> > algorithms;
		if ( withComparison )
		{
			LOG_TRACE("Sorting with all possible algorithms enabled");
			LOG_WARN("! Output file will be overwritten by subsequent algorithms !");

			algorithms.push_back(std::make_shared<QuickSortAlgorithm>());
			algorithms.push_back(std::make_shared<MergeSortAlgorithm>());
			algorithms.push_back(std::make_shared<BitonicSortAlgorithm>());
		}
		else
		{
			auto algorithm = ToolSet::GetSortAlgorithmByName(sortAlgorithmName);
			if ( algorithm != nullptr )
				algorithms.push_back(algorithm);
		}

		if ( !algorithms.empty() )
		{
			for ( auto sortAlgorithm : algorithms )
			{
				if ( sortAlgorithm != nullptr )
				{
					LOG_INFO("Input file: {0}", inFileName);
					LOG_INFO("Algorithm:  {0}", sortAlgorithm->GetName());
					LOG_INFO("Threads:    {0}", threadCount);

					// Create sorting manager
					SortingManager sortingManager(sortAlgorithm, inFileName, outFileName, threadCount);
					// Run sorting manager
					sortingManager.Run();
				}
			}

			if ( withVerify )
			{
				// Verify sorted file
				LOG_TRACE("File verifying started...");
				auto isSortedProperly = ToolSet::CheckIfIsSortedProperly(outFileName);

				if ( isSortedProperly )
				{
					LOG_INFO("File was sorted properly!");
				}
				else
				{
					LOG_ERROR("File was not sorted properly!");
				}
			}
		}
		else
		{
			LOG_ERROR("Algorithm {0} not found! Pass -h or --help to get help", sortAlgorithmName);
		}
	}
	else
	{
		LOG_ERROR("Parse error! Pass -h or --help to get help");
	}


	if ( parseRes != ArgParser::eParseResult::PARSE_OK || showHelpRequest )
	{
		auto helpStr = ArgParser::GetInstance().GetHelp();
		std::cout << helpStr;
	}

	return 0;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
