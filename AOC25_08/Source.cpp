#include "Elves.h"
using namespace std;
#include <algorithm>
#include <set>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

set<int> intersect(set<int> first, set<int> second)
{
	set<int> k;
	for (auto i : first)
	{
		if (second.contains(i))
			k.insert(i);
	}
	return k;
}

void addToGraph(vector<set<int>>& first, int j, int k)
{
	for (int i =0; i<first.size();i++)
	{
		if (first[i].contains(j))
		{
			first[i].insert(k);
			return;
		}
		else if (first[i].contains(k))
		{
			first[i].insert(j);
			return;
		}
	}
	first.push_back({ k });
}

void makeUnique(vector<set<int>>& first)
{
	for (int i = 0; i < first.size(); i++)
	{
		for (int j = i + 1; j < first.size(); j)
		{
			if (!intersect(first[i], first[j]).empty())
			{
				first[i].merge(first[j]);
				first.erase(first.begin() + j);
			}
			else
			{
				j++;
			}
		}
	}
}

int64_t calcDist(vector<int> first, vector<int> second)
{
	int64_t total = 0;
	for (int i = 0; i < first.size(); i++)
	{
		int64_t k = first[i] - second[i];
		total += k * k;
	}
	return total;
}

void print(vector<set<int>>first)
{
	for (auto i : first)
	{
		for (auto j : i)
		{
			cout << j << ", ";
		}
		cout << endl;
	}
}

void print(vector<vector<bool>> first)
{
	for (auto i : first)
	{
		for (auto j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
}

void printFirst(vector<vector<int64_t>> first)
{
	for (auto i : first)
	{
		cout << i[0] << endl;
	}
}

int runProg(int numLinks) {
	vector<string> lines = readFile("aoc.txt");

	vector<vector<int64_t>> sizes;
	vector<vector<int>> coords;
	vector<vector<bool>> linked;
	linked.resize(lines.size(), vector<bool>(lines.size(), false));
	for (auto i : lines)
	{
		coords.push_back(splitStringI(i,','));
	}
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			int64_t x = calcDist(coords[i],coords[j]);
			sizes.push_back({ x, i, j });
		}
	}
	//printFirst(sizes);
	sort(sizes.begin(), sizes.end(), [](const std::vector<int64_t>& a, const std::vector<int64_t>& b) {return a[0] < b[0]; });

	int64_t l = sizes[6303][1];
	int64_t m = sizes[6303][2]; 
	int64_t prod = coords[l][0] * coords[m][0];
	cout << coords[l][0] << endl;
	cout << coords[m][0] << endl;
	cout << prod << endl;

	for (int i = 0; i < numLinks; i++)
	{
		linked[sizes[i][1]][sizes[i][2]] = true;
		linked[sizes[i][2]][sizes[i][1]] = true;
	}
	//print(linked);
	vector<set<int>> circuits;

	for (int i = 0; i < coords.size(); i++)
	{
		addToGraph(circuits, i, i);
		for (int j = i + 1; j < coords.size(); j++)
		{
			if (linked[i][j])
			{
				addToGraph(circuits, i, j);
			}
		}
	}
	vector<set<int>>prev;
	while (prev != circuits)
	{
		prev = circuits;
		makeUnique(circuits);
	}
	//print(circuits);
	int64_t total = 1;
	vector<int> circuitSizes;
	for (auto i : circuits)
	{
		circuitSizes.push_back(i.size());
	}
	sort(circuitSizes.begin(), circuitSizes.end());
	int numCircuits = circuits.size();
	if (numCircuits > 2)
	{
		
		total = circuitSizes[numCircuits - 1] * circuitSizes[numCircuits - 2] * circuitSizes[numCircuits - 3];
		cout << total << endl;
	}
	else
	{
		return circuitSizes[numCircuits - 1];
	}
	

}

int main()
{
	runProg(1000);
	exit(0);

	//Change numbers in this and run it manually to get which link is actually the correct one

	//cout << runProg(6500) << endl;
	//exit(0);

	for (int i = 6300; i < 6310; i++)
	{
		int j = runProg(i);
		if (j == 1000)
		{
			cout << i << endl;
			exit(0);
		}
	}
}