#include "BinaryTree.h"

#include <iostream>
#include <stack>
#include <queue>

#include <cmath>
#include <exception>

BinaryTree::~BinaryTree()
{
	std::cout << "析构函数：" << std::endl;
	ReleaseNode(head);
	std::cout << std::endl;
}

void BinaryTree::ReleaseNode(Node *&p)
{
	if (!p)
	{
		return;
	}
	else
	{
		ReleaseNode(p->left);
		ReleaseNode(p->right);
		std::cout << p->data << " ";
		delete p;
		p = nullptr;
	}
}

int BinaryTree::GetDepth()
{
	return GetDepthAssist(head);
}

int BinaryTree::GetLeafNodeCount()
{
	return GetLeafNodeCountAssist(head);
}

int BinaryTree::GetNodeCountInLevelK(int k)
{
	return GetNodeCountInLevelKAssist(head, k);
}

bool BinaryTree::StructureCmp(const BinaryTree *tree)
{
	if (!tree && !head)
	{
		return true;
	}

	return StructureCmpAssist(head, tree->head);
}

bool BinaryTree::ConvertDoubleLink(Node *&first, Node *&last)
{
	std::cout << "二叉树转为双向链表：" << std::endl;
	ConvertDoubleLinkAssist(head, first, last);
	return (first && last);
}

void BinaryTree::ConvertLeftAndRight()
{
	std::cout << "二叉树转换左右子树：" << std::endl;
	ConvertLeftAndRightAssist(head);
}

int BinaryTree::GetDepthAssist(Node *p)
{
	if (!p)
	{
		return 0;
	}

	int left_depth = GetDepthAssist(p->left);
	int right_depth = GetDepthAssist(p->right);
	return (left_depth > right_depth ? (left_depth + 1) : (right_depth + 1));
}

int BinaryTree::GetLeafNodeCountAssist(Node *p)
{
	if (!p)
	{
		return 0;
	}

	if (!p->left && !p->right)
	{
		return 1;
	}

	int left_leaf_node_count = 0;
	if (p->left)
	{
		left_leaf_node_count = GetLeafNodeCountAssist(p->left);
	}
	int right_leaf_node_count = 0;
	if (p->right)
	{
		right_leaf_node_count = GetLeafNodeCountAssist(p->right);
	}

	return (left_leaf_node_count + right_leaf_node_count);
}

int BinaryTree::GetNodeCountInLevelKAssist(Node *p, int k)
{
	if (!p || k < 1)
	{
		return 0;
	}

	if (k == 1)
	{
		return 1;
	}

	int left_node_count = 0;
	if (p->left)
	{
		left_node_count = GetNodeCountInLevelKAssist(p->left, k - 1);
	}
	int right_node_count = 0;
	if (p->right)
	{
		right_node_count = GetNodeCountInLevelKAssist(p->right, k - 1);
	}
	return (left_node_count + right_node_count);
}

bool BinaryTree::StructureCmpAssist(Node *node1, Node *node2)
{
	if (!node1 && !node2)
	{
		return true;
	}
	else if (!node1 || !node2)
	{
		return false;
	}

	return (StructureCmpAssist(node1->left, node2->left) && StructureCmpAssist(node1->right, node2->right));
}

void BinaryTree::ConvertDoubleLinkAssist(Node *node, Node *&first, Node *&last)
{
	if (!node)
	{
		first = nullptr;
		last = nullptr;
		return;
	}

	// 当前结点的左子树为空，则当前结点即为双向链表的第一个结点
	// 当前结点的左子树不为空，则转换左子树可以得到其左子树的双向链表，连接其左子树的双向链表和当前结点
	if (node->left)
	{
		Node *first_left = nullptr;
		Node *last_left = nullptr;
		ConvertDoubleLinkAssist(node->left, first_left, last_left);
		first = first_left;
		node->left = last_left;
		last_left->right = node;
	}
	else
	{
		first = node;
	}

	// 当前结点的右子树为空，则当前结点即为双向链表的最后一个结点
	// 当前结点的右子树不为空，则转换右子树可以得到其右子树的双向链表，连接其右子树的双向链表和当前结点
	if (node->right)
	{
		Node *first_right = nullptr;
		Node *last_right = nullptr;
		ConvertDoubleLinkAssist(node->right, first_right, last_right);
		last = last_right;
		node->right = first_right;
		first_right->left = node;
	}
	else
	{
		last = node;
	}
}

