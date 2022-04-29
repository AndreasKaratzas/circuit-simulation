
#include "graph.hpp"

/**
 * @brief This function takes a primary input node and properly initializes it.
 *
 * @param graph       the graph representing the running circuit
 * @param address     the address of the primary input node inside the graph
 * @param vectors     the test vectors strored in a `PATTERN` structure
 * @param pattern_idx the index of the pattern that is being applied
 */
void apply_input(NODE *graph, int address, PATTERN *vectors, int pattern_idx)
{
    graph[address].correct_value = vectors[pattern_idx].primary_input_vec[vectors[pattern_idx].current_primary_input];
    graph[address].fault_value = vectors[pattern_idx].primary_input_vec[vectors[pattern_idx].current_primary_input];
    vectors[pattern_idx].current_primary_input += 1;
}

/**
 * @brief This function is the mapper driver. From here, every node is mapped to its
 *        corresponding gate. Inside each gate mapper, the circuit is updated according
 *        to the injected faults and the inputs applied.
 *
 * @param graph       the graph representing the running circuit
 * @param address     the address of the primary input node inside the graph
 * @param vectors     the test vectors strored in a `PATTERN` structure
 * @param pattern_idx the index of the pattern that is being applied
 */
void simulate_node(NODE *graph, int address, PATTERN *vectors, int pattern_idx)
{
    switch (graph[address].type)
    {
        case 1: apply_input(graph, address, vectors, pattern_idx); break;
        case 2: map_and(graph, address); break;
        case 3: map_nand(graph, address); break;
        case 4: map_or(graph, address); break;
        case 5: map_nor(graph, address); break;
        case 6: map_xor(graph, address); break;
        case 7: map_xnor(graph, address); break;
        case 8: map_buffer(graph, address); break;
        case 9: map_not(graph, address); break;
        case 10:map_from(graph, address); break;
    }
}

/**
 * @brief This function simulates all {fault, test vector} combinations.
 *
 * @param graph           the graph representing the running circuit
 * @param vectors         the test vectors strored in a `PATTERN` structure
 * @param faults          the faults which are to be injected
 * @param logs            the log structure which will be later used to output the simulation results
 * @param num_of_nodes    the total number of nodes
 * @param num_of_patterns the total number of test vectors
 * @param num_of_faults   the total number of faults under which the circuit was tested
 */
void simulate_circuit(NODE *graph, PATTERN *vectors, FAULT *faults, LOGGER *logs, int num_of_nodes, int num_of_patterns, int num_of_faults, int *node_dictionary)
{
    int address, pattern_idx, fault_idx;

    printf("INDEX | INPUT VECTOR | CORRECT OUTPUT | FAULT INJECTED | FAULTY OUTPUT | FAULT DETECTED\n");

    for (fault_idx = 0; fault_idx < num_of_faults; fault_idx += 1)
    {
        reset_pattern(vectors, num_of_patterns);
        inject_fault(graph, node_dictionary[faults[fault_idx].address], faults[fault_idx].fault);

        for (pattern_idx = 0; pattern_idx < num_of_patterns; pattern_idx += 1)
        {
            reset_circuit(graph, num_of_nodes);

            for (address = 0; address < num_of_nodes; address += 1)
            {
                simulate_node(graph, address, vectors, pattern_idx);
            }
            
            register_simulation(graph, num_of_nodes, vectors, pattern_idx, node_dictionary[faults[fault_idx].address], faults[fault_idx].fault, logs, num_of_patterns);
        }
    }
}

/**
 * @brief This function resets the node registers used during every {fault, test vector}
 *        simulation.
 *
 * @param graph        the graph representing the running circuit
 * @param num_of_nodes the total number of nodes
 */
void reset_circuit(NODE *graph, int num_of_nodes)
{
    int node_count;

    for (node_count = 0; node_count < num_of_nodes; node_count += 1)
    {
        graph[node_count].correct_value = 3;
        graph[node_count].fault_value = 3;
    }
}

/**
 * @brief This function resets the test vector registers used during every {fault, test vector}
 *        simulation.
 *
 * @param vectors         the test vectors strored in a `PATTERN` structure
 * @param num_of_patterns the total number of test vectors
 */
void reset_pattern(PATTERN *vectors, int num_of_patterns)
{
    int pattern_idx;

    for (pattern_idx = 0; pattern_idx < num_of_patterns; pattern_idx += 1)
    {
        vectors[pattern_idx].current_primary_input = 0;
    }
}
