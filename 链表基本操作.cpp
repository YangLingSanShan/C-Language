#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
typedef struct ListNode
{
    int x;//x���Ը��������޸� 
    struct ListNode* next;
}node;
void creatfromtail(node* l, int N)//β�巨��NΪ�ڵ�������ɸ���ʵ��Ҫ����е���
{
    node* p, * r = l;
    for (int i = 2;i <= N;i++)//�Ѿ�����һ��ͷ�ڵ㣬���Դ�2��ʼ
    {
        p = (node*)malloc(sizeof(node));//����һ���½��
        scanf("%d", &p->x);
        r->next = p;//βָ���ָ����ָ���½��p
        r = p;//����βָ�����p���棬βָ����Զ����� 
    }
    //�ɻ�
    // r->next = l;
    //����
    r->next = NULL;
}
struct ListNode* removeElements(struct ListNode* head, int val)//�Ƴ�������x==val�Ľڵ� 
{
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->next = head;//dummy����;��ָ��head�ڵ�
    struct ListNode* temp = dummyHead;
    while (temp->next != NULL)
        if (temp->next->x == val) 
            temp->next = temp->next->next;
        else 
            temp = temp->next;
    return dummyHead->next;
}
void deleteNode(struct ListNode* node)//ɾ��ָ���ڵ�ʱ���� 
{
    node->x = node->next->x;
    node->next = node->next->next;
}
struct ListNode* deleteDuplicates(struct ListNode* head)//ɾ�������������ظ�Ԫ��
{
    if (!head) {
        return head;
    }
    struct ListNode* cur = head;
    while (cur->next) {
        if (cur->x == cur->next->x) //�˴��ж����������޸� 
        {
            cur->next = cur->next->next;
        }
        else {
            cur = cur->next;
        }
    }
    return head;
}
struct ListNode* rotateRight(struct ListNode* head, int k) //��������תk��(ÿ���ڵ������ƶ�һ�ν�����ת1��)
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
struct ListNode* reverseList(struct ListNode* head)//��ת���� 
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
//ɾ��������N���ڵ� 
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
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)//�ϲ�������������,�ݹ�
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