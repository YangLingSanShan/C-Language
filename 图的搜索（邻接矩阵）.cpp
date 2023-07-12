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
// ��ʼ��ͼ
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
// ��ӱ�
void add_edge(int graph[MAX_SIZE][MAX_SIZE], int start, int end)//��Ȩ 
{
    graph[start][end] = 1;
}
void add_edge_point(int graph[MAX_SIZE][MAX_SIZE], int start, int end,int point)//��Ȩ 
{
    graph[start][end] = point;
}
/************************************************DFS�����������********************************************************/
// �����������
void dfs(int graph[MAX_SIZE][MAX_SIZE], int vertex, int* visited, int n) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < n; i++) {
        if (graph[vertex][i] == 1 && visited[i] == 0) {
            dfs(graph, i, visited, n);
        }
    }
}
// dfs����ͼ->1��
void traverse_graph(int graph[MAX_SIZE][MAX_SIZE], int n) {
    int visited[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            dfs(graph, i, visited, n);
        }
    }
}

/******************************** ������BFS(����������� )************************************************/
// ��ʼ������
void init_queue(Queue* q)
{
    q->front = q->rear = 0;
}

// ���
int enqueue(Queue* q, int value)
{
    if ((q->rear + 1) % QUEUE_SIZE == q->front) {
        return 0; // ��������
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return 1;
}
// ����
int dequeue(Queue* q, int* value)
{
    if (q->front == q->rear) {
        return 0; // ����Ϊ��
    }
    *value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return 1;
}
// �ж϶����Ƿ�Ϊ��
int is_empty_queue(Queue* q)
{
    return q->front == q->rear;
}
// ������ȱ���ͼ
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
// ��ȱ���1��ͼ
void traverse_graph_bfs(int graph[MAX_SIZE][MAX_SIZE], int n)
{
    int visited[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            bfs(graph, i, visited, n);
        }
    }
}
//������������������del->��del�ڵ�ɾ������б���
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
// ���Դ���
int main() {

    int n, m, a, b, c;
    scanf("%d%d", &n, &m);//n���ڵ㣬m����
    //init_graph(graph, n);
    for (int i = 1;i <= m;i++)
    {
        scanf("%d%d", &a, &b);
        add_edge(graph, a, b);
        add_edge(graph, b, a);
        /*
        * ����һ����������������ͼ �磺add_edge(graph, a, b);
        * ���ͼ��Ȩֵ�������Ȩֵ����Ϊadd_edge(graph,a,b,c);
        */
    }
    return 0;
}
