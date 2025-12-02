#include "Elves.h"
#include <set>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int64_t makeFull(int64_t half, int numReps)
{
	std::string k;
	string j = to_string(half);
	for (int i = 0; i < numReps; i++)
	{
		k += j;
	}
	return stoll(k);
}

set<int64_t> solve(int64_t first, int64_t last, int qStart, int numReps = 2)
{
	cout << first << ", " << last << ", " << qStart << ", " << numReps << endl;
	set<int64_t> total;
	int64_t half = first / (int64_t)pow(10, (numReps-1) * (qStart + 1) / numReps);
	//cout <<"x"<< half << endl;
	int64_t val = makeFull(half, numReps);
	//cout <<"y"<< val << endl;
	while (val <= last)
	{
		if (val >= first)
		{
			total.insert(val);
			//cout << val << endl;
		}
		half++;
		val = makeFull(half, numReps);
	}
	return total;
}

int64_t sumSet(set<int64_t> keys)
{
	int64_t total=0;
	for (auto i : keys)
	{
		total += i;
		cout << i << endl;
	}
	return total;
}

int main() {
	int64_t total = 0;
	int64_t total2 = 0;
	vector<string> lines = readFile("aoc.txt");
	vector<string> ranges = splitString(lines[0], ',');
	for (auto i : ranges)
	{
		vector<string> nums = splitString(i, '-');
		//cout << i << endl;
		int64_t first = stoll(nums[0]);
		int64_t last = stoll(nums[1]);

		
		int qStart = log10((float)first);
		int qEnd = log10((float)last);
		
		//total += solve(first, last, qStart);
		set<int64_t> keys;
		for (int j = 2; j <= qEnd + 1; j++)
		{
			
			int64_t firstMod = first;
			int64_t lastMod = last;
			int64_t qStartMod = qStart;
			int64_t qEndMod = qEnd;
			while ((qStartMod + 1) % j)
			{
				qStartMod++;
				firstMod = pow(10, qStartMod);
			}
			while ((qEndMod + 1) % j)
			{
				lastMod = pow(10, qEndMod) - 1;
				qEndMod--;
			}
			if (qStartMod > qEndMod)
			{
				continue;
			}
			keys.merge(solve(firstMod, lastMod, qStartMod, j));
		}
		total2 += sumSet(keys);
	}
	cout << total << endl;
	cout << total2 << endl;
}