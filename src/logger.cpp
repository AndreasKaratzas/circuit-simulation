
#include "graph.hpp"


/**
 * @brief This function registers results after a {fault, test vector} simulation
 *        according to the project guidelines. The project guidelines can be found
 *        inside the `docs` directory of this project.
 *
 * @param graph           the graph representing the running circuit
 * @param num_of_nodes    the total number of nodes
 * @param vectors         the test vectors strored in a `PATTERN` structure
 * @param pattern_idx     the index of the test vector applied on the circuit. The index is an argument with respect to the `PATTERN` array
 * @param faults          the faults which are to be injected
 * @param fault_idx       the index of the fault injected. The index is an argument with respect to the `FAULTS` array
 * @param logs            the log structure which will be later used to output the simulation results
 * @param num_of_patterns the total number of test vectors
 */
void register_simulation(NODE *graph, int num_of_nodes, PATTERN *vectors, int pattern_idx, FAULT *faults, int fault_idx, LOGGER *logs, int num_of_patterns)
{
    int address, primary_output_counter, fault_detected, log_idx, primary_input_counter;
    char correct_val_array[MAX_NUM_OF_PRIMARY_OUTPUTS];
    char fault_val_array[MAX_NUM_OF_PRIMARY_OUTPUTS];
    char pattern_string[MAX_NUM_OF_PRIMARY_INPUTS];

    fault_detected = -1;
    primary_output_counter = 0;
    log_idx = (fault_idx * num_of_patterns) + pattern_idx;

    for (address = 0; address < num_of_nodes; address += 1)
    {
        if (graph[address].primary_output == 1)
        {
            if (graph[address].correct_value != graph[address].fault_value)
            {
                fault_detected += 1;
            }

            correct_val_array[primary_output_counter] = graph[address].correct_value + '0';
            fault_val_array[primary_output_counter] = graph[address].fault_value + '0';
            primary_output_counter += 1;
        }
    }

    for (primary_input_counter = 0; primary_input_counter < vectors[pattern_idx].num_of_primary_inputs; primary_input_counter += 1)
    {
        pattern_string[primary_input_counter] = vectors[pattern_idx].primary_input_vec[primary_input_counter];
    }

    correct_val_array[primary_output_counter] = '\0';
    fault_val_array[primary_output_counter] = '\0';
    pattern_string[primary_input_counter] = '\0';

    logs[log_idx].input_vector = (char*) malloc(strlen(pattern_string) * sizeof(char));
    logs[log_idx].correct_output = (char*) malloc(strlen(correct_val_array) * sizeof(char));
    logs[log_idx].faulty_output = (char*) malloc(strlen(fault_val_array) * sizeof(char));

    logs[log_idx].input_vector = strdup(pattern_string);
    logs[log_idx].correct_output = strdup(correct_val_array);
    logs[log_idx].faulty_output = strdup(fault_val_array);

    logs[log_idx].index = log_idx;
    logs[log_idx].fault_address = faults[fault_idx].address;
    logs[log_idx].fault_value = faults[fault_idx].fault;

    if (fault_detected == 1)
    {
        sprintf(logs[log_idx].fault_detected, "YES");
    }
    else
    {
        sprintf(logs[log_idx].fault_detected, "NO");
    }
}

/**
 * @brief This function outputs the log file after a pettern/fault simulation.
 *
 *        An example log file can be reviewed below:
 *        ```
 *        INDEX | INPUT VECTOR | CORRECT OUTPUT | FAULT INJECTED | FAULTY OUTPUT | FAULT DETECTED
 *        1     | 1010110101   | 0110           | 2/1            | 0111          | YES
 *        ```
 *
 * @param out_file    the log file pointer
 * @param logs        the logs kept during the simulation
 * @param num_of_logs the number of registers inside the given logs
 */
void log_simulation(FILE *out_file, LOGGER *logs, int num_of_logs)
{
    int log_count;

    fprintf(out_file, "INDEX | INPUT VECTOR | CORRECT OUTPUT | FAULT INJECTED | FAULTY OUTPUT | FAULT DETECTED\n");

    for (log_count = 0; log_count < num_of_logs; log_count += 1)
    {
        fprintf(out_file, "%d | %s | %s | %d/%d | %s | %s\n",
            logs[log_count].index,
            logs[log_count].input_vector,
            logs[log_count].correct_output,
            logs[log_count].fault_address,
            logs[log_count].fault_value,
            logs[log_count].faulty_output,
            logs[log_count].fault_detected
        );
    }
}