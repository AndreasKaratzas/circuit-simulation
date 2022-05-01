
#include "graph.h"

/**
 * @brief Inserts an element `x` at the enf of a LIST structure.
 *        If `x` already exists in the list, then it is __NOT__ added.
 *
 * @param l the given LIST structure
 * @param x the given element of type INT
 */
void insert_element(LIST **l, int x)
{
    LIST *p, *tl;

    if ( ( p = (LIST *)malloc(sizeof(LIST)) ) == NULL )
    {
        printf("LIST: Out of memory\n");
        exit(1);
    }
    else
    {
        p->id = x;
        p->next = NULL;

        if (*l == NULL)
        {
            *l = p;
            return;
        }

        tl = NULL;
        tl = *l;

        while (tl != NULL)
        {
            if (tl->id == x)
            {
                break;
            }

            if (tl->next == NULL)
            {
                tl->next = p;
            }

            tl = tl->next;
        }
    }

    return;
}

/**
 * @brief Prints all elements of a LIST structure.
 *
 * @param l    the given LIST structure
 * @return int the length of the string printed
 */
int print_list(LIST *l)
{
    LIST *temp = NULL;

    char str[10];
    int  str_len;

    temp = l;
    str_len = 0;
    while (temp != NULL)
    {
        sprintf(str, "%d", temp->id);
        str_len = str_len + strlen(str) + 1;
        printf(" %s", str);
        temp = temp->next;
    }

    printf(" ");

    return (str_len + 1);
}

/**
 * @brief Deletes all elements found in a LIST structure.
 *
 * @param l the given LIST structure
 */
void delete_element(LIST **l)
{
    LIST *temp = NULL;

    if (*l == NULL)
    {
        return;
    }

    temp=(*l);

    while ((*l) != NULL)
    {
        temp = temp->next;
        free(*l);
        (*l) = temp;
    }
    (*l) = NULL;

    return;
}


/**
 * @brief Parses an ISC file into a graph of type NODE structure.
 *
 * @param isc_file  the given ISC file
 * @param graph     the result graph NODE structure entity
 * @return int      the index of the last node generated in the new graph entity
 */
