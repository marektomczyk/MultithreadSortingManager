//============================================================================
// Name        : ToolSet.h
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Tool set header file
//============================================================================

#ifndef _TOOLSET_H_
#define _TOOLSET_H_

#include <vector>
#include <fstream>
#include "../algorithm/SortAlgorithmBase.h"

class ToolSet
{
public:
	/// @brief Write sorted chunk into file
	static bool WriteChunkIntoFile(
		const std::vector<int>& sortedChunk, const unsigned int chunkCount);
	/// @brief Read chunk from given file
	static bool ReadChunkFromFile(
		std::ifstream& file, std::vector<int>& chunk, std::uintmax_t chunkSize);
	/// @brief Create tmp directory
	static void CreateTmpDirectory();
	/// @brief Check if number is power of two
	static bool CheckIfIsPowerOfTwo(
		std::uintmax_t number);
	/// @brief Check if file is properly sorted
	static bool CheckIfIsSortedProperly(
		std::string fileName, bool asc = true);
	/// @brief Get sort algorithm by name
	static std::shared_ptr< SortAlgorithmBase> GetSortAlgorithmByName(
		const std::string& algorithmName);
};

#endif /* TOOLS_TOOLSET_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
