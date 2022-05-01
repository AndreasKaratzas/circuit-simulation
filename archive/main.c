
#include "graph.h"

/**
 * @brief The driver function.
 *
 * @param argc number of terminal arguments/options
 * @param argv the string argument vector
 * @return int the execution status as per OS protocol
 *
 * @version 3.1.1
 *
 * @test To execute the target file use:
 *      $> ./project data/input/c17.isc data/input/c17.vec data/input/c17.faults data/output/c17.results
 *      $> ./project data/input/c880.isc data/input/c880.vec data/input/c880.faults data/output/c880.results
 *      $> ./project data/input/c1908.isc data/input/c1908.vec data/input/c1908.faults data/output/c1908.results
 *      $> ./project data/input/c7552.isc data/input/c7552.vec data/input/c7552.faults data/output/c7552.results
 *
 */
int main(int argc, char *argv[])
{
    FILE *isc_file, *vec_file, *faults_file, *out_file;
    int num_of_nodes, num_of_patterns, num_of_faults, verbose;
    int node_dictionary[MAX_NUM_OF_NODES];
    char benchmark[10];

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
    get_benchmark_name(benchmark, argv[1]);
    log_simulation(out_file, logs, num_of_patterns * num_of_faults, num_of_patterns, node_dictionary, benchmark);
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
