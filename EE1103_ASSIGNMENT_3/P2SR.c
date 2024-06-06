#include <stdio.h>
#include <math.h>
double error (double t) //Returns absolute error
{
   double e;
   e = fabs(t - 0.841347) ;
   return e;
}
double f(double x) //Returns value of f(x) for input x
{
   double y;
   y = exp((-1)*x*x/2);
   return y;
}
//To compute ERF 2 Replace line 6 : t-0.841347 by t - 0.977249 and Line 22 : x = 1.00000 by  x = 2.000000
int main()
{
   FILE *fp;
   fp = fopen("P2SR.txt","w");
   double l,a,b,c,d,e; //l and a is used to represent continuous intervals
   double x; //To compute ERF 1
   x = 1.0000;
   double dx; //Length of subinterval is stored in dx
   fprintf(fp,"n\t Area \t Error\n");
   for(int j = 4;j<=1024;j=j*2){
   dx = (x+4.000000)/j;
   double area = 0;  //Stores area
   l = -4.000000;   //Shows starting point of interval
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
    double pi = M_PI;    //Stores value of $\pi$
    area = area/sqrt(2*pi);
   printf("The area enclosed is %lf\n",area);
   double et;      //Stores absolute error
   et = error(area);
   printf("The error is %lf\n",et);
   fprintf(fp,"%d\t %lf\t %lf\n",j,area,et);
   }
}
