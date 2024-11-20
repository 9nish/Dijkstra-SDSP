typedef struct vertex {
    int vertex_id;
    double d;
    int p;
    int handle;
}VERTEX;

typedef struct min_heap {
    int heap_size;
    VERTEX *A;
}MIN_HEAP;

typedef struct node {
    int vertex_id;
    int weight;
    struct node *next;
}NODE;

typedef struct graph {
    int cardinality_of_V;
    VERTEX *V;
    NODE* *adj;
}GRAPH;

int PARENT(int i);

void MIN_HEAPIFY(GRAPH *G, MIN_HEAP *Q, int i);

VERTEX HEAP_EXTRACT_MIN(GRAPH *G, MIN_HEAP *Q);

void HEAP_DECREASE_KEY(GRAPH *G, MIN_HEAP *Q, int i, double key);

void MIN_HEAP_INSERT(MIN_HEAP *Q, GRAPH *G, VERTEX v);

void INITIALIZE_SINGLE_SOURCE(GRAPH *G, int s);

void RELAX(GRAPH *G, VERTEX u, VERTEX v, int weight_of_edge_u_v, MIN_HEAP *Q);

void DIJKSTRA(GRAPH *G, int s);

void PRINT_PATH(GRAPH *G, int i, int s, int d);

void PRINT_SHORTEST_PATH_DEST(GRAPH *G, int s);

NODE* INSERT_NODE(NODE *u, int v, int w);

void DEALLOCATE_ADJ(NODE *p);

void CREATE_GRAPH(GRAPH *G);








