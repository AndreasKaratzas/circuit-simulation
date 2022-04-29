
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

/**
 * @brief This function copies a string to another string.
 * 
 * @param from the source string
 * @param to   the destination string
 * @param len  the length of the string 
 *
 * @note The source string is a 2d char array that has only one 
 *       element in its second dimension.
 */
void copy_str(char from[][2], char *to, int len)
{
    int str_idx;

    printf("\n");
    for (str_idx = 0; str_idx < len; str_idx += 1)
    {
        to[str_idx] = from[str_idx][0];

        printf("%c", from[str_idx][0]);
    }
    printf("\n");
}
