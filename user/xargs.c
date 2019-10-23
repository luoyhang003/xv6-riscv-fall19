#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
  char buf[1024];
  char *args[MAXARG];

  char *begin;
  char *end;

  if(argc < 2) {
    printf("xargs: missing arguments.\n");
    exit();
  }

  for(int i=1; i<argc; i++)
    args[i-1] = argv[i];
  
  argc--;
  
  read(0, buf, 1024);
  begin = buf;

  while(1) {
    while(*begin == ' ')
      begin++;
    if(*begin == '\n' || *begin == 0)
      break;
    end = begin;
    while(*end != '\n' && *end != ' ')
      end++;
    *end = '\0';

    args[argc++] = begin;
    begin = end + 1;
  }

  if(fork() == 0) {
    exec(argv[1], args);
  }
  wait();
  exit();
}
