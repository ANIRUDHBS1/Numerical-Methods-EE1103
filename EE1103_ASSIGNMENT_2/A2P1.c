#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double error(double x)   //Function to find error with respect to PI. 
{
   double y;
   y = fabs(x-(M_PI))/(M_PI) *100;
   return y;
}
int main()
{
    srand(3141592653);         //Seed to generate random numbers
    int n,narc = 0;            //n is the number of darts, narc is the number of darts landing in the circle r =1
    FILE *fp;                  // To store data of n, value of pi estimated and error
    fp = fopen("EstimatePI.txt","a");
    double x,y,r;              //Uniform random samples x and y; r is their distance from the origin
    printf("Enter the value of n\n");
    scanf("%d",&n);
    int i;                     //Looping Variable
    for(i=1;i<=n;i++) 
    {
       x = (float) rand()/RAND_MAX;
       y = (float) rand()/RAND_MAX;
       r = sqrt(x*x+y*y);
       if(r<=1.00000)
       narc +=1;
    }
    double p,pi;                   //p stores the estimate of pi, pi stores actual value of pi
    pi = M_PI;
    p = (float) narc/n * 4;
    double et;                     //et stores error
    et = error(p);
    fprintf(fp,"%d\t %lf\t %lf\n",n,p,et);
    printf("n\t PI\t Absolute error\n");
    printf("%d\t %lf\t %lf\n",n,p,et);
    fclose(fp);
}
