#include "minishell.h"

extern t_global global;

void	ft_print_tokens(t_token *token)
{
	while (token)
	{
		printf("TYPE-> %d  DATA-> %s\n", token->type, token->data);
		token = token->next;
	}
}

void	ft_print_ast(t_node *ast, int depth)
{
	int	i;

	i = depth;
	if (!ast)
		return ;
	while (i > 0)
	{
		printf(" ");
		i--;
	}
	printf("NODE_TYPE-> %d  ", ast->type);
	if (ast->redir && (ast->redir->type == T_REDIR_IN || ast->redir->type == T_REDIR_HEREDOC))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	if (ast->data)
		printf("NODE_DATA-> %s ", ast->data);
	if (ast->redir && (ast->redir->type == T_REDIR_OUT || ast->redir->type == T_REDIR_APPEND))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	printf("\n");
	ft_print_ast(ast->left, depth + 1);
	ft_print_ast(ast->right, depth + 1);
}

void	ft_print_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	if (!global.cur_token)
	{
		while (token && token->next != global.cur_token)
			token = token->next;
		ft_putstr_fd(token->data, 2);
	}
	else if (global.cur_token->data)
		ft_putstr_fd(global.cur_token->data, 2);
	ft_putstr_fd("'\n", 2);
}

