#include "pch.h"
#include <fstream>
#include <vector>


void readDataFromFile(std::ifstream& inFile, std::vector<int>& data)
{
	if ( inFile.is_open() )
	{
		int tmp;
		while ( inFile >> tmp )
			data.push_back(tmp);
	}
}

bool verifySortedChunksTest(std::vector<int>& data)
{
	bool result = true;

	int prevNum = data[0];
	for ( auto num : data )
	{
		if ( prevNum > num )
		{
			result = false;
			break;
		}
		else
		{
			prevNum = num;
		}
	}

	return result;
}

TEST(SortedChunksTest, ascendingSortingTest) {
	bool testResult = false;

	bool openFileResult = false;
	int  chunkCounter = 0;

	do
	{
		std::string path = "D://Projekty//Prywatne//C++//MultithreadSortingManager//tmp//" + std::to_string((chunkCounter++)) + ".txt";
		std::ifstream inFile;
		inFile.open(path);

		if ( inFile.is_open() )
		{
			openFileResult = true;
			std::vector<int> data;
			readDataFromFile(inFile, data);
			testResult = verifySortedChunksTest(data);
			inFile.close();
		}
		else
		{
			openFileResult = false;
		}
	} while ( openFileResult && testResult );

	EXPECT_TRUE(testResult);
}