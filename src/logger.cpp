
#include "graph.hpp"


/**
 * @brief This function registers results after a {fault, test vector} simulation
 *        according to the project guidelines. The project guidelines can be found 
 *        inside the `docs` directory of this project.
 *
 * @param graph        the graph representing the running circuit
 * @param num_of_nodes the total number of nodes
 * @param vectors      the test vectors strored in a `PATTERN` structure
 * @param pattern_idx  the index of the test vector applied on the circuit. The index is an argument with respect to the `PATTERN` array
 * @param faults       the faults which are to be injected
 * @param fault_idx    the index of the fault injected. The index is an argument with respect to the `FAULTS` array
 * @param logs         the log structure which will be later used to output the simulation results
 */
void register_simulation(NODE *graph, int num_of_nodes, PATTERN *vectors, int pattern_idx, FAULT *faults, int fault_idx, LOGGER *logs)
{

}

/**
 * @brief This function outputs the 
 *
 *        An example results file can be reviewed below:
 *        ```
 *        INDEX | INPUT VECTOR | CORRECT RESPONSE | FAULT INJECTED | FAULTY RESPONSE | FAULT DETECTED
 *        1     | 1010110101   | 0110             | 2/1            | 0111            | 1
 *        ```
 * 
 * @param out_file 
 * @param logs 
 * @param num_of_logs 
 */
void log_simulation(FILE *out_file, LOGGER *logs, int num_of_logs)
{

}
