///\file main.c
///\brief Program that create a Minimum Spanning Tree (MST) using Prim and Kruskal algoritms.
///
/// Program that create a Minimum Spanning Tree (MST) using Prim and Kruskal algoritms.

#include <stdio.h>///> printf() , scanf() , fprintf() , fscanf()
#include <limits.h>///>INT_MAX
#include <stdbool.h>///> bool type
#include<malloc.h>///>malloc()
#include<time.h>///>time()
#include <stdlib.h>

int tree[1000][1000];
/*!
    \struct Edge
    \brief A structure to represent a weighted edge in graph.
*/
struct Edge
{
    int src;//!< src The curent node (the node searcherd)
    int dest;//!< dest The node that is linked to the curent (destination).
    int weight;//!< weight The weight between the curent and destination.
};

/*!
    \struct Graph
    \brief A structure to represent a connected, undirected and weighted graph.
*/
struct Graph
{
    int V;//!<  V Number of vertices.
    int E;//!< E Number of edges.

    struct Edge* edge;//!< edge The edge from src to dest is also edge from dest to src. Both are counted as 1 edge here.
};

/*!
    \struct subset
    \brief A structure to represent a connected, undirected and weighted graph.
*/
struct subset
{
    int parent;//!< parent The parent.
    int rank;//!< rank The rank.
};

/*!
    \fn int minKey(int vertices, int key[], bool mstSet[])
    \brief A utility function to find the vertex with minimum key value, from the set of vertices not yet included in MST.
    \param vertices Nr of vertices.
    \param key Key values used to pick minimum weight edge in cut.
    \param mstSet Represent set of vertices not yet included in MST.
*/
int minKey(int vertices, int key[], bool mstSet[])
{
    int min = INT_MAX;/**< min To search minimum value initialy initializated with a max value.*/
    int minPos;/**< minPos Index in order to stock the position of the minimum.*/
    int i;/**< i Index to move from an elelemnt to another.*/
    for ( i = 0; i < vertices; i++)
        if (mstSet[i] == false && key[i] < min)
            min = key[i], minPos = i;

    return minPos;
}
/*!
    \fn int printMST(int vertices, int parent[])
    \brief An utility function to print the constructed MST stored in parent[].
    \param vertices Nr of vertices.
    \param parent Array in which is stored the MST.
    \param aux Auxiliar to know if we need to write in file too.
    \param file File name to make the output file if its needed.
*/
int printMST(int vertices, int parent[], char aux, char file[])
{

    int i;/**< i Index to move from an elelemnt to another.*/
    printf("\nFollowing are the edges in the constructed MST with Prim\n \n");
    printf(" Edge   Weight\n");
    for (i = 1; i < vertices; i++)
        printf("%d -- %d == %d \n", parent[i], i, tree[i][parent[i]]);

    if(aux=='y')
    {
            FILE *f;/**< f A file data type used to read from file.*/
            f = fopen(file,"a");

                fprintf(f,"\nFollowing are the edges in the constructed MST with Prim\n \n");
                fprintf(f," Edge   Weight\n");
                    for (i = 1; i < vertices; i++)
                    fprintf(f,"%d -- %d == %d \n", parent[i], i, tree[i][parent[i]]);

            fclose(f);
    }
}

/*!
    \fn void primMST(int vertices)
    \brief Function to construct MST for a graph represented using adjacency matrix representation.
    \param vertices Nr of vertices.
    Function calls of printMST.
*/
void primMST(int vertices , char aux , char file[])
{
    int parent[vertices];/**< parent Array to store constructed MST.*/
    int key[vertices];/**< key Key values used to pick minimum weight edge in cut.*/
    bool mstSet[vertices];/**< mstSet To represent set of vertices not yet included in MST.*/

    int i;/**< i Index to move from an elelemnt to another.*/
    int v;/**< v Index to move from an elelemnt to another.*/
    for ( i = 0; i < vertices; i++)
        key[i] = INT_MAX, mstSet[i] = false;         // Initialize all key values as false

     key[0] = 0;        // Always include first 1st node in MST and make it the root.
     parent[0] = -1;

     for (i = 0; i < vertices-1; i++)
     {

        int u = minKey(vertices, key, mstSet);/**< u An auxiliar where is stored the position where is the minimum key value of the set not yet includee in MST.*/

        mstSet[u] = true;   // Add the picked vertex to the MST Set


        for (v = 0; v < vertices; v++)

          if (tree[u][v] && mstSet[v] == false && tree[u][v] <  key[v])
             parent[v]  = u, key[v] = tree[u][v];
     }

     printMST(vertices, parent ,aux ,file);
}

/*!
    \fn createGraph(int V, int E)
    \brief Creates a graph with V vertices and E edges
    \param V Nr of vertices.
    \param E Nr of edges.
*/
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );/**< graph A data type variabile in which is created the graph.*/
    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}
/*!
    \fn void randomGenerateFile(char file[] , int vertices , int edges)
    \brief Creates a file and fill it with random generated registrations.
    \param file The name of the file from which we read.
    \param vertices Nr of vertices.
    \param edges Nr of edges.
*/
void randomGenerateFile(char file[] , int vertices , int edges)
{
    FILE *f;/**< f A file data type used to read from file.*/
    f = fopen(file,"w");

    int i;/**< i Index.*/
    int j;/**< j Index.*/
    int ok=0;/**< ok Variable to check te stop condition.*/

    srand(time(NULL));

    for(j=1;ok!=edges;j++)
        for(i=0;(i<vertices)&&(ok!=edges);i++)
        {
            int r = rand();
            fprintf(f,"%d ",i%vertices);
            fprintf(f,"%d ",(i+j)%vertices);
            fprintf(f,"%d\n",r);
            ok++;
        }
    fclose(f);
}
/*!
    \fn readGraph(int edges , int vertices , char file[])
    \brief Function that read the graph from file. Function calls of createGraph().
    \param edges Nr of edges.
    \param vertices Nr of vertices.
    \param file The name of the file from which we read.
*/
struct Graph* readGraph(int edges , int vertices , char file[])
{

