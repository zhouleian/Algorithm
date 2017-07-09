#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <math.h>
using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	//TreeNode(int x) :
	//	val(x), left(NULL), right(NULL) {
	//	}
};
//层次打印二叉树
vector<int> print_layer(TreeNode* root){
	cout << "print_layer : " << endl;
	vector<int> vec;
	if(root == NULL)
		return vec;
	queue<TreeNode*> que;
	que.push(root);
	while(que.size()){
		TreeNode* p = que.front();
		vec.push_back(p->val);
		if(p->left)
			que.push(p->left);
		if(p->right)
			que.push(p->right);
		que.pop();
	}
	return vec;
}
void print_vec(vector<int> vec){
	int i = 0;
	for(;i < vec.size();i++){
		cout << vec[i] << "  ";
	}
	cout << endl;
}

//前序遍历，中序遍历，重建树
TreeNode* construct(vector<int> pre,vector<int>in){
	int pre_index = 0;
	int in_index = 0;
	TreeNode* root = new TreeNode;
	int len = pre.size();
	int in_len = in.size();
	if(len != in_len)
		return root;
	if(pre.size() == 0 || (in.size()==0))
		return root;
	root->val = pre[0];
	root->left = NULL;
	root->right = NULL;
	//判断是不是只有一个节点
	if(pre[0] == pre[len-1]){
		if(in[0] == pre[0] || in[0] == in[len-1])
			return root;
		else
			throw new exception();
	}
	while(in[in_index]!=root->val && in_index < len){
		in_index++;
	}
	if(in_index >= len)
		throw new exception();
	int i;
	int left_len = in_index;
	int right_len = len-in_index-1;
	if(left_len >0){
		vector<int> in_left,pre_left;
		for(i = 0;i < in_index;i++)
			in_left.push_back(in[i]);
		for(i = 1;i <= left_len;i++)
			pre_left.push_back(pre[i]);
		root->left = construct(pre_left,in_left);
	}
	if(right_len > 0){
		vector<int> in_right,pre_right;
		for(i = left_len+1;i < len;i++)
			pre_right.push_back(pre[i]);
		for(i = in_index+1;i < len;i++)
			in_right.push_back(in[i]);
		root->right = construct(pre_right,in_right);
	}
	return root;
}

int most_left_deep(TreeNode* root){
	if(root == NULL)
		return 0;
	int deep = 0;
	while(root){
		deep++;
		root = root->left;
	}
	return deep;
}

//计算完全二叉树节点数logN^2
int count(TreeNode* root){
	if(root == NULL)
		return 0;
	int nums = 0;
	int left_deep = most_left_deep(root->left);
	int right_deep = most_left_deep(root->right);
	if(left_deep > right_deep){
		//右子树完全二叉树
		nums = pow(2,right_deep) - 1 + count(root->left) + 1;
	}else{//左子树完全二叉树
		nums = pow(2,left_deep) - 1 + count(root->right) +1;
	}

	return nums;
}

int main(){
	vector<int> p = {1,2,4,8,5,3,6,7};
	vector<int> i = {8,4,2,5,1,6,3,7};
	//cout << "construct : " << endl;
	TreeNode* r = construct(p,i);
	vector<int> vec = print_layer(r);
	print_vec(vec);
	int nums = count(r);
	cout << nums << endl;

	
	return 0;


}
