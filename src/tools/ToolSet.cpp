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
#include "../timer/Timer.h"

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

	std::string path = "tmp//" + std::to_string(chunkCount) + ".bin";
	std::ofstream outFile(path, std::ios::binary);

	if ( outFile.is_open() )
	{
		Timer::TimeRecord record(Timer::TimeRecord::eRecordType::RT_WriteData);
		outFile.write((char*) sortedChunk.data(), (std::streamsize) sortedChunk.size() * sizeof(sortedChunk[0]));
		record.Stop();
		Timer::AddRecord(record);
		if ( outFile )
		{
			result = true;
			LOG_TRACE("Chunk {0} saved successfully", chunkCount);
		}
		outFile.close();
	}

	return result;
}

/*****************************************************************************
 *	@brief  Reads data chunk from file
 *
 *	@param  file  - file with data
 *  @param  chunk - vector into which the data will be loaded
 *  @param  chunkSize - chunk size
 *
 *	@return true  - when successfully created
 *	        false - otherwise
 ****************************************************************************/
bool ToolSet::ReadChunkFromFile(
	std::ifstream& file, std::vector<int>& chunk, std::uintmax_t chunkSize)
{
	bool result = true;
	if ( !file.is_open() )
		result = false;

	if ( chunk.capacity() != chunkSize )
		chunk.resize(chunkSize);

	if ( result )
	{
		Timer::TimeRecord record(Timer::TimeRecord::eRecordType::RT_ReadData);
		file.read((char*)chunk.data(), (std::streamsize) chunkSize * sizeof(chunk[0]));
		record.Stop();
		Timer::AddRecord(record);
	}

	if ( chunk.empty() )
		result = false;
	
	return result;
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
		LOG_TRACE("tmp directory actually exist - remove it");
		fs::remove_all("tmp");
	}

	LOG_TRACE("Creating tmp directory");
	fs::create_directories("tmp");
}

/*****************************************************************************
 *	@brief Check if given number is power of two
 *
 *	@param number - number to check
 *
 *	@return true  - when is power of two
 *	        false - otherwise
 ****************************************************************************/
bool ToolSet::CheckIfIsPowerOfTwo(std::uintmax_t number)
{
	return ( number != 0 ) && ( (number & ( number - 1 ) ) == 0 );
}

/*****************************************************************************
 *	@brief Check if given file is sorted properly
 *
 *	@param fileName - input file name
 *  @param asc - true when ascending / false if descending
 *
 *	@return true  - when is sorted properly
 *	        false - otherwise
 ****************************************************************************/
bool ToolSet::CheckIfIsSortedProperly(std::string fileName, bool asc)
{
	bool result = true;
	if ( fileName.empty() )
		result = false;

	if ( result )
	{
		std::ifstream file(fileName, std::ios::binary);
		if ( file.is_open() )
		{
			int previous;
			file.read((char*)&previous, (std::streamsize) sizeof(previous));

			while ( file )
			{
				int temp;
				file.read((char*)&temp, (std::streamsize) sizeof(temp));
				if ( file )
				{
					if ( ( asc && temp < previous ) || 
						   ( !asc && temp > previous ) )
					{
						result = false;
						break;
					}
					else
					{
						previous = temp;
					}
				}
			}

			file.close();
		}
	}

	return result;
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------
