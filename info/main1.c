#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef union uwb {
    unsigned w;
    unsigned char b[4];
} WBunion;

typedef unsigned Digest[4];

unsigned f0( unsigned abcd[] ){
    return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);}

unsigned f1( unsigned abcd[] ){
    return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);}

unsigned f2( unsigned abcd[] ){
    return  abcd[1] ^ abcd[2] ^ abcd[3];}

unsigned f3( unsigned abcd[] ){
    return abcd[2] ^ (abcd[1] |~ abcd[3]);}

typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned *calcKs( unsigned *k)
{
    double s, pwr;
    int i;

    pwr = pow( 2, 32);
    for (i=0; i<64; i++) {
        s = fabs(sin(1+i));
        k[i] = (unsigned)( s * pwr );
    }
    return k;
}

// ROtate v Left by amt bits
unsigned rol( unsigned v, short amt )
{
    unsigned  msk1 = (1<<amt) -1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

unsigned *md5( const char *msg, int mlen)
{
    static Digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
//    static Digest h0 = { 0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210 };
    static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22};
    static short rot1[] = { 5, 9,14,20};
    static short rot2[] = { 4,11,16,23};
    static short rot3[] = { 6,10,15,21};
    static short *rots[] = {rot0, rot1, rot2, rot3 };
    static unsigned kspace[64];
    static unsigned *k;

    static Digest h;
    Digest abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k==NULL) k= calcKs(kspace);

    for (q=0; q<4; q++) h[q] = h0[q];   // initialize
    {
        grps  = 1 + (mlen+8)/64;
        msg2 = malloc( 64*grps);
        memcpy( msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64*grps){ msg2[q] = 0; q++ ; }
        {
//            unsigned char t;
            WBunion u;
            u.w = 8*mlen;
//            t = u.b[0]; u.b[0] = u.b[3]; u.b[3] = t;
//            t = u.b[1]; u.b[1] = u.b[2]; u.b[2] = t;
            q -= 8;
            memcpy(msg2+q, &u.w, 4 );
        }
    }

    for (grp=0; grp<grps; grp++)
    {
        memcpy( mm.b, msg2+os, 64);
        for(q=0;q<4;q++) abcd[q] = h[q];
        for (p = 0; p<4; p++) {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);

                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p=0; p<4; p++)
            h[p] += abcd[p];
        os += 64;
    }

    if( msg2 )
        free( msg2 );

    return h;
}



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
					g_flag_q = 1;
				else if (argv[k][j] == 'r')
					g_flag_r = 1;
				else if (argv[k][j] == 's')
					{
            g_flag_s = 1;
            return k;
          }
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
  char *new_str = ft_strjoin(line,"\n");
  return(new_str);
}

t_node *flag_s (int j, char  **argv ,t_node *head)
{
  char  *line;
  if(g_flag_s ==1 && ft_strcmp("-s",argv[j-1]) == 0)
  {
    line = ft_strdup(argv[j]);
    head = add_to_back(head, line);
  }
  return head;
}

t_node *regular_read(int j,int argc, char  **argv ,t_node *head){
	char	*line;
	char	*lll;
	int		status;
	char *new_str;
	new_str =ft_strnew(1);
	ft_bzero(new_str,ft_strlen(new_str));

	// while (j < argc)
	// {
	// 	int fd = open(argv[j], O_RDONLY);
		// if(( ft_strcmp(argv[j - 1],"-s") == 0 ) || (fd == -1 && argv[j - 1][(ft_strlen(argv[j-1]) - 1)] == 's' && g_flag_s ==1))
		// {
		// 	line = ft_strdup(argv[j]);
		// 	head = add_to_back(head, line);
		// }
    while((ft_strcmp(argv[j],"-s") == 0  && g_flag_s == 1))
    {
      j++;
       head   = flag_s(j, argv, head);
       j++;
        j = checkerForFlags(argv,j);
    }
    if(g_flag_p == 1)
    {
      head = add_to_back(head ,read_from_echo());
      //head = regular_read(j,argc,argv,head);
    }
  //  j++;
    // int  k = checkerForFlags(argv,j-1);
    while (j < argc)
  	{
  		int fd = open(argv[j], O_RDONLY);
      if(fd == -1)
			{
        printf("md5: %s: No such file or directory\n" ,argv[j] );
      }
		if(fd > 1)
		{
			while((status = get_next_line(fd, &lll)) == 1)
        new_str = ft_strjoin(new_str,ft_strjoin(lll ,"\n"));
			new_str[ft_strlen(new_str)] = '\0';
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

	 if(j == argc)
	 		head = add_to_back(head ,read_from_echo());
	 else if (g_flag_p == 1)
	 {
		head = add_to_back(head ,read_from_echo());
		head = regular_read(j,argc,argv,head);
	 }
   else if (g_flag_p == 0)
    head =	regular_read(j, argc, argv, head);
	 return head;

}
void print_list(t_node *head){
	t_node *tmp = head;
	while(tmp){
		printf("%s",tmp->str);
		tmp =tmp->next;
	}
}

void do_md5(t_node *head){
  int j,k;
  t_node *tmp = head;
  while(head)
  {
      char *msg = ft_strdup(head->str);
      printf("\n%s\n",msg );
      unsigned *d = md5(msg, strlen(msg));
      WBunion u;
      printf("= 0x");
      for (j=0;j<4; j++)
      {
        u.w = d[j];
      for (k=0;k<4;k++)
        printf("%02x",u.b[k]);
      }
      head = head->next;
  }
}



int main( int argc, char *argv[] )
{
    int i;
    i = 0;
    int flag = 0;
    t_node *start = NULL;
      while(argv[i])
      {
        if (strcmp(argv[i], "md5") == 0)
        {
          int j = checkerForFlags(argv, i+1);
          start = read_from(j,argc,argv,start);
          invalid_flag();
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


    printf("\n");

    return 0;
}
