#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc <= 1){
    printf("sleep: argument required.\n");
    exit();
  } else {
  	int sec = atoi(argv[1]);
  	sleep(sec);
  }
  exit();
}