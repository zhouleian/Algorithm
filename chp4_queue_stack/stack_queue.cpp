#include <iostream>
#include <deque>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
//可查询最值的栈
stack<int> s_data,s_min;
void push(int value){
	if(s_min.empty() || value <= s_min.top())
		s_min.push(value);
	else if(!s_min.empty() && value > s_min.top())
		s_min.push(s_min.top());
	s_data.push(value);
}
void pop(){
	if(!s_min.empty())
		s_min.pop();
	if(!s_data.empty())
		s_data.pop();
}
int top(){
	int val = s_data.top();
	return val;
}
int min(){
	return s_min.top();
}
void print_vector(vector<int> vec){
	for(auto it = vec.begin();it != vec.end();it++)
		cout << *it << " ";
	cout << endl;
}

//双栈队列,支持push,pop，正数为push，0为pop
vector<int> twoStack(vector<int> ope,int n){
	cout << "双栈队列" << endl;
	vector<int> vec;
	stack<int> s_push,s_pop;
	for(auto it = ope.begin();it != ope.end();it++){
		if(*it > 0){//push
			s_push.push(*it);
		}else{//pop
			if(s_pop.empty()){
				while(!s_push.empty()){
					int val = s_push.top();
					s_push.pop();
					s_pop.push(val);
				}
			}
			vec.push_back(s_pop.top());
			s_pop.pop();
		}
	}

	return vec;

}
//get方法，得到栈底元素
int get(stack<int>& s){
	int res = s.top();
	s.pop();
	if(s.empty())
		return res;
	int last = get(s);
	s.push(res);
	return last;
}
void reverse(stack<int>& s){
	if(s.empty())
		return;
	int i = get(s);
	reverse(s);
	s.push(i);
}
//栈的反转,只能用递归，pop
vector<int> reverseStack(vector<int> A,int n){
	vector<int> vec;
	stack<int> s;
	for(int i = n-1;i >= 0;i--)
		s.push(A[i]);

	reverse(s);
	while(!s.empty()){
		int val = s.top();
		s.pop();
		vec.push_back(val);
	}
	return vec;
}

//栈的打印，从栈顶到栈尾
void print_stack(stack<int> s){
	while(!s.empty()){
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}
//双栈排序
vector<int> twoStacksSort(vector<int> numbers){
	vector<int> vec;
	stack<int> s,help;
	int n = numbers.size();
	for(int i = n-1;i >= 0;i--)
		s.push(numbers[i]);
	print_stack(s);
	for(int i = 0;i < n;i++){
		int val = s.top();
		if(help.empty()){
			help.push(val);
			s.pop();
		}else if(val >=help.top()){
			help.push(val);
			s.pop();
		}
		else{
			int count = 0;
			s.pop();
			while(!help.empty() && help.top()>val){
				int v = help.top();
				help.pop();
				s.push(v);
				count++;
			}
			help.push(val);
			for(int j = 0;j < count;j++){
				help.push(s.top());
				s.pop();
			}
		}
	}
	print_stack(help);
	while(!help.empty()){
		vec.push_back(help.top());
		help.pop();
	}
	/*
	while(!s.empty()){
		vec.push_back(s.top());
		s.pop();
	}
*/
	return vec;
}


//滑动窗口
vector<int> slide(vector<int> arr,int n,int w){
	vector<int> vec;
	if(n >= w && w >=1){
		deque<int> de;//下标
		for(int i = 0;i < w;i++){
			while(!de.empty() && arr[de.back()] <= arr[i])
				de.pop_back();
			de.push_back(i);
		}
		for(int i = w;i < n;i++){
			vec.push_back(arr[de.front()]);
			while(!de.empty() && arr[de.back()] <= arr[i])
				de.pop_back();
			if(!de.empty() && de.front() <= (i-w))
				de.pop_front();
			de.push_back(i);
		}
		vec.push_back(arr[de.front()]);
	}
	return vec;
}
//数组变树
//给定一个无重复元素的数组A和它的大小n，请返回一个数组，其中每个元素为原数组中对应位置元素在树中的父亲节点的编号，若为根则值为-1。
vector<int> buildMaxTree(vector<int> A,int n){
	vector<int> vec;
	stack<int> s;
	//左边第一个比A[i]大的
	for(int i = 0;i < n;i++){
		if(s.empty()){
			vec.push_back(-1);
		}else if(!s.empty() && A[s.top()] > A[i]){
			vec.push_back(s.top());
		}else{
			while(!s.empty() && A[s.top()] < A[i]){
				s.pop();
			}
			if(!s.empty())
				vec.push_back(s.top());
			else
				vec.push_back(-1);
		}
		s.push(i);
	}
	while(!s.empty())
		s.pop();
	print_vector(vec);
	//右边第一个比A[i]大的，两边都为空vec是-1,一边为空，vec取另一边，两边不空，取大的
	for(int i = n-1;i >=0;i--){
		//cout <<i <<" ";
		if(!s.empty() && A[s.top()] > A[i]){
			//cout << A[s.top()] << " "<< A[i] << " ";
			if(vec[i] ==-1)
				vec[i] = s.top();
			else if(A[s.top()] < A[vec[i]])
				vec[i] = s.top();
		}else{
			while(!s.empty() && A[s.top()] < A[i]){
			//	cout << A[s.top()] << " "<< A[i] << " ";
				s.pop();
			}
			if(!s.empty() && (vec[i] == -1 || A[s.top()] < A[vec[i]]))
				vec[i] = s.top();
		}
		s.push(i);
	}

	return vec;
}

int main(){
	//vector<int> A = {340,1387,2101,847,1660,733,36,528};
	vector<int> A = {1477,563,345,425,1905,991};
	int n = 6;
	vector<int> ret = buildMaxTree(A,n);
	print_vector(ret);
	/*
	//滑动窗口
	vector<int> arr = {4,3,5,4,3,3,6,7};
	int n = 8;
	int w = 3;
	vector<int> ret = slide(arr,n,w);
	print_vector(ret);
*/

	/*
	//栈的反转,只能用递归，pop
	vector<int> A = {4,3,2,1};
	int n= A.size();
	vector<int> ret = reverseStack(A,n);
	print_vector(ret);
	*/
	
	/*
	//双栈排序
	vector<int> numbers = {3,4,5,1,2};
	vector<int> ret2 = twoStacksSort(numbers);
	print_vector(ret2);
*/


	/*
	//双栈队列,支持push,pop，正数为push，0为pop
	vector<int> ope = {1,2,3,0,4,0};
	int n = ope.size();
	vector<int> ret = twoStack(ope,n);
	print_vector(ret);
*/
	/*
	   vector<int> vec = {1,3,5,2,4};
	   for(auto it = vec.begin();it!=vec.end();it++)
	   push(*it);
	   cout << min() << endl;
	   */
	return 0;
}
