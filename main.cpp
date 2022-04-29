
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
    FILE *isc_file, *vec_file, *faults_file, *out_file;
    int num_of_nodes, num_of_patterns, num_of_faults, verbose;
    int node_dictionary[MAX_NUM_OF_NODES];

    verbose = 0;

    NODE circuit[MAX_NUM_OF_NODES];
    PATTERN vectors[MAX_NUM_OF_TEST_VECTORS];
    FAULT faults[MAX_NUM_OF_STUCK_AT_FAULTS];
    LOGGER logs[MAX_NUM_OF_TEST_VECTORS * MAX_NUM_OF_STUCK_AT_FAULTS];

    isc_file = fopen(argv[1], "r");
    num_of_nodes = read_isc_file(isc_file, circuit, node_dictionary);
    fclose(isc_file);

    vec_file = fopen(argv[2], "r");
    num_of_patterns = read_vec_file(vec_file, vectors);
    fclose(vec_file);

    faults_file = fopen(argv[3], "r");
    num_of_faults = read_faults_file(faults_file, faults);
    fclose(faults_file);

    if (argc == 6)
    {
        verbose = atoi(argv[5]);
    }

    simulate_circuit(circuit, vectors, faults, logs, num_of_nodes, num_of_patterns, num_of_faults, node_dictionary, verbose);

    out_file = fopen(argv[4], "ab+");
    log_simulation(out_file, logs, num_of_patterns * num_of_faults);
    fclose(out_file);

    if (verbose == 1)
    {
        print_vectors(vectors, num_of_patterns);
        print_faults(faults, num_of_faults);
    }

    delete_circuit(circuit, MAX_NUM_OF_NODES);
    delete_vectors(vectors, num_of_patterns);

    return (0);
}
