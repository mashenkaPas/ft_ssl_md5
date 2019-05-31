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
int		g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};



// ROtate v Left by amt bits
unsigned rol( unsigned v, short amt )
{
    unsigned  msk1 = (1<<amt) -1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

unsigned *md5( const char *msg, int mlen)
{
    static Digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
    static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22};
    static short rot1[] = { 5, 9,14,20};
    static short rot2[] = { 4,11,16,23};
    static short rot3[] = { 6,10,15,21};
    static short *rots[] = {rot0, rot1, rot2, rot3 };
  //  static unsigned kspace[64];
    //static unsigned *k;

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

    //if (k==NULL) k= calcKs(kspace);

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
        for (p = 0; p<4; p++)
        {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++)
            {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + g_k[q+16*p] + mm.w[g], rotn[q%4]);

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


// int i= 0;
//     while (i<64){
//       printf("%d\n",g_k[i]);
//       printf("%d\n",kspace[i]);
//       printf("%d\n",k[i] );
//       i++;
//     }

    if( msg2 )
        free( msg2 );

    return h;
}
////////////////////////////////////////////////////////

static size_t	digit_count(long nb, int base)
{
	size_t		i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base(int value, int base)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;
	int		sign;

	if (base < 2 || base > 16)
		return (0);
	if (base == 10 && value == -2147483648)
		return ("-2147483648");
	sign = 0;
	if (base == 10 && value < 0)
		sign = 1;
	if (value < 0)
		value = -value;
	if (value == 0)
		return ("0");
	tab_base = (char *)malloc(sizeof(char) * 17);
	tab_base = "0123456789abcdef";
	taille = digit_count(value, base);
	taille += (sign ? 1 : 0);
	ret = (char *)malloc(sizeof(char) * (taille + 1));
	i = 1;
	sign ? (ret[0] = '-') : 0;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	return (ret);
}
//////////////////////




//sha256
#define uchar unsigned char
//#define uint unsigned int

#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

typedef struct {
	uchar data[64];
	unsigned int datalen;
  unsigned int bitlen[2];
	unsigned int state[8];
} SHA256_CTX;

unsigned int k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

void SHA256Transform(SHA256_CTX *ctx, uchar data[])
{
	unsigned int a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

void SHA256Init(SHA256_CTX *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen[0] = 0;
	ctx->bitlen[1] = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void SHA256Update(SHA256_CTX *ctx, char data[], unsigned int len)
{
  unsigned int i;
	for ( i = 0; i < len; ++i) {
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64) {
			SHA256Transform(ctx, ctx->data);
			DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 512);
			ctx->datalen = 0;
		}
	}
}

