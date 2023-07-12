#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// �ڽӱ�ڵ�
typedef struct edge {
    int data;
    struct edge* next;
}Edge;

// ͼ�Ľṹ��
typedef struct Graph {
    Edge* list[MAX_SIZE];
    int vertex_count;
} Graph;

// ��ʼ��ͼ
void init_graph(Graph* graph, int vertex_count) {
    graph->vertex_count = vertex_count;
    for (int i = 0; i < MAX_SIZE; i++) {
        graph->list[i] = NULL;
    }
}

// ��ӱ�
void add_edge(Graph* graph, int start, int end) //���ֵ���
{
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->data = end;
    edge->next = graph->list[start];
    graph->list[start] = edge;
}
void add_edge_dic(Graph* graph, int start, int end)//�ֵ���
{
    //edge->data = end;
    //edge->next = NULL;
    //edge->Path_ID = id;
    if (graph->list[start] == NULL)
    {
        graph->list[start] = (Edge*)malloc(sizeof(Edge));
        graph->list[start]->data = end;
        graph->list[start]->next = NULL;
    }
    else
    {
        Edge* head = graph->list[start];
        while (head->next != NULL)
            head = head->next;
        head->next = (Edge*)malloc(sizeof(Edge));
        head->next->next = NULL;
        head->next->data = end;
    }
}
// �����������ݹ飩
void traverse_dfs(Graph* graph, int start, int end, int* visited, int* path, int path_length) {
    visited[start] = 1;
    path[path_length] = start;
    path_length++;
    if (start == end) { // �ҵ�һ��·��
        for (int i = 0; i < path_length; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    else {
        Edge* current_node = graph->list[start];
        while (current_node != NULL) {
            int next_vertex = current_node->data;
            if (visited[next_vertex] == 0) {
                traverse_dfs(graph, next_vertex, end, visited, path, path_length);
            }
            current_node = current_node->next;
        }
    }
    visited[start] = 0;
}

// ����ͼ(dfs)
void traverse_graph(Graph* graph, int start, int end) {
    int visited[MAX_SIZE] = { 0 };
    int path[MAX_SIZE];
    traverse_dfs(graph, start, end, visited, path, 0);
}
int main()
{

}