#include "pch.h"
#include <random>

int partition(std::vector<int>& dataToSort, int left, int right)
{
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = dataToSort[pivotIndex];
	int tmp;

	while (left <= right)
	{
		while (dataToSort[left] < pivotValue)
			left++;
		while (dataToSort[right] > pivotValue)
			right--;

		if (left <= right)
		{
			tmp = dataToSort[left];
			dataToSort[left] = dataToSort[right];
			dataToSort[right] = tmp;
			left++;
			right--;
		}
	}

	return left;
}

void qSort(std::vector<int>& dataToSort, int left, int right)
{
	if (left < right)
	{
		int pivotIndex = partition(dataToSort, left, right);
		qSort(dataToSort, left, pivotIndex - 1);
		qSort(dataToSort, pivotIndex, right);
	}
}

void generateRandomData(std::vector<int>& v, int count)
{
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> dis(1, 1000);

	for (int i = 0; i < count; ++i)
	{
		v.push_back(dis(gen));
	}
}

bool verifyQuickSortAlgorithmTest(std::vector<int>& sortedData)
{
	bool result = true;

	int prevNum = sortedData[0];
	for ( auto num : sortedData )
	{
		std::cout << num << " ";
		if ( num < prevNum )
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
TEST(QuickSortAlgorithmTest, ascendingQuickSort) {
	bool testResult = false;

	std::vector<int> * v = new std::vector<int>();
	if ( v != nullptr )
	{
		generateRandomData(*v, 10);
		qSort(*v, 0, v->size() - 1);
		testResult = verifyQuickSortAlgorithmTest(*v);
	}

	EXPECT_TRUE(testResult);
}