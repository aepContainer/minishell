#include "../../inc/parser.h"

static char    **access_pathcheck(char **ctrl_paths, int p_len, int c_len)
{
    char	**success_arr;
    int		i;
    int		j;

	if (!ctrl_paths)
		return (NULL);
    success_arr = ft_calloc(c_len, sizeof(char *));
	if (!success_arr)
		return (NULL);
    i = -1;
    while (++i < c_len)
    {
        j = -1;
        while (++j < p_len)
        {
            if (!access(ctrl_paths[i * p_len + j], X_OK))
            {
                success_arr[i] = ft_strdup(ctrl_paths[i * p_len + j]);
                break ;
            }
        }
        if (success_arr[i] == NULL)
            return (NULL);
    }
    return (success_arr);
}

static char    **joins(char **env_paths, int paths_len, char **cmds, int cmds_len)
{
    char    **cmd_paths;
    char    *temp1;
    char    *temp2;
    int     index[3];

    cmd_paths = ft_calloc(cmds_len * paths_len + 1, sizeof(char *));
	if (!cmd_paths)
		return (NULL);
    index[2] = 0;
    index[0] = -1;
    while (cmds[++index[0]])
    {
        index[1] = -1;
        while (env_paths[++index[1]])
        {
            temp1 = ft_strjoin(env_paths[index[1]], ft_strdup("/"));
            temp2 = ft_strjoin(temp1, cmds[index[0]]);
            free(temp1);
            cmd_paths[index[2]] = ft_calloc(ft_strlen(temp2) + 1, 1);
            ft_strlcpy(cmd_paths[index[2]], temp2, ft_strlen(temp2) + 1);
            free(temp2);
            index[2]++;
        }
    }
    return (cmd_paths);
}

static char	get_data(t_mshell *mshell)
{
	char	*env;

	env = getenv("PATH");
    mshell->envp = ft_split(env, ':');
	free(env);
	if (!mshell->envp)
		return (EXIT_FAILURE);
	while (mshell->jobs->job_list)
	{
		mshell->cmds = str_arr_realloc(mshell->cmds, mshell->jobs->job_list->cmd);
		if (!mshell->cmds)
			return (free_str_arr(mshell->cmds), EXIT_FAILURE);
		mshell->jobs->job_list = mshell->jobs->job_list->next_job;
	}
	return (EXIT_SUCCESS);
}

char	**accessor(t_mshell *mshell)
{
    char    **success_arr;
    int     p_len;
    int     c_len;

	if (get_data(mshell))
		return (NULL);
    p_len = str_arr_len(mshell->envp);
    c_len = mshell->jobs->len;
    mshell->ctrl_paths = joins(mshell->envp, p_len, mshell->cmds, c_len);
    success_arr = access_pathcheck(mshell->ctrl_paths, p_len, c_len);
	free_str_arr(mshell->ctrl_paths);
	if (!success_arr)
		return (NULL);
    return (success_arr);
}
