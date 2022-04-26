
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
    char type[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char from[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char str1[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char str2[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char name[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char line[MAX_NUM_OF_CHARACTERS_IN_LINE];

    int  node_count, address, fid, Fin, fout, mid = 0;

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
        bzero(noty, strlen(noty));
        bzero(from, strlen(from));
        bzero(str1, strlen(str1));
        bzero(str2, strlen(str2));
        bzero(name, strlen(name));

        // break line into data
        sscanf(line, "%d %s %s %s %s", &address, name, type, fanout, fanin);

        // fill in the Type
        strcpy(graph[id].Name,name);
        graph[id].Type = map_logic_gate(noty);

        // fill in fanin and fanout numbers
        if(graph[id].Type != FROM)
        {
            fout = atoi(str1);
            Fin = atoi(str2);
        }
        else
        {
            Fin = 1;
            fout = 1;
            strcpy(from, str1);
        }

        if(id > mid)
        {
            mid = id;
        }

        graph[id].num_of_fan_outs = fout;
        graph[id].num_of_fan_ins = Fin;

        if(fout == 0)
        {
            graph[id].primary_op = 1;
        }

        // create fanin and fanout lists
        switch (graph[id].Type)
        {
            case 0     :    printf("ReadIsc: Error in input file (Node %d)\n",id); exit(1);

            case INPT  :    break;

            case AND   :

            case NAND  :

            case OR    :

            case NOR   :

            case XOR   :

            case XNOR  :

            case BUFF  :

            case NOT   :    for(i = 1; i <= Fin; i += 1)
                            {
                                fscanf(isc_file, "%d", &fid);
                                insert_element(&graph[id].Fan_in, fid);
                                insert_element(&graph[fid].Fan_out, id);
                            }

                            fscanf(isc_file, "\n");

                            break;

            case FROM  :    for(i = mid; i > 0; i -= 1)
                            {
                                if(graph[i].Type != 0)
                                {
                                    if(strcmp(graph[i].Name, from) == 0)
                                    {
                                        fid = i;
                                        break;
                                    }
                                }
                            }

                            insert_element(&graph[id].Fan_in, fid);
                            insert_element(&graph[fid].Fan_out, id);

                            break;
        }

        bzero(line, strlen(line));
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, isc_file);
    }

    return (mid);
}

/**
 * @brief Initializes a particular member of a given graph entity of type NODE structure.
 *
 * @param graph the given NODE structure
 * @param idx   the index of the particular entity
 */
void initialize_circuit(NODE *graph, int idx)
{
    bzero(graph[idx].Name, MAX_NODE_ALIAS_LEN);

    graph[idx].Type = 0;
    graph[idx].num_of_fan_ins = 0;
    graph[idx].num_of_fan_outs = 0;
    graph[idx].primary_op = 0;
    graph[idx].Mark = 0;

    graph[idx].correct_value = 3;
    graph[idx].fault_value = 3;

    graph[idx].Fan_in = NULL;
    graph[idx].Fan_out = NULL;

    return;
}

/**
 * @brief Maps the string arguments to classes of type int.
 *        Those classes representr logic gates.
 *
 * @param Type the given string argument
 * @return int the corresponding logic gate ID
 */
int map_logic_gate(char *Type)
{
    if ( (strcmp(Type, "inpt") == 0) || (strcmp(Type, "INPT") == 0) )
    {
        return (1);
    }
    else if ( (strcmp(Type, "and") == 0) || (strcmp(Type, "AND") == 0) )
    {
        return (2);
    }
    else if ( (strcmp(Type, "nand") == 0) || (strcmp(Type, "NAND") == 0) )
    {
        return (3);
    }
    else if ( (strcmp(Type, "or") == 0) || (strcmp(Type, "OR") == 0) )
    {
        return (4);
    }
    else if ( (strcmp(Type, "nor") == 0) || (strcmp(Type, "NOR") == 0) )
    {
        return (5);
    }
    else if ( (strcmp(Type, "xor") == 0) || (strcmp(Type, "XOR") == 0) )
    {
        return (6);
    }
    else if ( (strcmp(Type, "xnor") == 0) || (strcmp(Type, "XNOR") == 0))
    {
        return (7);
    }
    else if ( (strcmp(Type, "buff") == 0) || (strcmp(Type, "BUFF") == 0) )
    {
        return (8);
    }
    else if ( (strcmp(Type, "not") == 0) || (strcmp(Type, "NOT") == 0) )
    {
        return (9);
    }
    else if ( (strcmp(Type, "from") == 0) || (strcmp(Type, "FROM") == 0) )
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
 * @param graph the given graph entity
 * @param Max   the index of the last node generated in the new graph entity.
 *              This is returned by `ReadIsc()`
 */
void print_circuit(NODE *graph, int Max)
{
    LIST *temp;
    int  i;

    printf("\nID\tNAME\tTypeE\tPO\tIN#\tOUT#\tCVAL\tFVAL\tMarkK\tFANIN\tFANOUT\n");

    for(i = 0; i <= Max; i += 1)
    {
        if(graph[i].Type != 0)
        {
            printf("%d\t%s\t%d\t%d\t%d\t%d\t", i, graph[i].Name, graph[i].Type, graph[i].primary_op, graph[i].num_of_fan_ins, graph[i].num_of_fan_outs);
            printf("%d\t%d\t%d\t", graph[i].correct_value, graph[i].fault_value, graph[i].Mark);

            temp = NULL;
            temp = graph[i].Fan_in;

            if(temp != NULL)
            {
                print_list(temp);
            }

            printf("\t");

            temp = NULL;
            temp = graph[i].Fan_out;

            if(temp != NULL)
            {
                print_list(temp);
            }

            printf("\n");
        }
    }

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
    int idx = 0;

    for(idx = 0; idx < n_elements; idx += 1)
    {
        graph[idx].Type = 0;
        graph[idx].num_of_fan_ins = 0;
        graph[idx].num_of_fan_outs = 0;
        graph[idx].primary_op = 0;
        graph[idx].Mark = 0;
        graph[idx].correct_value = 0;
        graph[idx].fault_value = 0;

        if(graph[idx].Type != 0)
        {
            bzero(graph[idx].Name, MAX_NODE_ALIAS_LEN);

            if(graph[idx].Fan_in != NULL)
            {
                delete_element(&graph[idx].Fan_in);
                graph[idx].Fan_in = NULL;
            }

            if(graph[idx].Fan_out != NULL)
            {
                delete_element(&graph[idx].Fan_out);
                graph[idx].Fan_out = NULL;
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
