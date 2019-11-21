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

class ToolSet
{
public:
	/// @brief Write sorted chunk into file
	static bool WriteChunkIntoFile(
		const std::vector<int>& sortedChunk, const unsigned int chunkCount);
	/// @brief Read chunk from given file
	static bool ReadChunkFromFile(
		std::ifstream& file, std::vector<std::byte>& chunk, 
		std::size_t chunkSize, std::byte delim = std::byte{ 0x20 });
	/// @brief Convert from bytes to integers
	static void SplitAndConvert(
		std::vector<std::byte>& bytes, std::vector<int>& numbers,
		const std::byte delim = std::byte{ 0x32 });
	/// @brief Create tmp directory
	static void CreateTmpDirectory();
};

#endif /* TOOLS_TOOLSET_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
