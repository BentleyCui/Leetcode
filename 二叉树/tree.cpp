/*
	�������Ĳ���
*/
//�õݹ�ͷǵݹ����ʽʵ�ֶ������ı���
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

//����ǵݹ�
/*
* 1.��ջ�е���һ���ڵ�cur
* 2.��ӡcur
* 3.��ѹ����������ѹ������
* 4.ѭ��
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

//������� �ǵݹ�
/*
* ����ջ
* 1.�ȵ�cur��cur�����ռ�ջ
* 2.������������������
* 3.ѭ��
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


//������� �ǵݹ�
/*
* ÿ������������������߽��ջ�����ε�����ӡ���Ե����Ľڵ���������ظ�
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

//�������ȱ���
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

//�ж��Ƿ�������������
/*
* ������������Ƿ�����
*/
int preVal;	//����Ϊȫ����С
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

//��ͨ���׶�
bool chechBST(Node head) {
	vector<int> inOrderList;
	process(head, inOrderList);
	for (auto x : inOrderList) {
		//�ж��Ƿ��������
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
* �ǵݹ鷽ʽ���BST
* �ǵݹ���������ĸ�д
*/
bool checkBST3(Node head) {
	if (head != nullptr) {
		int preVal;	//����Ϊ��С
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

//�ж�һ�����Ƿ�����ȫ������
/*
* ��α���
* 1.�κ�һ���ڵ㣬ֻ���Һ��ӣ�û�����ӣ�return false
* 2.�ڣ�1����Υ�������£���һ�����Һ��Ӳ�ȫ˫�����֮��Ľڵ㶼��Ҷ�ӽڵ�
*/
bool isCBT(Node head) {
	if (head == nullptr)
		return true;
	queue<Node> queue;
	queue.push(head);
	bool leaf = false;	//��ʾ�Ƿ�������һ�����Һ��Ӳ�˫ȫ�Ľڵ�
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

//����DP����: ȷ��base case����������������Ҫ��ͬ

//�ж�һ�����Ƿ���ƽ�������:�κ�һ�����������������߶Ȳ����1
/*
* 1.�������Ƿ�ƽ�⣬�������Ƿ�ƽ��
* 2.ÿ�������ĸ߶�
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
	ReturnType leftData = process1(root.lchild);	//����õ�����������Ϣ
	ReturnType rightData = process1(root.rchild);	//����õ��ұߵ���Ϣ
	int height = math.max(leftData.height, rightData.height) + 1;
	bool isBalanced = leftData.isBalanced && rightData.isBalanced && math.abs(leftData.height - rightData.height.height) < 2;
	return new ReturnType(isBalanced, height);
}

/*
* �ݹ鷽������Ƿ�������������������DP��
* head.left.max < head.val < head.right.min
* ������Ϣ: min max �����Ƿ��������������������Ƿ�������������
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
	ReturnData leftData = process2(head.lchild);		//����õ���������Ϣ
	ReturnData rightData = process2(head.rchild);	//����õ���������Ϣ
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

//����Ƿ�����������
/*
* �ڵ��������ĸ߶����㣺nodes = 2*h-1
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

//Ѱ������������͹������Ƚ��
/*
* ����1����map��¼ÿ���ڵ�ĸ��ڵ�
* ����2���ݹ飨1��o1��o2��LAC����o2��o1��LAC
*			  (2)O1��o2����ΪLAC���������ҵ���������
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