Node* BinaryTree::ConvertLeftAndRightAssist(Node *p)
{
	if (!p)
	{
		return nullptr;
	}

	Node *left = nullptr;
	if (p->left)
	{
		left = ConvertLeftAndRightAssist(p->left);
	}
	Node *right = nullptr;
	if (p->right)
	{
		right = ConvertLeftAndRightAssist(p->right);
	}

	p->left = right;
	p->right = left;
	return p;
}

void BinaryTree::PreOrderCreate()
{
	std::cout << "先序建立二叉树：" << std::endl;
	PreOrderCreateAssist(head);
	std::cout << std::endl;
}

bool BinaryTree::RebuildTreeByPreOrderAndInOrder(char *pre_order_seq, char *in_order_seq, int node_count)
{
	std::cout << "根据先序遍历(" << pre_order_seq << ")和中序遍历(" << in_order_seq << ")重建二叉树：" << std::endl;
	try
	{
		head = RebuildTreeByPreOrderAndInOrderAssist(pre_order_seq, in_order_seq, node_count);
	}
	catch (...)
	{
		return false;
	}
	return (head);
}

void BinaryTree::PreOrderCreateAssist(Node *&p)
{
	char temp;
	std::cin >> temp;
	if (temp == '-')
	{
		return;
	}
	else
	{
		p = new Node(temp);
		++count;
		PreOrderCreateAssist(p->left);
		PreOrderCreateAssist(p->right);
	}
}

Node* BinaryTree::RebuildTreeByPreOrderAndInOrderAssist(char *pre_order_seq, char *in_order_seq, int node_count)
{
	if (!pre_order_seq || !in_order_seq || node_count <= 0)
	{
		return nullptr;
	}
	// 先序遍历的第一个数据就是根结点
	Node *p = new Node(pre_order_seq[0]);

	// 中序遍历中找出根结点的位置，根结点左边的即为二叉树的左子树，右边的即为二叉树的右子树，根据结点数量即可得到左子树和右子树的先序和中序序列，递归即可
	int root_pos_in_in_order = -1;
	for (int i = 0; i < node_count; ++i)
	{
		if (in_order_seq[i] == pre_order_seq[0])
		{
			root_pos_in_in_order = i;
			break;
		}
	}

	if (root_pos_in_in_order == -1)
	{
		std::cout << "序列错误" << std::endl;
		throw "RebuildTreeByPreOrderAndInOrderAssist invalid input";
		return nullptr;
	}

	p->left = RebuildTreeByPreOrderAndInOrderAssist(pre_order_seq + 1, in_order_seq, root_pos_in_in_order);
	p->right = RebuildTreeByPreOrderAndInOrderAssist(pre_order_seq + 1 + root_pos_in_in_order, in_order_seq + root_pos_in_in_order + 1, node_count - root_pos_in_in_order - 1);
	return p;
}

void BinaryTree::PreOrderTraverse()
{
	std::cout << "先序遍历二叉树：";
	PreOrderTraverseAssist(&head);
	std::cout << std::endl << std::endl;
}

void BinaryTree::InOrderTraverse()
{
	std::cout << "中序遍历二叉树：";
	InOrderTraverseAssist(head);
	std::cout << std::endl << std::endl;
}

void BinaryTree::PostOrderTraverse()
{
	std::cout << "后序遍历二叉树：";
	PostOrderTraverseAssist(head);
	std::cout << std::endl << std::endl;
}

void BinaryTree::PreOrderTraverseAssist(Node **p)
{
	if (*p)
	{
		std::cout << (*p)->data << " ";
		PreOrderTraverseAssist(&((*p)->left));
		PreOrderTraverseAssist(&((*p)->right));
	}
}

void BinaryTree::InOrderTraverseAssist(Node *&p)
{
	if (p)
	{
		InOrderTraverseAssist(p->left);
		std::cout << p->data << " ";
		InOrderTraverseAssist(p->right);
	}
}

