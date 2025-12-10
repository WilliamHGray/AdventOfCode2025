#include "Elves.h"
using namespace std;
#include <map>
#include <set>

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

bool testCombination(vector<vector<int>> buttons, vector<bool> answer)
{
	int s = answer.size();
	map<int, bool> res;
	for (auto i : buttons)
	{
		for (auto j : i)
		{
			if (!res.contains(j))
			{
				res[j] = true;
			}
			else
			{
				res[j] = !res[j];
			}
		}
	}
	for (int i = 0; i < answer.size(); i++)
	{
		bool k = res[i];
		if ((k && !res.contains(i)) || (answer[i] != k))
		{
			return false;
		}
	}
	return true;
}

set<set<int>> combinations(int total, int n)
{
	set<set<int>> q;
	for (int i = 0; i < total; i++)
	{
		set<int> p = { i };
		q.insert(p);
	}
	for (int i = 2; i <= n; i++)
	{
		set<set<int>> prev = q;
		q.clear();
		for (auto p : prev)
		{
			for (int j = 0; j < total; j++)
			{
				set<int> k = p;
				k.insert(j);
				if (k.size() == i)
				{
					q.insert(k);
				}
			}
		}
	}
	return q;
}

int main() {
	vector<string> lines = readFile("aoc.txt");
	vector<vector<bool>> lights;
	vector<vector<vector<int>>> buttons;
	vector<vector<int>> joltage;
	int total = 0;
	for (auto i : lines)
	{
		vector<vector<int>> theseButtons;
		int pos = i.find(']');
		string k = i.substr(1, pos - 1);
		vector<bool> light;
		for (auto i : k)
		{
			if (i == '#')
			{
				light.push_back(true);
			}
			else
			{
				light.push_back(false);
			}
		}
		lights.push_back(light);

		int prev = pos+3;
		pos = i.find(')', prev);
		while (pos != -1)
		{
			string q = i.substr(prev, pos - prev);
			vector<int> n = splitStringI(q, ',');
			theseButtons.push_back(n);
			prev = pos + 3;
			pos = i.find(')', prev);

		}
		buttons.push_back(theseButtons);
		pos = i.find('}');
		string j = i.substr(prev, pos - prev);
		joltage.push_back(splitStringI(j,','));
	}

	for (int i = 0; i < lights.size(); i++)
	{
		vector<vector<int>> q = buttons[i];
		int n = 1;
		bool b1 = false;
		bool b2 = false;
		while (true)
		{
			set<set<int>> c = combinations(q.size(), n);
			for (auto j : c)
			{
				vector<vector<int>> p;
				for (auto k : j)
				{
					p.push_back(q[k]);
				}
				if (testCombination(p, lights[i]))
				{
					b1 = true;
					total += n;
					break;
				}
			}
			if (b1)
			{
				break;
			}
			n++;
		}
	}

	cout<<total<<endl;


}