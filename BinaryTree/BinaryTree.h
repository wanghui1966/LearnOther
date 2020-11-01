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

// 红黑树结点颜色
enum RBT_NODE_COLOR
{
	RBT_NC_RED			= 0,
	RBT_NC_BLACK		= 1,
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

	// 二叉排序树，要么是空树要么具备以下性质
	// 1. 若其左子树不为空，则其左子树上所有结点的值均小于此结点的值
	// 2. 若其右子树不为空，则其右子树上所有结点的值均小于此结点的值
	// 3. 其左右子树均为二叉排序树
	// 4. 没有值相等的结点

	// 平衡二叉树，要么是空树要么具备以下性质
	// 1. 任意结点的平衡因子avl_node_state∈{-1, 0, 1}

	// 平衡二叉排序树
	AVL_NODE_STATE avl_node_state = AVL_NS_EH;

	// 红黑树，要么是空树要么具备以下性质
	// 1. 结点非黑即红
	// 2. 根结点为黑
	// 3. 叶子结点为黑
	// 4. 红结点的左右子结点均为黑
	// 5. 任一结点到其叶子结点的路径中包含相同的黑结点
	RBT_NODE_COLOR rbt_node_color = RBT_NC_RED;

	// B树，即B-Tree，每个结点都含有数据信息，假设为m阶
	// 1. 每个结点最多含有m个子结点，其中m>=2
	// 2. 除根结点和叶子结点外，其余结点最少含有ceil(m/2)个子结点
	// 3. 若根结点不是叶子结点，则至少含有2个子结点
	// 4. 所有的叶子结点都在同一层
	// 5. 非叶子结点有n个子结点，则其应该有n-1个关键字

	// B+树，即B+-Tree，满足B树性质，不同的是
	// 1. 非叶子结点有n个子结点，则其应该有n个关键字
	// 2. 只有叶子结点才含有所有的数据信息，非叶子结点只有关键字信息

	// 99. B+树还有一个最大的好处，方便扫库，B树必须用中序遍历的方法按序扫库，而B+树直接从叶子结点挨个扫一遍就完了，B+树支持range-query非常方便(比如查5-10之间的)，而B树不支持，这是数据库选用B+树的最主要原因。B树的好处，就是成功查询特别有利，因为树的高度总体要比B+树矮。不成功的情况下，B树也比B+树稍稍占一点点便宜。mysql底层存储是用B+树实现的，知道为什么么。内存中B+树是没有优势的，但是一到磁盘，B+树的威力就出来了。

	// 调试用
	int level = 0;			// 层级
	int seq = 0;			// 在完全二叉树中的序号
	int pos = 0;			// 打印的位置
};

class BinaryTree
{
public:
	BinaryTree() : root(nullptr), count(0) {}
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
	Node *root = nullptr;
	int count = 0;
};

#endif
