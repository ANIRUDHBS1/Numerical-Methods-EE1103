#include <stdio.h>
#include <math.h>
double error(double a, double b)   //Computes the error given two inputs a-the present value and b-the previous value
{
   double e;
   e = (fabs(a-b))/a * 100.00;   //This formula is used in finding out the approximate error
   return e;
}
double trueerror(double a)     //Evaluates true error
{
   double ans = 4.0016;
   double et;
   et = (fabs(a-ans)/fabs(ans))*100;
   return et;
}
double function(double a) //Returns the value of the function given for a particular input
{
   double v;
   v = 75*exp(-1.5*a)+20*exp(-0.075*a)-15;
   return v;
}
double derivative(double a) //Returns the value of the derivative of the function given for a particular input
{
   double v;
   v = -112.5*exp(-1.5*a)+(-1.5*exp(-0.075*a));
   return v;
}
int main()
{
   FILE *fp,*p;
   fp = fopen("NewtonRaphson.txt","w");          //fp is pointer to file that stores the data of errors vs iterations asked
   p = fopen("GraphP3.txt","w");                 //p is pointer to file that stores the points required to plot the graph
   double xrnew,xrold,ea,et;
   int count =1;
   for(double i=1.000;i<=9.000;i=i+0.001)          //Computes values for plotting of graph
   {
       double x,y;        //x denotes x coordinate y denotes y coordinate
       x = i;
       y = function(x);
       fprintf(p,"%lf\t %lf\n",x,y);
   }
   xrnew = 6.00;                      // stores first expected guess given in question which is 6
   xrold = xrnew;                    //Transfers variable to only ease up approximate error computation
   double e = 0.5;                   //Stores error of 0.5% as asked in question
   fprintf(fp,"Iteration Root Function True Error Approximate Error\n");
   do
   {
      xrnew = xrold - function(xrold)/derivative(xrold);
      ea = error(xrnew,xrold);
      et = trueerror(xrnew);
      fprintf(fp,"%d\t %lf\t %lf\t %lf\t %lf\n",count,xrnew,function(xrnew),et, ea);
      xrold = xrnew;
      count ++;                  //increments counter to compute number of iterations required
   }while(ea>e);
   printf("The value of the root is %lf\n",xrnew);
   printf("The approximate error is %lf\n",ea);
   printf("The true error is %lf\n",et);
   printf("Number of iterations required were %d\n",count-1);
   fclose(fp);
   fclose(p);
}