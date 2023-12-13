#include "shell.h"

/**
 * _string_length - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of the string
 */
int _string_length(const char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;

	return (length);
}

/**
 * _string_compare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _string_compare(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: pointer to the next character of haystack or NULL
 */
const char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (haystack);

	return (haystack);
}

/**
 * _string_concatenate - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_string_concatenate(char *destination, const char *source)
{
	char *result = destination;

	while (*destination)
		destination++;

	while (*source)
		*destination++ = *source++;

	*destination = *source;

	return (result);
}

