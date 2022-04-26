
#include "graph.hpp"

/**
 * @brief Handles an unknown address type by logging an error and exiting.
 * 
 * @param address the node address in the graph
 */
void unknown_handler(int address)
{
    printf("`read_isc_file()`:\n\tError in input file (node %d)\n", address);
    exit(1);
}

/**
 * @brief Handles a `FROM` gate type. This function updates the `fanin`
 *        and `fanout` of each node in the given graph (circuit) with 
 *        respect to the given gate.
 * 
 * @param graph              the given circuit
 * @param name               the name of the `FROM` logic gate
 * @param current_node_count the current circuit node count 
 * @param address            the address corresponding to the `FROM` logic gate
 */
void from_handler(NODE *graph, char *name, int current_node_count, int address)
{
    int _branch_line, input_address;

    for(_branch_line = current_node_count; _branch_line > 0; _branch_line -= 1)
    {
        if(graph[_branch_line].type != 0)
        {
            if(strcmp(graph[_branch_line].name, name) == 0)
            {
                input_address = _branch_line;
                break;
            }
        }
    }

    insert_element(&graph[address].fanin, input_address);
    insert_element(&graph[input_address].fanout, address);
    return;
}

/**
 * @brief Handles gates with a single primary input.
 *        This function updates the `fanin` and `fanout`
 *        of each node in the given graph (circuit) with
 *        respect to the given gate.
 * 
 * @param isc_file the given `ISC` file
 * @param graph    the (at that time) compiled graph structured
 * @param address  the given circuit node address
 */
void single_input_gate_handler(FILE *isc_file, NODE *graph, int address)
{
    int input_address; 

    fscanf(isc_file, "%d\n", &input_address);
    insert_element(&graph[address].fanin, input_address);
    insert_element(&graph[input_address].fanout, address);

    return;
}

/**
 * @brief Handles gates with two primary inputs.
 *        This function updates the `fanin` and `fanout`
 *        of each node in the given graph (circuit) with
 *        respect to the given gate.
 * 
 * @param isc_file the given `ISC` file
 * @param graph    the (at that time) compiled graph structured
 * @param address  the given circuit node address
 */
void two_input_gate_handler(FILE *isc_file, NODE *graph, int address)
{
    int input_address_a, input_address_b; 

    fscanf(isc_file, "%d %d\n", &input_address_a, &input_address_b);
    
    insert_element(&graph[address].fanin, input_address_a);
    insert_element(&graph[input_address_a].fanout, address);

    insert_element(&graph[address].fanin, input_address_b);
    insert_element(&graph[input_address_b].fanout, address);

    return;
}
