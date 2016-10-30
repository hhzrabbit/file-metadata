#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


void printInfo(char *s){
  struct stat * fileinfo = (struct stat*) malloc (sizeof(struct stat));
  stat(s, fileinfo);
  printf("file: %s\n", s);
  //l for long
  printf("size: %ld bytes\n", fileinfo -> st_size);
  // \o == octal
  printf("mode (permissions): %o\n", fileinfo -> st_mode); 
  //ctime takes pointer to time_t var
  printf("time of last access: %s\n", ctime( & (fileinfo -> st_atime) ) );
}

int main(){
  printInfo("main.c");
  return 0;
}