void BinaryTree::PostOrderTraverseAssist(Node *&p)
{
	if (p)
	{
		PostOrderTraverseAssist(p->left);
		PostOrderTraverseAssist(p->right);
		std::cout << p->data << " ";
	}
}

void BinaryTree::PreOrderTraverseNot()
{
	std::cout << "先序遍历二叉树(非递归)：";
	std::stack<Node*> s;
	if (head)
	{
		s.push(head);
	}

	while (!s.empty())
	{
		Node *p = s.top();
		s.pop();
		if (p)
		{
			std::cout << p->data << " ";
			if (p->right)
			{
				s.push(p->right);
			}
			if (p->left)
			{
				s.push(p->left);
			}
		}
	}
	std::cout << std::endl << std::endl;
}

void BinaryTree::InOrderTraverseNot()
{
	std::cout << "中序遍历二叉树(非递归)：";
	std::stack<Node*> s;
	if (head)
	{
		s.push(head);
	}

	Node *p;
	while (!s.empty())
	{
		while (p = s.top())
		{
			s.push(p->left);
		}

		s.pop();

		if (!s.empty())
		{
			p = s.top();
			s.pop();
			std::cout << p->data << " ";
			s.push(p->right);
		}
	}
	std::cout << std::endl << std::endl;
}

void BinaryTree::PostOrderTraverseNot()
{
	std::cout << "后序遍历二叉树(非递归)：";
	std::stack<Node*> s;
	if (head)
	{
		s.push(head);
	}
	Node *current = s.top();
	s.pop();
	Node *preVisited = nullptr;
	while (current != nullptr || !s.empty())
	{
		while (current)
		{
			s.push(current);
			current = current->left;
		}
		current = s.top();

		if (current->right == nullptr || current->right == preVisited)
		{
			std::cout << current->data << " ";
			preVisited = current;
			s.pop();
			current = nullptr;
		}
		else
		{
			current = current->right;
		}
	}
	std::cout << std::endl << std::endl;
}

void BinaryTree::LevelOrderTraverse()
{
	std::cout << "层次遍历二叉树：";
	if (head)
	{
		std::queue<Node*> q;
		q.push(head);

		while (!q.empty())
		{
			Node *p = q.front();
			std::cout << p->data << " ";

			if (p->left)
			{
				q.push(p->left);
			}
			if (p->right)
			{
				q.push(p->right);
			}
			q.pop();
		}
	}
	std::cout << std::endl << std::endl;
}

bool BinaryTree::SortTreeRebuild(char *seq, int node_count)
{
	std::cout << "建立二叉排序树(" << seq <<  ")：" << std::endl;
	for (int i = 0; i < node_count; ++i)
	{
		Node *pos = nullptr;
		if (SortTreeFindPos(head, seq[i], nullptr, pos))
		{
			continue;
		}
		else
		{
			Node *p = new Node(seq[i]);
			if (!pos)
			{
				head = p;
			}
			else if (seq[i] < pos->data)
			{
				pos->left = p;
			}
			else if (seq[i] > pos->data)
			{
				pos->right = p;
			}
		}
		OutPut();
	}
	return true;
}

bool BinaryTree::SortTreeFindPos(Node *p, char key, Node *last_pos, Node *&pos)
{
	if (!p)
	{
		pos = last_pos;
		return false;
	}

	if (key == p->data)
	{
		pos = p;
		return true;
	}
	else if (key < p->data)
	{
		return SortTreeFindPos(p->left, key, p, pos);
	}
	else if (key > p->data)
	{
		return SortTreeFindPos(p->right, key, p, pos);
	}
}

void BinaryTree::AVLTreeRebuild(char *seq, int node_count)
{
	std::cout << "建立平衡二叉排序树(" << seq <<  ")：" << std::endl;
	for (int i = 0; i < node_count; ++i)
	{
		AVLTreeInsert(head, seq[i]);
		OutPut();
	}
}

bool BinaryTree::AVLTreeFind(char key, Node *&p)
{
	Node *node = head;
	while (node)
	{
		if (key == node->data)
		{
			p = node;
			return true;
		}
		else if (key < node->data)
		{
			node = node->left;
		}
		else if (key > node->data)
		{
			node = node->right;
		}
	}

	return false;
}

