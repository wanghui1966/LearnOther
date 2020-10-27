#ifndef BINARYTREE_H
#define BINARYTREE_H

struct Node
{
	Node() : data(0), left(nullptr), right(nullptr) {}
	Node(int d) : data(d), left(nullptr), right(nullptr) {}

	char data = 0;
	struct Node *left = nullptr;
	struct Node *right = nullptr;
};

class BinaryTree
{
public:
	BinaryTree() : head(nullptr), count(0) {}
	virtual ~BinaryTree();

public:
	// 二叉树的深度
	int GetDepth(Node *p);

	// 二叉树的叶子结点数量
	int GetLeafNodeCount();

	// 二叉树结构比较
	bool StructureCmp(const BinaryTree *tree);

public:
	// 先序建立二叉树：按照二叉树先序方式输入结点，以空格作为结点分隔符号，-表示null叶结点
	void PreOrderCreate();

	// 根据前序遍历和中序遍历重建二叉树
	bool RebuildTreeByPreOrderAndInOrder(char *pre_order_seq, char *in_order_seq, int node_count);

	// 根据输入建立二叉排序树
	bool RebuildSortTree(char *seq, int node_count);

public:
	// 递归方式遍历，分别为先序、中序和后序
	void PreOrderTraverse();
	void InOrderTraverse();
	void PostOrderTraverse();

public:
	// 非递归方式遍历，分别为先序、中序和后序
	void PreOrderTraverseNot();
	void InOrderTraverseNot();
	void PostOrderTraverseNot();

public:
	// 二叉树变为双向链表
	bool ConvertDoubleLink(Node *&first, Node *&last);
	// 二叉树转换左右子树
	void ConvertLeftAndRight();

protected:
	void PreOrderCreateAssist(Node *&p);
	void ReleaseNode(Node *&p);
	void PreOrderTraverseAssist(Node **p);
	void InOrderTraverseAssist(Node *&p);
	void PostOrderTraverseAssist(Node *&p);
	Node* RebuildTreeByPreOrderAndInOrderAssist(char *pre_order_seq, char *in_order_seq, int node_count);
	void ConvertDoubleLinkAssist(Node *node, Node *&first, Node *&last);
	bool FindSortTreePos(Node *p, char key, Node *last_pos, Node *&pos);
	bool StructureCmpAssist(Node *node1, Node *node2);
	Node* ConvertLeftAndRightAssist(Node *p);
	int GetLeafNodeCountAssist(Node *p);

protected:
	Node *head = nullptr;
	int count = 0;
};

#endif
