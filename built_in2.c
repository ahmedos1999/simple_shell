#include "main.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_env(info_t *info)
{
        print_list_string(info->env);
        return (0);
}

/**
 * my_set_env - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_set_env(info_t *info)
{
        if (info->argc != 3)
        {
                _eputs("Incorrect number of arguements\n");
                return (1);
        }
        if (set_env(info, info->argv[1], info->argv[2]))
                return (0);
return (1);
}

/**
 * my_unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_unset_env(info_t *info)
{
        int i;

        if (info->argc == 1)
        {
                _eputs("Too few arguements.\n");
                return (1);
        }
        for (i = 1; i <= info->argc; i++)
                unset_env(info, info->argv[i]);
        return (0);
}
/**
 * my_history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_history(info_t *info)
{
	list_printer(info->history);
return (0);
}
