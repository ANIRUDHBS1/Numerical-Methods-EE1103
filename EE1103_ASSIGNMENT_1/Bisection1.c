#include <stdio.h>
#include <math.h>
double f(double p)   //Returns the value of the function given for a particular input
{
   double q;
   q = log(pow(p,4)) - 0.7;
   return q;
}
double trueerror(double a)     //Evaluates true error
{
   double ans = 1.191246;
   double et;
   et = (fabs(a-ans)/fabs(ans))*100;
   return et;
}
double error(double a, double b)   //Computes the error given two inputs a-the present value and b-the previous value
{
   double e;
   e = (fabs(a-b))/a * 100.00;   //This formula is used in finding out the approximate error
   return e;
}
double bisect(double x1, double x2)   //Computes the mid point of two points x1 and x2
{
   double c;
   c = (x1+x2)/2.00;
   return c;
}
int check(double xl, double xr)    //Checks if root lies in (x1,xr) or (xr,x2)
{
    double f1 = f(xl);
    double f2 = f(xr);
    double f = f1*f2;
    if(f<0.000)                  //We use Intermediate Value Theorem in finding out the root.
      return 1;
    else
      return 0;
}
int main()
{
    FILE *fp,*p;
    fp = fopen("Bisection.txt","w");       //fp stores the data for three iterations asked
    p = fopen("GraphP1a.txt","w");         //Stores data for plotting the graph of the function f(x)
   double xl,xu,xr,xrold,ea;
   //xl denotes lower bound 
   //xu denotes upper bound
    //xr denotes root value obtained using Bisection Algorithm
    //xrold stores root of previous iteration
    xl = 0.5;
    xu = 2.0;
    xr = 1.2;
   int count = 1;
   double et;    //To store true error
   for(double i=0.500;i<=2.000;i=i+0.001)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = f(x);
       fprintf(p,"%lf\t %lf\n",x,y);  //Plots the points on a text file.
   }
   fprintf(fp, "Iteration   Root xl xu True Error   Approximate Error\n");
   if(check(xl,xu)){
     printf("Root is being searched in the interval entered by you\n");
     do
     {
       xrold = xr;                //Switches values to store. Used in computation of error
       xr = bisect(xl,xu);        //Evaluates mid point of xl and xu and stores in xr
       ea = error(xr,xrold);      // ea is used to store the approximate error.
       et = trueerror(xr);        //To store true error
       fprintf(fp, "%d\t\t %lf\t %lf\t %lf\t %lf\t %lf\n",count,xr,xl,xu,et,ea);
       count++;                  //increments counter to store number of iterations
       if(f(xr)==0)
       break;
       if(check(xl,xr))
       {
          xu = xr;          //Updates the interval in which we check for root
       }
       else
       {
         xl = xr;          //Updates the interval in which we check for root
       }
     } while(count<=3);
     }
   else
     printf("There exists no root in the interval entered by you");
   printf("The root is %lf\n",xr);
   printf("The approximate error is %lf\n",ea);
   printf("The True error is %lf\n",et);
   fclose(fp);
   fclose(p);
}
