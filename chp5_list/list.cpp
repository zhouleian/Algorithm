#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

//复杂链表
struct RandomListNode{
	int label;
	struct RandomListNode* next,*random;
	RandomListNode(int x):
		label(x),next(NULL),random(NULL){
		}
};

struct ListNode{
	int key;
	ListNode* next;
	ListNode(int x):key(x),next(NULL){
	}
};
//创建链表
ListNode* create_node(int key){
	ListNode *node = new ListNode(key);
	node->key = key;
	node->next = NULL;
	return node;
}
//vector
void print_vector(vector<int> vec){
	for(auto it = vec.begin();it != vec.end();it++)
		cout << *it << " ";
	cout << endl;
}
//遍历链表
void print_from_head_to_tail(ListNode *head){
	cout << "遍历链表" << endl;
	vector<int> vec;
	ListNode* node = head;
	while(node){
		vec.push_back(node->key);
		node = node->next;
	}
	print_vector(vec);
}
//在表头插入节点
ListNode *insert_head(ListNode *head,ListNode *new_node){
	new_node->next = head;
	head = new_node;
	return head;
}
//表头删除节点
ListNode *del_head(ListNode* head){
	if(head->next!=NULL){
		ListNode *node = head;
		head = node->next;
		node->next = NULL;
	}else
		head = NULL;
	return head;
}
//表尾插入节点
ListNode *insert_tail(ListNode *head,ListNode *new_node){
	ListNode *node = head;
	while(node->next != NULL){
		node = node->next;
	}
	node->next = new_node;
	return head;
}
//表尾删除节点
ListNode *del_tail(ListNode *head){
	if(head->next == NULL){
		head = NULL;
		return head;
	}
	ListNode *node = head;
	ListNode *node2 = head->next;
	while(node2->next !=NULL){
		node=node->next;
		node2=node2->next;
	}
	node->next = NULL;
	return head;

}
//从尾到头打印
void print_from_tail_to_head(ListNode *head){
	cout << "从尾到头打印"<<endl;
	stack<ListNode*> ps;
	ListNode *node = head;
	while(node->next !=NULL){
		ps.push(node);
		node = node->next;
	}
	ps.push(node);
	int val;
	while(!ps.empty()){
		ListNode *p = ps.top();
		cout << p->key <<" ";
		ps.pop();
	}
	cout <<endl;
	return ;
}

//遍历循环单链表
void print_loop_list(ListNode *head,int size){
	vector<int> vec;
	for(int i = 0;i < size;i++){
		vec.push_back(head->key);
		head = head->next;
	}
	print_vector(vec);
	return ;
}
//有序环形链表插值
ListNode* insert(vector<int> A,vector<int> nxt,int val){
	auto it = A.begin(),iter = nxt.begin();
	ListNode *head =new ListNode(*it);
	ListNode *phead = head;
	it++;
	while((iter+1) !=nxt.end()){
		int tmp = *iter;
		//cout <<tmp <<": " << A[tmp]<< endl;
		ListNode *node =new ListNode(A[tmp]);
		phead->next = node;
		phead = phead->next;
		//cout << phead->key << endl;
		iter++;
	}
	phead->next = head;
	//print_loop_list(head,A.size());
	//插值
	ListNode *q = head;
	ListNode *valnode = new ListNode(val);
	ListNode *node = head->next;
	if(val < q->key || val > phead->key){
		cout << "------"<< endl;
		phead->next = valnode;
		valnode->next = head;
		head = valnode;
		return head;
	}
	while(node->key != phead->key){
		if((val <= node->key) && (val > q->key)){
			q->next = valnode;
			valnode->next = node;
			break;
		}else{
			node=node->next;
			q=q->next;
		}
	}
	return head; 
}
//单个节点的删除
ListNode *removeNode(ListNode *phead,int delval){
	//删除的是头节点
	if(phead ->key == delval){
		ListNode *node = phead->next;
		phead->next = NULL;
		phead = node;
		return phead;
	}
	ListNode *pnode = phead;
	ListNode *qnode = phead->next;
	while(qnode != NULL){
		if(qnode->key == delval){
			pnode->next = qnode->next;
			qnode->next = NULL;
		}else{
			pnode = pnode->next;
			qnode = qnode->next;
		}
	}
	/*
	while(pnode->key != delval){
		pnode = pnode->next;
		qnode = qnode->next;
	}//pnode就是要删除的节点
	while(qnode->next != NULL){
		pnode->key = qnode->key;
		pnode = pnode->next;
		qnode = qnode->next;
	}
	pnode->key = qnode->key;
	pnode->next = NULL;
	*/
	return phead;
}

