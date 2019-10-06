#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

int main()

{
  char * curWord = (char*)malloc(sizeof(char)*100);
  char ** allWords = (char**)malloc(sizeof(char*)*100);
  int size_str=100, size_line=100, count_str=0, count_line=0;
 
  char cur;
  int isEndOfFile;
  if(cur == EOF)
    return 0;
  else
    isEndOfFile=0;
  while(!isEndOfFile)
    {
      cur=getchar();
      checkIOError();

      if(cur == EOF)
	{
	  isEndOfFile=1;
	  cur = ' ';
        }

      if(size_str <= count_str)
	{
	  size_str= size_str* 2;
	  curWord = (char*) realloc(curWord, sizeof(char) * size_str);
	  checkAllocError(curWord);
        }

      curWord[count_str]=cur;
      count_str++;
      if(cur==' ')
	{
	  if (size_line<=count_line)
	    {
	      size_line=size_line*2;
	      allWords= (char**) realloc(allWords, sizeof(char*) *size_line);
	    }

	  allWords[count_line]=curWord;
	  count_line++;
	  curWord=(char*) malloc(sizeof(char)*100);
	  count_str=0;
	  size_str=100;
	}



    }
  qsort(allWords, count_line, sizeof(char*),&castedfrobcomp);

  unsigned long a,b,c;
  for(a = 0; a < count_line; a++)
    {
      for (b = 0;; b++)
	{
	  putchar(allWords[a][b]);
	  if (allWords[a][b] == ' ')
	    break;
	}
    }
 
  for (c = 0; c <size_line ; c++)
    free(allWords[c]);
  free(allWords);
   

  exit(0);
}

