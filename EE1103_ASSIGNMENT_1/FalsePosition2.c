#include <stdio.h>
#include <math.h>
#define R 225.00
#define L 0.5
#define C 0.0000006
#define Z 75.00
double f(double p)   //Returns the value of the function given for a particular input
{
   double q;
   double r = 1/(R*R);       //r stores the value 1/(R*R)
   double imp = 1/(Z);      //imp stores the value 1/Z
   double XL = 1/(p*L);      //XL stores the value 1/wL
   double XC = p*C;           //XC stores the value wC
   double m = XC - XL;              //m stores the value XC-XL
   q = r + m*m;
   q = sqrt(q)-imp;
   return q;
}
double trueerror(double a)     //Evaluates true error
{
   double ans = 157.9474;
   double et;
   et = (fabs(a-ans)/fabs(ans))*100;
   return et;
}
double error(double a, double b)   //Computes the error given two inputs a-the present value and b-the previous value
{
   double e;
   e = (fabs(a-b))/fabs(a) * 100.00;   //This formula is used in finding out the approximate error
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
    FILE *fp,*p, *t;
    fp = fopen("RegulaFalsiRLC.txt","w");       //fp stores the data for three iterations asked
    p = fopen("GraphP4b.txt","w");         //Stores data for plotting the graph of the function f(x)
    t =fopen("TRUEERROR6.txt","w");
   double xl,xu,xr,xrold,ea,e;
   xl = 1.00;         //Initialises the lower limit for w given in question to x which is 1
   xu = 1000.00;      //Initialises the upper limit for w given in question to x which is 1000
   xr = 150.00;       //We guess the first root to be around 150 
   e = 0.1;           //Initialise the given tolerance limit in the question in percent which is 0.1%
   double et;         //To store true error
   for(double i=1.00;i<=1000.00;i=i+0.01)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = f(x);
       fprintf(p,"%lf\t %lf\n",x,y);
   }
   int count = 1;                                 //Counter to store number of iterations
   fprintf(fp, "Iteration  Value of w xl xu True Error Approximate Error\n");
   if(check(xl,xu)){
     printf("Root is being searched in the interval entered by you\n");
     do
     {
       xrold = xr;                      //Transfer variable, Just used in evaluating approximate error
       xr = zerocross(xl,xu);           //Stores the point where chord joining xlxu crosses the x axis in xr
       ea = error(xr,xrold);            //Computes approximate error and stores in ea
       et = trueerror(xr);
       fprintf(t,"%lf\n",et);          //To print true error on a Text file to draw graph
       fprintf(fp, "%d\t\t %lf\t %lf\t %lf\t %lf\t %lf\n",count, xr,xl,xu,et,ea);
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
     } while((ea>e));    //we check if the error drops below tolerance and true error is within 1%
     }
   else
     printf("There exists no root in the interval entered by you");
   printf("The root is %lf\n",xr);
   printf("The approximate error is %lf\n",ea);
   printf("The true error is %lf\n",et);
   printf("Number of iterations required are %d\n",count-1);
   fclose(fp);
   fclose(p);
}


