
#include "graph.hpp"


/**
 * @brief Maps every character to its corresponding integer value as per instructions.
 *          * `0` is just typecasted to 0.
 *          * `1` is just typecasted to 1.
 *          * `x` and `X` are mapped to 2.
 *
 *        There is a basic protection mechanism in the case of an invalid parsed character.
 * 
 * @param pattern_str the test vector in raw string format
 * @param pattern_int the result test vector in integer format
 * @param num_of_vec_elements the number of primary inputs
 */
void map_pattern(char *pattern_str, int *pattern_int, int num_of_vec_elements)
{
    int vec_element_counter;

    for (vec_element_counter = 0; vec_element_counter < num_of_vec_elements; vec_element_counter += 1)
    {
        switch (pattern_str[vec_element_counter])
        {
            case '0': pattern_int[vec_element_counter] = 0; break;
            case '1': pattern_int[vec_element_counter] = 1; break;
            case 'x': pattern_int[vec_element_counter] = 2; break;
            case 'X': pattern_int[vec_element_counter] = 2; break;
            default: printf("`map_pattern(): Invalid vector element (%c)`", pattern_str[vec_element_counter]); exit(1);
        }
    }

    return;
}

/**
 * @brief Parses a `.vec` file.
 * 
 * @param vec_file the given `.vec` file to parse
 * @param vectors  the result vectors instantiated after processing the `.vec` file
 */
int read_vec_file(FILE *vec_file, PATTERN *vectors)
{
    int num_of_patterns = 0;
    char line[MAX_NUM_OF_CHARACTERS_IN_LINE];
    char raw_vector[MAX_NUM_OF_PRIMARY_INPUTS];

    while( !feof(vec_file) )
    {
        fgets(line, MAX_NUM_OF_CHARACTERS_IN_LINE, vec_file);
        
        if (strcmp(line, "") != 0 && strcmp(line, "\r\n") != 0 && strcmp(line, "\n") != 0 && strcmp(line, "\0") != 0)
        {
            sscanf(line, "%s", raw_vector);
            vectors[num_of_patterns].num_of_primary_inputs = strlen(raw_vector);
            vectors[num_of_patterns].primary_input_vec = (int*) malloc(vectors[num_of_patterns].num_of_primary_inputs * sizeof(int));
            map_pattern(raw_vector, vectors[num_of_patterns].primary_input_vec, vectors[num_of_patterns].num_of_primary_inputs);
            bzero(line, strlen(line));
            num_of_patterns += 1;
        }
    }
    
    return (num_of_patterns);
}

/**
 * @brief Prints all elements of a test vector entity of type PATTERN structure.
 *        The use case of this function is after parsing an VEC file
 *        using `read_vec_file()`.
 * 
 * @param vectors         the given vector entity
 * @param num_of_patterns the number of vector elements returned by `read_vec_file()`
 */
void print_vectors(PATTERN *vectors, int num_of_patterns)
{
    int vector_count, element_count;

    printf("Vectors:\n");
    for (vector_count = 0; vector_count < num_of_patterns; vector_count += 1)
    {
        printf("\tTest Vector[%d]: (Primary Inputs Count: %d)\n", vector_count + 1, vectors[vector_count].num_of_primary_inputs);
        for (element_count = 0; element_count < vectors[vector_count].num_of_primary_inputs; element_count += 1)
        {
            printf("\t\tPrimary Input[%d]: %d\n", element_count + 1, vectors[vector_count].primary_input_vec[element_count]);
        }
    }

    return;
}

/**
 * @brief Deallocates the memory segments used for saving test vectors of type PATTERN structure.
 * 
 * @param vectors         the given vector entity
 * @param num_of_patterns the number of vector elements returned by `read_vec_file()`
 */
void delete_vectors(PATTERN *vectors, int num_of_patterns)
{
    int vector_count, element_count;

    for (vector_count = 0; vector_count < num_of_patterns; vector_count += 1)
    {
        for (element_count = 0; element_count < vectors[vector_count].num_of_primary_inputs; element_count += 1)
        {
            free(vectors[vector_count].primary_input_vec);
        }
    }

    return;
}