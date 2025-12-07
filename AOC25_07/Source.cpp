#include "Elves.h"
using namespace std;
#include<set>
#include<algorithm>
#include<map>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

void print(set<int> first)
{
	for (auto i : first)
	{
		cout << i << ", ";
	}
	cout << endl;
}

void print(map<int, int>first)
{
	for (auto i : first)
	{
		cout << i.first << ": " << i.second << endl;
	}
}

void setMinus(set<int> &first, set<int> second)
{
	for (auto i : second)
	{
		first.erase(i);
	}
}

void setMinus(vector<int>& first, vector<int> second)
{
	for (auto i : second)
	{
		auto q = find(first.begin(), first.end(), i);
		if (q != first.end())
		{
			first.erase(q);
		}
	}
}

void merge(vector<int>& first, vector<int>& second)
{
	for (auto i : second)
	{
		first.push_back(i);
	}
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	int total = 0;

	set<int> prev;
	string first = lines.front();
	int S = first.find('S');
	prev.insert(S);
	lines.erase(lines.begin());
	for (auto i : lines)
	{
		//cout << i << endl;
		set<int> next;
		int prevPos = 0;
		int splitter = i.find('^');
		set<int> hits;
		while (splitter != -1)
		{
			prevPos = splitter + 1;
			if (prev.contains(splitter))
			{
				hits.insert(splitter);
				next.insert(splitter + 1);
				next.insert(splitter - 1);
				total++;
			}
			splitter = i.find('^', prevPos);
		}
		setMinus(prev, hits);
		next.merge(prev);
		string k = i;
		for (auto q : next)
		{
			k[q] = '|';
		}
		cout << k << endl;
		prev = next;
	}
	cout << total << endl;

	map<int,int64_t> prevV;
	prevV[S]++;
	for (auto i : lines)
	{
		map<int, int64_t> next;
		map<int, int64_t> hits;
		int prevPos = 0;
		for (auto j : prevV)
		{
			int pos = j.first;
			int64_t count = j.second;
			if (i[pos] == '^')
			{
				hits[pos] = count;
				next[pos+1] += count;
				next[pos-1] += count;
			}
		}
		for (auto j : hits)
		{
			int pos = j.first;
			int64_t count = j.second;
			prevV[pos] -= count;
		}
		for (auto j : prevV)
		{
			int pos = j.first;
			int64_t count = j.second;
			next[pos] += count;
		}
		prevV = next;
		/*
		//Very Useful debug for checking for negative numbers
		int64_t total2 = 0;
		for (auto i : prevV)
		{
			total2 += i.second;
		}
		cout << total2 << endl;*/
	}
	int64_t total2 = 0;
	for (auto i : prevV)
	{
		total2 += i.second;
	}
	cout << total2 << endl;
}