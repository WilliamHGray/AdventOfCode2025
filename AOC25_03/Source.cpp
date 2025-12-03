#include "Elves.h"
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

vector<int> stovi(string nums)
{
	vector<int> res;
	for (auto i : nums)
	{
		res.push_back(i-'0');
	}
	return res;
}

int64_t turnOnBatteries(vector<int> numbers, int numBatteries)
{
	vector<int> max;
	int prevMax = 0;

	for (int pos = 0; pos < numBatteries; pos++)
	{
		int currMax = 0;
		int maxPos = -1;
		int lastToCheck = numbers.size() - numBatteries + pos + 1;

		for (int i = prevMax; i < lastToCheck; i++)
		{
			if (numbers[i] > currMax)
			{
				currMax = numbers[i];
				maxPos = i;
			}
		}
		prevMax = maxPos+1;
		max.push_back(currMax);
	}
	
	int64_t jolt = 0;
	for (int i = 0; i < numBatteries; i++)
	{
		int64_t pow10 = (int64_t)pow(10, numBatteries - i - 1);
		jolt += pow10 * max[i];
	}
	cout << jolt << endl;
	return jolt;
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	int total = 0;
	int64_t total2 = 0;
	for (auto line : lines)
	{
		vector<int> numbers = stovi(line);
		total += turnOnBatteries(numbers, 2);
		total2 += turnOnBatteries(numbers, 12);
	}
	cout << total << endl;
	cout << total2 << endl;
}