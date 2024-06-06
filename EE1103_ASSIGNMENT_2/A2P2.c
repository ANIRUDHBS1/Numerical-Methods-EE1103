#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double error(double x)     //Function to find error with respect to PI. 
{
   double y;
   y = fabs(x-(M_PI))/(M_PI) *100;
   return y;
}
int main()
{
     FILE *XX;
     XX = fopen("SampleX.txt","a");
     srand(0);                 //Seed to generate random numbers
     int n;                    //n is used to store how many random numbers we need
     int i;                    //i is the looping variable, counts how many iterations are performed
     double u1,u2,E,x,y;       //u1 and u2 are two uniform distributions(assumed), E is the negative of the natural logarithm of U1, x and y are two Gaussian Distributions (assumed uniform)
     printf("Enter the value of n\n");
     scanf("%d",&n);
     for(i=1;i<=n;i++)
     {
        u1 = (float) rand()/RAND_MAX;
        u2 = (float) rand()/RAND_MAX;
        E = -log(u1);
        x = sqrt(E)*cos(2*(M_PI)*(u2));
        y = sqrt(E)*sin(2*(M_PI)*(u2));
        fprintf(XX,"%lf\n",x);
     }
     fclose(XX);
}