void BinaryTree::AVLTreeDelete(char key)
{
	AVLTreeDeleteAssist(head, key);
	std::cout << "平衡二叉排序树删除结点" << key << std::endl;
}

// 插入新结点f，导致b失去平衡，调整b，结点b为p，为单向左旋
//   b              d
//  / \            / \
// a   d          b   e
//    / \        / \   \
//   c   e      a   c   f
//        \
//         f
void BinaryTree::AVLTreeLRotate(Node *&p)
{
	Node *rc = p->right;
	p->right = rc->left;
	rc->left = p;
	p = rc;
}

// 插入新结点a，导致e失去平衡，调整e，结点e为p，为单向右旋
//       e          c
//      / \        / \
//     c   f      b   e
//    / \        /   / \
//   b   d      a   d   f
//  /
// a
void BinaryTree::AVLTreeRRotate(Node *&p)
{
	Node *lc = p->left;
	p->left = lc->right;
	lc->right = p;
	p = lc;
}

// 插入新结点c，导致e失去平衡，调整e，先左旋后右旋
//       e           e           d
//      / \         / \         / \
//     b   f       d   f       b   e
//    / \         /           / \   \
//   a   d       b           a   c   f
//      /       / \
//     c       a   c
//
//     1            2            3
void BinaryTree::AVLTreeLeftBalance(Node *&p)
{
	Node *lc = p->left;
	if (lc->avl_node_state == AVL_NS_EH)
	{
		p->avl_node_state = AVL_NS_LH;
		lc->avl_node_state = AVL_NS_RH;
		AVLTreeRRotate(p);
	}
	else if (lc->avl_node_state == AVL_NS_LH)
	{
		// 2 -> 3
		p->avl_node_state = AVL_NS_EH;
		lc->avl_node_state = AVL_NS_EH;
		AVLTreeRRotate(p);
	}
	else if (lc->avl_node_state == AVL_NS_RH)
	{
		// 1 -> 2 -> 3
		Node *rd = lc->right;
		if (rd->avl_node_state == AVL_NS_EH)
		{
			p->avl_node_state = AVL_NS_EH;
			lc->avl_node_state = AVL_NS_EH;
		}
		else if (rd->avl_node_state == AVL_NS_LH)
		{
			p->avl_node_state = AVL_NS_RH;
			lc->avl_node_state = AVL_NS_EH;
		}
		else if (rd->avl_node_state == AVL_NS_RH)
		{
			p->avl_node_state = AVL_NS_EH;
			lc->avl_node_state = AVL_NS_LH;
		}
		rd->avl_node_state = AVL_NS_EH;
		AVLTreeLRotate(p->left);
		AVLTreeRRotate(p);
	}
}

// 插入新结点c，导致b失去平衡，调整b，先右旋后左旋
//   b         b             d
//  / \       / \           / \
// a   e     a   d         b   e
//    / \       / \       / \   \
//   d   f     c   e     a   c   f
//  /               \
// c                 f
//
//   1          2            3
void BinaryTree::AVLTreeRightBalance(Node *&p)
{
	Node *rc = p->right;
	if (rc->avl_node_state == AVL_NS_EH)
	{
		p->avl_node_state = AVL_NS_RH;
		rc->avl_node_state = AVL_NS_LH;
		AVLTreeLRotate(p);
	}
	else if (rc->avl_node_state == AVL_NS_LH)
	{
		// 1 -> 2 -> 3
		Node *ld = rc->left;
		if (ld->avl_node_state == AVL_NS_EH)
		{
			p->avl_node_state = AVL_NS_EH;
			rc->avl_node_state = AVL_NS_EH;
		}
		else if (ld->avl_node_state == AVL_NS_LH)
		{
			p->avl_node_state = AVL_NS_EH;
			rc->avl_node_state = AVL_NS_RH;
		}
		else if (ld->avl_node_state == AVL_NS_RH)
		{
			//p->avl_node_state = AVL_NS_EH;
			//rc->avl_node_state = AVL_NS_LH;
			p->avl_node_state = AVL_NS_LH;
			rc->avl_node_state = AVL_NS_EH;
		}
		ld->avl_node_state = AVL_NS_EH;
		AVLTreeRRotate(p->right);
		AVLTreeLRotate(p);
	}
	else if (rc->avl_node_state == AVL_NS_RH)
	{
		// 2 -> 3
		p->avl_node_state = AVL_NS_EH;
		rc->avl_node_state = AVL_NS_EH;
		AVLTreeLRotate(p);
	}
}

