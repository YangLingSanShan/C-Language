#include<stdio.h>
#include<stdlib.h>
/*Kruskal�㷨
* ���ʣ�̰���㷨+���鼯
* ���룺����� ��� �յ� Ȩֵ
* �������СȨֵ+�������������� 
*/
#define MaxV 1001
int P, N;
struct Edge
{
    int id;
    int start;
    int end;
    int weigh;
}edges[MaxV], min_Tree[MaxV];
int Father[MaxV];
int cmp(const void* a, const void* b)
{
    return ((struct Edge*)a)->weigh - ((struct Edge*)b)->weigh;
}
void init_Father(int P, int Father[])
{
    for (int i = 0;i < P;i++)
    {
        Father[i] = i;
    }
}
int get_Father(int target, int Father[])
{
    return Father[target] == target ? target : (Father[target] = get_Father(Father[target], Father));
}
void kruskal(struct Edge edges[], struct Edge minTree[])
{
    int end, start, num = 0;

    qsort(edges, N, sizeof(edges[0]), cmp);    //����Ȩֵ�������б߽�����������
    //�������еı�
    for (int i = 0; i < N; i++) {
        //�ҵ���ǰ�ߵ����������� assists �����е�λ���±�
        start = get_Father(edges[i].start, Father);
        end = get_Father(edges[i].end, Father);
        //�������λ�ô����Ҷ���ı�ǲ�ͬ��˵������һ�������У����������·
        if (start != end) //����ɻ�
        {
            Father[start] = end;
            //��¼�ñߣ���Ϊ��С����������ɲ���
            minTree[num++] = edges[i];
            //���¼����������Ķ�����ȫ����Ϊһ����
            //���ѡ��ıߵ������Ͷ��������1��֤����С�������Ѿ��γɣ��˳�ѭ��  
        }
        if (num == P - 1)
        {
            break;
        }
    }
}
int cmp2(const void* a, const void* b)//���ն���˳�����
{
    return ((struct Edge*)a)->id - ((struct Edge*)b)->id;
}
void display_min_Tree(struct Edge min_Tree[])
{
    int cost = 0, i;
    for (i = 0; i < P - 1; i++)
    {
        cost += min_Tree[i].weigh;
    }
    qsort(min_Tree, P - 1, sizeof(min_Tree[0]), cmp2);
    printf("%d\n", cost);
    for (i = 0; i < P - 1; i++)
    {
        printf("%d ", min_Tree[i].id);
    }
}
int main()
{
    scanf("%d%d", &P, &N);//���㣬�� 
    init_Father(P, Father);
    for (int i = 0;i < N;i++)
    {
        scanf("%d%d%d%d", &edges[i].id, &edges[i].start, &edges[i].end, &edges[i].weigh);
    }
    kruskal(edges, min_Tree);
    display_min_Tree(min_Tree);
    return 0;
}