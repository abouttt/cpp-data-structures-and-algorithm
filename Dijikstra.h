#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;  // 인접행렬

// 인접 행렬 그래프 만들기
void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	// [0][1] -> 0번노드에서 1번노드 연결.
	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

// 다익스트라 알고리즘
void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;  // 정점
		int cost;    // 비용
	};

	list<VertexCost> discovered;     // 발견목록
	vector<int> best(6, INT32_MAX);  // 각 정점별로 지금까지 발견한 최소 거리
	vector<int> parent(6, -1);       // 부모 노드

	// 시작 정점을 위한 작업.
	// 다른 정점들은 이후에 수정하니 상관없다.
	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;       // 시작점은 최소거리 0
	parent[here] = here;

	// 발견한 정점이 계속 있다면 루프.
	while (discovered.empty() == false)
	{
		// 제일 좋은 후보를 찾는다.
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		// 제일 좋은 후보를 찾은 다음 데이터를 꺼내고 삭제하는 과정
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 방문할려는 정점의 대한 최소거리가 현재 루트를 통해 발견한 거리보다 작다면 스킵.
		if (best[here] < cost)
			continue;

		// 방문
		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵.
			if (adjacent[here][there] == -1)
				continue;

			// 현재까지 온 비용과 연결된 정점의 비용을 더한다.
			int nextCost = best[here] + adjacent[here][there];

			// 현재 정점에서 연결된 다음 정점의 총 비용을 비교하여 
			// 이전에 다른 루트를 통해 더 좋은 비용이 발견되었다면 스킵.
			if (nextCost >= best[there])
				continue;

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}