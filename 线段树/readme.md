## 线段树

线段树是一种**二叉树**，广义上也被归类为二叉搜索树

对于区间的修改、维护和查询 时间复杂度优化为 `log(n)`级别

小区间更新大区间，线段树是**平衡二叉树**

问题需要满足：区间加法，

即

```c++
对于[L, R]的区间，它的答案可以由
[L, M] 和 [M+1, R]的答案合并求出
```

可以解决的问题：区间求和，区间最大最小值

不可解决：区间的众数，最长连续问题

#### 建树



#### lazy标记

将此区间标记，表示这个区间的值已经更新

但它的子区间却没有更新，更新的信息就是标记里存的值

#### 区间修改

如果向下递归遍历所有节点一一修改，时间复杂度和暴力处理相差无几

用`lazy`标记

* 如果要修改的区间完全覆盖当前区间，直接更新这个区间，打上`lazy`标记
* 如果没有完全覆盖，且当前区间有`lazy`标记，先下传`lazy`标记到子区间，再清除当前区间的`lazy`标记
* 如果修改区间和左儿子有交集：搜索左儿子
* 如果修改区间和右儿子有交集：搜索右儿子
* 最后将当前区间的值更新

#### 区间查询

仅有单点修改的区间查询，不需要`lazy`标记：

* 如果要查询的区间完全覆盖当前区间，直接返回当前区间的值
* 如果查询区间和左儿子有交集，搜索左儿子
* 如果查询区间和右儿子有交集，搜索右儿子
* 最后合并处理两边查询的数据

区间修改后的区间查询：

* 如果要查询的区间完全覆盖当前区间，直接返回当前区间的值
* 如果没有完全覆盖，下传`lazy`标记
* 如果查询区间和左儿子有交集，搜索左儿子
* 如果查询区间和右儿子有交集，搜索右儿子
* 最后合并处理两边查询的数据



****

#### 线段树模板

```c++
class Node{
	Node *left, *right;
	int val;
	int lazy;	//懒惰标记
}
void update(Node* node, int start, int end, int l, int r, int val){
    //[l, r]为要更新的区间
    //[start, end]为当前搜索区间
    if(l <= start && end <= r){	// 完全覆盖当前区间
        node->val += (end - start +1)*val;	//注意：需要✖️该子树所有叶子节点
        node->lazy += val;
        return;
    }
    int mid = (start + end) >> 1;
    // 下推标记
    // mid - start + 1：表示左孩子区间叶子节点数量
    // end - mid：表示右孩子区间叶子节点数量
    pushDown(node, mid-start+1, end-mid);	//下传lazy标记到子区间
    // [start, mid] 和 [l, r] 可能有交集，遍历左孩子区间
    if(l<=mid) update(node->left, start, mid, l, r, val);
    // [mid + 1, end] 和 [l, r] 可能有交集，遍历右孩子区间
    if(r > mid) update(node->right, mid+1, end, l, r, val);
    //向上更新
    pushUp(node);
}
int query(Node* node, int start, int end, int l, int r){
    //查询区间[l,r]的值
    // 区间 [l ,r] 完全包含区间 [start, end]
    if(l<=start && end <= r)
        	return node->val;
    int mid = (start + end) >> 1;
    int ans = 0;
    pushDown(node, mid-start+1, end-mid);
    if(l<=mid) ans += query(node->left, start, mid, l, r);
    if(r > mid) ans += query(node->right, mid+1, end, l, r);
    // ans 把左右子树的结果都累加起来了，与树的后续遍历同理
    return ans;
}
void pushUp(Node* node){
    node->val = node->left->val + node->right->val;
}

//下推懒惰标记
//leftNum 和 rightNum 表示左右孩子区间的叶子节点数量
//因为如果是「加减」更新操作的话，需要用懒惰标记的值✖️叶子节点的数量
void pushDown(Node* node, int leftNum, int rightNum){
    //基于[动态开点]的前提，下推懒惰标记的时候，如果节点不存在左右孩子，那么就创建左右孩子节点
    if(node->left == nullptr)
        node->left = new Node();
    if(node->right == nullptr)
        node->right = new Node();
    //如果lazy==0，表示没有标记
    if(node->lazy == 0)
        return;
    node->left->val += node->lazy * leftNum;
    node->right->val += node->lazy * rightNum;
    //把标记下推给孩子
    //下推懒惰标记需要累加，不能直接覆盖
    node->left->lazy += node->lazy;
    node->right->lazy += node->lazy;
    //取消当前节点的标记
    node->lazy = 0;
}
```









