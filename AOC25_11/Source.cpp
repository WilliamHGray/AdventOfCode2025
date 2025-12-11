#include "Elves.h"
using namespace std;
#include <map>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

void print(map<string, int64_t> first)
{
	for (auto i : first)
	{
		cout << i.first << ": " << i.second << endl;
	} 
}

int findPath(map<string, vector<string>> path, string start, string fin)
{
	map<string, int64_t> nodes;
	nodes[start] = 1;
	map<string, int64_t> prev;
	while (prev != nodes)
	{
		prev = nodes;
		map<string, int64_t> next;
		for (auto i : nodes)
		{
			int64_t mag = i.second;
			string val = i.first;
			if (val == fin)
			{
				next[val] += mag;
			}
			else
			{
				for (auto j : path[val])
				{
					next[j] += mag;
				}
			}
		}
		nodes = next;
	}
	return nodes[fin];
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	map<string, vector<string>> path;
	
	for (auto i : lines)
	{
		string first = i.substr(0, 3);
		vector<string> second = splitString(i.substr(5, -1), ' ');
		path[first] = second;
	}
	
	cout << "Part 1: " << findPath(path, "you", "out") << endl;
	int64_t srvdac = findPath(path, "svr", "dac");
	int64_t srvfft = findPath(path, "svr", "fft");
	int64_t dacfft = findPath(path, "dac", "fft"); //graph has no loops so only one of these is non-zero
	int64_t fftdac = findPath(path, "fft", "dac");
	int64_t fftout = findPath(path, "fft", "out");
	int64_t dacout = findPath(path, "dac", "out");

	cout << "Part 2: " << max(srvdac * dacfft * fftout,srvfft * fftdac * dacout) << endl;

}