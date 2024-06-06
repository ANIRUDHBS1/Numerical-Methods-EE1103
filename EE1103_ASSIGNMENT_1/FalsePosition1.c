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
double error(double a, double b) //Computes the error given two inputs a-the present value and b-the previous value
{
   double e;
   e = (fabs(a-b))/a * 100.00;
   return e;
}
double zerocross(double x1, double x2) //Computes the point where line joining x1 and x2 crosses x axis
{
   double fu,fl;
   fu = f(x2);
   fl = f(x1);
   double x;
   x = x2 - (fu*(x1-x2))/(fl-fu);     //Stores the point x at which chord x1x2 crosses x axis
   return x;
}
int check(double xl, double xr)  //Checks if root lies in (x1,xr) or (xr,x2)
{
    double f1 = f(xl);
    double f2 = f(xr);
    double f = f1*f2;
    if(f<0.00)
      return 1;
    else
      return 0;
}
int main()
{
    FILE *fp,*p;
    fp = fopen("RegulaFalsi.txt","w");       //fp stores the data for three iterations asked
    p = fopen("GraphP1b.txt","w");         //Stores data for plotting the graph of the function f(x)
   double xl,xu,xr,xrold,ea;
   //xl stores lower limit of interval
  //xu stores upper limit of interval
  //xr stores the expected root obtained using False position
  //xrold stores the root obtained using previous iteration
  //ea stores approximate error.
  xl =0.5;
  xu = 2.0;
  xr = 1.2;
  double et;                                  //Stores True Error
   for(double i=0.500;i<=2.000;i=i+0.001)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = f(x);
       fprintf(p,"%lf\t %lf\n",x,y);
   }
   int count = 1;
   fprintf(fp, "Iteration  Root xl xu True Error Approximate Error\n");
   if(check(xl,xu)){
     printf("Root is being searched in the interval entered by you\n");
     do
     {
       xrold = xr;                      //Transfer variable, Just used in evaluating approximate error
       xr = zerocross(xl,xu);           //Stores the point where chord joining xlxu crosses the x axis in xr
       ea = error(xr,xrold);            //Computes approximate error and stores in ea
       et = trueerror(xr);
       fprintf(fp, "%d\t\t %lf\t %lf\t %lf\t %lf\t %lf\n",count, xr,xl,xu,et, ea);
       count++;                         //Increments counter to keep count on number of iterations
       if(f(xr)==0)
       break;
       if(check(xl,xr))
       {
          xu = xr;          //Updates the interval in which we check for root
       }
       else
       {
         xl = xr;           //Updates the interval in which we check for root
       }
     } while(count<=3);
     }
   else
     printf("There exists no root in the interval entered by you");
   printf("The root is %lf\n",xr);
   printf("The approximate error is %lf\n",ea);
   printf("The true error is %lf\n",et);
   fclose(fp);
   fclose(p);
}
