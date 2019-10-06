#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>


int fflag=0;
int frobcmp (char const * a , char const * b)
{
   
  int i=0;
  while (a[i] != ' ' && b[i] != ' ')
    {
      if ((a[i] ^ 0x2A) > (b[i] ^ 0x2A))
	return 1;
      else
	if ((a[i] ^ 0x2A) < (b[i] ^ 0x2A))
	  return -1;
      i++;
    }
  if (a[i] != ' ' && b[i] == ' ')
    return 1;
  else if (a[i] == ' ' && b[i]== ' ')
    return 0;
  else 
    return -1;

}
int castedfrobcomp(const void* a, const void* b)
{
  return frobcmp(*((const char**) a), *((const char**) b));
}

void checkAllocError(void* ptr){
  if(ptr == NULL){
    fprintf(stderr, "memory allocation failed");
    exit(1);
  }
}

void checkIOError() {
  if(ferror(stdin)) {
    fprintf(stderr, "reading failed");
    exit(1);
  }
}
int frobcmpf(char const *a, char const *b)
{
  if ((*a ^ 0x2A) > UCHAR_MAX || (*a ^ 0x2A) < 0 || (*b ^ 0x2A) > UCHAR_MAX || (*b ^ 0x2A) < 0)
    {
        fprintf(stderr, "can't put it in toupper");
        exit(1);
    }
  int i=0;
  while (a[i] != ' ' && b[i] != ' ')
    {
      if (toupper(a[i] ^ 0x2A) > toupper(b[i] ^ 0x2A))
	return 1;
      else
	if (toupper(a[i] ^ 0x2A) < toupper(b[i] ^ 0x2A))
	  return -1;
      i++;
    }
  if (a[i] != ' ' && b[i] == ' ')
    return 1;
  else if (a[i] == ' ' && b[i]== ' ')
    return 0;
  else 
    return -1;
}

int castedfrobcompf(const void* a, const void* b)
{
  return frobcmpf(*((const char**) a), *((const char**) b));
}

int  main(int argc,  char* argv[])
{
  if (argc > 2) {
    fprintf(stderr, "invalid number of operands");
    exit(1);
    }

  if (argc==2)
    {
      char* flag = argv[1];
      if(flag[0]!='-' ||flag[1]!='f')
	{
	  fprintf(stderr, "Invalid input");
	  exit(1);
	}
      fflag = 1;
    }

  struct stat sbuffer;
  int ret = fstat(STDIN_FILENO, &sbuffer);

  /*
  if (!S_ISREG(buffer.st_mode))
    {fprintf(stderr, "file is not regular");
      exit(1);
    }
  else
  {*/
  
  char *jin=(char*) malloc(sizeof(char) * (sbuffer.st_size+1));

  if(sbuffer.st_size)
    {
      int rreturn= read(STDIN_FILENO, jin, sbuffer.st_size);
      if (rreturn<0)
	{
	  fprintf(stderr,"cannot read");
	  exit(1);
	}
    }
      //if it grows
      int buffersize=sbuffer.st_size+1;
      char cur;
      int tempcount=sbuffer.st_size;
      while(read(STDIN_FILENO, &cur, 1) == 1)
	{
	  checkIOError();

	  if (tempcount+3>=buffersize)
	    {
	      buffersize=buffersize*2;
	      jin=(char*) realloc(jin,buffersize * sizeof(char));
	    }
	  jin[tempcount]=cur;
	  tempcount++;

	  }
	     
      //apeend a space if needs to
        if(jin[tempcount-1]!=' ')
	{
	  jin[tempcount]=' ';
	  tempcount++;
	  }
      
	//fprintf(stderr,"make them into arrays");

      char** allWords = (char**)malloc(sizeof(char*) * 100);
      allWords[0]=jin;
      int countline=1;
      int linesize=100;

     
      for(int i=0;i<tempcount;i++)
	{
	  if (linesize-1<=countline)
	    {
	      linesize=linesize*2;
	      allWords= (char**) realloc(allWords, sizeof(char*)*linesize);
	    }
	  if(jin[i]==' '&&i!=tempcount-1)
	    {
	      allWords[countline]=&(jin[i+1]);
	      countline++;
	    }

	}

      
      if(fflag==0)
	qsort(allWords, countline,sizeof(char*),&castedfrobcomp);
      else
	qsort(allWords, countline, sizeof(char*),&castedfrobcompf);


      // printf("//output");
      const char SPACE = ' ';
      const char NEWLINE = '\n';
      for (int i = 0; i < countline; i++)
	{
	  char *c = allWords[i];
	  while (*c != ' ' && *c != '\n') {
	    write(STDOUT_FILENO, c, 1);
	    c++;
	  }
	   write(STDOUT_FILENO, &SPACE, 1);
	}
 

      //free memory
      free(jin);
      free(allWords);
      
    

    
}
