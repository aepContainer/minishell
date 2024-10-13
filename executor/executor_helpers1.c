#include "../minishell.h"

char	**accessor(t_tree *tree)
{
    char	**success_arr;
    int		i;
    int		j;

    success_arr = ft_calloc(tree->c_len, sizeof(char *));
    i = -1;
    while (++i < tree->c_len)
    {
        j = -1;
        while (++j < tree->p_len)
        {
            if (!access(tree->paths[i * tree->p_len + j], X_OK))
            {
                success_arr[i] = ft_strdup(tree->paths[i * tree->p_len + j]);
                break ;
            }
        }
        if (success_arr[i] == NULL)
            return (NULL);
    }
    return (success_arr);
}

char    **joins(char **env_paths, int paths_len, char **cmds, int cmds_len)
{
    char    **cmd_paths;
    char    *temp1;
    char    *temp2;
    int     cmd_paths_index;
    int     i;
    int     j;

    cmd_paths_index = 0;
    cmd_paths = ft_calloc(cmds_len * paths_len + 1, sizeof(char *));
    i = -1;
    while (cmds[++i])
    {
        j = -1;
        while (env_paths[++j])
        {
            temp1 = ft_strjoin(env_paths[j], ft_strdup("/"));
            temp2 = ft_strjoin(temp1, cmds[i]);
            free(temp1);
            cmd_paths[cmd_paths_index] = ft_calloc(ft_strlen(temp2) + 1, 1);
            ft_strlcpy(cmd_paths[cmd_paths_index], temp2, ft_strlen(temp2) + 1);
            free(temp2);
            cmd_paths_index++;
        }
    }
    return (cmd_paths);
}
