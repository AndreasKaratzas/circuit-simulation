
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
 * @param verbose         this parameter can either take value 0 or 1 indicating the preference of the user to regularly log simulation information to the terminal
 */
void register_simulation(NODE *graph, int num_of_nodes, PATTERN *vectors, int pattern_idx, int fault_idx, int fault_address, int fault_value, LOGGER *logs, int num_of_patterns, int verbose)
{
    int address, primary_output_counter, fault_detected, log_idx, primary_input_counter;
    char correct_val_array[MAX_NUM_OF_PRIMARY_OUTPUTS][2];
    char fault_val_array[MAX_NUM_OF_PRIMARY_OUTPUTS][2];
    char pattern_string[MAX_NUM_OF_PRIMARY_INPUTS][2];

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

            bzero(correct_val_array[primary_output_counter], 2);
            bzero(fault_val_array[primary_output_counter], 2);

            correct_val_array[primary_output_counter][0] = graph[address].correct_value + '0';
            fault_val_array[primary_output_counter][0] = graph[address].fault_value + '0';
            primary_output_counter += 1;
        }
    }

    for (primary_input_counter = 0; primary_input_counter < vectors[pattern_idx].num_of_primary_inputs; primary_input_counter += 1)
    {
        bzero(pattern_string[primary_input_counter], 2);

        pattern_string[primary_input_counter][0] = vectors[pattern_idx].primary_input_vec[primary_input_counter] + '0';
    }

    logs[log_idx].input_vector = (char*) malloc((primary_input_counter) * sizeof(char));
    logs[log_idx].correct_output = (char*) malloc((primary_output_counter + 1) * sizeof(char));
    logs[log_idx].faulty_output = (char*) malloc((primary_output_counter + 1) * sizeof(char));

    bzero(logs[log_idx].input_vector, primary_input_counter);
    bzero(logs[log_idx].correct_output, primary_output_counter + 1);
    bzero(logs[log_idx].faulty_output, primary_output_counter + 1);

    copy_str(pattern_string, logs[log_idx].input_vector, primary_input_counter);
    copy_str(correct_val_array, logs[log_idx].correct_output, primary_output_counter);
    copy_str(fault_val_array, logs[log_idx].faulty_output, primary_output_counter);

    logs[log_idx].index = log_idx;
    logs[log_idx].fault_address = fault_address;
    logs[log_idx].fault_value = fault_value;

    if (fault_detected == 1)
    {
        sprintf(logs[log_idx].fault_detected, "YES");
    }
    else
    {
        sprintf(logs[log_idx].fault_detected, "NO");
    }

    if (verbose == 1)
    {
        printf("%d | %s | %s | %d/%d | %s | %s\n",
            logs[log_idx].index,
            logs[log_idx].input_vector,
            logs[log_idx].correct_output,
            logs[log_idx].fault_address,
            logs[log_idx].fault_value,
            logs[log_idx].faulty_output,
            logs[log_idx].fault_detected
        );
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

        printf ("%d | %s | %s | %d/%d | %s | %s\n", 
            logs[log_count].index,
            logs[log_count].input_vector,
            logs[log_count].correct_output,
            logs[log_count].fault_address,
            logs[log_count].fault_value,
            logs[log_count].faulty_output,
            logs[log_count].fault_detected
        );

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
