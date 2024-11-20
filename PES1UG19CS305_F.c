#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "PES1UG19CS305_H.h"

int PARENT(int i) {
    return (i - 1) >> 1;   // floor((i - 1) / 2)
}

void MIN_HEAPIFY(GRAPH *G, MIN_HEAP *Q, int i) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int smallest;
    if(l < Q->heap_size && Q->A[l].d < Q->A[i].d)
        smallest = l;
    else
        smallest = i;
    if(r < Q->heap_size && Q->A[r].d < Q->A[smallest].d)
        smallest = r;
    if(smallest != i) {
        VERTEX temp = Q->A[i];
        Q->A[i] = Q->A[smallest];
        Q->A[smallest] = temp;

        G->V[Q->A[smallest].vertex_id - 1].handle = smallest;
        G->V[Q->A[i].vertex_id - 1].handle = i;

        MIN_HEAPIFY(G, Q, smallest);
    }
}

VERTEX HEAP_EXTRACT_MIN(GRAPH *G, MIN_HEAP *Q) {
    VERTEX MIN = Q->A[0];
    Q->A[0] = Q->A[Q->heap_size-1];
    G->V[Q->A[0].vertex_id - 1].handle = 0;
    Q->heap_size--;
    MIN_HEAPIFY(G, Q, 0);
    return MIN;
}

void HEAP_DECREASE_KEY(GRAPH *G, MIN_HEAP *Q, int i, double key) {
    VERTEX x = Q->A[i];
    while(PARENT(i) >= 0 && Q->A[PARENT(i)].d > key) {
        Q->A[i] = Q->A[PARENT(i)];
        G->V[Q->A[i].vertex_id - 1].handle = i;
        i = PARENT(i);
    }
    x.d = key;
    Q->A[i] = x;
    G->V[x.vertex_id - 1].handle = i;
}

void MIN_HEAP_INSERT(MIN_HEAP *Q, GRAPH *G, VERTEX v) {
    double key = v.d;
    v.d = INFINITY;
    Q->A[Q->heap_size++] = v;
    HEAP_DECREASE_KEY(G, Q, Q->heap_size - 1, key);
}

void INITIALIZE_SINGLE_SOURCE(GRAPH *G, int s) {
    for(int i = 1; i <= G->cardinality_of_V; i++) {
        G->V[i-1].d = INFINITY;
        G->V[i-1].p = G->cardinality_of_V + 1;    // p = cardinality_of_V + 1 is equivalent to p = NIL
    }
    G->V[s-1].d = 0;
}

void RELAX(GRAPH *G, VERTEX u, VERTEX v, int weight_of_edge_u_v, MIN_HEAP *Q) {
    if(v.d > u.d + weight_of_edge_u_v) {
        G->V[v.vertex_id - 1].d = u.d + weight_of_edge_u_v;
        G->V[v.vertex_id - 1].p = u.vertex_id;
        HEAP_DECREASE_KEY(G, Q, v.handle, G->V[v.vertex_id - 1].d);
    }
}

void DIJKSTRA(GRAPH *G, int s) {
    INITIALIZE_SINGLE_SOURCE(G, s);
    MIN_HEAP Q;
    Q.A = malloc(sizeof(VERTEX) * G->cardinality_of_V);
    Q.heap_size = 0;
    for(int i = 1; i <= G->cardinality_of_V; i++)
        MIN_HEAP_INSERT(&Q, G, G->V[i-1]);
    VERTEX u;
    NODE *p;
    while(Q.heap_size > 1) {
        u = HEAP_EXTRACT_MIN(G, &Q);
        p = G->adj[u.vertex_id - 1];
        while(p !=NULL) {
            RELAX(G, G->V[u.vertex_id - 1], G->V[p->vertex_id -1], p->weight, &Q);
            p = p->next;
        }
    }
    free(Q.A);
}

void PRINT_PATH(GRAPH *G, int i, int s, int d) {
    if(i == s)
        printf("%d %d", i, d);
    else if(G->V[i - 1].p == G->cardinality_of_V + 1)
        printf("NO PATH");
    else {
        printf("%d ", i);
        PRINT_PATH(G, G->V[i - 1].p, s, d);
    }
}

void PRINT_SHORTEST_PATH_DEST(GRAPH *G, int s) {
    int d;
    for(int i = 1; i <= G->cardinality_of_V; i++) {
        if(i != s) {
            printf("%d ", i);
            if(G->V[i-1].d == INFINITY)
                d = -1;   //just to be safe and not cast INFINITY to an int
            else 
                d = (int)G->V[i-1].d;
            PRINT_PATH(G, i, s, d);
            printf("\n");
        }
    }
}


NODE* INSERT_NODE(NODE *u, int v, int w) {
    if(u == NULL) {
        u = malloc(sizeof(NODE));
        u->vertex_id = v;
        u->weight = w;
        u->next = NULL;
        return u;
    }

    NODE *p = u;
    while(p->next != NULL)
        p = p->next;
    p->next = malloc(sizeof(NODE));
    p->next->vertex_id = v;
    p->next->weight = w;
    p->next->next = NULL;
    return u;
}

void DEALLOCATE_ADJ(NODE *p) {
    if(p == NULL)
        return;
    NODE *q = p;
    while(q != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
}

void CREATE_GRAPH(GRAPH *G) {
    GRAPH *A = malloc(sizeof(GRAPH));
    FILE *ptr = fopen("adjacencylist.txt", "r");
    char c;
    fscanf(ptr, "%d", &A->cardinality_of_V);

    A->V = malloc(sizeof(VERTEX) * A->cardinality_of_V);
    A->adj = malloc(sizeof(NODE *) * A->cardinality_of_V);


    for(int i = 1; i <= A->cardinality_of_V; i++) {
        A->V[i-1].vertex_id = i;
        A->adj[i-1] = NULL;
    }

    fscanf(ptr, "%c", &c);

    int u, v, weight;
    int k = 1;
    while (k) {
        fscanf(ptr, "%d", &u);
        fscanf(ptr, "%c", &c);

        while(1) {
            fscanf(ptr, "%d", &v);

            fscanf(ptr, "%c", &c);

            fscanf(ptr, "%d", &weight);
            A->adj[u-1] = INSERT_NODE(A->adj[u-1], v, weight);
            
            if(fscanf(ptr, "%c", &c) == EOF) {
                k = 0;
                break;
            }

            if(c == '\n')
                break;
        }
    }

    fclose(ptr);

    G->cardinality_of_V = A->cardinality_of_V;

    G->V = malloc(sizeof(VERTEX) * G->cardinality_of_V);
    G->adj = malloc(sizeof(NODE *) * G->cardinality_of_V);

    for(int i = 1; i <= G->cardinality_of_V; i++) {
        G->V[i-1].vertex_id = i;
        G->adj[i-1] = NULL;
    }


    NODE *p;
    for(u=1; u <= G->cardinality_of_V; u++) {
        p = A->adj[u-1];
        while(p != NULL) {
            v = p->vertex_id;
            weight = p->weight;
            G->adj[v-1] = INSERT_NODE(G->adj[v-1], u, weight);
            p = p->next;
        }
    }

    for(int i = 1; i <= A->cardinality_of_V; i++)
        DEALLOCATE_ADJ(A->adj[i-1]);

    free(A->adj);
    free(A->V);

}