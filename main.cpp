
#include "graph.hpp"

/**
 * @brief The driver function.
 * 
 * @param argc number of terminal arguments/options
 * @param argv the string argument vector
 * @return int the execution status as per OS protocol
 */
int main(int argc, char *argv[])
{
    FILE *isc_file, *vec_file, *fault_file, *out_file;
    int num_of_nodes, num_of_patterns;

    NODE circuit[MAX_NUM_OF_NODES];
    PATTERN vectors[MAX_NUM_OF_TEST_VECTORS];
    
    isc_file = fopen(argv[1], "r");
    num_of_nodes = read_isc_file(isc_file, circuit);
    fclose(isc_file);
    print_circuit(circuit, num_of_nodes);
    delete_circuit(circuit, MAX_NUM_OF_NODES);

    vec_file = fopen(argv[2], "r");
    num_of_patterns = read_vec_file(vec_file, vectors);
    fclose(vec_file);
    print_vectors(vectors, num_of_patterns);
    delete_vectors(vectors, MAX_NUM_OF_TEST_VECTORS);
    
    return (0);
}
