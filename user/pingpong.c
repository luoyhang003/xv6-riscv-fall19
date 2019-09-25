#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int parent_fd[2];
  int child_fd[2];
  int buff[4];

  if(argc >=2) {
  	printf("pingpong: argument undesired.\n");
  	exit();
  }

  pipe(parent_fd);
  pipe(child_fd);
  
  if(fork() == 0) {
  	int child_pid = getpid();
  	read(parent_fd[0], buff, 4);
    printf("%d: received %s\n", child_pid, buff);
    write(child_fd[1], "pong", 4);
    exit();
  } else {
    int parent_pid = getpid();
    write(parent_fd[1], "ping", 4);
    read(child_fd[0], buff, 4);
    printf("%d: received %s\n", parent_pid, buff);
    exit();
  }

  exit();
}