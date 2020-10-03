#ifndef GRAPH_H
#define GRAPH_H

#include <string>

struct ArcNode
{
	int index = 0;
	struct ArcNode *next = nullptr;
	int weight = 0;
};

struct VNode
{
	std::string name;
	ArcNode *firstArc = nullptr;
};

class Graph
{
public:
	Graph();
	virtual ~Graph();

public:
	void Input();
	void OutPut();
	void DFSTraverse();
	void BFSTraverse();
	
	void Prim(int startIndex = 0);
	void Kruskal();

	void Dijkstra(int startIndex = 0);
	
private:
	void AdjacencyToMatrix();
	void MatrixToAdjacency();
	void DeleteMatrix();
	void DeleteAdjacency();

	int LocateVNode(std::string name);
	void DFSTraverseAssist(int index);

private:
	VNode *alG = nullptr;
	int vNum = 0;
	int arcNum = 0;
	bool *flag = nullptr;
	int **mG = nullptr;
	std::string *vertexName = nullptr;
};

#endif
