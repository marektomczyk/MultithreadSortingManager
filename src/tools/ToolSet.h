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

class ToolSet
{
public:
	/// @brief Write sorted chunk into file
	static void WriteChunkIntoFile(const std::vector<int>& sortedChunk,
		const unsigned int chunkCount);
	/// @brief Create tmp directory
	static void CreateTmpDirectory();
};

#endif /* TOOLS_TOOLSET_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