bool BinaryTree::AVLTreeInsert(Node *&p, char key)
{
	// 插入新结点，需要调整
	if (!p)
	{
		p = new Node(key);
		return true;
	}

	// 插入会影响父结点的平衡，一直调整到根结点
	if (key == p->data)
	{
		return false;
	}
	else if (key < p->data)
	{
		if (AVLTreeInsert(p->left, key))
		{
			if (p->avl_node_state == AVL_NS_EH)
			{
				// 父结点平衡，插入后必然会左边高，需要调整
				p->avl_node_state = AVL_NS_LH;
				return true;
			}
			else if (p->avl_node_state == AVL_NS_LH)
			{
				// 父结点左边高，插入后需要左调整，需要调整(函数内)
				AVLTreeLeftBalance(p);
				return false;
			}
			else if (p->avl_node_state == AVL_NS_RH)
			{
				// 父结点右边高，插入后平衡
				p->avl_node_state = AVL_NS_EH;
				return false;
			}
		}
	}
	else if (key > p->data)
	{
		if (AVLTreeInsert(p->right, key))
		{
			if (p->avl_node_state == AVL_NS_EH)
			{
				// 父结点平衡，插入后必然会右边高，需要调整(函数内)
				p->avl_node_state = AVL_NS_RH;
				return true;
			}
			else if (p->avl_node_state == AVL_NS_LH)
			{
				// 父结点左边高，插入后平衡
				p->avl_node_state = AVL_NS_EH;
				return false;
			}
			else if (p->avl_node_state == AVL_NS_RH)
			{
				// 父结点右边高，插入后需要右调整，需要调整(函数内)
				AVLTreeRightBalance(p);
				return false;
			}
		}
	}
}

Node* BinaryTree::AVLTreeDeleteAssist(Node *&p, char key)
{
	AVL_NODE_STATE child_avl_node_state;
	if (p)
	{
		if (key < p->data)
		{
			child_avl_node_state = p->left->avl_node_state;
			p->left = AVLTreeDeleteAssist(p->left, key);
			DeleteLeftCase(p, child_avl_node_state);
		}
		else if (key > p->data)
		{
			child_avl_node_state = p->right->avl_node_state;
			p->right = AVLTreeDeleteAssist(p->right, key);
			DeleteRightCase(p, child_avl_node_state);
		}
		else if (key == p->data)
		{
			child_avl_node_state = p->avl_node_state;
			if (p->left)
			{
				// 找左子树的最右子树(左边最大值)来代替被删节点
				Node *far_right = p->left;
				while (far_right->right)
				{
					far_right = far_right->right;
				}
				p->data = far_right->data;
				p->left = AVLTreeDeleteAssist(p->left, far_right->data);
				DeleteLeftCase(p, child_avl_node_state);
			}
			else if (p->right)
			{
				// 找右子树的最左子树(右边最小值)来代替被删节点
				Node *far_left = p->right;
				while (far_left->left)
				{
					far_left = far_left->left;
				}
				p->data = far_left->data;
				p->right = AVLTreeDeleteAssist(p->right, far_left->data);
				DeleteRightCase(p, child_avl_node_state);
			}
			else
			{
				// 叶子结点，直接删除
				free(p);
				p = nullptr;
			}
		}
	}

	return p;
}

void BinaryTree::DeleteLeftCase(Node *&p, AVL_NODE_STATE child_avl_node_state)
{
	// 删除没有左子树 或 被删除结点删除之前不平衡，删除之后平衡了
	// 说明p的平衡度有变化
	if (!p->left || (AVL_NS_EH != child_avl_node_state && AVL_NS_EH == p->left->avl_node_state))
	{
		switch (p->avl_node_state)
		{
		case AVL_NS_EH:
			p->avl_node_state = AVL_NS_RH;
			break;
		case AVL_NS_LH:
			p->avl_node_state = AVL_NS_EH;
			break;
		case AVL_NS_RH:
			AVLTreeRightBalance(p);
			break;
		}
	}
}

