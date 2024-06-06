#include <stdio.h>
#include <math.h>
double f(double x, double y,double h)  //This function returns the value of the derivative at a point (xi,yi). It is the differential equation given in the question
{
   double z;
   z = y + 99999*exp(-(x+h))*h;
   z = z/(1+100000*h);
   return z;
}
double tru(double x) //Returns the value obtained using the analytical solution of the ODE given in the Question
{
    double y;
    y = exp(-x) - exp(-100000*x);
    return y;
}
int main()
{
   FILE *fp;
   fp = fopen("Text.txt","w");
   double xi,yi,yi1,h; //xi - Present x value, yi - Present y value, y+1 - Next y value obtained using Eulers method, h - Interval size
   int i,n; //i is looping variable, n is number of iterations given by 2/h
   xi = 0;
   h = 0.1;
   yi = 0;
   n = 20;
   printf("Xi\t\t Yi\t\t Y_true\n");
   printf("%lf\t %lf\t %lf\n",xi,yi,tru(xi));
   fprintf(fp,"%lf\t %lf\n",xi,yi);
   for(i=1;i<=n;i++)
   {
      yi1 = f(xi,yi,h);
      xi = xi + h;
      yi = yi1;
      printf("%lf\t %lf\t %lf\n",xi,yi,tru(xi));
      fprintf(fp,"%lf\t %lf\n",xi,yi);
   }
}