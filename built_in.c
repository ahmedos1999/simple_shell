#include "main.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 **/
int my_exit(info_t *info)
{
	if (str_cmp(info->argv[0], "exit") == 0)
	{
		printf("exiting shell....\n");
		exit(info->status);
	}
}

/**
 * my_exit2 - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 **/
int my_exit2(info_t *info)
{
int statue, i = 0;

	if (info->argv[1] == NULL)
	{
		free(info->argv);
		exit(EXIT_SUCCESS);
	}

	while (info->argv[1][i])
	{
		statue = _atoi(info->argv[1]);
		free(info->argv);
		exit(statue);
	}
}

/**
 * my_help - show info about a command
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	put_str("help call works. Function not yet implemented \n");

	if (0)
		put_str(*arg_array); /* temp att_unused workaround */
	return (0);

}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
		{
			chdir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		}
		else
		{
			chdir_ret = chdir(dir);
		}
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			put_str(s);
			put_char('\n');
			return (1);
		}
		put_str(get_env(info, "OLDPWD=")), put_char('\n');
		chdir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
return (0);
}

/**
 * change_dir - Change Dirctorie
 * @info: Structure for carrying path
 *
 * Return: 0 Succes 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 **/
int change_dir(info_t *info)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (info->argv[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(info->argv[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
return (0);
}
