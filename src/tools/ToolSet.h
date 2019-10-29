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
	/// @biref Convert bytes into std::vector
	static std::vector<int> ConvertBytesToVector(const char * bytes,
																						   const char separator);
};

#endif /* TOOLS_TOOLSET_H_ */

//============================================================================
// End of file
//============================================================================
