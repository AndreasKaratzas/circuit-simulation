
#include "graph.hpp"



void mask_mapper_error(int gate_type, int address)
{
    switch (gate_type)
    {
        case 2: printf("`map_and()`: mapper failed at node %d\n", address); exit(1);
        case 3: printf("`map_nand()`: mapper failed at node %d\n", address); exit(1);
        case 4: printf("`map_or()`: mapper failed at node %d\n", address); exit(1);
        case 5: printf("`map_nor()`: mapper failed at node %d\n", address); exit(1);
        case 6: printf("`map_xor()`: mapper failed at node %d\n", address); exit(1);
        case 7: printf("`map_xnor()`: mapper failed at node %d\n", address); exit(1);
        case 8: printf("`map_buffer()`: mapper failed at node %d\n", address); exit(1);
        case 9: printf("`map_not()`: mapper failed at node %d\n", address); exit(1);
        case 10:printf("`map_from()`: mapper failed at node %d\n", address); exit(1);
        default:printf("`mask_mapper_error()`: mapper fault mask failed at node %d with unknown gate type %d\n", address, gate_type); exit(1);
    }
}

int get_complement(int value)
{
    switch (value)
    {
        case 0: return (1);
        case 1: return (0);
        case 2: return (2);
    }
}

int map_and(NODE *graph, LIST *fanin, int address)
{
    int fanin_counter, accumulator, zero_flag;

    accumulator = 0;
    zero_flag = 1;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter]].fault_value == 3)
        {
            if (graph[graph[address].fanin[fanin_counter]].correct_value == 0)
            {
                zero_flag = 1;
            }
            else
            {
                accumulator += graph[graph[address].fanin[fanin_counter]].correct_value;
            }
        }
        else
        {
            if (graph[graph[address].fanin[fanin_counter]].fault_value == 0)
            {
                zero_flag = 1;
            }
            else
            {
                accumulator += graph[graph[address].fanin[fanin_counter]].fault_value;
            }
        }
    }

    if (accumulator % graph[address].num_of_fan_ins == 0)
    {
        return (1);
    }
    else if (accumulator / graph[address].num_of_fan_ins > 1)
    {
        if (zero_flag == 1)
        {
            return (0);
        }
        else
        {
            return (2);
        }
    }
    else
    {
        return (0);
    }
}

int map_nand(NODE *graph, LIST *fanin, int address)
{
    return (get_complement(map_and(graph, fanin, address)));
}

static inline int map_or(NODE *graph, LIST *fanin, int address)
{
    int fanin_counter, accumulator, dont_care_counter;

    accumulator = 0;
    dont_care_counter = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter]].fault_value == 3)
        {
            if (graph[graph[address].fanin[fanin_counter]].correct_value == 2)
            {
                dont_care_counter += 1;
            }
            accumulator += graph[graph[address].fanin[fanin_counter]].correct_value;
        }
        else
        {
            accumulator += graph[graph[address].fanin[fanin_counter]].fault_value;
        }
    }

    if (dont_care_counter > 0)
    {
        if (accumulator - (2 * dont_care_counter) > 0)
        {
            return (1);
        }
        else
        {
            return (2);
        }
    }
    else
    {
        if (accumulator > 0)
        {
            return (1);
        }
        else
        {
            return (0);
        }
    }
}

int map_nor(NODE *graph, LIST *fanin, int address)
{
    (get_complement(map_or(graph, fanin, address)));
}

int map_xor(NODE *graph, LIST *fanin, int address)
{
    int fanin_counter, accumulator, dont_care_flag;

    accumulator = 0;
    dont_care_flag = 0;

    for (fanin_counter = 0; fanin_counter < graph[address].num_of_fan_ins; fanin_counter += 1)
    {
        if (graph[graph[address].fanin[fanin_counter]].fault_value == 3)
        {
            if (graph[graph[address].fanin[fanin_counter]].correct_value == 2)
            {
                dont_care_flag = 1;
            }
            accumulator += graph[graph[address].fanin[fanin_counter]].correct_value;
        }
        else
        {
            accumulator += graph[graph[address].fanin[fanin_counter]].fault_value;
        }
    }

    accumulator = accumulator % 2;

    if (accumulator == 0)
    {
        if (dont_care_flag == 0)
        {
            return (1);
        }
        else
        {
            return (2);
        }
    }
    else
    {
        if (dont_care_flag == 1)
        {
            return (2);
        }
        else
        {
            return (0);
        }
    }
}

int map_xnor(NODE *graph, LIST *fanin, int address)
{
    return (get_complement(map_xor(graph, fanin, address)));
}

static inline int map_buffer(int input, int address)
{
    return input;
}

static inline int map_not(int input, int address)
{
    switch (input)
    {
        case 0: return 1;
        case 1: return 0;
        case 2: return 2;
        default: mask_mapper_error(9, address);
    }
}

static inline int map_from(int input, int address)
{
    return input;
}
