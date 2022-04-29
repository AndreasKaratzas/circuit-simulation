
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

    for (_branch_line = current_node_count; _branch_line > 0; _branch_line -= 1)
    {
        if (graph[_branch_line].type != 0)
        {
            if (strcmp(graph[_branch_line].name, name) == 0)
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
 * @brief Handles gates.
 *        This function updates the `fanin` and `fanout`
 *        of each node in the given graph (circuit) with
 *        respect to the given gate.
 *
 * @param isc_file        the given `ISC` file
 * @param graph           the (at that time) compiled graph structured
 * @param fanin           the fanin of the gate
 * @param address         the given circuit node address
 * @param node_dictionary a dictionary that maps the original node address to the compressed one
 */
void gate_handler(FILE *isc_file, NODE *graph, int fanin, int address, int *node_dictionary)
{
    int _branch_line, input_address;

    for (_branch_line = 0; _branch_line < fanin; _branch_line += 1)
    {
        fscanf(isc_file, "%d", &input_address);
        input_address = node_dictionary[input_address];
        insert_element(&graph[address].fanin, input_address);
        insert_element(&graph[input_address].fanout, address);
    }

    fscanf(isc_file, "\n");

    return;
}
