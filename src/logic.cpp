
#include "graph.hpp"


/**
 * @brief This is a utility that returns the compelment
 *        of a given three value state as per the rules
 *        of three value Boolean Algebra.
 *
 * @param input the given state
 * @return int  the complementary of the given state
 */
int complementary(int input)
{
    switch (input)
    {
        case 0: return (1);
        case 1: return (0);
        case 2: return (2);
    }
}

/**
 * @brief This function computes the result of an AND logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the AND
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the AND gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the AND gate.
 *
 * @note This function uses the `correct_value` attribute of each
 *       node in the graph. In other words, it is used for pattern
 *       simulation.
 */
int compute_and_correct(NODE *graph, int address)
{
    int fanin_counter, result, zero_flag, dont_care_flag;

    zero_flag = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 0)
        {
            zero_flag = 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (zero_flag == 1)
    {
        result = 0;
    }
    else if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        result = 1;
    }

    return (result);
}

/**
 * @brief This function computes the result of an AND logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the AND
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the AND gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the AND gate.
 *
 * @note This function uses the `fault_value` attribute of each
 *       node in the graph. In other words, it is used for fault
 *       simulation.
 */
int compute_and_fault(NODE *graph, int address)
{
    int fanin_counter, result, zero_flag, dont_care_flag;

    zero_flag = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 0)
        {
            zero_flag = 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (zero_flag == 1)
    {
        result = 0;
    }
    else if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        result = 1;
    }

    return (result);
}

/**
 * @brief This function computesthe result of an OR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the OR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the OR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the OR gate.
 *
 * @note This function uses the `correct_value` attribute of each
 *       node in the graph. In other words, it is used for pattern
 *       simulation.
 */
int compute_or_correct(NODE *graph, int address)
{
    int fanin_counter, result, one_flag, dont_care_flag;

    one_flag = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 1)
        {
            one_flag = 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (one_flag == 1)
    {
        result = 1;
    }
    else if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        result = 0;
    }

    return (result);
}

/**
 * @brief This function computesthe result of an OR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the OR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the OR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the OR gate.
 *
 * @note This function uses the `fault_value` attribute of each
 *       node in the graph. In other words, it is used for fault
 *       simulation.
 */
int compute_or_fault(NODE *graph, int address)
{
    int fanin_counter, result, one_flag, dont_care_flag;

    one_flag = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 1)
        {
            one_flag = 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (one_flag == 1)
    {
        result = 1;
    }
    else if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        result = 0;
    }

    return (result);
}

/**
 * @brief This function computesthe result of a XOR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the XOR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the XOR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the XOR gate.
 *
 * @note This function uses the `correct_value` attribute of each
 *       node in the graph. In other words, it is used for pattern
 *       simulation.
 */
int compute_xor_correct(NODE *graph, int address)
{
    int fanin_counter, result, one_counter, dont_care_flag;

    one_counter = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 1)
        {
            one_counter += 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].correct_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        if (one_counter % 2 == 0)
        {
            if (one_counter > 0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            result = 0;
        }
    }

    return (result);
}

/**
 * @brief This function computesthe result of a XOR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the XOR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the XOR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 * @return int    the result of the XOR gate.
 *
 * @note This function uses the `fault_value` attribute of each
 *       node in the graph. In other words, it is used for fault
 *       simulation.
 */
int compute_xor_fault(NODE *graph, int address)
{
    int fanin_counter, result, one_counter, dont_care_flag;

    one_counter = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 1)
        {
            one_counter += 1;
        }
        if (graph[graph[address].fanin[fanin_counter].id].fault_value == 2)
        {
            dont_care_flag = 1;
        }
    }

    if (dont_care_flag == 1)
    {
        result = 2;
    }
    else
    {
        if (one_counter % 2 == 0)
        {
            if (one_counter > 0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            result = 0;
        }
    }

    return (result);
}

/**
 * @brief This is a mapper function for the NOT logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the whole circuit by reference is to check
 *                the fanin nodes for any injected faults.
 * @param address the address of the running node.
 */
