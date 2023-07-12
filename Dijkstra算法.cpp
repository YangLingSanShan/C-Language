#include <stdio.h>
#include <stdlib.h>
#define MAX 100 //定义最大顶点数
#define inf 9999999
int graph[MAX][MAX]; //邻接矩阵表示图
int dist[MAX]; //存储起点到各点的最短距离
int visited[MAX]; //标记顶点是否已访问
int pre[MAX]; //存储每个顶点的前驱节点
int n; //顶点数

void dijkstra(int start,int end) 
{
    //初始化
    for (int i = 0; i < n; i++) 
    {
        dist[i] = graph[start][i];
        visited[i] = 0;
        if (i != start && graph[start][i] < inf) 
        {
            pre[i] = start;
        }
        else 
        {
            pre[i] = -1;
        }
    }
    dist[start] = 0;
    visited[start] = 1;

    //对于除起点外的其它n-1个顶点，每次找到最小的dist[j]并标记visited[j]
    for (int i = 1; i < n; i++) 
    {
        int minDist = inf, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        //终止
        if (index==-1||index == end)	
            return;
        visited[index] = 1;
        //更新距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && dist[index] + graph[index][j] < dist[j]) 
            {
                dist[j] = dist[index] + graph[index][j];
            }
        }
    }
}
void printPath(int start, int end) 
{
    if (pre[end] == -1) {
        printf("No path from %d to %d", start, end);
        return;
    }
    if (start == end) {
        printf("%d", start);
        return;
    }
    int path[MAX], len = 0;
    path[len++] = end;
    while (pre[end] != start) {
        path[len++] = pre[end];
        end = pre[end];
    }
    path[len++] = start;
    for (int i = len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
}
void dijkstra(int start) //从start点到所有顶点的最短距离（不显示路径）,用for循环输出即可
{
    //初始化
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        visited[i] = 0;
    }
    dist[start] = 0;
    visited[start] = 1;

    //对于除起点外的其它n-1个顶点，每次找到最小的dist[j]并标记visited[j]
    for (int i = 1; i < n; i++) {
        int minDist = inf, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                index = j;
            }
        }
        visited[index] = 1;

        //更新距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[index][j] > 0 && dist[index] + graph[index][j] < dist[j]) 
            {
                dist[j] = dist[index] + graph[index][j];
            }
        }
    }
}
//以上代码即可实现Dijkstra算法
//优先队列进行优化O（VlogV）——使用最小堆

#define INF 0x7fffffff  // 定义一个极大值

// 定义邻接表的结构
typedef struct _edge {
    int v;       // 邻接的节点
    int w;       // 边的权重
    struct _edge* next;   // 指向下一条边的指针
} Edge;

typedef struct {
    int u;       // 起点
    int C;       // 路径长度
} Path;

// 定义堆的结构
typedef struct {
    int n;           // 堆的大小
    Path* data;      // 存储路径的数组
} Heap;

// 创建一个空的堆
Heap* createHeap(int size) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->n = 0;
    heap->data = (Path*)malloc((size + 1) * sizeof(Path));  // 注意数组下标从 1 开始
    return heap;
}

// 向堆中添加一个节点
void push(Heap* heap, Path path) {
    int i = ++heap->n;
    while (i > 1 && heap->data[i / 2].C > path.C) {
        heap->data[i] = heap->data[i / 2];
        i /= 2;
    }
    heap->data[i] = path;
}

// 弹出堆顶节点
Path pop(Heap* heap) {
    Path minPath = heap->data[1];
    Path lastPath = heap->data[heap->n--];
    int i = 1, j = 2;
    while (j <= heap->n) {
        if (j < heap->n && heap->data[j].C > heap->data[j + 1].C) j++;
        if (lastPath.C <= heap->data[j].C) break;
        heap->data[i] = heap->data[j];
        i = j;
        j *= 2;
    }
    heap->data[i] = lastPath;
    return minPath;
}

// Dijkstra 算法的优化版
void dijkstra(Edge** adjList, int n, int s, int* dist) {
    Heap* heap = createHeap(n);
    for (int i = 0; i < n; i++) dist[i] = INF;   // 初始化 dist 数组
    dist[s] = 0;
    Path temp = { s,0 };
    push(heap, temp);
    while (heap->n > 0) {
        Path minPath = pop(heap);
        int u = minPath.u;
        if (minPath.C > dist[u]) continue;  // 如果路径不是最短的就忽略
        for (Edge* e = adjList[u]; e != NULL; e = e->next) {
            int v = e->v, w = e->w;
            if (dist[u] + w < dist[v]) {    // 如果发现了更短的路径就更新
                dist[v] = dist[u] + w;
                temp = { v,dist[v] };
                push(heap, temp );
            }
        }
    }
}

int main() //此处的main是优化算法的
{
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);//s为开始点
    Edge** adjList = (Edge**)malloc(n * sizeof(Edge*));
    for (int i = 0; i < n; i++) 
        adjList[i] = NULL;
    int u, v, w;
    for (int i = 0; i < m; i++) 
    {
        scanf("%d%d%d", &u, &v, &w);
        Edge* e = (Edge*)malloc(sizeof(Edge));
        e->v = v;
        e->w = w;
        e->next = adjList[u];
        adjList[u] = e;
    }
    int* dist = (int*)malloc(n * sizeof(int));
    dijkstra(adjList, n, s, dist);
    for (int i = 0; i < n; i++) {
        if (dist[i] < INF) {
            printf("%d\n", dist[i]);
        }
        else {
            printf("INF\n");
        }
    }
    return 0;
}

