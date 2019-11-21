//============================================================================
// Name        : SortingManager.cpp
// Author      : Marek Tomczyk
// Version     :
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Sorting manager source file
//============================================================================

#include "pch.h"
#include "../src/tools/ToolSet.h"
#include <vector>
#include <fstream>

/*****************************************************************************
 *	@brief  Write chunk into file
 *
 ****************************************************************************/
TEST(ToolSetTest, writeChunkIntoFile)
{
	ToolSet::CreateTmpDirectory();

	std::vector<int> chunk0 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	EXPECT_TRUE( ToolSet::WriteChunkIntoFile(chunk0, 0) );

	std::vector<int> chunk1 = { 12345678, 34234234, 2432432 };
	EXPECT_TRUE( ToolSet::WriteChunkIntoFile(chunk1, 1) );

	std::vector<int> chunk2 = { 1234567890 };
	EXPECT_TRUE(ToolSet::WriteChunkIntoFile(chunk2, 2));
}

/*****************************************************************************
 *	@brief  Try write empty chunk into file
 *
 ****************************************************************************/
TEST(ToolSetTest, writeEmptyChunk)
{
	std::vector<int> emptyChunk;
	EXPECT_FALSE( ToolSet::WriteChunkIntoFile(emptyChunk, 0) );
}

/*****************************************************************************
 *	@brief  Read previously saved chunk
 *
 ****************************************************************************/
TEST(ToolSetTest, readChunkFromFile)
{
	bool result = false;
	std::string path = "tmp/" + std::to_string(0u) + ".txt";
	std::ifstream file(path);

	if ( file.is_open() )
	{
		std::size_t size = 18;
		std::vector<std::byte> bytes;
		result = ToolSet::ReadChunkFromFile(file, bytes, size);

		if ( result )
		{
			std::vector<std::byte> verify =
				{ std::byte{'1'}, std::byte{' '},
					std::byte{'2'}, std::byte{' '},
					std::byte{'3'}, std::byte{' '},
					std::byte{'4'}, std::byte{' '},
					std::byte{'5'}, std::byte{' '},
					std::byte{'6'}, std::byte{' '},
					std::byte{'7'}, std::byte{' '},
					std::byte{'8'}, std::byte{' '},
					std::byte{'9'}, std::byte{' '}
				};
			for ( int i = 0; i < bytes.size(); ++i )
			{
				if ( bytes[i] != verify[i] )
				{
					result = false;
					break;
				}
			}
		}

		file.close();
	}

	EXPECT_TRUE(result);
}

/*****************************************************************************
 *	@brief  Check if chunk size is in the middle of the number (1)
 *
 ****************************************************************************/
TEST(ToolSetTest, readChunkFromUntilDelim1)
{
	bool result = false;
	std::string path = "tmp/" + std::to_string(1u) + ".txt";
	std::ifstream file(path);

	if ( file.is_open() )
	{
		std::size_t size = 20;
		std::vector<std::byte> bytes;
		result = ToolSet::ReadChunkFromFile(file, bytes, size);
		
		if ( result )
		{
			std::vector<std::byte> verify =
			{ std::byte{'1'}, std::byte{'2'},
				std::byte{'3'}, std::byte{'4'},
				std::byte{'5'}, std::byte{'6'},
				std::byte{'7'}, std::byte{'8'},
				std::byte{' '}, std::byte{'3'},
				std::byte{'4'}, std::byte{'2'},
				std::byte{'3'}, std::byte{'4'},
				std::byte{'2'}, std::byte{'3'},
				std::byte{'4'}, std::byte{' '},
				std::byte{'2'}, std::byte{'4'},
				std::byte{'3'}, std::byte{'2'},
				std::byte{'4'}, std::byte{'3'},
				std::byte{'2'}, std::byte{' '}
			};
			for ( int i = 0; i < bytes.size(); ++i )
			{
				if ( bytes[i] != verify[i] )
				{
					result = false;
					break;
				}
			}
		}

		file.close();
	}

	EXPECT_TRUE(result);
}

/*****************************************************************************
 *	@brief  Check if chunk size is in the middle of the number (2)
 *
 ****************************************************************************/
TEST(ToolSetTest, readChunkFromUntilDelim2)
{
	bool result = false;
	std::string path = "tmp/" + std::to_string(2u) + ".txt";
	std::ifstream file(path);

	if ( file.is_open() )
	{
		std::size_t size = 2;
		std::vector<std::byte> bytes;
		result = ToolSet::ReadChunkFromFile(file, bytes, size);

		if ( result )
		{
			std::vector<std::byte> verify =
			{ std::byte{'1'}, std::byte{'2'},
				std::byte{'3'}, std::byte{'4'},
				std::byte{'5'}, std::byte{'6'},
				std::byte{'7'}, std::byte{'8'},
				std::byte{'9'}, std::byte{'0'},
				std::byte{' '}
			};
			for ( int i = 0; i < bytes.size(); ++i )
			{
				if ( bytes[i] != verify[i] )
				{
					result = false;
					break;
				}
			}
		}

		file.close();
	}

	EXPECT_TRUE(result);
}

TEST(ToolSetTest, splitAndConvertTest)
{
	std::vector<std::byte> bytes =
	{ std::byte{'1'}, std::byte{'2'},
		std::byte{'3'}, std::byte{'4'},
		std::byte{'5'}, std::byte{'6'},
		std::byte{' '}, std::byte{' '},
		std::byte{'5'}, std::byte{'6'},
		std::byte{'7'}, std::byte{' '},
		std::byte{'8'}, std::byte{' '},
		std::byte{'9'}, std::byte{'1'},
		std::byte{'0'}, std::byte{' '},
		std::byte{'1'}, std::byte{'2'}
	};

	std::vector<int> verify =
	{
		123456, 567, 8, 910, 12
	};

	bool result = true;
	std::vector<int> coverted;
	ToolSet::SplitAndConvert(bytes, coverted);
	
	if ( !coverted.empty() )
	{
		for ( int i = 0; i < verify.size(); ++i )
		{
			if ( coverted[i] != verify[i] )
			{
				result = false;
				break;
			}
		}
	}

	if ( result && ( !bytes.empty() || coverted.empty() ) )
	{
		result = false;
	}

	EXPECT_TRUE(result);
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------