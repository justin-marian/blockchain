#include "./include/block_dag.h"


/**
 * @brief Check the validity of the DAG and write the result to a file.
 */
void checkValidDag(void) {
    // Create a new graph.
    Graph *g = Create_Graph();

    // Handle memory allocation failure.
    if (!g) {
        fprintf(stderr, "Couldn't allocate g");
        exit(EXIT_FAILURE);
    }

    // Open a file for writing results.
    FILE *fout = fopen("blockdag.out", "w");

    // Handle opening file failure.
    if (!fout) {
        Free_Graph(g);
        fprintf(stderr, "Couldn't open file for writing");
        exit(EXIT_FAILURE);
    }

    // Check if the graph has a cycle.
    bool hasCycle = HasCycle(g);

    // Correct - graph is DAG.
    if (hasCycle)
        fprintf(fout, "impossible\n");
    else
        fprintf(fout, "correct\n");

    Free_Graph(g);
    fclose(fout);
}

/**
 * @brief Perform various operations on the graph based on a given node name.
 * 
 * @param name The name of the node to operate on.
 */
void graphSets(char *name) {
    // Create a new graph.
    Graph *g = Create_Graph();

    // Handle memory allocation failure.
    if (!g) {
        fprintf(stderr, "Couldn't allocate g");
        exit(EXIT_FAILURE);
    }

    // Get the vertex index of a node by name.
    int idx = Get_IdxNode(g, name);

    // Free graph memory if the node doesn't exist.
    if (idx <= -1) {
        Free_Graph(g);
        return;
    }

    // Open a file for writing results.
    FILE *fout = fopen("blockdag.out", "w");

    // Handle opening file failure.
    if (!fout) {
        fprintf(stderr, "Couldn't open file for writing");
        Free_Graph(g);
        exit(EXIT_FAILURE);
    }
    
    // Retrieve and print: past, future, anticone, and tips sets.
    ListVal *tips = Tips(g);
    ListVal *past = Past(g, idx);
    ListVal *future = Future(g, idx);
    ListVal *anticone = Anticone(g, idx, past, future);

    fprintf(fout, "past(%s) : ", name);
    Print_Ord(past, fout);
    Free_Ord(past);

    fprintf(fout, "future(%s) : ", name);
    Print_Ord(future, fout);
    Free_Ord(future);

    fprintf(fout, "anticone(%s) : ", name);
    Print_Ord(anticone, fout);
    Free_Ord(anticone);

    fprintf(fout, "tips(G) : ");
    Print_Ord(tips, fout);
    Free_Ord(tips);

    Free_Graph(g);
    fclose(fout);
}

int main(int argc, char **argv) {
    // Handle too many / missing command(s).
    if (argc > 3) {
        fprintf(stderr, "Too many command-line arguments");
        return EXIT_FAILURE;
    }
    if (argc < 2) {
        fprintf(stderr, "Missing command");
        return EXIT_FAILURE;
    }

    char *cmd = argv[1];

    switch (cmd[1]) {
        case 'c':
            switch (cmd[2]) {
                case '1':
                    checkValidDag();
                    break;
                case '2':
                    if (argc != 3) {
                        fprintf(stderr, "Invalid number of arguments for -c2 command");
                        return EXIT_FAILURE;
                    }
                    graphSets(argv[2]);
                    break;
                default:
                    fprintf(stderr, "Unknown command...");
                    return EXIT_FAILURE;
            }
            break;
        default:
            fprintf(stderr, "Unknown command...");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
