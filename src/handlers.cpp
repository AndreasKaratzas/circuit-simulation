
#include "graph.hpp"


void unknown_handler(int address)
{
    printf("`read_isc_file()`:\n\tError in input file (node %d)\n", address);
    exit(1);
}

void not_handler(FILE *isc_file, NODE *graph, int fanin, int address)
{
    int _branch_line, fanout_address; 

    for(_branch_line = 1; _branch_line <= fanin; _branch_line += 1)
    {
        fscanf(isc_file, "%d", &fanout_address);
        insert_element(&graph[address].fanin, fanout_address);
        insert_element(&graph[fanout_address].fanout, address);
    }

    fscanf(isc_file, "\n");
    return;
}

void from_handler(NODE *graph, char *from, int num_of_circuit_elements, int address)
{
    int _branch_line, fanout_address;

    for(_branch_line = num_of_circuit_elements; _branch_line > 0; _branch_line -= 1)
    {
        if(graph[_branch_line].type != 0)
        {
            if(strcmp(graph[_branch_line].name, from) == 0)
            {
                fanout_address = _branch_line;
                return;
            }
        }
    }

    insert_element(&graph[address].fanin, fanout_address);
    insert_element(&graph[fanout_address].fanout, address);
    return;
}
