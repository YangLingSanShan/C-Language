#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define QUEUE_SIZE 1000
int graph[MAX_SIZE][MAX_SIZE];
typedef struct Queue
{
    int data[QUEUE_SIZE];
    int front;
    int rear;
} Queue;
// 初始化图
void init_graph(int graph[MAX_SIZE][MAX_SIZE], int vertex_count)
{
    for (int i = 0; i < vertex_count; i++)
    {
        for (int j = 0; j < vertex_count; j++)
        {
            graph[i][j] = 0;
        }
    }
}
// 添加边
void add_edge(int graph[MAX_SIZE][MAX_SIZE], int start, int end)//无权 
{
    graph[start][end] = 1;
}
void add_edge_point(int graph[MAX_SIZE][MAX_SIZE], int start, int end,int point)//有权 
{
    graph[start][end] = point;
}
/************************************************DFS深度优先搜索********************************************************/
// 深度优先搜索
void dfs(int graph[MAX_SIZE][MAX_SIZE], int vertex, int* visited, int n) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < n; i++) {
        if (graph[vertex][i] == 1 && visited[i] == 0) {
            dfs(graph, i, visited, n);
        }
    }
}
// dfs遍历图->1次
void traverse_graph(int graph[MAX_SIZE][MAX_SIZE], int n) {
    int visited[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            dfs(graph, i, visited, n);
        }
    }
}

/******************************** 下面是BFS(广度优先搜索 )************************************************/
// 初始化队列
void init_queue(Queue* q)
{
    q->front = q->rear = 0;
}

// 入队
int enqueue(Queue* q, int value)
{
    if ((q->rear + 1) % QUEUE_SIZE == q->front) {
        return 0; // 队列已满
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return 1;
}
// 出队
int dequeue(Queue* q, int* value)
{
    if (q->front == q->rear) {
        return 0; // 队列为空
    }
    *value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return 1;
}
// 判断队列是否为空
int is_empty_queue(Queue* q)
{
    return q->front == q->rear;
}
// 广度优先遍历图
void bfs(int graph[MAX_SIZE][MAX_SIZE], int vertex, int* visited, int n) {
    Queue queue;
    init_queue(&queue);
    visited[vertex] = 1;
    printf("%d ", vertex);
    enqueue(&queue, vertex);
    while (!is_empty_queue(&queue)) {
        int current_vertex;
        dequeue(&queue, &current_vertex);
        for (int i = 0; i < n; i++) {
            if (graph[current_vertex][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                printf("%d ", i);
                enqueue(&queue, i);
            }
        }
    }
}
// 广度遍历1次图
void traverse_graph_bfs(int graph[MAX_SIZE][MAX_SIZE], int n)
{
    int visited[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            bfs(graph, i, visited, n);
        }
    }
}
//下面两个函数是输入del->将del节点删除后进行遍历
void delete_graph(int del,int n)
{
    for (int i = 0;i < n;i++)
    {
        graph[i][del] = 0;
        graph[del][i] = 0;
    }
}
void traverse_graph_bfs_del(int graph[MAX_SIZE][MAX_SIZE], int n, int del)
{
    int visited[MAX_SIZE] = { 0 };
    delete_graph(del,n);
    for (int i = 0; i < n; i++)
    {
        if (i == del)
            continue;
        if (visited[i] == 0) {
            bfs(graph, i, visited, n);
        }
    }
}
void traverse_graph_dfs_del(int graph[MAX_SIZE][MAX_SIZE], int n, int del) {
    int visited[MAX_SIZE] = { 0 };
    delete_graph(del, n);
    for (int i = 0; i < n; i++)
    {
        if (i == del)
            continue;
        if (visited[i] == 0) {
            dfs(graph, i, visited, n);
        }
    }
}
/***************************************************************************************************************/
// 测试代码
int main() {

    int n, m, a, b, c;
    scanf("%d%d", &n, &m);//n个节点，m条边
    //init_graph(graph, n);
    for (int i = 1;i <= m;i++)
    {
        scanf("%d%d", &a, &b);
        add_edge(graph, a, b);
        add_edge(graph, b, a);
        /*
        * 单用一个函数，就是有向图 如：add_edge(graph, a, b);
        * 如果图有权值，则添加权值，改为add_edge(graph,a,b,c);
        */
    }
    return 0;
}
