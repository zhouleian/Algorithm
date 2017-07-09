#include<iostream>
#include<stack>
#include<vector>
using namespace std;
struct ListNode{
    int key;
    ListNode* next;
};
ListNode* create_node(){
    cout << "Enter node key: " << endl;
    int val;
    cin >> val;
    ListNode *node = new ListNode;
    node->key = val;
    node->next = NULL;
    return node;
}
//遍历链表
void print_from_head_to_tail(ListNode *head){
    ListNode *pnode = head;
    cout << "遍历链表" << endl;
    while(pnode != NULL){
        cout << pnode->key << endl;
        pnode = pnode->next;
    }
    cout << endl;
}
//在表头插入节点
ListNode* insert_head(ListNode *head){
    cout << "表头插入节点： " << endl;
    ListNode *phead = create_node();
    phead->next = head;
    return phead;
}
//在表头删除节点
ListNode* delete_head(ListNode* head){
    ListNode* phead = head;
    if(head->next != NULL){
        head = phead->next;
        phead->next = NULL;
    }
    else
        head = NULL;
    return head;
}
//在表尾部插入节点
ListNode* insert_tail(ListNode* head){
    ListNode* pnode = head;
    while(pnode->next != NULL){
        pnode = pnode->next;
    }
    ListNode* new_node = create_node();
    pnode->next = new_node;
    return head;
}
//在表尾删除节点
ListNode* delete_tail(ListNode* head){
    ListNode* pnode = head;
    ListNode* qnode = pnode;
    if(head->next != NULL){
        while(pnode->next != NULL){
            pnode = pnode->next;
            qnode->next = pnode;
        }
        qnode->next = NULL;
    }
    else
        head = NULL;
    return head;
}
vector<int> tail_to_head(ListNode* head){
    stack<ListNode*> ps;
    vector<int> ret;
    int val;
    ListNode* snode = head;
    while(snode->next != NULL){
        ps.push(snode);
        snode = snode->next;
    }
    while(!ps.empty()){
        val = ps.top()->key;
        ret.push_back(val);
        ps.pop();
    }
    return ret;
}
ListNode* find_kth_to_tail(ListNode* head,int k){
    if(head == NULL || k == 0)
        return NULL;
    ListNode* p = head;
    ListNode* q = head;
    int i;
    for(i = 0;i < k-1;i++){
        if(p->next != NULL)
            p = p->next;
        else
            return NULL;
    }
    while(p->next != NULL){
        p = p->next;
        q = q->next;
    }
    return q;
}
//链表中间节点
ListNode* get_midnode(ListNode* head){
    ListNode* p = head;
    ListNode* q = head;
    while(p != NULL){
        if(p!= NULL)
            p = p->next;
        else
            return q;
        if(p != NULL)
            p = p->next;
        else
            return q;
        if(q->next != NULL)
            q = q->next;
        else
            return q;
    }
    return head;
}
//判断是不是环形链表  
bool loop_or_not(ListNode* head){
    if(head == NULL)
        return false;
    ListNode* p = head;
    ListNode* q = head;
    while(p->next != NULL && q->next != NULL){
        p = p->next;
        if(p->next != NULL)
            p = p->next;
        else
            return false;
        q = q->next;
        if(p == q)
            return true;
    }
}
//反转链表
ListNode* reverse_list(ListNode* head){
    if(head == NULL){
        cout << "head is NULL " << endl;
        return NULL;
    }
    
    ListNode* pnode = head;
    ListNode* reverse_head = NULL;
    ListNode* qnode = NULL;
    ListNode* next_node = NULL;
    while(pnode != NULL){
        next_node = pnode->next;
        if(next_node == NULL)
            reverse_head = pnode;
        pnode->next = qnode;
        qnode = pnode;
        pnode = next_node;
    }
    return reverse_head;
}
// 合并两个有序链表
ListNode* merge(ListNode* phead,ListNode* qhead){
    ListNode* merge_head = NULL;
    if(phead == NULL)
        return qhead;
    else if(qhead == NULL)
        return phead;
    if(phead->key < qhead->key){
        merge_head = phead;
        merge_head->next = merge(phead->next,qhead);
    }
    else{
        merge_head = qhead;
        merge_head->next = merge(phead,qhead->next);
    }
    return merge_head;
}
//删除节点
ListNode* delete_node(ListNode* head,ListNode* del_node){
    ListNode* ret_head = head;
    if(head->next == NULL){
        cout << "head is NULL " << endl;
        ret_head = NULL;
        delete del_node;
        del_node = NULL;
    }
    else if(del_node->next == NULL){
        //删除的节点是尾节点
        cout << " 尾部节点" << endl;
        ListNode* pnode = head;
        while(pnode->next != del_node){
            pnode = pnode->next;
        }
        pnode->next = NULL;
        delete del_node;
        del_node= NULL;
    }
    else{
        // 删除的节点不是尾部节点
        ListNode* qnode = del_node->next;
        del_node->key = qnode->key;
        del_node->next = qnode->next;
        delete qnode;
        qnode=NULL;
    }
    return ret_head;
}
int main(){
    ListNode *p;
    ListNode *q;
    int times;
    int i;
    cout << "输入节点个数" << endl;
    cin >> times;
    if(times>0){
        for(i = 0;i <times;i++){
            if(i == 0){
                p = create_node();
                cout << "--------";
            }
            else
                p = insert_tail(p);
        }
    }
    else{
        p = NULL;
        if(p == NULL)
            cout << " p is NULL " << endl;
    }
    print_from_head_to_tail(p);
    //删除节点
    ListNode* del_node = NULL;
    ListNode* p_head = p;
    while(p_head->next != NULL){
        p_head = p_head->next;
        del_node = p_head;
    }
    ListNode* del_head = delete_node(p,del_node);
    cout << "del_head = " ;
    if(del_head == NULL)
        cout << " del_head is NULL" << endl;
    else
        print_from_head_to_tail(del_head);

    /*
    cout << "输入节点个数" << endl;
    cin >> times;
    if(times>0){
        for(i = 0;i <times;i++){
            if(i == 0){
                q = create_node();
                cout << "--------";
            }
            else
                q = insert_tail(q);
        }
    }
    else{
        q = NULL;
        if(q == NULL)
            cout << " q is NULL " << endl;
    }
    cout << endl;
    ListNode* merge_head = merge(p,q);
    cout << "merge_head ---------------" << endl;
    print_from_head_to_tail(merge_head);
    cout << endl;
    */
    /*
    //tail_to_head(p);
    int k;
    cout << " k  = " ;
    cin >> k;
    ListNode* kth_node = find_kth_to_tail(p,k);
    cout << "k th number is : " << kth_node->key << endl;
    */
    //求链表的中间节点
    /*
    cout << "mid_node : " << endl;
    ListNode* mid_node = get_midnode(p);
    if(mid_node == NULL)
        cout << "NULL " << endl;
    else
        cout << mid_node->key << endl;
    //判断是否是环形链表
    //mid_node->next = p;
    bool loop_not = loop_or_not(p);
    cout << " loop = " << loop_not << endl;
    //反转链表
    ListNode* reverse_head = reverse_list(p);
    while(reverse_head != NULL){
        cout << reverse_head->key << "  ";
        reverse_head = reverse_head->next;
    }
    cout << endl;
    */
    return 0;
}
