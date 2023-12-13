#include "shell.h"

/**
 * handleExitArgument - Handles the exit argument when provided.
 * @info: Structure containing potential arguments.
 *
 * Return: -2 if the exit argument is provided, otherwise 0.
 */
int handleExitArgument(info_t *info)
{
    int exit_check = _erratoi(info->argv[1]);
    if (exit_check == -1)
    {
        info->status = 2;
        print_error(info, "Illegal number: ");
        _eputs(info->argv[1]);
        _eputchar('\n');
        return 1;
    }
    info->err_num = exit_check;
    return -2;
}

/**
 * handleExitCommand - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0 if info->argv[0] != "exit").
 */
int handleExitCommand(info_t *info)
{
    if (info->argv[1])
    {
        int exit_check = handleExitArgument(info);
        if (exit_check != -2)
            return exit_check;
    }

    info->err_num = -1;
    return (-2);
}

/**
 * changeToHomeDirectory - Changes to the home directory.
 * @info: Structure containing potential arguments.
 *
 * Return: Result of chdir operation.
 */
char *changeToHomeDirectory(info_t *info)
{
    char *dir = _getenv(info, "HOME=");
    if (!dir)
    {
        chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
    }
    else
    {
        chdir(dir);
    }
    return dir;
}

/**
 * changeToPreviousDirectory - Changes to the previous directory.
 * @info: Structure containing potential arguments.
 * @s: Current directory.
 *
 * Return: Result of chdir operation.
 */
char *changeToPreviousDirectory(info_t *info, char *s)
{
    char *dir;
    if (!_getenv(info, "OLDPWD="))
    {
        _puts(s);
        _putchar('\n');
        return NULL;
    }

    dir = _getenv(info, "OLDPWD=");
    _puts(dir);
    _putchar('\n');

    chdir(dir ? dir : "/");
    return dir;
}

/**
 * handleDirectoryChangeResult - Handles the result of the directory change operation.
 * @info: Structure containing potential arguments.
 * @chdir_ret: Result of chdir operation.
 * @buffer: Buffer containing the current directory.
 */
void handleDirectoryChangeResult(info_t *info, int chdir_ret, char *buffer)
{
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
}

/**
 * changeDirectory - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Result of chdir operation.
 */
int changeDirectory(info_t *info)
{
    char *s, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        char *dir = changeToHomeDirectory(info);
        /* Use 'dir' in your code if needed */
        return (dir != NULL ? 0 : -1); /* Return an error code if changeToHomeDirectory fails */
    }

    if (_strcmp(info->argv[1], "-") == 0)
    {
        char *dir = changeToPreviousDirectory(info, s);
        /* Use 'dir' in your code if needed */
        return (dir != NULL ? 0 : -1); /* Return an error code if changeToPreviousDirectory fails */
    }

    chdir_ret = chdir(info->argv[1]);
    handleDirectoryChangeResult(info, chdir_ret, buffer);

    return (0);
}

/**
 * displayHelp - Displays help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int displayHelp(info_t *info)
{
    char **arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");

    if (0)
        _puts(*arg_array); /* temp att_unused workaround */

    return (0);
}
