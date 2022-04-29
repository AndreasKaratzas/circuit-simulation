
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
    int num_of_nodes, num_of_patterns, num_of_faults;

    NODE circuit[MAX_NUM_OF_NODES];
    PATTERN vectors[MAX_NUM_OF_TEST_VECTORS];
    FAULT faults[MAX_NUM_OF_STUCK_AT_FAULTS];
    LOGGER logs[MAX_NUM_OF_TEST_VECTORS * MAX_NUM_OF_STUCK_AT_FAULTS];

    isc_file = fopen(argv[1], "r");
    num_of_nodes = read_isc_file(isc_file, circuit);
    fclose(isc_file);
    print_circuit(circuit, num_of_nodes);
    delete_circuit(circuit, MAX_NUM_OF_NODES);

    vec_file = fopen(argv[2], "r");
    num_of_patterns = read_vec_file(vec_file, vectors);
    fclose(vec_file);
    print_vectors(vectors, num_of_patterns);
    delete_vectors(vectors, num_of_patterns);

    faults_file = fopen(argv[3], "r");
    num_of_faults = read_faults_file(faults_file, faults);
    fclose(faults_file);
    print_faults(faults, num_of_faults);

    out_file = fopen(argv[4], "r");
    log_simulation(logs, out_file, num_of_patterns * num_of_faults);
    fclose(out_file);

    return (0);
}
