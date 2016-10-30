#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void printInfo(char *s){
  printf("file: %s\n", s);

  struct stat * fileinfo = (struct stat*) malloc (sizeof(struct stat));
  int status = stat(s, fileinfo);

  if (status < 0){ //failed to get stats
    printf("error: %s\n", strerror(errno));
    return;
  }

  //l for long
  printf("size: %ld bytes\n", fileinfo -> st_size);
  // %o == octal
  printf("mode (permissions): %o\n", fileinfo -> st_mode); 
  //ctime takes pointer to time_t
  printf("time of last access: %s\n", ctime( & (fileinfo -> st_atime) ) );
}

int main(){
  printInfo("main.c");
  return 0;
}
