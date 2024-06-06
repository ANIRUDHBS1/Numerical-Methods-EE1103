#include <stdio.h>
#include <math.h>
#define R 225.00
#define L 0.5
#define C 0.0000006
#define Z 75.00
double f(double p)     
//Returns the value of the function given for a particular input
{
   double q;
   double r = 1/(R*R);        //r stores the value 1/(R*R)
   double imp = 1/(Z);      //imp stores the value 1/(Z)
   double XL = 1/(p*L);      //XL stores the value 1/wL
   double XC = p*C;           //XC stores the value wC
   double m = XC - XL;              //m stores the value XC-XL
   q = r + m*m ;
   q = sqrt(q) - imp;
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
    if(f<0.000)
      return 1;
    else
      return 0;
}
int main()
{
    FILE *fp,*p;
    fp = fopen("BisectionRLC.txt","w");     //fp is pointer to file that stores the data of errors vs iterations asked
    p = fopen("GraphP4a.txt","w");         //Stores data for plotting the graph of the function f(x)
   double xl,xu,xr,xrold,ea,e;
   xl = 1.00;         //Initialises the lower limit for w given in question to x which is 1
   xu = 1000.00;      //Initialises the upper limit for w given in question to x which is 1000
   xr = 150.00;       //We guess the first root to be around 150 
   e = 0.1;           //Initialise the given tolerance limit in the question in percent which is 0.1%
   int count = 1;                                   //Counter to store number of iterations
   double et;
   for(double i=1.00;i<=1000.00;i=i+0.01)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = f(x);
       fprintf(p,"%lf\t %lf\n",x,y);
   }
   fprintf(fp, "Iteration   Value of w  xl xu True Error  Approximate Error\n");
   if(check(xl,xu)){
     printf("Root is being searched in the interval entered by you\n");
     do
     {
       xrold = xr;                //Switches values to store. Used in computation of error
       xr = bisect(xl,xu);        //Evaluates mid point of xl and xu and stores in xr
       ea = error(xr,xrold);      // ea is used to store the approximate error.
       et = trueerror(xr);        //Stores true error  
       fprintf(fp, "%d\t\t %lf\t %lf\t %lf\t %lf\t %lf\n",count,xr,xl,xu, et,ea);
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
     } while(ea>e);
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