void map_not(NODE *graph, int address)
{
    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = complementary(graph[graph[address].fanin[0].id].fault_value);
    }

    graph[address].correct_value = complementary(graph[graph[address].fanin[0].id].correct_value);
}

/**
 * @brief This is a mapper function for the AND logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the AND
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the AND gate
 *                is completely dynamic.
 * @param address the address of the running node.
 */
void map_and(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_and_correct(graph, address);
    fault_val = compute_and_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = fault_val;
    }

    graph[address].correct_value = correct_val;
}

/**
 * @brief This is a mapper function for the NAND logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the NAND
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the NAND gate
 *                is completely dynamic.
 * @param address the address of the running node.
 *
 * @note  The logic behind this module is to use the already coded AND
 *        function and compute its complementary value as described by
 *        the corresponding table in the `docs` directory.
 */
void map_nand(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_and_correct(graph, address);
    fault_val = compute_and_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = complementary(fault_val);
    }

    graph[address].correct_value = complementary(correct_val);
}

/**
 * @brief This is a mapper function for the OR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the OR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the OR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 */
void map_or(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_or_correct(graph, address);
    fault_val = compute_or_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = fault_val;
    }

    graph[address].correct_value = correct_val;
}

/**
 * @brief This is a mapper function for the NOR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the NOR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the NOR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 *
 * @note  The logic behind this module is to use the already coded OR
 *        function and compute its complementary value as described by
 *        the corresponding table in the `docs` directory.
 */
void map_nor(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_or_correct(graph, address);
    fault_val = compute_or_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = complementary(fault_val);
    }

    graph[address].correct_value = complementary(correct_val);
}

/**
 * @brief This is a mapper function for the XOR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the XOR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the XOR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 */
void map_xor(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_xor_correct(graph, address);
    fault_val = compute_xor_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = fault_val;
    }

    graph[address].correct_value = correct_val;
}

/**
 * @brief This is a mapper function for the XNOR logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the circuit by reference, and not just some
 *                specific gates is that the input of the XNOR
 *                gate is dynamic in our project. That means
 *                that there can be an arbitrary amount of
 *                inputs with which the given gate is connected.
 *                In other words, the `fanin` of the XNOR gate
 *                is completely dynamic.
 * @param address the address of the running node.
 *
 * @note  The logic behind this module is to use the already coded XOR
 *        function and compute its complementary value as described by
 *        the corresponding table in the `docs` directory.
 */
void map_xnor(NODE *graph, int address)
{
    int correct_val, fault_val;

    correct_val = compute_xor_correct(graph, address);
    fault_val = compute_xor_fault(graph, address);

    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = complementary(fault_val);
    }

    graph[address].correct_value = complementary(correct_val);
}

/**
 * @brief This is a mapper function for the BUFFER logic gate.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic.
 *
 * @param graph   the current circuit. The reason for passing
 *                the whole circuit by reference is to check
 *                the fanin nodes for any injected faults.
 * @param address the address of the running node.
 */
void map_buffer(NODE *graph, int address)
{
    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = graph[graph[address].fanin[0].id].fault_value;
    }

    graph[address].correct_value = graph[graph[address].fanin[0].id].correct_value;
}

/**
 * @brief This is a mapper function for the FROM module.
 *        The architecture of this module follows the propagation
 *        table protocol located at the `docs`directory. This
 *        table supports a three value logic. The FROM module is
 *        another version of the BUFFER. However, it actually
 *        covers the connections and is replacing the wiring.
 *
 * @param graph   the current circuit. The reason for passing
 *                the whole circuit by reference is to check
 *                the fanin nodes for any injected faults.
 * @param address the address of the running node.
 */
void map_from(NODE *graph, int address)
{
    if (graph[address].fault_value == 3)
    {
        graph[address].fault_value = graph[graph[address].fanin[0].id].fault_value;
    }

    graph[address].correct_value = graph[graph[address].fanin[0].id].correct_value;
}
