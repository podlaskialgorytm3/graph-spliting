#ifndef GRAPH_
#define GRAPH_

typedef struct edges
{
    int soruceNode;
    int endNode;
    struct edges *next;
} edges, *edgesPtr;

typedef struct graphFragments
{
    int node;
    struct graphFragments *next;
} graphFragments, *graphFragmentsPtr;

typedef struct nodeIndex
{
    int index;
    struct nodeIndex *next;
} nodeIndex, *nodeIndexPtr;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

edgesPtr insertEdge(edgesPtr list, int sourceNode, int endNode);

graphFragmentsPtr insertGraphFragment(graphFragmentsPtr list, int node);

graphFragmentsPtr getGraphFragment(char *filename);

int getSizeGraphFragment(graphFragmentsPtr list);

nodeIndexPtr insertNodeIndex(nodeIndexPtr list, int index);

nodeIndexPtr getNodeIndex(char *filename);

edgesPtr edgesInsertion(char *filename);

void printEdges(edgesPtr list);

void printGraphFragments(graphFragmentsPtr list);

void printNodeIndex(nodeIndexPtr list);

void freeEdges(edgesPtr list);

void freeGraphFragments(graphFragmentsPtr list);

void freeNodeIndex(nodeIndexPtr list);

#endif