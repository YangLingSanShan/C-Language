#include <stdio.h>
#define MAX 100 //定义最大顶点数
#define inf 9999999
int graph[MAX][MAX]; //邻接矩阵表示图
int dist[MAX]; //存储当前生成树到各点的最短距离
int visited[MAX]; //标记顶点是否已访问
int n; //顶点数
/*
* 依次在G中选择一条一个顶点仅在V中,另一个顶点在U中,并且权值最小的边加入集合TE,同时将该边仅在V 中的那个顶点加入集合U。
  重复上述过程n–1次,使得U=V,此时T为G的最小生成树
*/
void prim(int start) {
    //初始化
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        visited[i] = 0;
    }
    dist[start] = 0;
    visited[start] = 1;

    //生成n-1条边
    for (int i = 1; i < n; i++) 
    {
        int minDist = inf, index = -1;
        //找到当前生成树外距离最短的顶点
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        visited[index] = 1;

        //更新距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && graph[index][j] < dist[j]) 
            {
                dist[j] = graph[index][j];
            }
        }
    }
}

int main() {
    //输入顶点数和边数
    scanf("%d", &n);
    int m;
    scanf("%d", &m);

    //输入每条边的信息
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        graph[a][b] = w;
        graph[b][a] = w; //无向图
    }

    //求最小生成树
    prim(0);

    //输出结果
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dist[i];
    }
    printf("Weight of minimum spanning tree: %d", sum);
    return 0;
}