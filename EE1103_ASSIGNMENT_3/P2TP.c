#include <stdio.h>
#include <math.h>
double error (double t)  //Returns absolute error
{
   double e;
   e = fabs(t - 0.841347) ;
   return e;
}
double f(double x)   //Returns value of f(x) for input x
{
   double y;
   y = exp((-1)*x*x/2);
   return y;
}
double trapezoid(double a, double b)  //Returns average of function values at the end points
{
   double bisect;
   bisect = (f(a)+f(b))/2.0;
   return bisect;
}
//To compute ERF 2 Replace line 6 : t-0.841347 by t - 0.977249 and Line 28 : x = 1.00000 by  x = 2.000000
int main()
{
   FILE *fp;
   fp = fopen("P2TP.txt","w");
   double i,a,b,c; //i is used to represent continuous intervals, a is the lower limit of interval, b is upper limit of interval, c is average of function values at the end points
   double dx; //Stores length of subinterval
   double x = 1.00000; //To compute ERF 1
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = (x+4.0000)/j;
   double area = 0.00000; //Stores area
   i  = -4.000000;
   for(int k =1;k<=j;k++)
   {
      a = i;
      b = i +dx;
      c = trapezoid(a,b);
      area = area + dx*c;
      i = i + dx;
   }
   area = area*(1/sqrt(2*(M_PI)));
   printf("The area enclosed is %lf\n",area);
   double et;   //Stores absolute error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}