    FILE *f;/**< f A file data type used to read from file.*/
    f = fopen(file,"r");

    struct Graph* graph = createGraph(vertices, edges);

    int i;/**< i Index.*/
    for(i=0;i<edges;i++)
    {
        fscanf(f,"%d",&graph->edge[i].src);
        fscanf(f,"%d",&graph->edge[i].dest);
        fscanf(f,"%d",&graph->edge[i].weight);
        tree[graph->edge[i].src][graph->edge[i].dest]=graph->edge[i].weight;
        tree[graph->edge[i].dest][graph->edge[i].src]=graph->edge[i].weight;
    }

    fclose(f);
    return graph;
}

 /*!
    \fn int find(struct subset subsets[], int i)
    \brief Function used to find set of an element i by finding the root and make root as parent of i.
    \param subsets The subset created by Krushal sent in order to be modify.
    \param i The element from we need to find a set.
*/
int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

/*!
    \fn void unionOfSets(struct subset subsets[], int a, int b)
    \brief A function that does union of two sets of a and b by rank.
    \param subsets The subset created by Krushal sent in order to be modify.
    \param a A variable to know which element of subset we use.
    \param b A variable to know which element of subset we use.
*/
void unionOfSets(struct subset subsets[], int a, int b)
{
    int aroot = find(subsets, a);/**< aroot the root of element a.*/
    int broot = find(subsets, b);/**< broot the root of element b.*/

    if (subsets[aroot].rank < subsets[broot].rank)
        subsets[aroot].parent = broot;
    else if (subsets[aroot].rank > subsets[broot].rank)
        subsets[broot].parent = aroot;

    else
    {
        subsets[broot].parent = aroot;
        subsets[aroot].rank++;
    }
}

/*!
    \fn int Compare(const void* edge1, const void* edge2)
    \brief Compare two edges according to their weights used in qsort().
    \param edge1 The edge number 1.
    \param edge2 The edge number 2.
*/
int Compare(const void* edge1, const void* edge2)
{
    struct Edge* aux1 = (struct Edge*)edge1;/**< Auxiliar.*/
    struct Edge* aux2 = (struct Edge*)edge2;/**< Auxiliar.*/
    return aux1->weight > aux2->weight;
}
/*!
    \fn void KruskalMST(struct Graph* graph)
    \brief The main function to construct MST using Kruskal's algorithm.
    \param graph The graph that stores the tree.
*/
void KruskalMST(struct Graph* graph, char aux ,char file[])
{
    int V = graph->V;/**< V Nr of vertices.*/
    struct Edge result[V];/**< result Tnis will store the resultant MST.*/
    int e = 0;/**< e Index for result.*/
    int i = 0;/**< i Index.*/
    int v;/**< v An index variable, used for sorted edges.*/

    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), Compare);

    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );

    // Create V subsets with single elements
    for (v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            unionOfSets(subsets, x, y);
        }
        // Else discard the next_edge
    }

    printf("\nFollowing are the edges in the constructed MST with Kruskal\n \n");
    printf(" Edge   Weight\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);

    if(aux=='y')
    {
            FILE *f;/**< f A file data type used to read from file.*/
            f = fopen(file,"w");

            fprintf(f,"\nFollowing are the edges in the constructed MST with Kruskal\n \n");
            fprintf(f," Edge   Weight\n");
            for (i = 0; i < e; ++i)
                fprintf(f,"%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);

            fclose(f);
    }
    return;
}
/*!
    \fn int main()
    \brief Main function.
    \ Function calls of KruskalMST() , primMST() , randomGenerateFile()
*/
int main()
{
    int vertices /**<vertices Number of vertices in graph.*/;
    int edges ;/**<edges Number of edges in graph.*/;
    char File[100];/**< A string to stock the name of the file from where we will read.*/
    char file[100];/**< A string to stock the name of the file where the program need to display the output data.*/
    char s[] = "fi.in";/**< A string use to compare;*/
    char aux;/**< An auxiliar used for the chose menu;*/

    printf("In order to be easy to see if the tests are working properly enter the number \n");
    printf("of vertices and edges of the Minimum Spanning Tree you want to create and the \n");
    printf("file from where you want to read the MTS in this order: start,the destination \n");
    printf("and the weight between them, or use our thest file(fi.in) that contains 10000 \n");
    printf("registrations(edges) with random genereted wights between nodes 500 vertices \n");

    printf("You want to display the output data in a file too y/n? \n");
    aux=getchar();

    printf("Imput the number of vertices: \n");
    scanf("%d",&vertices);
    printf("Imput the number of edges: \n");
    scanf("%d",&edges);
    printf("Imput the name of the input file: \n");
    scanf("%s",&File);

    if (strcmp(File,s) == 0)
        randomGenerateFile(File,vertices,edges);

    if(aux=='y')
    {
    printf("Imput the name of the output file: \n");
    scanf("%s",&file);
    }

    struct Graph* graph = readGraph(edges,vertices,File);

    KruskalMST(graph,aux,file);

    primMST(vertices,aux,file);

    return 0;
}
