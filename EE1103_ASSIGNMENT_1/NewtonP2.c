#include <stdio.h>
#include <math.h>
double error(double a, double b)   //Computes the error given two inputs a-the present value and b-the previous value
{
   double e;
   e = (fabs(a-b))/fabs(a) * 100.00;   //This formula is used in finding out the approximate error
   return e;
}
double trueerror(double a)     //Evaluates true error
{
   double ans = 0.474572;
   double et;
   et = (fabs(a-ans)/fabs(ans))*100;
   return et;
}
double function(double a) //Returns the value of the function given for a particular input
{
   double v;
   v = -2.00 + 6.0*a - 4.0*a*a+0.5*a*a*a;
   return v;
}
double derivative(double a) //Returns the value of the derivative of the function given for a particular input
{
   double v;
   v = 6.00 - 8.0*a + 1.5*a*a;
   return v;
}
int main()
{
   FILE *fp,*p;
   fp = fopen("GraphP2.txt","w");      //fp is pointer to file that stores the points required to plot the graph
   p = fopen("P2Error.txt","w");      //p is pointer to file that stores the data of errors vs iterations asked
   double xrnew,xrold,ea,et;
   int count =1;
   for(double i=-5.000;i<=5.000;i=i+0.001)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = function(x);
       fprintf(fp,"%lf\t %lf\n",x,y);
   }
   printf("Enter the value of expected root\n");
   scanf("%lf",&xrnew);
   fprintf(p,"Iteration Root Function True Error Approx Error\n");
   xrold = xrnew;
   do
   {
      xrnew = xrold - function(xrold)/derivative(xrold);
      ea = error(xrnew,xrold);
      et = trueerror(xrnew);
      fprintf(p,"%d\t %lf\t %lf\t %lf\t %lf\n",count,xrnew,function(xrnew),et,ea);
      xrold = xrnew;
      count ++;
   }while(count<=50);
   printf("The value of the root is %lf\n",xrnew);
   printf("The approximate error is %lf\n",ea);
   printf("The True error is %lf\n",et);
   fclose(fp);
   fclose(p);
}
