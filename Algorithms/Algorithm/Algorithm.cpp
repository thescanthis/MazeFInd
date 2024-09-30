#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector <vector<int>>(6);

	/* 인접 리스트
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);
	*/

	//인접 행렬
	adjacent = vector<vector<int>>
	{
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0}
	};
}

void DFS(int here)
{
	visited[here] = true;
	cout << "Visited : " << here << endl;
	
	/*
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];

		if (visited[there] == false)
			DFS(there);
	}
	*/

	for (int there = 0; there < 6; there++)
	{
		if (adjacent[here][there] == 0)
			continue;

		if (visited[there] == false)
			DFS(there);
	}
}

void DFSAll()
{
	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
			DFS(i);
}

int main()
{
	CreateGraph();
	visited = vector<bool>(6, false);

	DFSAll();
}