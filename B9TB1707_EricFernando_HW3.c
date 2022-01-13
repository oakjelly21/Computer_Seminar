#include <stdio.h>
#include <math.h>
int main(void){
    // Your code here!
    long double tant1 = 0.0;//stores value of atan 1/5
    long double tant2 = 0.0;// stores value of atan 1/239
    long double x2 = 1.0/239.0;//stores value of 1/239
    for (int i =1; i<=30;i++)
    {
        tant1 += (pow(-1,i+1)*(pow(0.2,(2*i)-1))/((2*i)-1));
        tant2 += (pow(-1,i+1)*(pow(x2,(2*i)-1))/((2*i)-1));
    }
    printf("Pi = %Lf",(16*tant1)-(4*tant2));
}
