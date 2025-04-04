#ifndef MAIN_H
#define MAIN_H

#include "Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_var
{
	char *key;
	char *value;
	char meaning;
	struct s_var *next;
} t_var;

typedef struct s_data
{
	char *path;
	char *cmd;
	char *pwd;
	char **words;
	char *exit_code;
	t_var *env_lst;
} t_data;

char *get_path(char **env);
int free_matrix(char **env);
void free_env_list(t_var *head);

void handle_sigint(int sig);
void handle_sigquit(int sig);

int cmds_process_loop(t_data *data);

/*----Built-ins----*/
int execute_builtin(t_data *data);
int is_builtin(char *cmd);
/*-------echo------*/
int ft_echo(t_data *data);
int check_nl(char *new_line);
void remove_quotes(char *word);
/*-------pwd-------*/
int ft_pwd(t_data *data);
/*-------env-------*/
int ft_env(t_data *data);
void init_env(char **envp, t_data *data);
t_var *init_envp_node(char *env);
void env_addtolist(t_var **lst, t_var *node);
/*-------cd--------*/
int ft_cd(t_data *data);
void cd_with_no_param(t_data *data);
void cd_with_dash_param(t_data *data);
void cd_with_param(t_data *data, char *path_value);
void add_env_list(char *key, char *value, t_data *data);
char *get_env_value(char *key, t_data *data);
/*------export------*/
int ft_export(t_data *data);
int get_env_len(t_var *env);
char **list_to_arr(int size, t_var *env);
char **sort_arr_list(char **arr, int size);
void get_export(char **sorted_arr, t_data *data);
void export_with_param(t_data *data);

// void check_echo_$(t_data *data);
// int check$(char *sign);
// void print_env_to_envp(t_data *data);
// t_var *env_content(char *key, char *value);
// t_var *lst_new_elem(char *name, char *value);
// void lst_add_back(t_var **lst, t_var *new_node);
// t_var *lst_last(t_var *lst);
// void init_env(char **envp, t_data *data);
// void set_shlvl(t_data *data, char **envp, int i);

void print_env(t_var *head);
int ft_strcmp(const char *s1, const char *s2);

#endif
