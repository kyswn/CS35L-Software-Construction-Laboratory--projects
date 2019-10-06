#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) 
{
  if (argc!=3)
    { fprintf(stderr, "doesn't have right number of argument");
      exit(1);}

  const char * from =argv[1];
  const char * to=argv[2];
  if(strlen(from)!=strlen(to))
    {fprintf(stderr, "from and to have different length");
      exit(1);
    }

  for(int i=0;i<strlen(from);i++)
    {
      for(int j=i+1;j<strlen(from);j++)
	{
	  if(from[i]==from[j])
	    {
	      fprintf(stderr, "from has duplicates");
	      exit(1);
	    }
	}
    }
  char a;
  ssize_t b=read(0,&a,1);
  if(b!=1)
    {
    fprintf(stderr,"nothing to read");
    exit(1);
    }
  while(b==1)
    {
      int i=0;
      for(i=0;i<strlen(from);i++)
	{
	  if(a==from[i])
	    {
	      char c=to[i];
	      write(1, &c, 1);
	      break;
	    }
	}
      if(i==strlen(from))
	    write (1,&a,1);
      b=read(0,&a,1);
    }
}
