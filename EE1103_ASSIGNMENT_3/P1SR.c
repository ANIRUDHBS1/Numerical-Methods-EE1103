#include <stdio.h>
#include <math.h>
double error (double t)  //Returns absolute error
{
   double e;
   e = fabs(t - 2.0);
   return e;
}
double f(double x)  //Returns value of f(x) for input x
{
   double y;
   y = sin(x);
   return y;
}
int main()
{
   FILE *fp;
   fp = fopen("P1SR.txt","w");
   double l,a; //l and a is used to represent continuous intervals
   double pi = M_PI; //Stores value of $\pi$
   double dx; //Stores length of subinterval
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = pi/j;
   double area = 0;  //Stores area
    l = 0.00000;
    for (int i = 0; i <= j; i++) {
            a =l;
        if (i == 0 || i == j)
            area += f(a);
        else if (i % 2 != 0)
            area += 4 * f(a);
        else
            area += 2 * f(a);
        l = l + dx;
    }
    area = area * (dx/3);
   printf("The area enclosed is %lf\n",area);
   double et;  //Stores absolute error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}
