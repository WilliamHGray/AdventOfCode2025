#include "Elves.h"
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int main() {
	vector<string> lines = readFile("aoc.txt");
	int total = 0;
	int total2 = 0;
	int start = 50;
	for (auto i : lines)
	{
		int num = stoi(i.substr(1, -1));
		//cout << num << endl;
		char k = i[0];
		int diff;
		if (k == 'L')
		{
			diff = -1 * num;
		}
		else
		{
			diff = num;
		}

		for (int i = 0; i < num; i++)
		{
			if (diff < 0)
			{
				start--;
			}
			else
			{
				start++;
			}
			if (abs(start) == 100)
			{
				start = 0;
			}
			if (start == 0)
			{
				total2++;
			}
		}
		if (start == 0)
		{
			total++;
		}
		
	}
	cout << total << endl;
	cout << total2 << endl;
}