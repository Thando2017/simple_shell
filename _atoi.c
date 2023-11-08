#include "shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim_str: the string of delimiters
 * Return: 1 if it is a delimiter, 0 if not
 */
int is_delimiter(char c, char *delim_str)
{
	while (*delim_str)
	{
		if (*delim_str++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alphabetic - checks for an alphabetic character
 * @c: the character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * string_to_integer - converts a string to an integer
 * @str: the string to convert
 * Return: 0 if there are no numbers in the string, otherwise the converted number
 */
int string_to_integer(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}

