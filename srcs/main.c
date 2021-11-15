#include "../includes/minishell.h"

typedef struct node {
  char **args;
  char *env;
  char *env_key;
  char *env_value;
  char *path;
  struct node * next;
} ListNode;

ListNode *g_envp;


void ft_echo(ListNode *node)
{
    int i;
    int check_n;
    char **args;
    int argc;

    args = node->args;
        argc = ft_strlen2(args);
    int sp = 0;
    check_n = 0;

    i = 1;
    while(ft_strcmp("-n",args[i]) == 0)
    {
        sp = 1;
        i++;
    }
    while(i < argc)
    {
        ft_putstr(args[i]);
        i++;
        if(args[i])
            ft_putstr(" ");
    }
    if(sp == 0)
        ft_putstr("\n");
}


// =====================env=============================

int fill_env1(ListNode **head, char *data)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    ListNode *line = *head;
    char **s;
    s = ft_split(data,'=');
    newNode->env = data;
    newNode->env_key = s[0];
    newNode->env_value = s[1];
    newNode->next = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        return 0;
    }
    while(line->next != NULL)
        line = line->next;
    line->next = newNode;
    return (0);
}



ListNode    *fill_env(char **env)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    int i;
    i = 0;
    ListNode *temp;
    char **s;
    while (env[i])
    {
        s = ft_split(env[i],'=');
        temp = malloc(sizeof(*temp));
        temp->env = env[i];
        temp->env_key = s[0];
        temp->env_value= s[1];
        temp->next = NULL;
        if (!head)
        {
            head = temp;
            tail = head;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
        i++;
    }
    return (head);
}

void    ft_env()
{
    ListNode *current = g_envp;
    while(current != NULL)
    {
        ft_putstr(current->env_key);
        ft_putstr("=");
        ft_putstr(current->env_value);
        ft_putstr("\n");
        current = current->next;
    }
}
// =====================================================
// =====================export=============================

ListNode *add_content(char **content)
{
    ListNode *lst;
    if(!(lst = malloc(sizeof(ListNode))))
        return (NULL);
    lst->env_key = content[0];
    lst->env_value = content[1];
    lst->next = NULL;

    return(lst);
}


void	ft_lstadd_back(ListNode **alst, ListNode *new)
{
	ListNode		*begin;

	if (alst && (*alst) && new)
	{
		begin = (*alst);
		if (begin == NULL)
			(*alst) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

void    addto_list(char *args,ListNode *node)
{

   ListNode *current = g_envp;
   char **s = ft_split(args,'=');
   int b = 0;
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,s[0]) == 0)
        {
            current->env_value = s[1];
            b=1;
            break;
        }
        current = current->next;
    }
    if(!b)
        ft_lstadd_back(&g_envp,add_content(s));
}

void    print_list()
{
    ListNode *current = g_envp;
    while(current != NULL)
    {
        ft_putstr("declare -x ");
        ft_putstr(current->env_key);
        ft_putstr("=\"");
        ft_putstr(current->env_value);
        ft_putstr("\"\n");
        current = current->next;
    }
}


void ft_export(ListNode *node)
{
    int i = 0;
    if(node->args)
    {
         while(node->args[++i])
            addto_list(node->args[i],node);
    }
    if(!node->args[1])
        print_list();
    // ListNode *current = g_envp;
    // while(current != NULL)
    // {
    //     if(current->env_value != NULL)
    //     {
    //         ft_putstr("declare -x ");
    //         ft_putstr(current->env_key);
    //         ft_putstr("=\"");
    //         ft_putstr(current->env_value);
    //         ft_putstr("\"\n");
    //         current = current->next;
    //     }
    //     else
    //         break;
        
    // }
}




// =====================================================

void       delet_v_env(ListNode *node,char *argv)
{
    (void)node;
    ListNode *current = g_envp;
    ListNode *temp, *prev;
    char **s = ft_split(argv,'=');
    if ((ft_strcmp(current->env_key, s[0]) == 0) && current != NULL)
    {
        temp = current->next;
        free(current);
        current = NULL;
        g_envp = temp;
        write(1, "--\n", 3);
        return ;
    }
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,s[0]) == 0)
        {
            temp = current->next;
            prev->next = temp;
            free(current);
            break ;
        }
        prev = current;
        current = current->next;
    }
}


void    ft_unset(ListNode *node)
{
    int i = -1;
    if(node->args)
        while(node->args[++i])
            delet_v_env(node,node->args[i]);
}


// =====================================================

