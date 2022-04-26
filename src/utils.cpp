
#include "utils.hpp"


/**
 * @brief Substitutes a string of a constant character with another character.
 * 
 * @param s     the given string
 * @param from  the source character
 * @param to    the target character
 */
void subst(char *s, char from, char to) 
{
    while (*s == from)
    *s++ = to;
}

/**
 * @brief Appends a character to the beginning of a string.
 * 
 * @param s the source string
 * @param t the target string
 */
void prepend(char *s, const char *t)
{
    size_t len = strlen(t);
    memmove(s + len, s, strlen(s) + 1);
    memcpy(s, t, len);
}
