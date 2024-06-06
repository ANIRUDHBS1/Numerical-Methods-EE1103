#include <stdio.h>
#include <math.h>
double error (double t) //Returns value of absolute error
{
   double e;
   e = fabs(t - 2.0);
   return e;
} 
double f(double x)  //Returns the value of function f(x) for x
{
   double y;
   y = sin(x);
   return y;
}
double trapezoid(double a, double b) //Returns average of function values at the end points
{
   double bisect;
   bisect = (f(a)+f(b))/2.0;
   return bisect;
}
int main()
{
   FILE *fp;
   fp = fopen("P1TP.txt","w");
   double i,a,b,c; //i is used to represent continuous intervals, a is the lower limit of interval, b is upper limit of interval, c is average of function values at the end points
   double pi = M_PI; //Stores value of $\pi$
   double dx;  //Stores length of sub-interval
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = pi/j;
   double area = 0;  //stores area 
   i = 0.000000;
   for(int k =1;k<=j;k++)
   {
      a = i;
      b = i +dx;
      c = trapezoid(a,b);
      area = area + dx*c;
      i = i + dx;
   }
   printf("The area enclosed is %lf\n",area);
   double et;  //Stores error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}
