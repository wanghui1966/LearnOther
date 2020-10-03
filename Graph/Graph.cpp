#include "Graph.h"

#include <deque>
#include <iostream>

// 克鲁斯卡尔算法辅助
struct Edge
{
	int start = 0;
	int end = 0;
	int weight = 0;
	int flag = 0;
};

Graph::Graph()
{
	alG = nullptr;
	vNum = 0;
	arcNum = 0;
	flag = nullptr;
	mG = nullptr;
	vertexName = nullptr;
}

Graph::~Graph()
{
	DeleteAdjacency();
	DeleteMatrix();
}

void Graph::DeleteAdjacency()
{
	if (!alG)
	{
		return;
	}

	for (int i = 0; i < vNum; ++i)
	{
		for (ArcNode *arc = alG[i].firstArc; arc;)
		{
			ArcNode *temp = arc->next;
			delete arc;
			arc = temp;
		}
	}
	delete []alG;
	alG = nullptr;
}

void Graph::DeleteMatrix()
{
	if (!mG)
	{
		return;
	}

	for (int i = 0; i < vNum; ++i)
	{
		delete []mG[i];
	}
	mG = nullptr;
	delete []vertexName;
	vertexName = nullptr;
}

void Graph::Input()
{
	std::cout << "请输入图的顶点数：";
	std::cin >> vNum;
	alG = new VNode[vNum];
	std::cout << "请依次输入顶点名称：";
	for (int i = 0; i < vNum; i++)
	{
		std::cin >> alG[i].name;
		alG[i].firstArc = nullptr;
	}
	std::cout << "请输入弧的条数：";
	std::cin >> arcNum;
	std::cout << "请输入弧的信息(v1 v2 6)：" << std::endl;
	std::string v1;
	std::string v2;
	int w;
	for (int i = 0; i < arcNum; i++)
	{
		std::cin >> v1 >> v2 >> w;
		int j = LocateVNode(v1);
		int k = LocateVNode(v2);
		if (j == -1 || k == -1)
		{
			continue;
		}

		ArcNode *arcNode = new ArcNode;
		arcNode->index = k;
		arcNode->next = nullptr;
		arcNode->weight = w;
		ArcNode *temp = alG[j].firstArc;
		if (!temp)
		{
			alG[j].firstArc = arcNode;
		}
		else
		{
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = arcNode;
		}

		// 无向图 + 这段
		arcNode = new ArcNode;
		arcNode->index = j;
		arcNode->next = nullptr;
		arcNode->weight = w;
		temp = alG[k].firstArc;
		if (!temp)
		{
			alG[k].firstArc = arcNode;
		}
		else
		{
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = arcNode;
		}
	}
	flag = new bool[vNum];
	std::cout << std::endl << std::endl;
}