int read_isc_file(FILE *isc_file, NODE *graph, int *node_dictionary)
{
    char name[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char type[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char fanout_str[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char fanin_str[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char line[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char from[MAX_NUM_OF_CHARACTERS_IN_LINE];

    int node_count, address, fanout, fanin, _branch_line, offset;

    offset = 0;

    // initialize all nodes in graph structure
    for (node_count = 0; node_count < MAX_NUM_OF_NODES; node_count += 1)
    {
        initialize_circuit(graph, node_count);
    }

    // initialize the node dictionary
    for (node_count = 0; node_count < MAX_NUM_OF_NODES; node_count += 1)
    {
        node_dictionary[node_count] = -1;
    }

    // reset node count
    node_count = 0;

    // skip the comment lines
    do {
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, isc_file);
    } while (line[0] == '*');

    // read line by line
    while ( !feof(isc_file) )
    {

        // initialize temporary strings
        bzero(name, strlen(name));
        bzero(type, strlen(type));
        bzero(fanout_str, strlen(fanout_str));
        bzero(fanin_str, strlen(fanin_str));
        bzero(from, strlen(from));

        // break line into data
        sscanf(line, "%d %s %s %s %s", &address, name, type, fanout_str, fanin_str);

        if (address != node_count)
        {
            offset = node_count - address;
        }

        // this array is used to map the nodes in the `fanin` column of the `isc` file
        node_dictionary[address] = address + offset;

        // update address of node with respect to the offset
        address += offset;

        // fill in the Type
        strcpy(graph[address].name, name);
        graph[address].type = map_logic_gate(type);

        // fill in fanin and fanout numbers
        if (graph[address].type != FROM)
        {
            fanout = atoi(fanout_str);
            fanin = atoi(fanin_str);
        }
        else
        {
            fanin = 1;
            fanout = 1;
            strcpy(from, fanout_str);
        }

        graph[address].num_of_fan_outs = fanout;
        graph[address].num_of_fan_ins = fanin;

        if (fanout == 0)
        {
            graph[address].primary_output = 1;
        }

        // create fanin and fanout lists
        switch (graph[address].type)
        {
            case 0    : unknown_handler(address);
            case INPT : break;
            case AND  : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case NAND : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case OR   : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case NOR  : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case XOR  : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case XNOR : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case BUFF : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case NOT  : gate_handler(isc_file, graph, fanin, address, node_dictionary); break;
            case FROM : from_handler(graph, from, address); break;
        }

        bzero(line, strlen(line));
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, isc_file);

        node_count += 1;
    }

    return (node_count);
}

/**
 * @brief Initializes a particular node of a given graph entity of type NODE structure.
 *
 * @param graph   the given NODE structure
 * @param address the address of the particular node entity
 */
void initialize_circuit(NODE *graph, int address)
{
    bzero(graph[address].name, MAX_NODE_ALIAS_LEN);

    graph[address].type = 0;
    graph[address].num_of_fan_ins = 0;
    graph[address].num_of_fan_outs = 0;
    graph[address].primary_output = 0;

    graph[address].correct_value = 3;
    graph[address].fault_value = 3;

    graph[address].fanin = NULL;
    graph[address].fanout = NULL;

    return;
}

/**
 * @brief Maps the string arguments to classes of type int.
 *        Those classes representr logic gates.
 *
 * @param type the given string argument
 * @return int the corresponding logic gate ID
 */
int map_logic_gate(char *type)
{
    if ( (strcmp(type, "inpt") == 0) || (strcmp(type, "INPT") == 0) )
    {
        return (1);
    }
    else if ( (strcmp(type, "and") == 0) || (strcmp(type, "AND") == 0) )
    {
        return (2);
    }
    else if ( (strcmp(type, "nand") == 0) || (strcmp(type, "NAND") == 0) )
    {
        return (3);
    }
    else if ( (strcmp(type, "or") == 0) || (strcmp(type, "OR") == 0) )
    {
        return (4);
    }
    else if ( (strcmp(type, "nor") == 0) || (strcmp(type, "NOR") == 0) )
    {
        return (5);
    }
    else if ( (strcmp(type, "xor") == 0) || (strcmp(type, "XOR") == 0) )
    {
        return (6);
    }
    else if ( (strcmp(type, "xnor") == 0) || (strcmp(type, "XNOR") == 0))
    {
        return (7);
    }
    else if ( (strcmp(type, "buff") == 0) || (strcmp(type, "BUFF") == 0) )
    {
        return (8);
    }
    else if ( (strcmp(type, "not") == 0) || (strcmp(type, "NOT") == 0) )
    {
        return (9);
    }
    else if ( (strcmp(type, "from") == 0) || (strcmp(type, "FROM") == 0) )
    {
        return (10);
    }
    else
    {
        return (0);
    }
}

/**
 * @brief Prints all members of a graph entity of type NODE structure.
 *        The use case of this function is after parsing an ISC file
 *        using `read_isc_file()`.
 *
 * @param graph        the given graph entity
 * @param num_of_nodes the index of the last node generated in the new graph entity.
 *                     This is returned by `read_isc_file()`
 */
void print_circuit(NODE *graph, int num_of_nodes)
{
    LIST *temp;
    int  address, _str_len;
    char title[] = "| ADDRESS |        NAME |  TYPE | PRIMARY OUTPUT # | INPUT # | OUTPUT # | CORRECT VALUE | FAULT VALUE |                           FANIN |                          FANOUT |";
    char splitter[512];

    store_repeat(splitter, '-', strlen(title) - 1);
    splitter[0] = '+';
    splitter[strlen(title) - 1] = '+';
    splitter[strlen(title)] = '\0';

    printf("%s\n", splitter);
    printf("%s\n", title);
    printf("%s\n", splitter);

    for (address = 0; address < num_of_nodes; address += 1)
    {
        if (graph[address].type != 0)
        {
            printf("| %7d | %11s | %4d  | %16d | %7d | %8d | ",
                address,
                graph[address].name,
                graph[address].type,
                graph[address].primary_output,
                graph[address].num_of_fan_ins,
                graph[address].num_of_fan_outs);

            printf("%13d | %11d |",
                graph[address].correct_value,
                graph[address].fault_value);

            temp = NULL;
            temp = graph[address].fanin;

            if (temp != NULL)
            {
                _str_len = print_list(temp);
            }
            else
            {
                _str_len = 0;
            }

            repeat(' ', 32 - _str_len);
            printf(" |");

            temp = NULL;
            temp = graph[address].fanout;

            if (temp != NULL)
            {
                _str_len = print_list(temp);
            }
            else
            {
                _str_len = 0;
            }

            repeat(' ', 32 - _str_len);
            printf(" |\n");
        }
        else
        {
            printf("CRITICAL ERROR: `print_circuit()` parsed node of type `0` [node.address: %d]\n", address);
        }
    }

    printf("%s\n", splitter);

    return;
}

/**
 * @brief Deletes a graph entity of type NODE structure.
 *
 * @param graph      the given graph entity
 * @param n_elements the number of elements in the given graph entity
 */
void delete_circuit(NODE *graph, int n_elements)
{
    int address;

    for (address = 0; address < n_elements; address += 1)
    {
        graph[address].type = 0;
        graph[address].num_of_fan_ins = 0;
        graph[address].num_of_fan_outs = 0;
        graph[address].primary_output = 0;
        graph[address].correct_value = 0;
        graph[address].fault_value = 0;

        if (graph[address].type != 0)
        {
            bzero(graph[address].name, MAX_NODE_ALIAS_LEN);

            if (graph[address].fanin != NULL)
            {
                delete_element(&graph[address].fanin);
                graph[address].fanin = NULL;
            }

            if (graph[address].fanout != NULL)
            {
                delete_element(&graph[address].fanout);
                graph[address].fanout = NULL;
            }
        }
    }

    return;
}

/**
 * @brief Parses a VEC file into a vector of type PATTERN structure.
 *
 * @param vec_file   the given VEC file
 * @param vector_bak the result vector PATTERN structure entity
 * @return int       the total primary inputs count
 *
 * @deprecated This was the original version of `read_vec_file()`.
 */
int read_vec_file_bak(FILE *vec_file, PATTERN_bak *vector_bak)
{
    int num_of_ins;
    char token[MAX_NUM_OF_PRIMARY_INPUTS];

    num_of_ins = 0;

    while ( !feof(vec_file) )
    {
        bzero(token, MAX_NUM_OF_PRIMARY_INPUTS);
        fgets(token, MAX_NUM_OF_PRIMARY_INPUTS, vec_file);

        if (*token != '\0')
        {
            bzero(vector_bak[num_of_ins].primary_input_vec, MAX_NUM_OF_PRIMARY_INPUTS);
            strcpy(vector_bak[num_of_ins].primary_input_vec, token);
            num_of_ins += 1;
        }
    }

    return (num_of_ins);
}