void SHA256Final(SHA256_CTX *ctx, uchar hash[])
{
  unsigned int i;
	 i = ctx->datalen;

	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else {
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		SHA256Transform(ctx, ctx->data);
		memset(ctx->data, 0, 56);
	}

	DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], ctx->datalen * 8);
	ctx->data[63] = ctx->bitlen[0];
	ctx->data[62] = ctx->bitlen[0] >> 8;
	ctx->data[61] = ctx->bitlen[0] >> 16;
	ctx->data[60] = ctx->bitlen[0] >> 24;
	ctx->data[59] = ctx->bitlen[1];
	ctx->data[58] = ctx->bitlen[1] >> 8;
	ctx->data[57] = ctx->bitlen[1] >> 16;
	ctx->data[56] = ctx->bitlen[1] >> 24;
	SHA256Transform(ctx, ctx->data);

	for (i = 0; i < 4; ++i) {
		hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

char* SHA256(char *data) {
	int strLen = strlen((char*)data);
	SHA256_CTX ctx;
	unsigned char hash[32];
	char* hashStr = malloc(65);
	strcpy(hashStr, "");

	SHA256Init(&ctx);
	SHA256Update(&ctx, data, strLen);
	SHA256Final(&ctx, hash);

	char s[3];
	for (int i = 0; i < 32; i++) {
		sprintf(s, "%02x", hash[i]);
		strcat(hashStr, s);
	}
//printf("%02x\n",hashStr );
	return hashStr;
}









/////////////////////
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>


typedef struct s_node
{
	// char	*str;
  char  *name;
  char  *hash;
	struct s_node *next;
}							t_node;

typedef struct s_flag
{
  char  name;
  int seen_before;
	struct s_flag *next;
}							t_flag;
t_node *start = NULL;


void	lstdel_node(t_node **list)
{
	t_node	*temp;

	if ((*list))
	{
		temp = (*list)->next;
		(*list)->next = NULL;
		ft_strdel(&(*list)->name);
		ft_strdel(&(*list)->hash);
		ft_memdel((void**)&(*list));
		lstdel_node(&(temp));
	}
}

void	lstdel_flag(t_flag **list)
{
	t_flag	*temp;

	if ((*list))
	{
		temp = (*list)->next;
		(*list)->next = NULL;
		free(&(*list)->name);
		free(&(*list)->seen_before);
		ft_memdel((void**)&(*list));
		lstdel_flag(&(temp));
	}
}

char *read_from_echo()
{
	 char	*line;
	 get_next_line(0,&line);
  char *new_str = ft_strjoin(line,"\n");
  return(new_str);
}

void add_to_back( char *str, char *hash)
{
  t_node *ptm;
  if(!start)
  {
    start =(t_node*)malloc(sizeof(t_node));
    start->name = ft_strdup(str);
    start->hash = ft_strdup(hash);
    start->next = NULL;
    return ;
  }
  ptm = start;
  while(ptm->next != NULL)
    ptm = ptm->next;
  t_node *node = (t_node*)malloc(sizeof(t_node));
  node->name = ft_strdup(str);
  node->hash = ft_strdup(hash);
  node->next = NULL;
  ptm->next = node;
}

t_flag *add_to_flag(t_flag *head, char name , int seen_before)
{
  t_flag *ptm;
  if(!head)
  {
	   head =(t_flag*)malloc(sizeof(t_flag));
	   head->name = name;
     head->seen_before = seen_before;
	   head->next = NULL;
	return head;
  }
  ptm = head;
  while(ptm->next != NULL)
	 ptm = ptm->next;
  t_flag *node = (t_flag*)malloc(sizeof(t_flag));
  node->name = name;
  node->seen_before = seen_before;
  node->next = NULL;
  ptm->next = node;
  return head;
}

void print_flag(t_flag *head)
{
	t_flag *tmp = head;
	while(tmp){
		printf("%c\n", tmp->name);
		tmp = tmp->next;
	}
}


int check_have_seen(t_flag *flag, char name)
{
  t_flag *tmp = flag;
  while (tmp)
  {
    if(tmp->name == name)
    return 1;
    tmp = tmp->next;
  }
  return 0;
}


char *do_md5_str (char *str){
  int j,k;
  char *newstr;
  char *tmp;

      newstr = ft_strnew(1);
    //  ft_bzero(newstr,1);

      char *msg = ft_strdup(str);
      unsigned *d = md5(msg, strlen(msg));
      WBunion u;
      for (j=0;j<4; j++)
      {
        u.w = d[j];
      for (k=0;k<4;k++)
      {
          tmp = ft_itoa_base(u.b[k],16);
          if(ft_strlen(tmp) == 1)
            tmp = ft_strjoin("0",tmp);
          newstr = ft_strjoin(newstr,tmp);
          //printf("%02x",u.b[k]);

      }
      }

      newstr[33]='\0';
//free(str);
//free(tmp);
return newstr;
}


t_flag *checkerForFlags(char **argv, int i , t_flag *flag, char* (*fun)(char *) )
{
	int j;
	int end = 0;

	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '-'  && end != 1)
		{
			while(argv[i][j])
			{
				if(argv[i][j] == 'p')
        {
            char *data = ft_strdup(read_from_echo());
            char *hhh = fun(data);
            if(check_have_seen(flag, 'p') == 0  && check_have_seen(flag, 'q') == 0 &&check_have_seen(flag, 'r') == 0)
            {
               add_to_back(data, hhh);
              flag = add_to_flag(flag, 'p', 1);
            }
            if(check_have_seen(flag, 'p') == 0  && check_have_seen(flag, 'q') == 1)
            {
             add_to_back("", hhh);
              flag = add_to_flag(flag, 'p', 1);
            }
            if(check_have_seen(flag, 'p') == 0  && check_have_seen(flag, 'q') == 0 && check_have_seen(flag, 'r') == 1)
            {
               add_to_back(hhh, data);
              flag = add_to_flag(flag, 'p', 1);
            }
           free(data);
           free(hhh);
        }
				else if (argv[i][j] == 'q')
        {
          if(check_have_seen(flag, 'q') == 0 )
            flag = add_to_flag(flag,'q',1);
        }
				else if (argv[i][j] == 'r')
				{
          if(check_have_seen(flag, 'r') == 0 )
            flag = add_to_flag(flag,'r',1);
        }
				else if (argv[i+1] && argv[i][j] == 's')
				{
          char *str = ft_strdup(argv[i+1]);
          char *hhh = fun(str);
          flag = add_to_flag(flag, 's', 1);
          if(check_have_seen(flag, 'q') == 0 && check_have_seen(flag, 'r') == 0 )
             add_to_back(str,hhh);
          else if(check_have_seen(flag, 'q') == 1)
              add_to_back(hhh, "");
          else if(check_have_seen(flag, 'r') == 1 && check_have_seen(flag, 'q') == 0)
               add_to_back(hhh, str);
         free(str);
         free(hhh);
          return checkerForFlags(argv, i+2 , flag, fun );
        }
				else
        {
          char c = argv[i][1];
            flag = add_to_flag(flag,'E',1);
            add_to_back("illigal option --", &c);
            add_to_back("ERROR","usage: md5 [-pqrt] [-s string] [files ...]");
            return flag;
        }
				j++;
			}
		}
		if (argv[i][0] != '-')
			end = 1;
		if (end == 1)
			return  flag;
		i++;
	}
	return flag;
}



