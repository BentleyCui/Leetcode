/*
	二叉树的操作
*/
//用递归和非递归的形式实现二叉树的遍历
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
struct Node {
	/* data */
	int val;
	Node* lchild;
	Node* rchild;
	Node(int data) : val(data), lchild(nullptr), rchild(nullptr) {};
};

void preOrderRecur(Node head) {
	if (head == nullptr)
		return;
	cout << head->val << " ";
	preOrderRecur(head->left);
	preOrderRecur(head->right);
}

void inOrderRecur(Node head) {
	if (head == nullptr)
		return;
	inOrderRecur(head->left);
	cout << head->val << " ";
	inOrderRecur(head->right);
}

void posOrderRecur(Node head) {
	if (head == nullptr)
		return;
	posOrderRecur(head->left);
	posOrderRecur(head->right);
	cout << head->val << " ";
}

//先序非递归
/*
* 1.从栈中弹出一个节点cur
* 2.打印cur
* 3.先压右子树，再压左子树
* 4.循环
*/
void preOrderUnRecur(Node head) {
	if (head == nullptr)
		return;
	stack<Node> stack;
	stack.push(head);
	while (!stack.empty()) {
		head = stack.pop();
		cout << head.val << " ";
		if (head.rchild != nullptr)
			stack.push(head.rchild);
		if (head.lchild != nullptr)
			stack.push(head.lchild);
	}
}

