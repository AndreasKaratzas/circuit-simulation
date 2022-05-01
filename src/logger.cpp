
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

    fault_detected = 0;
    primary_output_counter = 0;
    log_idx = (fault_idx * num_of_patterns) + pattern_idx;

    for (address = 0; address < num_of_nodes; address += 1)
    {
        if (graph[address].primary_output == 1)
        {
            if (graph[address].correct_value != graph[address].fault_value)
            {
                if (graph[address].correct_value != 2 && graph[address].fault_value != 2)
                {
                    fault_detected += 1;
                }
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

    logs[log_idx].input_vector = (char*) malloc((primary_input_counter + 1) * sizeof(char));
    logs[log_idx].correct_output = (char*) malloc((primary_output_counter + 1) * sizeof(char));
    logs[log_idx].faulty_output = (char*) malloc((primary_output_counter + 1) * sizeof(char));

    bzero(logs[log_idx].input_vector, primary_input_counter + 1);
    bzero(logs[log_idx].correct_output, primary_output_counter + 1);
    bzero(logs[log_idx].faulty_output, primary_output_counter + 1);

    copy_str(pattern_string, logs[log_idx].input_vector, primary_input_counter);
    copy_str(correct_val_array, logs[log_idx].correct_output, primary_output_counter);
    copy_str(fault_val_array, logs[log_idx].faulty_output, primary_output_counter);

    logs[log_idx].index = log_idx;
    logs[log_idx].fault_address = fault_address;
    logs[log_idx].fault_value = fault_value;

    if (fault_detected > 0)
    {
        sprintf(logs[log_idx].fault_detected, "Fault detected");
    }
    else
    {
        sprintf(logs[log_idx].fault_detected, "Fault NOT detected");
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
 *        The results file follows a similar pattern to that of the Atalanta tool.
 *
 * @param out_file        the log file pointer
 * @param logs            the logs kept during the simulation
 * @param num_of_logs     the number of registers inside the given logs
 * @param num_of_patterns the total number of test vectors
 * @param node_dictionary the mapper for the compressed version of the circuit
 */
void log_simulation(FILE *out_file, LOGGER *logs, int num_of_logs, int num_of_patterns, int *node_dictionary, char *benchmark)
{
    int log_count, prev_fault_node_address, prev_fault_value, original_node_address;

    prev_fault_node_address = -1;
    prev_fault_value = -1;

    log_description(out_file, benchmark);

    for (log_count = 0; log_count < num_of_logs; log_count += 1)
    {
        original_node_address = get_original_node_address(node_dictionary, logs[log_count].fault_address);

        if (prev_fault_node_address != original_node_address || prev_fault_value != logs[log_count].fault_value)
        {
            prev_fault_node_address = original_node_address;
            prev_fault_value = logs[log_count].fault_value;

            fprintf(out_file, "%d/%d:\n", prev_fault_node_address, prev_fault_value);
        }

        fprintf(out_file, "\t%d: %s %s %s (%s)\n",
            logs[log_count].index % num_of_patterns,
            logs[log_count].input_vector,
            logs[log_count].correct_output,
            logs[log_count].faulty_output,
            logs[log_count].fault_detected
        );
    }
}

/**
 * @brief Get the original node address with respect to the circuit file
 *
 * @param node_dictionary         the node dictionary compiled while creating the circuit
 * @param compressed_node_address the node address corresponding to the compressed version of the circuit
 * @return int                    the original node address (before compression)
 */
int get_original_node_address(int *node_dictionary, int compressed_node_address)
{
    int node_count;

    for (node_count = 0; node_count < MAX_NUM_OF_NODES; node_count += 1)
    {
        if (node_dictionary[node_count] == compressed_node_address)
        {
            return (node_count);
        }
    }

    printf("`get_original_node_address()`: Did not find the node %d.\n", compressed_node_address);
    exit(1);
}

/**
 * @brief This logs some information about the project and the structure of the results file
 *
 * @param out_file  the results file
 * @param benchmark the name of the ISCAS '85 benchmark circuit
 */
void log_description(FILE *out_file, char *benchmark)
{
    int bench_char_length;

    bench_char_length = strlen(benchmark);

    fprintf(out_file, "******************************************************************");
    fprintf(out_file, "******************************************************************");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Version - 3.0.5                                                ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Copyright - Andreas Karatzas                                   ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Contact - andreas.karatzas@siu.edu                             ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Github - https://github.com/AndreasKaratzas/circuit_simulation.");
    fprintf(out_file, "git                                                              *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Abstract - This was implemented for course ECE 520 - VLSI Desig");
    fprintf(out_file, "n & Test Automation                                              *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* @Semester - Spring 2022                                         ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*                                                                 ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* This is the results file for the ISCAS '85 Benchmark `%s`. It", benchmark);

    while (10 - bench_char_length)
    {
        fprintf(out_file, " ");
        bench_char_length += 1;
    }

    fprintf(out_file, "                                                            *");
    fprintf(out_file, "\n");

    fprintf(out_file, "* follows a similar pattern with that of Atalanta tool. Example:  ");
    fprintf(out_file, "                                                                 *");
    fprintf(out_file, "\n");

    fprintf(out_file, "*+----------------------------------------------------------------");
    fprintf(out_file, "----------------------------------------------------------------+*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|<first fault node address> / <first fault value>:               ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|      0. <first test pattern> <correct value line> <faulty value");
    fprintf(out_file, " line> (<Fault detected/Fault NOT detected>)                    |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|      1. <second test pattern> <correct value line> <faulty valu");
    fprintf(out_file, "e line> (<Fault detected/Fault NOT detected>)                   |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|<second fault node address> / <second fault value>:             ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|      0. <first test pattern> <correct value line> <faulty value");
    fprintf(out_file, " line> (<Fault detected/Fault NOT detected>)                    |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|      1. <second test pattern> <correct value line> <faulty valu");
    fprintf(out_file, "e line> (<Fault detected/Fault NOT detected>)                   |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*|       .                                                        ");
    fprintf(out_file, "                                                                |*");
    fprintf(out_file, "\n");

    fprintf(out_file, "*+----------------------------------------------------------------");
    fprintf(out_file, "----------------------------------------------------------------+*");
    fprintf(out_file, "\n");

    fprintf(out_file, "******************************************************************");
    fprintf(out_file, "******************************************************************");
    fprintf(out_file, "\n");

    fprintf(out_file, "\n");
    fprintf(out_file, "\n");
}

/**
 * @brief Get the benchmark name from one of the command line options.
 *
 * @param benchmark     the benchmark name
 * @param sample_option the command line argument
 *
 * @note This function works ONLY for UNIX systems and benchmark filenames under 9 characters.
 *       The filepath can be of an arbitrary length, but the filename without its tail must
 *       be less than 9 characters.
 */
void get_benchmark_name(char *benchmark, const char *sample_option)
{
    int char_counter, checkpoint, offset;

    char_counter = 0;
    checkpoint = 0;
    bzero(benchmark, 10);

    while (sample_option[char_counter] != '.')
    {
        if (sample_option[char_counter] == '/')
        {
            checkpoint = char_counter;
        }

        char_counter += 1;
    }

    checkpoint += 1;
    offset = checkpoint;

    while (checkpoint < char_counter)
    {
        benchmark[checkpoint - offset] = sample_option[checkpoint];
        checkpoint += 1;
    }
}
