
#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "/Users/yoo-lee/42/minishell0307/libft/libft.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1

#define BUFFER_SIZE 10000
#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif
#define REDIRECT_PROMPT "> "

typedef enum e_token_kind
{
	TK_WORD = 0,
	TK_IO_NUMBER,
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_REDIRECT_DLESS,
	TK_REDIRECT_DGREAT,
	TK_SEMICOLON,
} t_token_kind;

typedef enum e_node_kind
{
	ND_COMMAND,
	ND_PIPE,
	ND_SEMICOLON,
} t_node_kind;

typedef enum e_quote_state
{
	NORMAL,
	IN_QUOTE,
	IN_DQUOTE,
} t_quote_state;

typedef struct s_tokenize_state
{
	size_t trim_start;
	size_t current_pos;
	t_quote_state quote_state;
	t_token_kind token_kind;
} t_tokenize_state;

typedef struct s_token
{
	char *content;
	t_token_kind attr;
} t_token;

typedef struct s_expand_state
{
	size_t start;
	size_t current_pos;
	t_quote_state quote_state;
	t_token *original_token;
	t_list *token_list;
} t_expand_state;

typedef struct s_node
{
	t_node_kind attr;
	struct s_node *lhs;
	struct s_node *rhs;
	t_list *tokens;
	int is_furthest_left;
	int is_furthest_right;
	int is_top;
} t_node;

typedef struct s_envs
{
	int envs_num;
	char **content;
} t_envs;

int ft_echo(char **argv, t_envs *envs);
int ft_pwd(char **argv, t_envs *envs);
int ft_env(char **argv, t_envs *envs);
int ft_cd(char **argv, t_envs **envs);
int remove_env(int index, t_envs **envs)

	void free_strings(char **argv);
void set_curpath(char **argv, t_envs **envs, char **curpath);
int ft_export(char **argv, t_envs **envs);
int ft_unset(char **argv, t_envs **envs);
int ft_exit(char **argv, t_envs **envs);

void exit_with_error(char *msg);
void print_command_error(char *command, char *msg);

int print_envs(t_envs *envs);
int get_env_pos(char *env_name, t_envs *envs);
int get_first_char_pos(char *word, char c);

int set_env(char *name, char *val, t_envs **envs);

int make_new_envs(char *name, char *val, t_envs **envs);
int init_envs(t_envs **envs, char **envp);
char **sort_envs(char **dup_env);
int get_env_name_and_value(char **name, char **value, char *env);
char *get_env(char *name, t_envs *envs);
int set_env(char *name, char *value, t_envs **envs);

#endif
