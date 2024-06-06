#include <stdio.h>
#include <math.h>
double error (double t) //To compute Absolute Error
{
   double e;
   e = fabs(t - 2.0);
   return e;
}
double midpoint(double a, double b) //To compute Mid-Point
{
   double bisect;
   bisect = (a+b)/2.0;
   return bisect;
}
double f(double x)  //Returns f(x) when x is taken input
{
   double y;
   y = sin(x);
   return y;
}
int main()
{
   FILE *fp;
   fp = fopen("P1MP.txt","w");
   double i,a,b,c;   //i is used to represent continuous intervals, a is the lower limit of interval, b is upper limit of interval, c is mid point of interval
   double pi = M_PI; //Stores the value of $\pi$
   double dx; //Stores length of interval
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = pi/j;
   double area = 0;  //Stores area
   i = 0.000000;
   for(int k =1;k<=j;k++)
   {
      a = i;
      b = i +dx;
      c = midpoint(a,b);
      area = area + dx*f(c);
      i = i + dx;
   }
   printf("The area enclosed is %lf\n",area);
   double et;  //Stores absolute error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}