//后序遍历 非递归
/*
* 两个栈
* 1.先弹cur，cur放入收集栈
* 2.先左子树，后右子树
* 3.循环
*/
void posOrderUnRecur(Node head) {
	if (head != nullptr) {
		stack<Node> s1;
		stack<Node> s2;
		s1.push(head);
		while (!s1.empty()) {
			head = s1.pop();
			s2.push(head);
			if (head.lchild != nullptr)
				s1.push(head.lchild);
			if (head.rchild != nullptr)
				s1.push(head.rchild);
		}
		while (!s2.empty()
		{
			cout << s2.pop() << " ";
		}
	}
}


//中序遍历 非递归
/*
* 每棵子树，整棵树的左边界进栈，依次弹出打印，对弹出的节点的右子树重复
*/
void inOrderUnRecur(Node head) {
	if (head != nullptr)
	{
		stack<Node> stack;
		while (!stack.empty() || head != nullptr)
		{
			if (head != nullptr) {
				stack.push(head);
				head = head.lchild;
			}
			else
			{
				head = stack.top();
				stack.pop();
				cout << head.val << " ";
				head = head.rchild;
			}
		}
	}
}

//宽度优先遍历
void wOrder(Node head) {
	if (head == nullptr)
		return;
	queue<Node> queue;
	queue.push(head);
	while (!queue.empty()) {
		Node cur = queue.front();
		queue.pop();
		cout << cur.val << " ";
		if (cur.lchild != nullptr)
			queue.push(cur.lchild);
		if (cur.rchild != nullptr)
			queue.push(cur.rchild);

	}
}

//判断是否是搜索二叉树
/*
* 中序遍历，看是否升序
*/
int preVal;	//定义为全局最小
bool isBST(Node head) {
	if (head == nullptr)
		return true;
	bool isLeftBST = isBST(head.lchild);
	if (!isLeftBST)
		return false;
	else
		preVal = head.val;
	return isBST(head.rchild);
}

//更通俗易懂
bool chechBST(Node head) {
	vector<int> inOrderList;
	process(head, inOrderList);
	for (auto x : inOrderList) {
		//判断是否是升序的
	}
}
void process(Node head, vector<int> inOrderList) {
	if (head == nullptr)
		return;
	process(head.lchild, inOrderList);
	inOrderList.push_back(head.val);
	process(head.rchild, inOrderList);
}

/*
* 非递归方式检查BST
* 非递归中序遍历的改写
*/
bool checkBST3(Node head) {
	if (head != nullptr) {
		int preVal;	//设置为最小
		stack<Node> stack;
		while (!stack.empty() || head != nullptr) {
			if (head != nullptr) {
				stack.push(head);
				head = head.lchild;
			}
			else {
				head = stack.top();
				stack.pop();
				if (head.val <= preVal)
					return false;
				else
					preVal = head.val;
				head = head.rchild;
			}
		}
		return true;
	}
}

//判断一棵树是否是完全二叉树
/*
* 层次遍历
* 1.任何一个节点，只有右孩子，没有左孩子，return false
* 2.在（1）不违规的情况下，第一个左右孩子不全双的情况之后的节点都是叶子节点
*/
bool isCBT(Node head) {
	if (head == nullptr)
		return true;
	queue<Node> queue;
	queue.push(head);
	bool leaf = false;	//表示是否遇到第一个左右孩子不双全的节点
	Node l = nullptr;
	Node r = nullptr;
	while (!queue.empty()) {
		head = queue.front();
		queue.pop();
		l = head.lchild;
		r = head.rchild;
		if ((l == nullptr && r != nullptr) || (leaf && (l != nullptr || r != nullptr)))
			return false;
		if (l != nullptr)
			queue.push(l);
		if (r != nullptr)
			queue.push(r);
		if (l == nullptr || r == nullptr)
			leaf = true;
	}
	return true;
}

//树的DP问题: 确定base case，左右子树的问题要相同

//判断一棵树是否是平衡二叉树:任何一棵子树，左右子树高度差不超过1
/*
* 1.左子树是否平衡，右子树是否平衡
* 2.每棵子树的高度
*/
class ReturnType {
	bool isBlanced;
	int height;
	ReturnType(bool isB, int heig) {
		isBlanced = isB;
		height = heig;
	}
};
bool isBalanced(Node head) {
	return process(head).isBlanced;
}
ReturnType process1(Node root) {
	if (root == nullptr) {
		return new ReturnType(true, 0);
	}
	ReturnType leftData = process1(root.lchild);	//假设得到左子树的信息
	ReturnType rightData = process1(root.rchild);	//假设得到右边的信息
	int height = math.max(leftData.height, rightData.height) + 1;
	bool isBalanced = leftData.isBalanced && rightData.isBalanced && math.abs(leftData.height - rightData.height.height) < 2;
	return new ReturnType(isBalanced, height);
}

/*
* 递归方法求解是否是搜索二叉树（树形DP）
* head.left.max < head.val < head.right.min
* 给的信息: min max 左树是否是搜索二叉树，右树是否是搜索二叉树
*/
class ReturnData {
	bool isBST;
	int min;
	int max;
	ReturnData(bool isB, int mi, int ma) {
		isBST = isB;
		min = mi;
		max = ma;
	}
};
ReturnData process2(Node head) {
	if (head == nullptr)		//base case
		return NULL;
	ReturnData leftData = process2(head.lchild);		//假设得到左子树信息
	ReturnData rightData = process2(head.rchild);	//假设得到右子树信息
	int min = head.val;
	int max = head.val;
	if (leftData != NULL) {
		min = math.min(min, leftData.min);
		max = Math.max(max, leftData.max);
	}
	if (rightData != NULL) {
		min = math.min(min, rightData.min);
		max = Math.max(max, rightData.max);
	}
	bool isBST = true;
	if (leftData != NULL && (!leftData.isBST || leftData.max > head.val))
		isBST = false;
	if (rightData != NULL && (!rightData.isBST || rightData.min < head.val))
		isBST = false;
	return new ReturnData(isBST, min, max);
}

//求解是否是满二叉树
/*
* 节点数和树的高度满足：nodes = 2*h-1
*/
class Info{
	int height;
	int nodes;
	Info(int h ,int n) {
		height = h;
		nodes = n;
	}
};
bool isFullBinTree(Node head) {
	if (head == nullptr)
		return true;
	Info data = process3(head);
	return data.nodes == (1 << data.height - 1);
}
Info process3(Node x) {
	if (x == nullptr)
		return NULL;
	Info leftData = process3(x.lchild);
	Info rightData = process3(x.rchild);
	int nodes = leftData.nodes + rightData.nodes + 1;
	int height = max(leftData.height, rightData.height) + 1;
	return new Info(height, nodes);
}

//寻找两个结点的最低公共祖先结点
/*
* 方法1：用map记录每个节点的父节点
* 方法2：递归（1）o1是o2的LAC或者o2是o1的LAC
*			  (2)O1与o2不互为LAC，则向上找到公共祖先
*/
Node lowestAC(Node head, Node o1, Node o2) {
	if (head == nullptr || head == o1 || head == o2)
		return head;
	Node left = lowestAC(head.lchild, o1, o2);
	Node right = lowestAC(head.rchild, o1, o2);
	if (left != nullptr && right != nullptr)
		return head;
	return left != nullptr ? left : right;
}