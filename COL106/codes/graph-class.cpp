#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

// assuming undirected edges
class Graph
{
private:
	// map from vertices --> set of vertices
	std::unordered_map<int, std::unordered_set<int>> adjList;

public:
	// Add a vertex to the graph
	void addVertex(int vertex)
	{
		if (adjList.find(vertex) == adjList.end())
		{
			// add the vertex --> empty set entry
			adjList[vertex] = std::unordered_set<int>();
		}
	}

	void addEdge(int vertex1, int vertex2, int weight = 0)
	{
		addVertex(vertex1);
		addVertex(vertex2);
		adjList[vertex1].insert(vertex2);
		// adjList[vertex2].insert(vertex1); // since it's undirected
	}

	// Remove an undirected edge between two vertices
	void removeEdge(int vertex1, int vertex2)
	{
		if (adjList.find(vertex1) != adjList.end() &&
			adjList.find(vertex2) != adjList.end())
		{
			adjList[vertex1].erase(vertex2);
			adjList[vertex2].erase(vertex1);
		}
	}

	// BFS traversal starting from a given vertex
	void BFS(int startVertex)
	{
		std::unordered_set<int> visited;
		BFSUtil(startVertex, visited);
	}

	void BFSUtil(int vertex, std::unordered_set<int> &visited)
	{
		std::vector<int> queue;
		queue.push_back(vertex);

		visited.insert(vertex);

		while (!queue.empty())
		{
			int currentVertex = queue[0];
			queue.erase(queue.begin());

			std::cout << currentVertex << " ";

			for (int neighbor : adjList[currentVertex])
			{
				if (visited.find(neighbor) == visited.end())
				{
					queue.push_back(neighbor);
					visited.insert(neighbor);
				}
			}
		}
	}

	// DFS traversal starting from a given vertex
	void DFS(int startVertex)
	{
		std::unordered_set<int> visited;
		DFSUtil(startVertex, visited);
	}

	void DFSUtil(int vertex, std::unordered_set<int> &visited)
	{
		visited.insert(vertex);

		std::cout << vertex << " ";

		for (int neighbor : adjList[vertex])
		{
			if (visited.find(neighbor) == visited.end())
			{
				DFSUtil(neighbor, visited);
			}
		}
	}

	// All paths starting from a given vertex for an unweighted graph
	void AllPaths(int startVertex, int destination)
	{
		std::unordered_set<int> visited;
		vector<string> all_paths;
		AllPathsUtil(startVertex, destination, visited, "", all_paths);

		for (int i = 0; i < all_paths.size(); i++)
		{
			cout << "Path_" + to_string(i) + ": " + all_paths[i] << endl;
		}
	}

	void AllPathsUtil(int vertex, int destination, std::unordered_set<int> &visited, string path, vector<string> &paths)
	{
		if (vertex == destination)
		{
			path += to_string(vertex);
			paths.push_back(path);
			// cout << path << endl;
			return;
		}

		visited.insert(vertex);

		for (int neighbor : adjList[vertex])
		{
			if (visited.find(neighbor) == visited.end())
			{
				AllPathsUtil(neighbor, destination, visited, path + to_string(vertex) + " -> ", paths);
				visited.erase(neighbor);
			}
		}
	}

	// Detect cycle in the graph
	bool CycleDetection()
	{
		std::unordered_set<int> visited;

		for (auto vertex : adjList)
		{
			if (visited.find(vertex.first) == visited.end())
			{
				if (CycleDetectionUtil(vertex.first, visited, -1))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool CycleDetectionUtil(int vertex, std::unordered_set<int> &visited, int parent)
	{
		visited.insert(vertex);

		for (int neighbor : adjList[vertex])
		{
			if (visited.find(neighbor) == visited.end())
			{
				if (CycleDetectionUtil(neighbor, visited, vertex))
				{
					return true;
				}
			}
			else if (neighbor != parent)
			{
				return true;
			}
		}
		return false;
	}
	
};

int main()
{
	Graph g;
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);

	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(3, 5);

	int BFS_Vertex = 3;
	int DFS_Vertex = 5;

	cout << "BFS of " << BFS_Vertex << ": ";
	g.BFS(BFS_Vertex);
	cout << endl;

	cout << "DFS of " << DFS_Vertex << ": ";
	g.DFS(DFS_Vertex);
	cout << endl;

	g.AllPaths(1, 5);

	bool cycle = g.CycleDetection();

	if (cycle)
	{
		cout << "Graph contains a cycle" << endl;
	}
	else
	{
		cout << "Graph does not contain any cycle" << endl;
	}

	return 0;
}
