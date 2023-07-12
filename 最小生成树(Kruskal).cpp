#include<stdio.h>
#include<stdlib.h>
/*Kruskal算法
* 本质：贪心算法+并查集
* 输入：边序号 起点 终点 权值
* 输出：最小权值+按照序号升序输出 
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

    qsort(edges, N, sizeof(edges[0]), cmp);    //根据权值，对所有边进行升序排序
    //遍历所有的边
    for (int i = 0; i < N; i++) {
        //找到当前边的两个顶点在 assists 数组中的位置下标
        start = get_Father(edges[i].start, Father);
        end = get_Father(edges[i].end, Father);
        //如果顶点位置存在且顶点的标记不同，说明不在一个集合中，不会产生回路
        if (start != end) //不会成环
        {
            Father[start] = end;
            //记录该边，作为最小生成树的组成部分
            minTree[num++] = edges[i];
            //将新加入生成树的顶点标记全部改为一样的
            //如果选择的边的数量和顶点数相差1，证明最小生成树已经形成，退出循环  
        }
        if (num == P - 1)
        {
            break;
        }
    }
}
int cmp2(const void* a, const void* b)//按照顶点顺序输出
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
    scanf("%d%d", &P, &N);//顶点，边 
    init_Father(P, Father);
    for (int i = 0;i < N;i++)
    {
        scanf("%d%d%d%d", &edges[i].id, &edges[i].start, &edges[i].end, &edges[i].weigh);
    }
    kruskal(edges, min_Tree);
    display_min_Tree(min_Tree);
    return 0;
}