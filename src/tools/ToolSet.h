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
	/// @brief Read chunk from given file
	static bool ReadChunkFromFile(
		std::ifstream& file, std::vector<int>& chunk, std::uintmax_t chunkSize);
	/// @brief Convert from bytes to integers
	static void SplitAndConvert(
		std::vector<std::byte>& bytes, std::vector<int>& numbers,
		const std::byte delim = std::byte{ 0x20 });
	/// @brief Create tmp directory
	static void CreateTmpDirectory();
	/// @brief Check if number is power of two
	static bool CheckIfIsPowerOfTwo(std::uintmax_t number);
	/// @brief Check if file is properly sorted
	static bool CheckIfIsSortedProperly(std::string fileName, bool asc = true);
};

#endif /* TOOLS_TOOLSET_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
