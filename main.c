#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <math.h>

void printSize(int size){
  int save = size; //for printing in bytes at the end
  int vals[4]; // [ gb, mb, kb, b ]

  //fill vals array
  int pos = 0;
  int i;
  for (i = 3; i > 0; i--){
    int divisor = pow(1000, i);
    vals[pos] = size / divisor;
    size = size % divisor;
    pos++;
  }
  vals[3] = size;

  //fill labels array
  char * labels[4];
  labels[0] = "GB";
  labels[1] = "MB";
  labels[2] = "KB";
  labels[3] = "B";

  //print size
  for (pos = 0; pos < 4; pos++){
    if (vals[pos])
      printf("%d %s ", vals[pos], labels[pos]);
  }
  printf("(%d bytes)\n", save);
  
}

//mode of area < 8
void printOneArea(int permission){
  char flags[3];
  flags[0] = 'r';
  flags[1] = 'w';
  flags[2] = 'x';
  int i;
  int pos = 0;
  for (i = 2; i >= 0; i--){
    int value = pow(2, i);
    if (permission >= value) {
      printf("%c", flags[pos]);
      permission -= value;
    }
    else
      printf("-");
    pos++;
  }
}

void printPermissions(int permissions){
  permissions %= 512; // get rid of front values

  printOneArea( permissions / 64 ); //owner
  printOneArea( permissions % 64 / 8 ); //group
  printOneArea( permissions % 8 ); //other
  printf("\n");
}

void printInfo(char *s){
  printf("file: %s\n", s);

  struct stat * fileinfo = (struct stat*) malloc (sizeof(struct stat));
  int status = stat(s, fileinfo);

  if (status < 0){ //failed to get stats
    printf("error: %s\n", strerror(errno));
    return;
  }

  printf("size: ");
  printSize(fileinfo -> st_size);

  printf("mode (permissions):");
  printPermissions( fileinfo -> st_mode);

  //ctime takes pointer to time_t
  printf("time of last access: %s\n", ctime( & (fileinfo -> st_atime) ) );
}

int main(){
  printInfo("main.c");
  return 0;
}
