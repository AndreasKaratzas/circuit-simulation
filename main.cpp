
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
    int last_node;

    NODE circuit[MAX_NUM_OF_NODES];
    
    isc_file = fopen(argv[1], "r");
    last_node = read_isc_file(isc_file, circuit);
    fclose(isc_file);
    print_circuit(circuit, last_node);
    delete_circuit(circuit, MAX_NUM_OF_NODES);
    
    return (0);
}
