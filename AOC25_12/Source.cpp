#include "Elves.h"
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

int main() {
	vector<string> lines = readFile("aoc.txt");
	vector<vector<string>> shapes;
	vector<string> grids;
	vector<string> t;
	int total = 0;
	for (auto i : lines)
	{
		if (i == "")
		{
			shapes.push_back(t);
			t.clear();
		}
		else if (i.size() != 2)
		{
			t.push_back(i);
		}
	}
	grids = (t);

	vector<int> shapeAreas;
	for (auto i : shapes)
	{
		int h = 0;
		for (auto j : i)
		{
			for (auto k : j)
			{
				if (k == '#')
				{
					h++;
				}
			}
		}
		shapeAreas.push_back(h);
	}

	vector<int> gridAreas;
	vector<vector<int>> toFit;
	for (auto i : grids)
	{
		int pos = i.find(':');

		string f = i.substr(0, pos);
		vector<int> q = splitStringI(f, 'x');
		int p = q[0] * q[1];
		gridAreas.push_back(p);

		string l = i.substr(pos + 2, -1);
		vector<int> v = splitStringI(l, ' ');
		toFit.push_back(v);
	}

	for (int i = 0; i < toFit.size(); i++)
	{
		int totalArea = 0;
		for (int j = 0; j < toFit[i].size(); j++)
		{
			totalArea += shapeAreas[j] * toFit[i][j];
		}
		if (totalArea <= gridAreas[i])
		{
			total++;
		}
	}
	cout << total << endl;
}