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

/*****************************************************************************
 *	@brief Convert bytes to std::vector
 *
 *	@param bytes     - block of memory which contains data from file
 *	@param separator - separator between two numbers read from file
 *
 *	@return std::vector with values
 ****************************************************************************/
std::vector<int> ToolSet::ConvertBytesToVector(const char * bytes,
																			         const char separator)
{
  std::vector<int> output;

  if ( bytes != nullptr )
  {
  	std::string_view strv(bytes);
  	std::vector<std::string_view> values;
  	std::size_t first = 0;

  	while ( first < strv.size() )
  	{
  		const auto second = strv.find_first_of(separator, first);
  		if ( first != second )
  			values.emplace_back( strv.substr(first, second-first) );

  		if ( second == std::string_view::npos )
  			break;

  		first = second + 1;
  	}

  	output.reserve( values.size() );
  	for ( auto val : values )
  	{
  		output.emplace_back( std::stoi(val.data()) );
  	}
  }

  return output;
}

//============================================================================
// End of file
//============================================================================
