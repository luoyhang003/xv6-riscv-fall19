#include "kernel/types.h"
#include "user/user.h"

void
redirect(int i, int p[])
{
  close(i);

  dup(p[i]);

  close(p[0]);
  close(p[1]);
}

void
cull(int prime)
{
  int n;

  while(read(0, &n, sizeof(n))) {
  	if(n % prime != 0) {
  		write(1, &n, sizeof(n));
  	}
  }
}

void
seive()
{
  int p[2];
  int prime;

  while(read(0, &prime, sizeof(prime))) {
  	pipe(p);
	printf("prime %d\n", prime);
  	if(fork() != 0) {
  		redirect(0, p);
  		continue;
  	} else {
  		redirect(1, p);
  		cull(prime);
  	}
  }
}

void
source()
{
  int i;

  for(i = 2; i < 36; i++) {
  	write(1, &i, sizeof(i));
  }
}

int main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if(fork() != 0) {
  	redirect(0, p);
  	seive();
  } else {
    redirect(1, p);
    source();
  }
  exit();
}