
#include "utils.hpp"

/**
 * @brief Prints a given character `n` times
 * 
 * @param c            the character
 * @param num_of_chars the number of times to repeat the character
 */
void repeat(char c, int num_of_chars)
{
    int counter;
    
    for (counter = 0; counter < num_of_chars; counter += 1)
    {
        printf("%c", c);
    }

    return;
}

/**
 * @brief Stores a given character `n` times into a string
 * 
 * @param str          the empty string
 * @param c            the character
 * @param num_of_chars the number of times to repeat the character
 */
void store_repeat(char *str, char c, int num_of_chars)
{
    int counter;
    
    for (counter = 0; counter < num_of_chars; counter += 1)
    {
        str[counter] = c;
    }

    return;
}
