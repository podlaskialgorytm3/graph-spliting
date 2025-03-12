#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

int main()
{
    edgesPtr edgeList = edgesInsertion("graf.csrrg"); // Pobieramy bezposrednio z folderu ./data
    printEdges(edgeList);
    freeEdges(edgeList);

    // graphFragmentsPtr graphFragmentsList = getGraphFragment("graf3.csrrg");
    // printGraphFragments(graphFragmentsList);
    // freeGraphFragments(graphFragmentsList);

    return 0;
}