//============================================================================
// Name        : ToolSet.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Tool set implementation
//============================================================================

#include "ToolSet.h"
#include <string_view>
#include <sstream>
#include <charconv>
#include <fstream>
#include <filesystem>

/*****************************************************************************
 *	@brief Write chunk into file
 *
 *	@param sortedChunk - sorted chunk
 *	@param chunkCount  - sorted chunk number
 *
 *	@return None
 ****************************************************************************/
void ToolSet::WriteChunkIntoFile(const std::vector<int>& sortedChunk,
	const unsigned int chunkCount)
{
	namespace fs = std::filesystem;

	if (sortedChunk.empty())
		return;

	std::string path = "tmp/" + std::to_string(chunkCount) + ".txt";

	std::ofstream outFile;
	outFile.open(path);

	if (outFile.is_open())
	{
		const unsigned int numInRow = 10;
		unsigned int numCounter = numInRow;

		for (auto num : sortedChunk)
		{
			outFile << num << " ";

			--numCounter;
			if (numCounter == 0)
			{
				numCounter = numInRow;
				outFile << "\n";
			}
		}

		outFile.close();
	}
}

/*****************************************************************************
 *	@brief Creates tmp directory, clear tmp folder if actually exists
 *
 *	@param None
 *
 *	@return true  - when successfully created
 *	        false - otherwise
 ****************************************************************************/
void ToolSet::CreateTmpDirectory()
{
	namespace fs = std::filesystem;

	bool res = false;

	if (fs::exists("tmp"))
		fs::remove_all("tmp");

	fs::create_directories("tmp");
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
