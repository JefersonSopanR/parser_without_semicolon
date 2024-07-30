#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	T_WORD,
	T_O_PARENTHESIS,
	T_C_PARENTHESIS,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_PIPE,
	T_AND,
	T_OR,
}   t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef	struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
}	t_node_type;

typedef	enum e_rror
{
	E_NONE,
	E_SYNTAX,
}	t_error;

typedef	struct s_node
{
	t_node_type		type;
	t_redir			*redir;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef	struct s_global
{
	t_token		*cur_token;
	t_error		error_type;
}	t_global;

t_node  *ft_connect_nodes(t_token_type op, t_node *left, t_node *right);
t_node_type ft_convert_type(t_token_type op);
int ft_prec(t_token_type type);
t_node	*ft_new_node(t_node_type type);
bool	ft_is_cmd(t_token *token);
void	ft_print_ast(t_node *ast, int depth);
void	ft_print_error(t_token *token);
void	ft_free_redir(t_redir *redir);
void	ft_free_cmd(t_node *ast);
void	ft_free_ast(t_node *ast);
void	ft_print_tokens(t_token *token);
void	ft_id_redir_input(t_token **token ,char *line, int *i);
void	ft_id_redir_output(t_token **token, char *line, int *i);
void	ft_identify_redir(t_token **token, char *line, int *i);
void	ft_identify_parenthesis(t_token **token, char *line, int *i);
void	ft_identify_and_or(t_token **token, char *line, int *i);
void	ft_identify_operators(t_token **token, char *line, int *i);
t_redir	*ft_fill_redir(t_redir **redir);
t_node	*ft_get_cmd_node(void);
t_node	*ft_primary(void);
t_node	*ft_expression(int	min_prec);
t_node	*ft_create_ast(t_token *token);
void	ft_free_tokens(t_token **token);
bool    ft_check_quotes(char *line);
bool	ft_is_not_op(char *line, int *i);
bool	ft_is_cmd(t_token *token);
bool	ft_is_redir(t_token_type type);
t_token	*ft_new_token(t_token_type type, char *data);
void	ft_add_back(t_token **token, t_token *new);
t_node	*ft_new_node(t_node_type type);
t_redir	*ft_new_redir(void);
void	ft_add_redir_back(t_redir **redir, t_redir *new);

#endif