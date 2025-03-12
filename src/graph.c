#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        return -1;
    }

    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF)
    {
        return -1;
    }
    if (bufptr == NULL)
    {
        bufptr = malloc(128);
        if (bufptr == NULL)
        {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF)
    {
        if ((p - bufptr) > (size - 1))
        {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL)
            {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n')
        {
            break;
        }
        c = fgetc(stream);
    }
    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

edgesPtr insertEdge(edgesPtr list, int sourceNode, int endNode)
{
    if (list == NULL)
    {
        edgesPtr newList = (edgesPtr)malloc(sizeof(edges));
        if (newList == NULL)
        {
            exit(1);
        }
        newList->soruceNode = sourceNode;
        newList->endNode = endNode;
        newList->next = list;

        return newList;
    }
    else
    {
        list->next = insertEdge(list->next, sourceNode, endNode);
        return list;
    }
}
graphFragmentsPtr insertGraphFragment(graphFragmentsPtr list, int node)
{
    if (list == NULL)
    {
        graphFragmentsPtr newList = (graphFragmentsPtr)malloc(sizeof(graphFragments));
        if (newList == NULL)
        {
            exit(1);
        }
        newList->node = node;
        newList->next = list;

        return newList;
    }
    else
    {
        list->next = insertGraphFragment(list->next, node);
        return list;
    }
}

nodeIndexPtr insertNodeIndex(nodeIndexPtr list, int index)
{
    if (list == NULL)
    {
        nodeIndexPtr newList = (nodeIndexPtr)malloc(sizeof(nodeIndex));
        if (newList == NULL)
        {
            exit(1);
        }
        newList->index = index;
        newList->next = list;

        return newList;
    }
    else
    {
        list->next = insertNodeIndex(list->next, index);
        return list;
    }
}

graphFragmentsPtr getGraphFragment(char *filename)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "./data/%s", filename);
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for reading\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;
    graphFragmentsPtr list = NULL;

    while ((read = getline(&line, &len, file)) != -1)
    {
        lineNumber++;
        if (lineNumber == 4)
        {
            char *token = strtok(line, ";");
            while (token != NULL)
            {
                int node = atoi(token);
                list = insertGraphFragment(list, node);
                token = strtok(NULL, ";");
            }
            break;
        }
    }

    free(line);
    fclose(file);
    return list;
}

nodeIndexPtr getNodeIndex(char *filename)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "./data/%s", filename);
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for reading\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;
    nodeIndexPtr list = NULL;

    while ((read = getline(&line, &len, file)) != -1)
    {
        lineNumber++;
        if (lineNumber == 5)
        {
            char *token = strtok(line, ";");
            while (token != NULL)
            {
                int index = atoi(token);
                list = insertNodeIndex(list, index);
                token = strtok(NULL, ";");
            }
            break;
        }
    }

    free(line);
    fclose(file);
    return list;
}

edgesPtr edgesInsertion(char *filename)
{
    graphFragmentsPtr graphFragmentsList = getGraphFragment(filename);
    nodeIndexPtr nodeIndexList = getNodeIndex(filename);
    edgesPtr edgeList = NULL;
    int graphFragmentSize = getSizeGraphFragment(graphFragmentsList);
    int sourceNode, limit;

    while (nodeIndexList != NULL)
    {
        sourceNode = graphFragmentsList->node;
        if (nodeIndexList->next == NULL)
        {
            limit = graphFragmentSize;
        }
        else
        {
            limit = nodeIndexList->next->index;
        }
        for (int i = nodeIndexList->index; i < limit - 1; i++)
        {
            graphFragmentsList = graphFragmentsList->next;
            edgeList = insertEdge(edgeList, sourceNode, graphFragmentsList->node);
        }
        graphFragmentsList = graphFragmentsList->next;
        nodeIndexList = nodeIndexList->next;
    }

    return edgeList;
}

int getSizeGraphFragment(graphFragmentsPtr list)
{
    int size = 0;
    while (list != NULL)
    {
        size++;
        list = list->next;
    }
    return size;
}

void printEdges(edgesPtr list)
{
    while (list != NULL)
    {
        printf("%d - %d \n", list->soruceNode, list->endNode);
        list = list->next;
    }
}

void printGraphFragments(graphFragmentsPtr list)
{
    printf("Generated graph fragments: \n");
    while (list != NULL)
    {
        printf("%d ", list->node);
        list = list->next;
    }
    printf("\n");
}

void printNodeIndex(nodeIndexPtr list)
{
    printf("Node indexes: \n");
    while (list != NULL)
    {
        printf("%d ", list->index);
        list = list->next;
    }
    printf("\n");
}

void freeEdges(edgesPtr list)
{
    edgesPtr temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}

void freeGraphFragments(graphFragmentsPtr list)
{
    graphFragmentsPtr temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}

void freeNodeIndex(nodeIndexPtr list)
{
    nodeIndexPtr temp;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}