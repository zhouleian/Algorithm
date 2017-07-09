#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
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
bool judge_tree(TreeNode* A,TreeNode* B){
	bool ret = false;
	if(B == NULL)
		return true;
	if(A == NULL)
		return false;//A到了叶节点，B没到
	if(A->val != B->val)
		return false;
	return judge_tree(A->left,B->left) && judge_tree(A->right,B->right);
}
bool kmp(string A,string B){
	int lena = strlen(A.c_str());
	int lenb = strlen(B.c_str());
	for(int i = 0;i < lena;i++){
		int j = 0;
		for(;j < lenb;j++){
			if(A[i+j] != B[j])
				break;
		}
		if(j == lenb)
			return true;
	}
	return false;
}
//序列化
void serialize(TreeNode* A,string &str){
	if(A == NULL){
		str.push_back('*');
		return;
	}
	str.push_back((A->val));
	serialize(A->left,str);
	serialize(A->right,str);
}
//A中是否存在一棵同构于B的子树
bool chkIdentical(TreeNode* A, TreeNode* B) {
	bool ret = false;
	string stra,strb;
	serialize(A,stra);
	serialize(B,strb);
	ret = kmp(stra,strb);
/*递归
	if(B->left == NULL && B->right == NULL && A->val == B->val)
		return false;
	if(A!=NULL && B!=NULL){

		if(A->val == B->val)
			ret = judge_tree(A,B);
		if(!ret)
			ret = chkIdentival(A->left,B);
		if(!ret)
			ret = chkIdentival(A->right,B);
	}
	*/
	return ret;
}


int main(){
	vector<int> pre = {1,2,4,5,3,6,7};
	vector<int> in = {4,2,5,1,6,3,7};
	//cout << "construct : " << endl;
	TreeNode* A = construct(pre,in);
	//vector<int> vec = print_layer(root);
	//print_vec(vec);
	vector<int> preb = {3,6,7};
	vector<int> inb = {6,3,7};
	//cout << "construct : " << endl;
	TreeNode* B = construct(preb,inb);
	cout << chkIdentical(A,B);
	
	return 0;


}
