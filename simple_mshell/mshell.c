#include "mshell.h"

char	ctrl_builtins(char	*prompt)
{
	if (!ft_strncmp(prompt, "pwd", ft_strlen(prompt)))
		return (pwd());
	return (-1);
}

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

char	process(t_mshell *mshell)
{
	mshell->prompt = read_prompt();
	if (!mshell->prompt)
		return (free(mshell), -1);
	//parser(mshell);
	ctrl_builtins(mshell->prompt);
	//executor(mshell);
}

int main(void)
{
	t_mshell	*mshell;
	char		**envp;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (-1);
	while (1)
		if (!process(mshell))
			break ;
	//quitting(mshell);
	return (0);
}
