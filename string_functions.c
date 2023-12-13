/**
 * _strncpy - copies up to 'n' characters from the source to the destination
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to copy
 * Return: a pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n - 1 && src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strncat - concatenates up to 'n' characters from the source
 * to the destination
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to concatenate
 * Return: a pointer to the destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t i, j;

	for (i = 0; dest[i] != '\0'; ++i)
		for (j = 0; j < n && src[j] != '\0'; ++j, ++i)
		{
			dest[i] = src[j];
		}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the first occurrence of 'c' in 's',
 * or NULL if not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		++s;
	}
	return (NULL);
}
