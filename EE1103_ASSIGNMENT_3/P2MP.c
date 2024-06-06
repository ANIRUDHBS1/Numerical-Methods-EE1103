#include <stdio.h>
#include <math.h>
double error (double t) //To compute Absolute Error
{
   double e;
   e = fabs(t - 0.841347) ;
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
   y = exp((-1)*x*x/2);
   return y;
}
//To compute ERF 2 Replace line 6 : t-0.841347 by t - 0.977249 and Line 28 : x = 1.00000 by  x = 2.000000
int main()
{
   FILE *fp;
   fp = fopen("P2MP.txt","w");
   double i,a,b,c;  //i is used to represent continuous intervals, a is the lower limit of interval, b is upper limit of interval, c is mid point of interval
   double x; //To calculate ERF 1
   x = 1.0000;
   double dx; //Stores length of subinterval
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = (x+4.000000)/j;
   double area = 0.0000;  //Stores area
   i = -4.000000;
   for(int k =1;k<=j;k++)
   {
      a = i;
      b = i +dx;
      c = midpoint(a,b);
      area = area + dx*f(c);
      i = i + dx;
   }
   area = area*(1/sqrt(2*(M_PI)));
   printf("The area enclosed is %lf\n",area);
   double et;        //Stores absolute error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}