void Graph::OutPut()
{
	if (alG)
	{
		std::cout << "图的邻接表为:" << std::endl;
		for (int i = 0; i < vNum; ++i)
		{
			std::cout << alG[i].name << ":";
			for (ArcNode *arc = alG[i].firstArc; arc; arc = arc->next)
				std::cout << " <" << alG[arc->index].name << "," << arc->weight << ">";
			std::cout << std::endl;
		}
	}
	if (mG)
	{
		std::cout << "图的邻接矩阵为:" << std::endl;
		for (int i = 0; i < vNum; ++i)
		{
			std::cout << vertexName[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < vNum; ++i)
		{
			for (int j = 0; j < vNum; ++j)
			{
				if (mG[i][j] == INT32_MAX)
				{
					std::cout << "× ";
				}
				else
				{
					std::cout << mG[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

int Graph::LocateVNode(std::string name)
{
	if (alG)
	{
		for (int i = 0; i < vNum; i++)
		{
			if (alG[i].name == name)
			{
				return i;
			}
		}
	}
	if (mG)
	{
		for (int i = 0; i < vNum; ++i)
		{
			if (vertexName[i] == name)
			{
				return i;
			}
		}
	}
	return -1;
}

void Graph::DFSTraverse()
{
	std::cout << "深度遍历结果为：";
	for (int i = 0; i < vNum; i++)
	{
		flag[i] = false;
	}
	for (int i = 0; i < vNum; i++)
	{
		if (!flag[i])
		{
			DFSTraverseAssist(i);
		}
	}
	std::cout << std::endl << std::endl;
}

void Graph::DFSTraverseAssist(int index)
{
	flag[index] = true;
	std::cout << alG[index].name << " ";
	for (ArcNode *arc = alG[index].firstArc; arc; arc = arc->next)
	{
		if (!flag[arc->index])
		{
			DFSTraverseAssist(arc->index);
		}
	}
}

void Graph::BFSTraverse()
{
	std::cout << "广度遍历结果为：";
	for (int i = 0; i < vNum; i++)
	{
		flag[i] = false;
	}
	std::deque<VNode> q;
	for (int i = 0; i < vNum; i++)
	{
		if (!flag[i])
		{
			flag[i] = true;
			std::cout << alG[i].name << " ";
			q.push_back(alG[i]);
			while (!q.empty())
			{
				VNode v = q.front();
				q.pop_front();
				for (ArcNode *a = v.firstArc; a; a = a->next)
				{
					if (!flag[a->index])
					{
						flag[a->index] = true;
						std::cout << alG[a->index].name << " ";
						q.push_back(alG[a->index]);
					}
				}
			}
		}
	}
	std::cout << std::endl << std::endl;
}

void Graph::AdjacencyToMatrix()
{
	if (!alG)
	{
		return;
	}

	mG = new int*[vNum];
	vertexName = new std::string[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		mG[i] = new int[vNum];
	}
	for (int i = 0; i < vNum; ++i)
	{
		for (int j = 0; j < vNum; ++j)
		{
			mG[i][j] = INT32_MAX;
		}
	}

	for (int i = 0; i < vNum; ++i)
	{
		for (ArcNode *a = alG[i].firstArc; a; a = a->next)
		{
			mG[i][a->index] = a->weight;
		}
		vertexName[i] = alG[i].name;
	}
	DeleteAdjacency();
}

void Graph::MatrixToAdjacency()
{
	if (!mG)
	{
		return;
	}

	alG = new VNode[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		alG[i].firstArc = nullptr;
		alG[i].name = vertexName[i];
	}
	for (int i = 0; i < vNum; ++i)
	{
		for (int j = 0; j < vNum; ++j)
		{
			if (mG[i][j] != INT32_MAX)
			{
				ArcNode *arcNode = new ArcNode;
				arcNode->index = j;
				arcNode->next = nullptr;
				arcNode->weight = mG[i][j];
				ArcNode *temp = alG[i].firstArc;
				if (!temp)
				{
					alG[i].firstArc = arcNode;
				}
				else
				{
					while (temp->next)
					{
						temp = temp->next;
					}
					temp->next = arcNode;
				}
			}
		}
	}
	DeleteMatrix();
}

void Graph::Prim(int startIndex)
{
	AdjacencyToMatrix();

	flag = new bool[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		flag[i] = false;
	}

	// 储存的是已选结点与未选节点的最短距离
	int *low = new int[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		if (startIndex != i)
		{
			low[i] = mG[startIndex][i];
		}
	}
	flag[startIndex] = true;
	low[startIndex] = 0;

	for (int i = 0; i < vNum; ++i)
	{
		int min = INT32_MAX;
		int pos = -1;
		for (int j = 0; j < vNum; ++j)
		{
			if (flag[j] == false && min > low[j])
			{
				min = low[j];
				pos = j;
			}
		}
		flag[pos] = true;
		for (int j = 0; j < vNum; ++j)
		{
			if (flag[j] == false && low[j] > mG[pos][j])
			{
				low[j] = mG[pos][j];
			}
		}
	}

	std::cout << "Prim算法求得最小生成树的边为：";
	for (int i = 0; i < vNum; ++i)
	{
		if (startIndex != i)
		{
			std::cout << low[i] << " ";
		}
	}
	std::cout << std::endl;
}

int EdgeComp(const void *edgeOne, const void *edgeTwo)
{
	if (((Edge*)edgeOne)->weight <= ((Edge*)edgeTwo)->weight)
	{
		return -1;
	}
	return 1;
}

void Graph::Kruskal()
{
	AdjacencyToMatrix();

	Edge *e = new Edge[arcNum];
	int index = 0;
	for (int i = 0; i < vNum; ++i)
	{
		for (int j = i + 1; j < vNum; ++j)
		{
			if (mG[i][j] < INT32_MAX)
			{
				e[index].start = i;
				e[index].end = j;
				e[index].weight = mG[i][j];
				e[index].flag = false;
				++index;
			}
		}
	}
	// 并查集，判断弧的两个结点是否属于同一个阵营
	int *iFlag = new int[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		iFlag[i] = i;
	}
	qsort(e, arcNum, sizeof(Edge), EdgeComp);
	index = 0;
	while (1)
	{
		while (index < arcNum && iFlag[e[index].start] == iFlag[e[index].end])
		{
			++index;
		}
		if (index >= arcNum)
		{
			break;
		}
		int tempMin;
		int tempMax;
		if (iFlag[e[index].start] < iFlag[e[index].end])
		{
			tempMin = iFlag[e[index].start];
			tempMax = iFlag[e[index].end];
		}
		else
		{
			tempMin = iFlag[e[index].end];
			tempMax = iFlag[e[index].start];
		}
		for (int i = 0; i < vNum; ++i)
		{
			if (iFlag[i] == tempMax)
			{
				iFlag[i] = tempMin;
			}
		}
		e[index].flag = true;
	}

	std::cout << "Kruskal算法求得最小生成树的边为：" << std::endl;
	for (int i = 0; i < arcNum; ++i)
	{
		if (e[i].flag == true)
		{
			std::cout << " <" << e[i].start << "," << e[i].end << "," << e[i].weight << ">";
		}
	}
	std::cout << std::endl;
}

void Graph::Dijkstra(int startIndex)
{
	AdjacencyToMatrix();

	int *d = new int[vNum];
	flag = new bool[vNum];
	for (int i = 0; i < vNum; ++i)
	{
		flag[i] = false;
		d[i] = mG[startIndex][i];
	}
	d[startIndex] = 0;
	flag[startIndex] = true;

	for (int i = 0; i < vNum; ++i)
	{
		if (i != startIndex)
		{
			int min = INT32_MAX;
			int pos = -1;
			for (int j = 0; j < vNum; ++j)
			{
				if (!flag[j] && d[j] < min)
				{
					pos = j;
					min = d[j];
				}
			}
			flag[pos] = true;
			for (int j = 0; j < vNum; ++j)
			{
				if (!flag[j] && mG[pos][j] != INT32_MAX && min + mG[pos][j] < d[j])
				{
					d[j] = min + mG[pos][j];
				}
			}
		}
	}

	std::cout << "Dijkstra最短路径为:" << std::endl;
	std::cout << "   ";
	for (int i = 0; i < vNum; ++i)
	{
		if (i != startIndex)
		{
			std::cout << vertexName[i] << " ";
		}
	}
	std::cout << std::endl << vertexName[startIndex] << " ";
	for (int i = 0; i < vNum; ++i)
	{
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;
}
