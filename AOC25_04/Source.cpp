#include "Elves.h"
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0}, {-1,-1}, {-1,1}, {1,-1}, {1,1} };

int checkNeighbours(vector<string> grid, int x, int y, char k)
{
	int total = 0;
	for (auto i : moves)
	{
		vector<int> start = { x,y };
		vector<int> newPos = start + i;
		if (checkPos(newPos, grid))
		{
			total += (k == getEl(grid, newPos));
		}
	}
	return total;
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	int total = 0;
	vector<string>prev;
	bool part1 = true;
	while (prev != lines)
	{
		prev = lines;
		vector<string> next;
		for (int y = 0; y < lines.size(); y++)
		{
			string nextLine;
			for (int x = 0; x < lines[y].size(); x++)
			{
				string nextChar;
				if (getEl(lines, { x,y }) == '@')
				{
					int numNeighbours = checkNeighbours(lines, x, y, '@');
					if (numNeighbours < 4)
					{
						total++;
						nextChar = '.';
					}
					else
					{
						nextChar = '@';
					}
				}
				else
				{
					nextChar += '.';
				}
				nextLine += nextChar;
			}
			next.push_back(nextLine);
		}
		if (part1)
		{
			part1 = false;
			cout << total << endl;
		}
		lines = next;
	}
	cout << total << endl;
}