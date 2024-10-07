#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct  Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacnet;

void CreateGraph()
{
	vertices.reserve(6);
	adjacnet = vector<vector<int>>(6, vector<int>(6,-1));

	adjacnet[0][1] = 15;
	adjacnet[0][3] = 35;

	adjacnet[1][0] = 15;
	adjacnet[1][2] = 5;
	adjacnet[1][3] = 10;
	adjacnet[3][4] = 5;
	adjacnet[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered; // 발견목록
	vector<int> best(6, INT32_MAX); // 각 정점별 최소거리
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{here,0});
	best[here] = 0;
	parent[here] = here;
	while (!discovered.empty())
	{
		//제일 좋은 후보를 찾는다.
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;

			if (cost < bestCost)
			{
				bestCost = cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		//더 짧은 경로를 뒤늦게 찾았다면
		if (best[here] < cost)
			continue;

		for (int there = 0; there< 6; there++)
		{
			if (adjacnet[here][there] == -1)
				continue;

			int nextCost = best[here] + adjacnet[here][there];

			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there,nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}

	int a = 3;
}

int main()
{
	CreateGraph();
	Dijikstra(0);

	return 0;
}