void BinaryTree::DeleteRightCase(Node *&p, AVL_NODE_STATE child_avl_node_state)
{
	// 删除没有右子树 或 被删除结点删除之前不平衡，删除之后平衡了
	// 说明p的平衡度有变化
	if (!p->right || (AVL_NS_EH != child_avl_node_state && AVL_NS_EH == p->right->avl_node_state))
	{
		switch (p->avl_node_state)
		{
		case AVL_NS_EH:
			p->avl_node_state = AVL_NS_LH;
			break;
		case AVL_NS_RH:
			p->avl_node_state = AVL_NS_EH;
			break;
		case AVL_NS_LH:
			AVLTreeLeftBalance(p);
			break;
		}
	}
}

void BinaryTree::OutPut()
{
	std::cout << "二叉树：" << std::endl;

	PreOutPut();
	if (head)
	{
		std::queue<Node*> q;
		q.push(head);

		int cur_out_put_level = 1;
		std::map<int, int> cut_out_put_pos;
		while (!q.empty())
		{
			Node *p = q.front();
			if (p->level != cur_out_put_level)
			{
				std::cout << std::endl << std::endl;
				cur_out_put_level = p->level;
			}
			int space_num = p->pos - cut_out_put_pos[cur_out_put_level];
			for (int i = 0; i < space_num; ++i)
			{
				std::cout << " ";
			}
			std::cout << p->data;
			cut_out_put_pos[cur_out_put_level] += (space_num + 1);

			if (p->left)
			{
				q.push(p->left);
			}
			if (p->right)
			{
				q.push(p->right);
			}
			q.pop();
		}
	}

	std::cout << std::endl << std::endl;
}

void BinaryTree::PreOutPut()
{
	std::map<int, int> seq_pos_map;
	PreOutPutAssist(GetDepth(), seq_pos_map, head, 1, 1);
}

#define GET_LEVEL_BY_SEQ(seq) ((int)(std::log(seq) / std::log(2)) + 1)
#define GET_LEVEL_SEQ_BY_SEQ(seq) (int)((seq) % (int)std::pow(2, (GET_LEVEL_BY_SEQ(seq)) - 1) + 1)
#define GET_POS_BY_SEQ(seq) (int)((((GET_LEVEL_SEQ_BY_SEQ(seq)) % 2 == 1) ? 1 : 5) + ((GET_LEVEL_SEQ_BY_SEQ(seq) - 1) / 2) * 6)

#define GET_LEVEL_SEQ_BY_SEQ_AND_LEVEL(seq, level) (int)((seq) % (int)std::pow(2, (level) - 1) + 1)
#define GET_POS_BY_SEQ_AND_LEVEL(seq, level) (int)((((GET_LEVEL_SEQ_BY_SEQ_AND_LEVEL(seq, level)) % 2 == 1) ? 1 : 5) + ((GET_LEVEL_SEQ_BY_SEQ_AND_LEVEL(seq, level) - 1) / 2) * 6)
void BinaryTree::PreOutPutAssist(int depth, std::map<int, int>& seq_pos_map, Node *p, int level, int seq)
{
	if (!p)
	{
		return;
	}
	p->level = level;
	p->seq = seq;

	if (p->left)
	{
		PreOutPutAssist(depth, seq_pos_map, p->left, level + 1, seq * 2);
	}
	if (p->right)
	{
		PreOutPutAssist(depth, seq_pos_map, p->right, level + 1, seq * 2 + 1);
	}

	if (p->level == depth)
	{
		seq_pos_map[p->seq] = GET_POS_BY_SEQ_AND_LEVEL(p->seq, p->level);
	}
	else
	{
		int tmp = std::pow(2, depth - p->level);
		int seq_start = seq * tmp;
		int seq_end = (seq + 1) * tmp - 1;
		for (int s = seq_start; s <= seq_end; ++s)
		{
			if (seq_pos_map[s] == 0)
			{
				seq_pos_map[s] = GET_POS_BY_SEQ(s);
			}

			seq_pos_map[p->seq] += seq_pos_map[s];
		}
		seq_pos_map[p->seq] /= tmp;
	}
	p->pos = seq_pos_map[p->seq];
}
