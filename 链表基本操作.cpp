#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
typedef struct ListNode
{
    int x;//x可以根据需求修改 
    struct ListNode* next;
}node;
void creatfromtail(node* l, int N)//尾插法，N为节点个数，可根据实际要求进行调整
{
    node* p, * r = l;
    for (int i = 2;i <= N;i++)//已经有了一个头节点，所以从2开始
    {
        p = (node*)malloc(sizeof(node));//建立一个新结点
        scanf("%d", &p->x);
        r->next = p;//尾指针的指针域指向新结点p
        r = p;//再让尾指针放在p后面，尾指针永远在最后 
    }
    //成环
    // r->next = l;
    //线性
    r->next = NULL;
}
struct ListNode* removeElements(struct ListNode* head, int val)//移除链表中x==val的节点 
{
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->next = head;//dummy的用途：指向head节点
    struct ListNode* temp = dummyHead;
    while (temp->next != NULL)
        if (temp->next->x == val) 
            temp->next = temp->next->next;
        else 
            temp = temp->next;
    return dummyHead->next;
}
void deleteNode(struct ListNode* node)//删除指定节点时调用 
{
    node->x = node->next->x;
    node->next = node->next->next;
}
struct ListNode* deleteDuplicates(struct ListNode* head)//删除有序链表中重复元素
{
    if (!head) {
        return head;
    }
    struct ListNode* cur = head;
    while (cur->next) {
        if (cur->x == cur->next->x) //此处判断条件可以修改 
        {
            cur->next = cur->next->next;
        }
        else {
            cur = cur->next;
        }
    }
    return head;
}
struct ListNode* rotateRight(struct ListNode* head, int k) //将链表旋转k次(每个节点向右移动一次叫做旋转1次)
{
    if (k == 0 || head == NULL || head->next == NULL)
    {
        return head;
    }
    int n = 1;
    struct ListNode* iter = head;
    while (iter->next != NULL)
    {
        iter = iter->next;
        n++;
    }
    int add = n - k % n;
    if (add == n)
    {
        return head;
    }
    iter->next = head;
    while (add--)
    {
        iter = iter->next;
    }
    struct ListNode* ret = iter->next;
    iter->next = NULL;
    return ret;
}
struct ListNode* reverseList(struct ListNode* head)//翻转链表 
{
    struct ListNode* cur = NULL, * pre = head;
    while (pre != NULL)
    {
        struct ListNode* t = pre->next;
        pre->next = cur;
        cur = pre;
        pre = t;
    }
    return cur;
}
//删除倒数第N个节点 
int getLength(struct ListNode* head)
{
    int length = 0;
    while (head) {
        ++length;
        head = head->next;
    }
    return length;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->x = 0, dummy->next = head;
    int length = getLength(head);
    struct ListNode* cur = dummy;
    for (int i = 1; i < length - n + 1; ++i)
        cur = cur->next;
    cur->next = cur->next->next;
    struct ListNode* ans = dummy->next;
    free(dummy);
    return ans;
}
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)//合并两个有序链表,递归
{
    if (list1 == NULL)
        return list2;
    else if (list2 == NULL)
        return list1;
    if (list1->x <= list2->x)
    {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    else
    {
        list2->next = mergeTwoLists(list2->next, list1);
        return list2;
    }
}
int main()
{
    int N;
    node* head = (node*)malloc(sizeof(node));
    scanf("%d%d", &N, &head->x);
    head->next = NULL;
    creatfromtail(head, N);
    return 0;
}