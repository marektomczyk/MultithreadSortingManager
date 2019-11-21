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
#include "../log/Logger.h"

/*****************************************************************************
 *	@brief Write chunk into file
 *
 *	@param sortedChunk - sorted chunk
 *	@param chunkCount  - sorted chunk number
 *
 *	@return None
 ****************************************************************************/
bool ToolSet::WriteChunkIntoFile(
	const std::vector<int>& sortedChunk, const unsigned int chunkCount)
{
	namespace fs = std::filesystem;
	bool result = false;

	if ( sortedChunk.empty() )
		return false;

	std::string path = "tmp/" + std::to_string(chunkCount) + ".txt";
	std::ofstream outFile(path);

	if ( outFile.is_open() )
	{
		const unsigned int numInRow = 10;
		unsigned int numCounter = numInRow;

		for ( auto num : sortedChunk )
		{
			outFile << num << " ";

			--numCounter;
			if ( numCounter == 0 )
			{
				numCounter = numInRow;
				outFile << "\n";
			}
		}

		result = true;
#if 0
		LOG_TRACE("Chunk {0} saved successfully", chunkCount);
#endif
		outFile.close();
	}

	return result;
}

/*****************************************************************************
 *	@brief  Reads data chunk from file
 * 
 *	@note   Reads more data if the position is in the middle of a number
 *
 *	@param  file  - file with data
 *  @param  chunk - vector into which the data will be loaded
 *  @param  chunkSize - chunk size
 *  @param  delim - delimeter (by default 0x32 - space)
 *
 *	@return true  - when successfully created
 *	        false - otherwise
 ****************************************************************************/
bool ToolSet::ReadChunkFromFile(
	std::ifstream& file, std::vector<std::byte>& chunk, 
	std::size_t chunkSize, std::byte delim)
{
	bool result = true;
	if ( !file.is_open() )
		result = false;

	if ( chunk.capacity() != chunkSize )
		chunk.resize(chunkSize);

	if ( result )
		file.read((char*) chunk.data(), chunkSize);

	if ( chunk.empty() )
		result = false;
	
	if ( result )
	{
		if ( ( chunk.back() != delim ) && ( !file.eof() ) )
		{
			std::byte byte;
			do
			{
				file.read((char*) &byte, sizeof(std::byte));
				if ( file )
					chunk.push_back(byte);
			} while ( ( byte != delim ) && ( file ) );
		}
	}
	return result;
}

/*****************************************************************************
 *	@brief Split data by given delim and convetrs from bytes to integers
 *
 *	@param  bytes - vector from data will be converted
 *  @param  numbers - vector into which the data will be loaded
 *  @param  delim - delimeter (by default 0x32 - space)
 *
 *	@return true  - when successfully created
 *	        false - otherwise
 ****************************************************************************/
void ToolSet::SplitAndConvert(
	std::vector<std::byte>& bytes, std::vector<int>& numbers,
	const std::byte delim)
{
	if ( !bytes.empty() )
	{
		std::stringstream stream;
		do
		{
			auto iterator = bytes.begin();
			if ( ( *iterator != delim ) && 
				    std::isdigit(static_cast<unsigned char>(*iterator)) )
			{
				stream << (int)((char) *iterator - '0');
			}
			else
			{
				if ( stream.tellp() != 0 )
				{
					int tmp;
					stream >> tmp;
					numbers.push_back(tmp);
					stream.str("");
					stream.clear();
				}
			}
			bytes.erase(iterator);
		} while ( !bytes.empty() );

		if ( stream.tellp() != 0 )
		{
			int tmp;
			stream >> tmp;
			numbers.push_back(tmp);
			stream.str("");
			stream.clear();
		}
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
	{
#if 0
		LOG_TRACE("tmp directory actually exist - remove it");
#endif
		fs::remove_all("tmp");
	}

#if 0
	LOG_TRACE("Creating tmp directory");
#endif
	fs::create_directories("tmp");
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
