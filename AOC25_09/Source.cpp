#include "Elves.h"
using namespace std;
#include <set>
#include <algorithm>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int64_t calcSizeOfTriangle(int64_t x1, int64_t x2, int64_t y1, int64_t y2)
{
	int64_t x = abs(x2 - x1) + 1;
	int64_t y = abs(y2 - y1) + 1;
	return x * y;
}


bool inPoly(int x1, int x2, int y1, int y2, set<vector<int>> perimeter)
{
	int minX = min(x1, x2);
	int maxX = max(x1, x2);
	int minY = min(y1, y2);
	int maxY = max(y1, y2);
	for (auto i : perimeter)
	{
		int pX = i[0];
		int pY = i[1];
		if (minX < pX && pX < maxX && minY < pY && pY < maxY)
		{
			return false;
		}
	}
	return true;
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	vector<vector<int>> coords;
	for (auto i : lines)
	{
		coords.push_back(splitStringI(i, ','));
	}
	vector<vector<int64_t>> rectangles;

	set<vector<int>> perimeter;
	for (int i = 0; i < coords.size(); i++)
	{
		int q = (i + 1) % coords.size();
		int x1 = coords[i][0];
		int y1 = coords[i][1];
		int x2 = coords[q][0];
		int y2 = coords[q][1];
		if (y1 == y2)
		{
			int minX = min(x1, x2);
			int maxX = max(x1, x2);
			for (int x = minX; x <= maxX; x++)
			{
				perimeter.insert({ x,y1 });
			}
		}
		else
		{
			int minY = min(y1, y2);
			int maxY = max(y1, y2);
			for (int y = minY; y <= maxY; y++)
			{
				perimeter.insert({ x1, y });
			}
		}
	}

	for (int i = 0; i < coords.size(); i++)
	{
		int x1 = coords[i][0];
		int y1 = coords[i][1];
		for (int j = i + 1; j < coords.size(); j++)
		{

			int64_t x2 = coords[j][0];
			int64_t y2 = coords[j][1];

			int64_t area = calcSizeOfTriangle(x1, x2, y1, y2);
			rectangles.push_back({ area, i, j });

		}
	}
	sort(rectangles.begin(), rectangles.end(), [](const std::vector<int64_t>& a, const std::vector<int64_t>& b) {return a[0] > b[0]; });
	cout << "Part 1: " << rectangles[0][0] << endl;


	cout << rectangles.size() << endl;
	for(int i=0; i<rectangles.size();i++)
	{
		cout << i << endl;
		bool k = inPoly(coords[rectangles[i][1]][0], coords[rectangles[i][2]][0], coords[rectangles[i][1]][1], coords[rectangles[i][2]][1], perimeter);
		if (k)
		{
			cout << "Part 2: " << rectangles[i][0] << endl;
			exit(0);
		}
	}
}