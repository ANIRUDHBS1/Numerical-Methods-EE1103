#include <stdio.h>
#include <math.h>
int main()
{
    int n,i,j; //n stores the number of data points, i and j are looping variables
    double m; //m is used to store the product of the continued factors (x-xi)
    double sum = 0; //Sum stores the sum of the continued product computed using m
    n= 6;
    double x[6] = {0,5,10,20,30,40};
    double y[6] = {1.787,1.519,1.307,1.002,0.7975,0.6529};
    for(j=0;j<n-1;j++)
    {
       for(i=n-1;i>j;i--)
       {
           y[i]= (y[i]-y[i-1])/(x[i]-x[i-j-1]);  //Computes Newton's Divided Difference
       }
    }
    printf("The values of the coefficients are\n");
    for(i=0;i<n;i++)
    {
        printf("The value of b %d is %0.12lf\n",(i),y[i]);
    }
    for(i=n-1;i>=0;i--)
    {
        m = 1;
        for(j=0;j<i;j++)
            m = m*(7.5-x[j]);
        m = m *y[j];
        sum = sum + m;
    }
    printf("The value required is %lf\n",sum);
}
