#include <iostream>
#include <queue>
#include <stack>
#include<set>
#include <list>
#include"vector"

using namespace std;


bool dfs(int u, vector<vector<int>>& graph, vector<int>& match, vector<bool>& visited) {
	for (int v : graph[u]) {
		if (!visited[v]) {
			visited[v] = true;
			if (match[v] == -1 || dfs(match[v], graph, match, visited)) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int maxMatching(vector<vector<int>>& graph, int n, int m) {
	vector<int> match(m, -1);
	int result = 0;

	for (int u = 0; u < n; u++) {
		vector<bool> visited(m, false);
		if (dfs(u, graph, match, visited)) {
			result++;
		}
	}

	return result;
}


int FindPath(vector<vector<int>>& c, vector<vector<int>>& f, int source, int target)
{
	int vertices = c.size();
	vector<int> Flow(vertices, 0);
	vector<int> Link(vertices, -1);
	vector<int> used(vertices, 0);
	stack<int> s;

	Flow[source] = INT_MAX;
	s.push(source);

	while (!s.empty())
	{
		int vertex = s.top();
		if (vertex == target) break;
		s.pop();

		for (int i = 0; i < vertices; i++)
		{
			if (c[vertex][i] - f[vertex][i] > 0 && !used[i])
			{
				s.push(i);
				Flow[i] = min(c[vertex][i] - f[vertex][i], Flow[vertex]);
				Link[i] = vertex;
			}
		}
		used[vertex] = 1;
	}

	if (Link[target] == -1) return 0;

	int CurVertex = target;
	while (CurVertex != source)
	{
		f[Link[CurVertex]][CurVertex] += Flow[target];
		CurVertex = Link[CurVertex];
	}

	return Flow[target];
}


int MaxFlow(vector<vector<int>>& c, int source, int target)
{
	int vertices = c.size();
	vector<vector<int>> f(vertices, vector<int>(vertices, 0));
	int MaxFlow = 0;
	int AddFlow;

	do
	{
		AddFlow = FindPath(c, f, source, target);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);

	return MaxFlow;
}


bool hamiltoncycle(vector<vector<int> >& mat, vector <bool>& visited, vector <int>& path, int curr)
{
	path.push_back(curr);
	if (path.size() == mat.size() && mat[path[0]][path[path.size() - 1]] > 0) return true;

	if (path.size() == mat.size() && mat[path[0]][path[path.size() - 1]] != 0)
	{
		visited[curr] = false;
		path.pop_back();
		return false;
	}
	visited[curr] = true;
	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
			if (hamiltoncycle(mat, visited, path, i)) return true;
	}

	visited[curr] = false;
	path.pop_back();
	return false;
}


vector<int> greedyColoring (vector<vector<int>>& mat)
{
	vector<int> ans(mat.size(), -1);
	ans[0] = 0;
	set<int> neigbors_colors;

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat.size(); j++)
		{
			if (mat[i][j] != 0)
			{
				neigbors_colors.insert(ans[j]);
			}
		}
		int color = 0;
		while (neigbors_colors.find(color) != neigbors_colors.end()) {
			color++;
		}
		ans[i] = color;
		neigbors_colors.clear();
	}

	return ans;
}

int main()
{
	vector<vector<int>> mat2 = {{3}, {4}, {5}, {7}, {5}, {5}, {6}, {7}};

	vector<vector<int>> mat = {
	{ 0, 0, 0, 7, 6, 0, 1, 4, 4, 5, 6, 6, 7 },
	{ 0, 0, 6, 4, 4, 1, 2, 3, 2, 0, 1, 4, 2 },
	{ 0, 6, 0, 8, 8, 4, 3, 6, 5, 3, 6, 6, 5 },
	{ 7, 4, 8, 0, 5, 4, 5, 8, 0, 9, 3, 6, 8 },
	{ 6, 4, 8, 5, 0, 1, 4, 2, 7, 7, 7, 2, 0 },
	{ 0, 1, 4, 4, 1, 0, 7, 4, 4, 2, 4, 2, 6 },
	{ 1, 2, 3, 5, 4, 7, 0, 7, 1, 2, 2, 9, 8 },
	{ 4, 3, 6, 8, 2, 4, 7, 0, 8, 4, 2, 3, 2 },
	{ 4, 2, 5, 0, 7, 4, 1, 8, 0, 2, 5, 8, 1 },
	{ 5, 0, 3, 9, 7, 2, 2, 4, 2, 0, 5, 9, 7 },
	{ 6, 1, 6, 3, 7, 4, 2, 2, 5, 5, 0, 9, 6 },
	{ 6, 4, 6, 6, 2, 2, 9, 3, 8, 9, 9, 0, 5 },
	{ 7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0 }
	};

	for (vector<vector<int>>::iterator it_v = mat.begin(); it_v < mat.end(); it_v++)
	{
		for (vector<int>::iterator it_vv = (*it_v).begin(); it_vv < (*it_v).end(); it_vv++)
		{
			cout << (*it_vv) << " ";
		}
		cout << "\n";
	}

	vector<bool> visited(mat.size());
	vector<int> path = {};
	hamiltoncycle(mat, visited, path, 0);
	cout << "\nhamiltoncycle: \n";
	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i] << " ";
	}
	cout << endl;


	int source = 0;
	int target = 12;

	int result = MaxFlow(mat, source, target);
	cout << "\nMax flow: " << result << endl;

	vector<int> colors = greedyColoring(mat);
	cout << "\nColors: " << "\n";
	for (int i = 0; i < colors.size(); i++)
	{
		cout << colors[i] << ' ';
	}
	cout << "\n";
	
	int n = 8;
	int m = 8;

	int res = maxMatching(mat2, n, m);
	cout << "\nMax Matching: " << res << endl;

}

