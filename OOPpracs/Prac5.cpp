#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>


using namespace std;
using adjacency_matrix = vector<vector<int>>;


vector<int> dfs(const vector<vector<int>>& mat, int v)
{
	vector<int> path(v, 0);
	vector<int> used(v, 0);
	stack<int> s;
	s.push(0);
	path[0] = 0;
	used[0] = 1;
	int step = 1;
	while (!s.empty())
	{
		int cur_vertex = s.top(); s.pop();
		for (int i = 0; i < 9; i++)
			if (mat[cur_vertex][i] != 0 && used[i] == 0)
			{
				s.push(i); used[i] = 1;
			}
		path[cur_vertex] = step++;
	}
	return path;
}

using vertex_number = int;
using dist = int;
using pair_vector = vector<pair<int, int>>;

vector<int> Dijkstra(const vector<vector<int>>& graph, int v)
{
	int size = graph.size();

	vector<int> distances(size, 10000);
	priority_queue<pair<dist, vertex_number>, pair_vector, greater<pair<int, int>>> pq;

	distances[v] = 0;
	pq.push({ 0, v });

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		for (int v = 0; v < size; v++)
		{
			if (graph[u][v] != 0 && distances[v] > distances[u] + graph[u][v])
			{
				distances[v] = distances[u] + graph[u][v];
				pq.push({ distances[v], v });
			}
		}
	}

	return distances;
}

vector<int> bfs(const vector<vector<int>>& mat, int v)
{
	vector<bool> used(v, false);
	vector<int> degrees(v, 0);
	queue<int> q;
	q.push(0);
	used[0] = true;
	while (!q.empty())
	{
		int cur_vertex = q.front();
		q.pop();
		for (int i = 0; i < 9; i++)
			if (mat[cur_vertex][i] != 0)
			{
				degrees[i] += 1;
				if (!used[i])
				{
					q.push(i);
					used[i] = true;
				}
			}
	}
	return degrees;
}

double average_degree(const vector<vector<int>>& mat)
{
	double sum = 0.0;
	vector<int> degrees = bfs(mat, mat.size());
	for (int i = 0; i < mat.size(); i++)
	{
		sum += degrees[i];
	}
	return sum / degrees.size();
}

vector<vector<int>> Prim(adjacency_matrix& graph) {
	int n = graph.size();

	vector<int> parent(n, -1);
	vector<int> key(n, INT_MAX);
	vector<bool> visited(n, false);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	key[0] = 0;
	pq.push({ 0, 0 });
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		visited[u] = true;
		for (int v = 0; v < n; v++) {
			if (graph[u][v] > 0 && !visited[v] && graph[u][v] < key[v]) {
				key[v] = graph[u][v];
				parent[v] = u;
				pq.push({ key[v], v });
			}
		}
	}
	vector<vector<int>> span(n, vector<int>(n, 0));
	for (int i = 1; i < n; i++) {
		span[i][parent[i]] = span[parent[i]][i] = graph[i][parent[i]];
	}
	return span;
}

int main() {
	int start, target;
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

	vector<int> dist(13, 0);

	vector<int> answer = dfs(mat, mat.size());
	cout << "DFS order: ";
	for (int i = 0; i < 13; i++) cout << answer[i] << " ";
	dist = Dijkstra(mat, 0);
	cout << "\nDijsktra distances: ";
	for (int i = 0; i < 13; i++) cout << dist[i] << " ";
	dist = bfs(mat, 13);
	cout << "\nBFS Degrees: ";
	for (int i = 0; i < 13; i++) cout << dist[i] << " ";
	cout << "\nAverage Degree: " << average_degree(mat);
	mat = Prim(mat);
	cout << "\nPrim result: " << endl;
	for (int i = 0; i < 13; i++)
	{
		cout << "{ ";
		for (int j = 0; j < 13; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << "}" << endl;
	}
	answer = dfs(mat, mat.size());
	cout << "DFS order: ";
	for (int i = 0; i < 13; i++) cout << answer[i] << " ";
	dist = Dijkstra(mat, 0);
	cout << "\nDijkstra distances: ";
	for (int i = 0; i < 13; i++) cout << dist[i] << " ";
	dist = bfs(mat, 13);
	cout << "\nBFS Degrees: ";
	for (int i = 0; i < 13; i++) cout << dist[i] << " ";
	cout << "\nAverage Degree: " << average_degree(mat) << endl;
	return 0;
}