#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
int g_flag_p = 0;
int g_flag_q = 0;
int g_flag_r = 0;
int g_flag_s = 0;
int g_flag_ERROR= 0;

typedef struct s_node
{
	char	*str;
	struct s_node *next;
}							t_node;

t_node *add_to_back(t_node *head, char *str){
t_node *ptm;
if(!head){
	head =(t_node*)malloc(sizeof(t_node));
	head->str = ft_strdup(str);
	head->next = NULL;
	return head;
}
ptm = head;
while(ptm->next != NULL)
	ptm = ptm->next;
t_node *node = (t_node*)malloc(sizeof(t_node));
node->str = ft_strdup(str);
node->next = NULL;
ptm->next = node;
return head;
}

int  checkerForFlags(char **argv,int i){
	int j;
	int end = 0;
    int k = i;
	while (argv[k])
	{
		j = 1;
		if (argv[k][0] == '-'  && end != 1)
		{
			while(argv[k][j])
			{
				if(argv[k][j] == 'p')
					g_flag_p = 1;
				else if (argv[k][j] == 'q')
					g_flag_q= 1;
				else if (argv[k][j] == 'r')
					g_flag_r = 1;
				else if (argv[k][j] == 's')
					g_flag_s = 1;
				else
					g_flag_ERROR = 1;
				j++;
			}
		}
		if (argv[k][0] != '-')
			end = 1;
		if (end == 1)
			return k;
		k++;
	}
	printf("P:%d Q:%d R:%d S:%d Error:%d\n ", g_flag_p, g_flag_q, g_flag_r, g_flag_s,g_flag_ERROR);
	return k;
}

void invalid_flag()
{
	if (g_flag_ERROR == 1)
	{
		printf("illegal option --");
		exit(1);
	}
}


char *read_from_echo()
{
	char	*line;
	get_next_line(0,&line);
return(line);
}

t_node *regular_read(int j,int argc, char  **argv ,t_node *head){
	char	*line;
	char	*lll;
	int		status;
	char *new_str;
	new_str =ft_strnew(1);
	ft_bzero(new_str,ft_strlen(new_str));
	while (j < argc)
	{
		int fd = open(argv[j], O_RDONLY);
		if((fd == -1 && ft_strcmp(argv[j - 1],"-s") == 0 ) || (fd == -1 && argv[j - 1][(ft_strlen(argv[j-1]) - 1)] == 's' && g_flag_s ==1))
		{
			line = ft_strdup(argv[j]);
			head = add_to_back(head, line);
		}else if(fd == -1)
			printf("md5: %s: No such file or directory\n" ,argv[j] );
		else
		{
			while((status = get_next_line(fd, &lll)) == 1)
				new_str = ft_strjoin(new_str,ft_strjoin(lll ,"\n"));
				new_str[ft_strlen(new_str)-1] ='\0';
				head = add_to_back(head,new_str);
		}
		close(fd);
		j++;
	}
	return head;
}

t_node *read_from(int j,int argc,char  **argv,t_node *head)
{
	char	*lll;
	int		status;
		// printf("%s\n",line );
	 if(j == argc)
	 		head = add_to_back(head ,read_from_echo());
	 else if (g_flag_p == 0)
		head =	regular_read(j, argc, argv, head);
	 else if (g_flag_p == 1)
	 {
		head = add_to_back(head ,read_from_echo());
		head = regular_read(j,argc,argv,head);
	 }
	 return head;

}
void print_list(t_node *head){
	t_node *tmp = head;
	while(tmp){
		printf("%s\n",tmp->str);
		tmp =tmp->next;
	}
}

int main (int argc, char **argv)
{
  int i;
	i = 0;
	int flag = 0;
	t_node *start = NULL;
    while(argv[i])
    {
			if (strcmp(argv[i],"md5") == 0)
			{
				flag = 1;
				int j = checkerForFlags(argv, i+1);
				start = read_from(j,argc,argv,start);

				//invalid_flag();
				do_md5(start);
      }
			if (strcmp(argv[i],"sha256") == 0)
      {
				flag = 2;
        int j = checkerForFlags(argv, i+1);
				start = read_from(j,argc,argv,start);
			//	invalid_flag();
			//	do_ss256()

      }
      i++;
    }


}
