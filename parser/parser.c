#include "../minishell.h"

t_ParseTree	*parser(int argc, char **argv)
{
	t_ParseTree	*rtrn;
	int			i;

	if (!argc)
		return (NULL);
	argv = space_ctrl(argc, argv);// (cmd) -> ( cmd )
	if (!argv)
		return (NULL);
	rtrn = ft_calloc(1, sizeof(t_ParseTree));
	if (!rtrn)
		return (NULL);
	// job nasıl elde edilir? Entegre edilecek!
	i = -1;
	while (++i < argc)
	{
		rtrn->this_node->type = lexer(argv[i]);
		if (rtrn->this_node->type == CMD)
			rtrn->this_node->cmd = ft_strdup(argv[i]);
		else if (rtrn->this_node->type == ARG)
			rtrn->this_node->arg = ft_strdup(argv[i]);
	}
}
