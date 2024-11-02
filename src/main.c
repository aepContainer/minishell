#include "../inc/minishell.h"

static char	*read_prompt(void)
{
	char	*rtrn;

	rtrn = readline(PROMPT);
	if (!rtrn)
		return (NULL);
	if (*rtrn)
		add_history(rtrn);
	return (rtrn);
}

static char	process(t_mshell *mshell)
{
	char	*prompt;

	prompt = read_prompt();
	mshell->prompt = ft_strtrim(prompt, " \t");
	free(prompt);
	if (!mshell->prompt)
		return (EXIT_FAILURE);
	//parser(mshell);
	if (executor(mshell))
		mshell->quest_mark = 0;
	return (free(mshell->prompt), EXIT_SUCCESS);
}

int main(void)
{
	t_mshell	*mshell;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (EXIT_FAILURE);
	signal_handle_general(mshell);
	while (1)
		if (process(mshell))
			break ;
	//quitting(mshell);
	return (EXIT_SUCCESS);
}
