#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <map>

// 平衡二叉排序树结点平衡度
enum AVL_NODE_STATE
{
	AVL_NS_EH			= 0,	// 高度一样
	AVL_NS_LH			= 1,	// 左边高
	AVL_NS_RH			= 2,	// 右边高
};

struct Node
{
	Node() { Init(0); }
	Node(int d) { Init(d); }
	void Init(int d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
		avl_node_state = AVL_NS_EH;
		level = 0;
		seq = 0;
		pos = 0;
	}

	char data = 0;
	struct Node *left = nullptr;
	struct Node *right = nullptr;

	// 平衡二叉树用
	AVL_NODE_STATE avl_node_state = AVL_NS_EH;

	// 调试用
	int level = 0;			// 层级
	int seq = 0;			// 在完全二叉树中的序号
	int pos = 0;			// 打印的位置
};

class BinaryTree
{
public:
	BinaryTree() : head(nullptr), count(0) {}
	virtual ~BinaryTree();
protected:
	void ReleaseNode(Node *&p);

public:
	// 二叉树的深度
	int GetDepth();
	// 二叉树的叶子结点数量
	int GetLeafNodeCount();
	// 二叉树第k层结点数量
	int GetNodeCountInLevelK(int k);
	// 二叉树结构比较
	bool StructureCmp(const BinaryTree *tree);
	// 二叉树变为双向链表
	bool ConvertDoubleLink(Node *&first, Node *&last);
	// 二叉树转换左右子树
	void ConvertLeftAndRight();
protected:
	int GetDepthAssist(Node *p);
	int GetLeafNodeCountAssist(Node *p);
	int GetNodeCountInLevelKAssist(Node *p, int k);
	bool StructureCmpAssist(Node *node1, Node *node2);
	void ConvertDoubleLinkAssist(Node *node, Node *&first, Node *&last);
	Node* ConvertLeftAndRightAssist(Node *p);

public:
	// 先序建立二叉树：按照二叉树先序方式输入结点，以空格作为结点分隔符号，-表示null叶结点
	void PreOrderCreate();
	// 根据前序遍历和中序遍历重建二叉树
	bool RebuildTreeByPreOrderAndInOrder(char *pre_order_seq, char *in_order_seq, int node_count);

protected:
	void PreOrderCreateAssist(Node *&p);
	Node* RebuildTreeByPreOrderAndInOrderAssist(char *pre_order_seq, char *in_order_seq, int node_count);

public:
	// 递归方式遍历，分别为先序、中序和后序
	void PreOrderTraverse();
	void InOrderTraverse();
	void PostOrderTraverse();
protected:
	void PreOrderTraverseAssist(Node **p);
	void InOrderTraverseAssist(Node *&p);
	void PostOrderTraverseAssist(Node *&p);

public:
	// 非递归方式遍历，分别为先序、中序和后序
	void PreOrderTraverseNot();
	void InOrderTraverseNot();
	void PostOrderTraverseNot();

public:
	// 层次遍历
	void LevelOrderTraverse();

public:
	// 根据输入建立二叉排序树
	bool SortTreeRebuild(char *seq, int node_count);
protected:
	bool SortTreeFindPos(Node *p, char key, Node *last_pos, Node *&pos);

public:
	// 根据输入建立平衡二叉排序树
	void AVLTreeRebuild(char *seq, int node_count);
	// 查找
	bool AVLTreeFind(char key, Node *&p);
	// 删除结点
	void AVLTreeDelete(char key);
protected:
	void AVLTreeLRotate(Node *&p);
	void AVLTreeRRotate(Node *&p);
	void AVLTreeLeftBalance(Node *&p);
	void AVLTreeRightBalance(Node *&p);
	bool AVLTreeInsert(Node *&p, char key);
	Node* AVLTreeDeleteAssist(Node *&p, char key);
	void DeleteLeftCase(Node *&p, AVL_NODE_STATE child_avl_node_state);
	void DeleteRightCase(Node *&p, AVL_NODE_STATE child_avl_node_state);

public:
	void OutPut();
protected:
	void PreOutPut();
	void PreOutPutAssist(int depth, std::map<int, int>& seq_pos_map, Node *p, int level, int seq);

protected:
	Node *head = nullptr;
	int count = 0;
};

#endif
