//============================================================================
// Name        : AlgorithmBase.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting algorithm base class
//============================================================================

#ifndef _ALGORITHM_SORTALGORITHMBASE_H_
#define _ALGORITHM_SORTALGORITHMBASE_H_

#include <string>
#include <vector>
#include <memory>

class SortAlgorithmBase
{
public:
	/// @brief Class constructor
	SortAlgorithmBase(const std::string algorithmName)
		: m_algorithmName(algorithmName) { }

	/// @brief Class destructor
	virtual ~SortAlgorithmBase() = default;

	/// @brief Get name function
	inline const std::string GetName() const { return m_algorithmName; }

	/// @brief Sort function
	virtual void Sort(const char * dataToSort, unsigned int chunkCount) = 0;

private:
	const std::string m_algorithmName;
};


#endif /* ALGORITHM_ALGORITHMBASE_H_ */
