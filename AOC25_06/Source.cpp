#include "Elves.h"
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int main() {
	vector<string> lines = readFile("aoc.txt");
	vector<vector<string>> numbers;
	int numRows = lines.size();
	int numColumns = lines[0].size();
	numbers.resize(numRows);
	int prev = 0;
	for (int c = 0; c < numColumns; c++)
	{
		bool split = true;
		for (int r = 0; r < numRows; r++)
		{
			if (lines[r][c] != ' ')
			{
				split = false;
			}
		}
		if (split)
		{
			for (int r = 0; r < numRows; r++)
			{
				numbers[r].push_back(lines[r].substr(prev, c - prev));
			}
			prev = c+1;
		}
	}
	for (int r = 0; r < numRows; r++)
	{
		numbers[r].push_back(lines[r].substr(prev, -1));
	}

	numColumns = numbers[0].size();
	for (int c = 0; c < numColumns; c++)
	{
		for (int r = 0; r < numRows; r++)
		{
			cout << numbers[r][c] << endl;
		}
		cout << endl;
	}

	int64_t total = 0;
	int64_t total2 = 0;

	for (int i = 0; i < numColumns; i++)
	{
		int64_t tempTotal = 0;
		int64_t tempTotal2 = 0;
		int sums = numRows - 1;
		char k = numbers[sums][i][0];
		
		if (k == '*')
		{
			tempTotal++;
			tempTotal2++;
		}
		for (int j = 0; j < sums; j++)
		{

			if (k == '*')
			{
				tempTotal *= stoll(numbers[j][i]);
			}
			else
			{ 
				tempTotal += stoll(numbers[j][i]);
			}
		}
		total += tempTotal;
			
		int intColumns = numbers[0][i].size();
		
		for (int c = 0; c < intColumns; c++)
		{
			string q;
			for (int r = 0; r < sums; r++)
			{
				char p = numbers[r][i][c];
				if(p!=' ')
					q.push_back(p);
			}
			if (k == '*')
			{
				tempTotal2 *= stoll(q);
			}
			else
			{
				tempTotal2 += stoll(q);
			}
			
		}
		total2 += tempTotal2;

	}
	cout << total << endl;
	cout << total2 << endl;



}