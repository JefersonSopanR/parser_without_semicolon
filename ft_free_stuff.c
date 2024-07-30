#include "minishell.h"

void	ft_free_tokens(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	cur = *token;
	while (cur)
	{
		free(cur->data);
		next = cur->next;
		free(cur);
		cur = next;
	}
	*token = NULL;
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir)
	{
		free(redir->file);
		next = redir->next;
		free(redir);
		redir = next;
	}
}

void	ft_free_cmd(t_node *ast)
{
	if (ast->data)
		free(ast->data);
	ft_free_redir(ast->redir);
}

void	ft_free_ast(t_node *ast)
{
	if (!ast)
		return ;
	ft_free_cmd(ast);
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast);
}
