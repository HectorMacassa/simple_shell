#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	list_t *node = NULL;

	int fd = open_history_file(filename);
	free(filename);

	if (fd == -1)
		return (-1);

	write_history_to_file(info, fd);
	close(fd);

	return (1);
}

/**
 * open_history_file - opens the history file
 * @filename: the name of the history file
 *
 * Return: file descriptor on success, else -1
 */
int open_history_file(char *filename)
{
	return open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
}

/**
 * write_history_to_file - writes history to the given file descriptor
 * @info: the parameter struct
 * @fd: file descriptor
 */
void write_history_to_file(info_t *info, int fd)
{
	list_t *node = info->history;

	for (; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);
	int linecount = 0;
	ssize_t fsize = 0;
	char *buf = read_history_file(filename, &fsize);

	if (!buf)
		return (0);

	process_history_buffer(info, buf, fsize, &linecount);
	free(buf);

	cleanup_history(info);

	return (info->histcount);
}

/**
 * read_history_file - reads the contents of the history file
 * @filename: the name of the history file
 * @fsize: pointer to store the size of the file
 *
 * Return: buffer containing file content, or NULL on failure
 */
char *read_history_file(char *filename, ssize_t *fsize)
{
	int fd;
	struct stat st;
	char *buf;

	fd = open(filename, O_RDONLY);

	if (fd == -1)
		return (NULL);

	if (fstat(fd, &st))
		return (NULL);

	*fsize = st.st_size;

	if (*fsize < 2)
		return (NULL);

	buf = malloc(sizeof(char) * (*fsize + 1));

	if (!buf)
		return (NULL);

	ssize_t rdlen = read(fd, buf, *fsize);
	buf[*fsize] = 0;

	if (rdlen <= 0)
		return (free(buf), NULL);

	close(fd);

	return (buf);
}

/**
 * process_history_buffer - processes the history buffer
 * @info: the parameter struct
 * @buf: buffer containing file content
 * @fsize: size of the buffer
 * @linecount: pointer to store the line count
 */
void process_history_buffer(info_t *info, char *buf, ssize_t fsize, int *linecount)
{
	int i, last = 0;

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, (*linecount)++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buf + last, (*linecount)++);
}

/**
 * cleanup_history - cleans up history by removing excess entries
 * @info: the parameter struct
 */
void cleanup_history(info_t *info)
{
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}

