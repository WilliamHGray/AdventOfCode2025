#include "Elves.h"
using namespace std;
#include <algorithm>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int main() {
	vector<string> lines = readFile("aoc.txt");
	vector<vector<int64_t>> ranges;
	vector<int64_t> ingredients;
	bool toCheck = true;
	int total = 0;

	for (auto line : lines)
	{
		if (line == "")
		{
			toCheck = false;
		}
		else if (toCheck)
		{
			vector<string> startEnd = splitString(line, '-');
			vector<int64_t> startEndI;
			startEndI.push_back(stoll(startEnd[0]));
			startEndI.push_back(stoll(startEnd[1]));
			ranges.push_back(startEndI);
		}
		else
		{
			ingredients.push_back(stoll(line));
		}
	}
	for (auto i : ingredients)
	{
		bool found = false;
		for (auto j : ranges)
		{
			if (i >= j[0] && i <= j[1])
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			total++;
		}
	}
	cout << total << endl;

	std::sort(ranges.begin(), ranges.end());
	
	for (int i = 0; i < ranges.size(); i++)
	{
		for (int j = i + 1; j < ranges.size(); j)
		{
			vector<int64_t> first = ranges[i];
			vector<int64_t> second = ranges[j];
			int64_t x1 = first[0];
			int64_t x2 = second[0];
			int64_t y1 = first[1];
			int64_t y2 = second[1];
			if(y1>=x2)
			{
				int64_t endVal = max(y1, y2);
				ranges[i][1] = endVal;
				ranges.erase(ranges.begin() + j);
			}
			else
			{
				j++;
			}

		}
	}

	int64_t total2 = 0;
	for (auto i : ranges)
	{
		cout << i[0] << "-" << i[1] << endl;
		total2 += (i[1] - i[0] + 1);
	}
	cout << total2 << endl;
		
}