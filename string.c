#include "shell.h"

/**
 * custom_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of the string
 */
int custom_strlen(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (*str++)
        length++;

    return length;
}

/**
 * custom_strcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int custom_strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);

        str1++;
        str2++;
    }

    return (*str1 == *str2) ? 0 : (*str1 < *str2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *custom_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

/**
 * custom_strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *custom_strcat(char *destination, char *source)
{
    char *result = destination;

    while (*destination)
        destination++;

    while (*source)
    {
        *destination++ = *source++;
    }

    *destination = *source;

    return result;
}
