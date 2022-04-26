
#include "graph.hpp"

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

    if ((p = (LIST *)malloc(sizeof(LIST))) == NULL)
    {
        printf("LIST: Out of memory\n");
        exit(1);
    }
    else
    {
        p->id = x;
        p->next = NULL;

        if(*l == NULL)
        {
            *l = p;
            return;
        }

        tl = NULL;
        tl = *l;

        while(tl != NULL)
        {
            if(tl->id == x)
            {
                break;
            }

            if(tl->next == NULL)
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
 * @param l the given LIST structure
 */
void print_list(LIST *l)
{
    LIST *temp = NULL;

    temp = l;
    while(temp != NULL)
    {
        printf("%d ", temp->id);
        temp = temp->next;
    }

    return;
}

/**
 * @brief Deletes all elements found in a LIST structure.
 *
 * @param l the given LIST structure
 */
void delete_element(LIST **l)
{
    LIST *temp = NULL;

    if(*l == NULL)
    {
        return;
    }

    temp=(*l);

    while((*l) != NULL)
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
int read_isc_file(FILE *isc_file, NODE *graph)
{
    char name[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char type[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char fanout_str[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char fanin_str[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char line[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char from[MAX_NUM_OF_CHARACTERS_IN_LINE];

    int node_count, address, fanout, fanin, num_of_circuit_elements, _branch_line, fanout_address;

    num_of_circuit_elements = 0;

    // initialize all nodes in graph structure
    for(node_count = 0; node_count < MAX_NUM_OF_NODES; node_count += 1)
    {
        initialize_circuit(graph, node_count);
    }

    // skip the comment lines
    do {
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, isc_file);
    } while(line[0] == '*');

    // read line by line
    while( !feof(isc_file) )
    {

        // initialize temporary strings
        bzero(name, strlen(name));
        bzero(type, strlen(type));
        bzero(fanout_str, strlen(fanout_str));
        bzero(fanin_str, strlen(fanin_str));
        bzero(from, strlen(from));

        // break line into data
        sscanf(line, "%d %s %s %s %s", &address, name, type, fanout_str, fanin_str);

        // fill in the Type
        strcpy(graph[address].name, name);
        graph[address].type = map_logic_gate(type);

        // fill in fanin and fanout numbers
        if(graph[address].type != FROM)
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

        if(address > num_of_circuit_elements)
        {
            num_of_circuit_elements = address;
        }

        graph[address].num_of_fan_outs = fanout;
        graph[address].num_of_fan_ins = fanin;

        if(fanout == 0)
        {
            graph[address].primary_output = 1;
        }

        // create fanin and fanout lists
        switch (graph[address].type)
        {
            case 0     :    printf("`read_isc_file()`:\n\tError in input file (node %d)\n", address); 
                            exit(1);

            case INPT  :    break;

            case AND   :

            case NAND  :

            case OR    :

            case NOR   :

            case XOR   :

            case XNOR  :

            case BUFF  :

            case NOT   :    for(_branch_line = 1; _branch_line <= fanin; _branch_line += 1)
                            {
                                fscanf(isc_file, "%d", &fanout_address);
                                insert_element(&graph[address].fanin, fanout_address);
                                insert_element(&graph[fanout_address].fanout, address);
                            }

                            fscanf(isc_file, "\n");

                            break;

            case FROM  :    for(_branch_line = num_of_circuit_elements; _branch_line > 0; _branch_line -= 1)
                            {
                                if(graph[_branch_line].type != 0)
                                {
                                    if(strcmp(graph[_branch_line].name, from) == 0)
                                    {
                                        fanout_address = _branch_line;
                                        break;
                                    }
                                }
                            }

                            insert_element(&graph[address].fanin, fanout_address);
                            insert_element(&graph[fanout_address].fanout, address);

                            break;
        }

        bzero(line, strlen(line));
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, isc_file);
    }

    return (num_of_circuit_elements);
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
    graph[address].marker = 0;

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
 *        using `ReadIsc()`.
 *
 * @param graph        the given graph entity
 * @param num_of_nodes the index of the last node generated in the new graph entity.
 *                     This is returned by `ReadIsc()`
 */
void print_circuit(NODE *graph, int num_of_nodes)
{
    LIST *temp;
    int  address;
    char title[] = "| ADDRESS |       NAME   |  TYPE | PRIMARY OUTPUT # | INPUT # | OUTPUT # | CORRECT VALUE | FAULT VALUE | MARKER |                FANIN |              FANOUT |";
    char msg[512];

    memset(msg, '-', strlen(title) - 1);
    msg[0] = '+';    
    msg[strlen(title) - 1] = '+';
    msg[strlen(title)] = '\0';

    printf("%s\n", msg);
    printf("%s\n", title);
    printf("%s\n", msg);

    for(address = 0; address <= num_of_nodes; address += 1)
    {
        if(graph[address].type != 0)
        {
            printf("| %7d | %10s\t | %4d  | %16d | %7d | %8d | ", 
                address, 
                graph[address].name, 
                graph[address].type, 
                graph[address].primary_output, 
                graph[address].num_of_fan_ins, 
                graph[address].num_of_fan_outs);

            printf("%13d | %11d | %6d |", 
                graph[address].correct_value, 
                graph[address].fault_value, 
                graph[address].marker);

            temp = NULL;
            temp = graph[address].fanin;

            if(temp != NULL)
            {
                print_list(temp);
            }

            printf(" \t | ");

            temp = NULL;
            temp = graph[address].fanout;

            if(temp != NULL)
            {
                print_list(temp);
            }

            printf(" |\n");
        }
    }
    
    printf("%s\n", msg);

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

    for(address = 0; address < n_elements; address += 1)
    {
        graph[address].type = 0;
        graph[address].num_of_fan_ins = 0;
        graph[address].num_of_fan_outs = 0;
        graph[address].primary_output = 0;
        graph[address].marker = 0;
        graph[address].correct_value = 0;
        graph[address].fault_value = 0;

        if(graph[address].type != 0)
        {
            bzero(graph[address].name, MAX_NODE_ALIAS_LEN);

            if(graph[address].fanin != NULL)
            {
                delete_element(&graph[address].fanin);
                graph[address].fanin = NULL;
            }

            if(graph[address].fanout != NULL)
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
 * @param vec_file the given VEC file
 * @param vector   the result vector PATTERN structure entity
 * @return int     the total primary inputs count
 */
int read_vec_file(FILE *vec_file, PATTERN *vector)
{
    int num_of_ins;
    char token[MAX_NUM_OF_PRIMARY_INPUTS];

    num_of_ins = 0;

    while( !feof(vec_file) )
    {
        bzero(token, MAX_NUM_OF_PRIMARY_INPUTS);
        fgets(token, MAX_NUM_OF_PRIMARY_INPUTS, vec_file);

        if(*token != '\0')
        {
            bzero(vector[num_of_ins].primary_input_vec, MAX_NUM_OF_PRIMARY_INPUTS);
            strcpy(vector[num_of_ins].primary_input_vec, token);
            num_of_ins += 1;
        }
    }

    return (num_of_ins);
}
