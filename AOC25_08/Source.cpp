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

int64_t makeLinks(vector<vector<int64_t>> sizes, vector<vector<int>> coords, int numLinks)
{
	vector<vector<bool>> linked;
	linked.resize(coords.size(), vector<bool>(coords.size(), false));
	for (int i = 0; i < numLinks; i++)
	{
		linked[sizes[i][1]][sizes[i][2]] = true;
		linked[sizes[i][2]][sizes[i][1]] = true;
	}
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
		return total;
	}
	else
	{
		return circuitSizes[numCircuits - 1];
	}
}


int main()
{
	vector<string> lines = readFile("aoc.txt");

	vector<vector<int64_t>> sizes;
	vector<vector<int>> coords;

	for (auto i : lines)
	{
		coords.push_back(splitStringI(i, ','));
	}
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			int64_t x = calcDist(coords[i], coords[j]);
			sizes.push_back({ x, i, j });
		}
	}
	sort(sizes.begin(), sizes.end(), [](const std::vector<int64_t>& a, const std::vector<int64_t>& b) {return a[0] < b[0]; });

	int minLinks = 1000;
	int maxLinks = 10000;
	cout << "Part1: " << makeLinks(sizes, coords, minLinks) << endl;

	while ((minLinks != maxLinks) && (minLinks != maxLinks-1))
	{
		int midpoint = (maxLinks + minLinks) / 2;

		int maxSize = makeLinks(sizes, coords, midpoint);
		if (maxSize == coords.size())
		{
			maxLinks = midpoint;
		}
		else
		{
			minLinks = midpoint;
		}
	}
	int64_t part2;
	int first = sizes[maxLinks - 1][1];
	int second = sizes[maxLinks - 1][2];
	part2 = coords[first][0] * coords[second][0];
	cout << "Part2: " << part2 << endl;

}