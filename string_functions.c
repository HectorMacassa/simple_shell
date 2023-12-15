#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i, j;
	char *s = dest;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for (j = i; j < n; j++)
	{
		dest[j] = '\0';
	}

	return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