//链表的分化练习
ListNode *listDivide(ListNode* head,int val){
	ListNode* smaller = NULL;
	ListNode* larger = NULL;
	ListNode* equal = NULL;
	ListNode* node = head;
	ListNode* pre = NULL;
	//处理larger
	node = head->next;
	pre = head;
	while(node !=NULL){
		if(node->key > val){
			larger = node;
			break;
		}else{
			pre = pre->next;
			node = node->next;
		}
	}
	ListNode *pnode,*qnode;
	//找大于val的链表
	if(larger !=NULL){
		pnode = larger->next;
		while(pnode->key <= val && pnode!=NULL){
			pre->next = pnode;
			pre = pre->next;
			pnode=pnode->next;
		}
		if(pnode!=NULL){//找到比val大的第二个数
			larger->next = pnode;
			qnode = pnode;
			pnode = pnode->next;
			while(pnode!=NULL){
				if(pnode->key > val){
					qnode->next = pnode;
					qnode = pnode;
				}else{
					pre->next = pnode;
					pre = pre->next;
				}
				pnode=pnode->next;
			}
			qnode->next = NULL;
			//	cout << "larger"<<endl;
			//	print_from_head_to_tail(larger);
		}
	}
	pre->next = NULL;
	//cout << "head"<<endl;
	//print_from_head_to_tail(head);
	//处理equal
	ListNode *pre_equal;
	node = head->next;
	pre_equal = head;
	while(node !=NULL){
		if(node->key == val){
			equal = node;
			break;
		}else{
			pre_equal = pre_equal->next;
			node = node->next;
		}
	}
	if(equal->next !=NULL){
		pnode = equal->next;
		while(pnode->key != val && pnode!=NULL){
			pre_equal->next = pnode;
			pre_equal = pre_equal->next;
			pnode=pnode->next;
		}

		if(pnode!=NULL){//找到比val大的第二个数
			equal->next = pnode;
			qnode = pnode;
			pnode = pnode->next;
			while(pnode!=NULL){
				if(pnode->key > val){
					qnode->next = pnode;
					qnode = pnode;
				}else{
					pre_equal->next = pnode;
					pre_equal = pre_equal->next;
				}
				pnode=pnode->next;
			}
			qnode->next = NULL;
			print_from_head_to_tail(equal);
		}
	}
	pre_equal->next = NULL;
	/*
	   cout << "equal"<<endl;
	   print_from_head_to_tail(equal);
	   cout << "head"<<endl;
	   print_from_head_to_tail(head);
	   */
	pre_equal->next = equal;
	pre->next = larger;

	return head;
}
//顺序数组转换为链表
ListNode* vector_to_list(vector<int> vec){
	auto it = vec.begin();
	ListNode* head = new ListNode(*it);
	ListNode* p = head;
	it++;
	while(it != vec.end()){
		ListNode* node = new ListNode(*it);
		p->next = node;
		p = p->next;
		it++;
	}
	return head;
}
//找两个链表公共节点
vector<int> findCommonParts(ListNode* headA,ListNode* headB){
	vector<int> vec;
	if(headA == NULL || headB == NULL)
		return vec;
	while(headA !=NULL && headB != NULL){
		if(headA->key == headB->key){
			vec.push_back(headA->key);
			headA = headA->next;
			headB = headB->next;
		}else if(headA->key < headB->key){
			headA = headA->next;
		}else
			headB = headB->next;
	}
	return vec;

}
//链表的K逆序
ListNode* inverse(ListNode* head,int k){
	cout << "链表k逆序" << endl;
	if(head == NULL)
		return head;
	stack<int> ps;
	ListNode* pnode = head;
	ListNode* qnode = pnode;
	int tmp = 0;
	while(qnode!=NULL){
		ps.push(qnode->key);
		qnode = qnode->next;
		tmp++;
		if(tmp%k==0){
			while(!ps.empty()){
				pnode->key = ps.top();
				ps.pop();
				pnode = pnode->next;
			}
		}
	}
	//print_from_head_to_tail(head);
	return head;
}
//链表指定值清除
ListNode* clear(ListNode * head,int val){
	ListNode* node = head;
	while(node!=NULL){
		if(node->key ==val){
			node = node->next;
		}else
			break;
	}
	head = node;
	node = node->next;
	ListNode* now = head;
	while(node!=NULL){
		if(node->key !=val){
			now->next = node;
			now = node;
			node = node->next;
		}else{
			node = node->next;
		}
	}
	return head;
}
//反转链表
ListNode* reverse(ListNode* head){
	ListNode* reverse_head = NULL;
	if(head == NULL)
		return reverse_head;
	ListNode* pre = NULL;
	ListNode* pnode = head;
	ListNode* next_node = NULL;
	while(pnode!=NULL){
		next_node = pnode->next;
		if(next_node == NULL)
			reverse_head = pnode;
		pnode->next = pre;
		pre = pnode;
		pnode = next_node;
	}
	return reverse_head;
}
//链表回文结构
bool isPalindrome(ListNode* pHead){
	ListNode* node = pHead;
	int length = 0;
	while(node!=NULL){
		node=node->next;
		length++;
	}
	if(length == 1)
		return false;
	int k;
	if(length%2 ==0)
		k = length/2;
	else
		k = length/2+1;
	ListNode* head2 = NULL;
	while(k){
		head2 = pHead->next;
		head2 = head2->next;
		k--;
	}
	head2 = reverse(head2);
	while(pHead !=NULL && head2!=NULL){
		if(pHead->key != head2->key)
			return false;
		pHead = pHead->next;
		head2 = head2->next;
	}
	return true;
}
//复杂链表复制
RandomListNode* clone(RandomListNode* pHead){
	RandomListNode* node = pHead;
	//复制next
	while(node !=NULL){
		RandomListNode* pnode = new RandomListNode(node->label);
		pnode->next = node->next;
		node->next = pnode;
		node = pnode->next;
	}
	//random指针复制
	node = pHead;
	while(node != NULL){
		RandomListNode* pnode = node->next;
		pnode->random = node->random->next;
		node = pnode->next;
	}
	//拆分
	node = pHead;
	RandomListNode* ret_head = pHead->next;
	RandomListNode* qnode = ret_head;
	while(node!=NULL){
		node->next = qnode->next;
		qnode->next = qnode->next->next;
		node = node->next;
		qnode = qnode->next;
	}
	return ret_head;
}
//链表判断环,返回入口节点值,无环返回-1
int chkLoopi(ListNode* head){
	cout << "链表判断环，返回入口" <<endl;
	//环长度
	int ret = -1;
	if(head == NULL || head->next == NULL)
		return ret;
	ListNode* fast = head;
	ListNode* slow = head;
	int flag = 1;
	while(fast !=NULL && slow!= NULL){
		if(fast == slow && flag != 1)
			break;
		flag  = 0;
		fast = fast->next->next;
		slow = slow->next;
	//	cout << "fast:" << fast->key << " " << slow->key << endl;
	}
	if(fast == NULL || slow == NULL)
		return -1;
	//else 相遇
	slow = slow->next;
	int len = 0;
	while(fast !=slow){
		len++;
		slow =slow->next;
	}
	len++;
	//cout << len << endl;
	//快指针先走len步
	fast = head;
	slow = head;
	while(len){
		fast = fast->next;
		len--;
	}
	while(fast !=slow){
		slow = slow->next;
		fast = fast->next;
	}
	ret = fast->key;
	return ret;
}
//链表判断环,返回入口节点
ListNode* chkLoop(ListNode* head){
	cout << "链表判断环，返回入口" <<endl;
	//环长度
	if(head == NULL || head->next == NULL)
		return NULL;
	ListNode* fast = head;
	ListNode* slow = head;
	int flag = 1;
	while(fast !=NULL && slow!= NULL){
		if(fast == slow && flag != 1)
			break;
		flag  = 0;
		fast = fast->next->next;
		slow = slow->next;
	//	cout << "fast:" << fast->key << " " << slow->key << endl;
	}
	if(fast == NULL || slow == NULL)
		return NULL;//无环
	//else 相遇
	slow = slow->next;
	int len = 0;
	while(fast !=slow){
		len++;
		slow =slow->next;
	}
	len++;
	//cout << len << endl;
	//快指针先走len步
	fast = head;
	slow = head;
	while(len){
		fast = fast->next;
		len--;
	}
	while(fast !=slow){
		slow = slow->next;
		fast = fast->next;
	}
	return fast;
}
//无环链表判相交
bool chkIntersect(ListNode* headA,ListNode* headB){
	int lena = 0;
	int lenb = 0;
	ListNode *anode = headA;
	ListNode *bnode = headB;
	while(anode != NULL){
		lena++;
		anode = anode->next;
	}
	while(bnode != NULL){
		lenb++;
		bnode = bnode->next;
	}
	anode = headA;
	bnode = headB;
	int diff=0;
	//先走diff步
	if(lena > lenb){
		diff = lena-lenb;
		while(diff){
			anode = anode->next;
			diff--;
		}
	}else{
		diff = lenb-lena;
		while(diff){
			bnode = bnode->next;
			diff--;
		}
	}
	while(anode != NULL && bnode != NULL){
		if(anode != bnode){
			anode = anode->next;
			bnode = bnode->next;
		}else
			break;
	}
	if(anode == NULL || bnode == NULL)
		return false;
	return true;
}
//两个有环单链表判断相交
bool chkInter(ListNode* head1,ListNode* head2){
	ListNode* in1 = chkLoop(head1);
	ListNode* in2 = chkLoop(head2);
	if(in1 == in2)
		return true;
	//环中相遇
	ListNode* node = in1;
	while(node != in1){
		if(node == in2)
			return true;
		else
			node = node->next;
	}
	return false;
}
//单链表相交判断
bool inter(ListNode* head1,ListNode* head2){
	//有环？
	ListNode* in1 = chkLoop(head1);
	ListNode* in2 = chkLoop(head2);
	//都有环
	if(in1 !=NULL && in2!= NULL)
		return chkInter(head1,head2);
	if(in1 == NULL && in2==NULL){
		return chkInter(head1,head2); 
		//都无环
	}
	//一个有一个无
	if(in1 == NULL || in2==NULL){
		return false;
	}
}
int main(){
	vector<int> vec = {1,2,3,4,5,6,7,8};
	ListNode* head = vector_to_list(vec);


	//有环链表构建
	/*
	ListNode* node = head->next->next->next->next;
	cout << node->key << endl;
	ListNode* p = head;
	while(p->next!=NULL){
		p = p->next;
	}
	p->next = node;
	//构建完毕
	*/
	/*
	//链表判断环,返回入口节点值,无环返回-1
	int ret = chkLoop(head);
	cout << ret << endl;
	*/
	/*
	//链表回文结构
	vector<int> vec2 = {1,2,3,3,2,1};
	ListNode* pHead = vector_to_list(vec2);
	print_from_head_to_tail(pHead);
	bool ret = isPalindrome(pHead);
	cout << ret << endl;
	*/
	/*
	//反转链表
	ListNode* re = reverse(head);
	print_from_head_to_tail(re);
	*/
	/*
	//链表指定值清除
	int val = 4;
	head = clear(head,val);
	print_from_head_to_tail(head);
	*/
	
	//链表的K逆序
	int k = 3;
	head = inverse(head,k);
	print_from_head_to_tail(head);

	/*
	 * //找两个链表公共节点
	 vector<int> vec = {1,2,3,4,5,6,7,8};
	 ListNode* headA = vector_to_list(vec);
	 vector<int> vec2 = {2,4,6,8,10};
	 ListNode* headB = vector_to_list(vec2);
	 vector<int> ret = findCommonParts(headA,headB);
	 if(ret.size() > 0)
	 print_vector(ret);
	//print_from_head_to_tail(head);
	*/
	   /*
	   ListNode *head = new ListNode(0);
	   ListNode *p = new ListNode(1);
	   head->next = p;
	   for(int i = 2;i < 10;i++){
	   ListNode *q;
	   if(i%2==0)
	   q =new  ListNode(i*2);
	   else
	   q = new ListNode(i);
	   p->next = q;
	   p = p->next;
	   }
	   print_from_head_to_tail(head);
	   print_from_tail_to_head(head);
	   cout << "----"<<endl;
	   ListNode *ret = listDivide(head,5);
	   print_from_head_to_tail(ret);

	   ListNode *node = new ListNode(100);
	   head = insert_head(head,node);
	   print_from_head_to_tail(head);

	   head = del_head(head);
	   print_from_head_to_tail(head);
	//有序环形链表插值
	cout << "有序环形链表插值" << endl;
	vector<int> A = {1,3,4,5,7};
	vector<int> nxt = {1,2,3,4,0};
	int val = 2;
	ListNode* ret_head = insert(A,nxt,val);
	print_loop_list(ret_head,A.size());
	//单个节点的删除
	removeNode(head,5);
	print_from_head_to_tail(head);
	*/




	return 0;

}
