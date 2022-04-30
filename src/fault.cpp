
#include "graph.hpp"


/**
 * @brief Parses a `.faults` file.
 *
 * @param faults_file the given `.faults` file to parse
 * @param faults      the result faults instantiated after processing the `.faults` file
 * @return int        the total fault count
 */
int read_faults_file(FILE *faults_file, FAULT *faults)
{
    int char_counter;
    int num_of_faults;
    int num_of_characters_in_fault_file;
    char MAX_NUM_OF_CHARACTERS_IN_LINE_char;
    char *line;
    char *node_address;

    num_of_faults = 0;
    MAX_NUM_OF_CHARACTERS_IN_LINE_char = MAX_NUM_OF_CHARACTERS_IN_LINE + '0';

    // inject some redundancy in case of extra whitespaces and other unwanted characters
    num_of_characters_in_fault_file = strlen(MAX_NUM_OF_CHARACTERS_IN_LINE_char) + 10;
    
    line = (char*) malloc(num_of_characters_in_fault_file * sizeof (char));
    node_address = (char*) malloc(num_of_characters_in_fault_file * sizeof (char));

    while( !feof(faults_file) )
    {
        bzero(line, num_of_characters_in_fault_file);
        bzero(node_address, num_of_characters_in_fault_file);

        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, faults_file);

        if (strlen(line) > 0)
        {
            for (char_counter = 0; strcmp(line[char_counter], '/') != 0, char_counter += 1)
            {
                node_address[char_counter] = line[char_counter];
            }

            while(strcmp(line[char_counter], '/') == 0 or strcmp(line[char_counter], ' ') == 0)
            {
                char_counter += 1;
            }

            faults[num_of_faults].address = atoi(node_address[char_counter])
            faults[num_of_faults].fault = atoi(line[char_counter]);
            
            num_of_faults += 1;
        }
    }

    return (num_of_faults);
}

/**
 * @brief Prints all elements of a faults entity of type FAULT structure.
 *        The use case of this function is after parsing an FAULTS file
 *        using `read_faults_file()`.
 *
 * @param faults        the given faults entity
 * @param num_of_faults the number of faults returned by `read_faults_file()`
 */
void print_faults(FAULT *faults, int num_of_faults)
{
    int fault_count;

    printf("FAULTS:\n");
    for (fault_count = 0; fault_count < num_of_faults; fault_count += 1)
    {
        printf("\tFault [%3d]:\n\t\tAddress: %6d stuck-at %2d\n", fault_count + 1, faults[fault_count].address, faults[fault_count].fault);
    }

    return;
}

/**
 * @brief Injects the desired fault in the circuit.
 *
 * @param graph   the graph that represents a circuit
 * @param address the address of the node to be injected with the fault
 * @param fault   the desired (stuck-at) fault value
 * @param verbose this parameter can either take value 0 or 1 indicating the preference of the user to regularly log simulation information to the terminal
 */
void inject_fault(NODE *graph, int address, int fault, int verbose)
{
    if (verbose == 1)
    {
        printf("Injected fault of type stuck-at %d at node %s\n", fault, graph[address].name);
    }

    graph[address].fault_value = fault;
}
