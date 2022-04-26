
#include "utils.hpp"

/**
 * @brief Repeats a given character `n` times to build a string
 * 
 * @param str          the empty string
 * @param c            the character
 * @param num_of_chars the number of times to repeat the character
 */
void repeat(char *str, char c, int num_of_chars)
{
    int counter;

    for (counter = 0; counter < num_of_chars; counter += 1)
    {
        str[counter] = c;
    }

    return;
}