char* searchch(char *word,char *changed)
{
    ListNode *current = g_envp;
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,word) == 0)
        {
            current->env_value = changed;
            break;
        }
        current = current->next;
    }

    return(current->env_value);
}


void    ft_cd(ListNode *node,char *path)
{
    char *pwd = NULL;

    if(chdir(node->args[1])!= 0)
        ft_putstr("Error\n");
    // printf("%s\n",pwd);
    pwd = getcwd(pwd,0);
    // printf("%s\n",pwd);
    // printf("%s\n",path);
    searchch("PWD",pwd);
    // ft_putstr("\n");
    // searchch("OLDPWD",path);
    // ft_putstr("\n");
}


void ft_pwd()
{
    char *r = NULL;
    ft_putstr(getcwd(r,1));
    ft_putstr("\n");
}

int     check_fill_path(ListNode *node)
{
    int     i;
    char    **w;
    char    *s;
    int     fd;
    
    i = 0;
    fd = 0;
	s = NULL;
    ListNode *current = g_envp;
    while (current != NULL)
    {
        if (!ft_strcmp(current->env_key, "PATH"))
        {
            w = ft_split(current->env_value, ':');
            while (w[i])
            {
                s = ft_strjoin(w[i], "/");
                s = ft_strjoin(s, node->args[0]);
                fd = open(s, O_RDONLY);
                if (fd > 0)
                {
                    node->path = s;
					close(fd);
                    return (1);
                }
				close(fd);
				free(s);
                i++;
            }
        }
        current = current->next;
    }
	// node->path = NULL;
    return (0);
}


char    **fill_paramlist(ListNode *node)
{
    int     i;
    char    **w;

    i = 0;
    w = malloc(sizeof(char *) * 3);
    w[0] = ft_strdup(node->path);
    if (node->args)
        w[1] = ft_strdup(node->args[0]);
    else
        w[1] = NULL;
    return (w);
}


void    ft_exec(ListNode *node)
{
    // check_fill_path(node);
    int pid = fork();
    int status;

   if (pid == -1)
   {
        ft_putstr("Error\n");
        exit(0);
    }
    if(pid == 0)
    {
        execve(node->path,fill_paramlist(node), NULL);
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    wait(&status);
    // (void)node;
    check_fill_path(node);
    fill_paramlist(node);
    printf("%s\n",node->path);
}



void    ft_simplecmd(ListNode *node)
{

    char *path = NULL;
    path = getcwd(path,0);

    // printf("%s\n",path);
    if (ft_strcmp("echo",node->args[0]) == 0)
        ft_echo(node);
    // else if(ft_strcmp("export",node->value[0]) == 0)
    //     ft_export(node);
    else if(ft_strcmp("export",node->args[0]) == 0)
        ft_export(node);
    else if (ft_strcmp("env", node->args[0]) == 0)
        ft_env();
    else if(strcmp("unset",node->args[0]) == 0)
        ft_unset(node);
    else if(ft_strcmp("cd",node->args[0]) == 0)
        ft_cd(node,path);
    else if(ft_strcmp("pwd",node->args[0]) == 0)
        ft_pwd();
    // else if(ft_strcmp("exit",node->lower_builtin) == 0)
    //     ft_exit(node);
    else
        ft_exec(node);
}
void   ft_checkcmd1(ListNode *node)
{
        // ft_simplecmd(node,str);
        ft_simplecmd(node);
}



int fill(ListNode **head, char **data)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    ListNode *line = *head;

    newNode->args = data;
    newNode->next = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        return 0;
    }
    while(line->next != NULL)
        line = line->next;
    line->next = newNode;

    return (0);
}


void	init_t_sep(ListNode *node)
{
	node->path = NULL;
	// node->t_sp = '\0';
	// node->args = NULL;
	
}

void    fill_args(char **args)
{
    ListNode *data = malloc(sizeof(ListNode));
    ListNode *head;
    // init_t_sep(data);
    head = NULL;
    int i = 0;
    while(args[i])
    {
        data->args = &args[i];
        fill(&head,data->args);
        i++;
    }
    // check_fill_path(head);
    // printf("%s\n",head->path);
    ft_checkcmd1(head);
}


int main(int ac, char **av,char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    char *str;
    g_envp = fill_env(env);
    char **args;
    // fill_env(env);
    while(1)
    {
        str = NULL;
        str = readline("S_SHELL > ");
        add_history(str);
        args = ft_split(str,' ');
        fill_args(args);


    }
    return (0);
}