#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef linux
#include <unistd.h>
#endif
int main(void){

  char Uname[10];
  char pass[10];
  printf("Enter Username (1 to 10 characters long)\n");
  scanf("%s",Uname);
  printf("Enter Password (1 to 10 characters long)\n");
  scanf("%s",pass);
  printf("Entered Username: %s\nEntered Password: %s\nPreparing to save.....\n\n",Uname,pass );
  #ifdef _WIN32
    Sleep(1000);
  #endif
  #ifdef linux
    sleep(10);
  #endif
  FILE *fin;
  FILE *fout;
  fout = fopen("HW2.txt","w");
  fprintf(fout,"%s\n",Uname);
  fprintf(fout,"%s\n",pass);
  fclose(fout);
  if((fin = fopen("HW2.txt","r"))==NULL)
  {
      printf("BIG OOOF\n");
      exit(1);
  }
  char buff[100];
  printf("The Username stored is %s\n",fgets(buff,100,fin));
  printf("The Password stored is %s\n",fgets(buff,100,fin));
  printf("Save Complete");
  return 0;
}
