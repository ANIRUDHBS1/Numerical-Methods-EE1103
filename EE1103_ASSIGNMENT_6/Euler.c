#include <stdio.h>
#include <math.h>
#include <time.h>
double f(double x, double y) //This function returns the value of the derivative at a point (xi,yi). It is the differential equation given in the question
{
   double z;
   z = y*x*x*x - 1.5*y;
   return z;
}
double analytical(double t) //Returns the value obtained using the analytical solution of the ODE given in the Question
{
    double x;
    x = exp((t*t*t*t-6*t)/4);
    return x;
}
double error(double x, double y) //Computes the absolute error and returns the same
{
    double e;
    e = fabs(x-y);
    return e;
}
int main()
{
   FILE *fp;
   fp = fopen("Text.txt", "w");
   double xi,yi,yi1,h; //xi - Present x value, yi - Present y value, y+1 - Next y value obtained using Eulers method, h - Interval size
   double et; //Stores absolute error
   int i,n; //i is looping variable, n is number of iterations given by 2/h
   int sw; //Switch variable
   printf("Choose one case : \n");
   printf("1. h=0.10 \n");
   printf("2. h=0.25 \n");
   printf("3. h=0.50 \n");
   scanf("%d",&sw);
   switch(sw)
   {
      case 1:
        h = 0.1;
        n = 20;
        break;
      case 2 :
        h = 0.25;
        n = 8;
        break;
      case 3 :
        h = 0.5;
        n = 4;
        break;
      default :
        printf("Enter a valid choice\n");
   }
   xi = 0; //lower limit
   yi = 1.000; //Initial condition
   clock_t begin = clock();
   printf("Xi\t\t Yi \t\tY_True\t\t Error\n");
   printf("%lf\t %lf\t %lf\t %lf\n",xi,yi,analytical(xi),error(analytical(xi),yi));
   fprintf(fp,"%lf\t %lf\n",xi,yi);
   for(i=1;i<=n;i++)
   {
      yi1 = yi + f(xi,yi)*h;
      xi = xi + h;
      yi = yi1;
      et = error(analytical(xi),yi);
      printf("%lf\t %lf\t %lf\t %lf\n",xi,yi,analytical(xi),et);
      fprintf(fp,"%lf\t %lf\n",xi,yi);
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("The time spent is %lf\n",time_spent);
}