char *read_opt(char **argv, int j)
{
  char *new_str;
  char *lll;
  int status;
  new_str = ft_strnew(1);
  int fd = open(argv[j], O_RDONLY);
  if(fd == -1)
  {
    add_to_back(argv[j], ": No such file or directory");
    return NULL;
  }
  if(fd > 1)
  {
  	while((status = get_next_line(fd, &lll)) == 1)
    new_str = ft_strjoin(new_str,ft_strjoin(lll ,"\n"));
  	new_str[ft_strlen(new_str)] = '\0';
  }
  close(fd);
  	return new_str;
}

 void read_from(int j,int argc,char **argv, t_flag *flag, char* (*fun)(char *))
{
	char	*lll;
  char  *tmp;
	int		status;

	 if((argc ) == 2)
	 	{
      tmp = read_from_echo();
      lll = fun(tmp);
      add_to_back("",lll);
      free(lll);
      free(tmp);
    }
	  else
    {
      while (j < argc)
      {
        lll = read_opt(argv,j);
        if(lll)
        {
          tmp = fun(lll);
          if(check_have_seen(flag, 'q') == 0 && check_have_seen(flag, 'r') == 0)
            add_to_back(argv[j],tmp);
          if( check_have_seen(flag, 'q') == 1)
            add_to_back("",tmp);
          if( check_have_seen(flag, 'q') == 0 && check_have_seen(flag, 'r') == 1)
            add_to_back(tmp,argv[j]);
          free(lll);
          free(tmp);
        }
        j++;
      }

    }

}

void print_list(char *format)
{
	t_node *tmp = start;
	while(tmp)
  {
    if(ft_strcmp("ERROR",tmp->name)==0)
    {
      printf("%s\n",tmp->hash);
      return;
    }
		  printf("%s %s\n",tmp->name,tmp->hash);
		tmp = tmp->next;
	}
}

int find_files(char **argv){
  int i = 2;
  while(argv[i])
  {
    if( i!=0 && ft_strcmp(argv[i-1],"-s") !=0  && argv[i][0] !='-')
      return i;
    i++;
  }
  return i;
}

char* (*builtin_func[]) (char *)= {&do_md5_str, &SHA256};



int main( int argc, char *argv[] )
{
    int i;
    i = 1;
    t_flag *flag = NULL;
      while(argv[i])
      {
        if (ft_strcmp(argv[i], "md5") == 0)
        {
          flag = checkerForFlags(argv, i+1, flag, builtin_func[0]);
          int j = find_files(argv);
          read_from(j,argc,argv,flag, builtin_func[0]);
          print_list("md5");
        }
        if (ft_strcmp(argv[i],"sha256") == 0)
        {
          flag = checkerForFlags(argv, i+1, flag, builtin_func[1]);
          int j = find_files(argv);
          read_from(j,argc,argv,flag, builtin_func[1]);
          print_list("sha-256");
        }
        i++;
      }
      lstdel_node(&(start));
      if(!flag)
          lstdel_flag(&(flag));
    return 0;
}
