
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
    int num_of_faults = 0;
    char line[MAX_NUM_OF_CHARACTERS_IN_LINE];
    
    while( !feof(faults_file) )
    {
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, faults_file);
        
        if (strcmp(line, "") != 0 && strcmp(line, "\r\n") != 0 && strcmp(line, "\n") != 0 && strcmp(line, "\0") != 0)
        {
            sscanf(line, "%d/%d", &faults[num_of_faults].address, &faults[num_of_faults].fault);
            bzero(line, strlen(line));
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
 */
void inject_fault(NODE *graph, int address, int fault)
{
    graph[address].fault_value = fault;
}
