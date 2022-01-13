#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct information {
  char name[256];
  int age;
  char address[256];
  int zip_code;
};
typedef struct information Info;

int main(void)
{
  Info information[100];
  FILE *fp; /* File pointer */
  int num; /* Number of people to read */
  fp = fopen("info.dat", "r");
  fscanf(fp, "%d", &num);
  for (int i=0;i<num;i++)
    {
      fscanf(fp, "%s%d%s%d\n",
  	         information[i].name, &(information[i].age),
  	         information[i].address, &(information[i].zip_code));
    }
  fclose(fp);
  int choice = 0;
  while (choice!=4)
  {
    printf("Enter 1 to see directory,\n2 to add new address,\n3 to delete address,\nand 4 to quit\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:
        printf("      name        age      address    zipcode\n");
        for (int i=0; i < num; i++ )
        {
      /* Print data to the screen */
          printf("%15s %5d %15s %d\n", information[i].name, information[i].age, information[i].address, information[i].zip_code);
          }
          break;
        case 2:
          if(num==100)
            printf("Sorry directory is full delete an entry first\n");
          else
          {
            printf("Enter the info in proper format no commas, in a single line seprated by a single wite space.\n");
            scanf("%s%d%s%d",
        	         information[num].name, &(information[num].age),
        	         information[num].address, &(information[num].zip_code));
            num++;
          }
          printf("%s",information[num].name);
          break;
        case 3:
         printf("Enter name to delete\n");
         char dname[256];
         scanf("%s",dname);
         int flag  = 0;
         for (int i = 0;i<num;i++)
         {
            //printf("%s",information[i].name);
            if (strcmp(dname,information[i].name)==0)
            {
              for (int j = i;j+1<num;j++)
              {
                information[j] = information[j+1];
              }
              flag =1;
              break;
            }
         }
         if (flag==1)
          num--;
         else
          printf("element not found\n");
        break;
        case 4:
        break;
        }
      }
    FILE *fp2;
    fp2 = fopen("info.dat", "w");
    fprintf(fp2,"%d\n",num);
    //printf("%d",num);
    for (int i = 0;i<num;i++)
    {
      fprintf(fp2,"%s %d %s %d\n", information[i].name, information[i].age, information[i].address, information[i].zip_code);
    }
    fclose(fp2);
  }
