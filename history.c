#include "shell.h"

/**
 * generate_history_file_path - generates the history file path
 * @info: parameter struct
 *
 * Return: allocated string containing the history file path
 */
char *generate_history_file_path(info_t *info)
{
	char *buf, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		free(home_dir);
		return (NULL);
	}

	buf[0] = 0;
	_strcpy(buf, home_dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	free(home_dir);
	return (buf);
}

/**
 * write_history_to_file - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: (1) on success, else (-1)
 */
int write_history_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = generate_history_file_path(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history_from_file - reads history from file
 * @info: the parameter struct
 *
 * Return: (histcount) on success, 0 otherwise
 */
int read_history_from_file(info_t *info)
{
	int linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = generate_history_file_path(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return (close(fd), 0);

	buf = malloc(sizeof(char) * (fsize + 1));

	if (!buf)
		return (close(fd), 0);

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		return (free(buf), close(fd), 0);

	close(fd);

	linecount = process_history_buffer(info, buf, fsize);

	free(buf);
	return (linecount);
}

/**
 * process_history_buffer - processes the history buffer
 * @info: the parameter struct
 * @buf: history buffer
 * @fsize: size of the buffer
 *
 * Return: (histcount) on success, 0 otherwise
 */
int process_history_buffer(info_t *info, char *buf, size_t fsize)
{
	int i, last = 0, linecount = 0;

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buf + last, linecount++);

	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}
