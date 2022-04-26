
#include "graph.hpp"


void unknown_handler(int address)
{
    printf("`read_isc_file()`:\n\tError in input file (node %d)\n", address);
    exit(1);
}

void not_handler(FILE *isc_file, NODE *graph, int fanin, int address)
{
    int _branch_line, input_address; 

    for(_branch_line = 1; _branch_line <= fanin; _branch_line += 1)
    {
        fscanf(isc_file, "%d", &input_address);
        insert_element(&graph[address].fanin, input_address);
        insert_element(&graph[input_address].fanout, address);
    }

    fscanf(isc_file, "\n");
    return;
}

void from_handler(NODE *graph, char *from, int current_node_count, int address)
{
    int _branch_line, input_address;

    for(_branch_line = current_node_count; _branch_line > 0; _branch_line -= 1)
    {
        if(graph[_branch_line].type != 0)
        {
            if(strcmp(graph[_branch_line].name, from) == 0)
            {
                input_address = _branch_line;
                return;
            }
        }
    }

    insert_element(&graph[address].fanin, input_address);
    insert_element(&graph[input_address].fanout, address);
    return;
}
