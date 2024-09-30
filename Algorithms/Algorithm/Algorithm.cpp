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
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector <vector<int>>(6);

	// 인접 리스트
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);
	/*
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
	*/
}

void BFS(int here)
{
	// 누구에 의해 발견 되었는가?
	vector<int> parent(6, -1);
	vector<int>distance(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;
	
	parent[here] = here;
	distance[here] = 0;

	while (!q.empty())
	{
		here = q.front();
		q.pop();

		cout << "Visited " << here << '\n';
		for (auto there : adjacent[here])
		{
			if (discovered[there] == true)
				continue;

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}
	int a = 0;
}

void BFSAll()
{
	for(int i=0; i<6; i++)
	{
		if(!discovered[i])
			BFS(i);
	}
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);
	BFS(0);
}