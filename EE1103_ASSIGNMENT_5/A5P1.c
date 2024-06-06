#include <stdio.h>
#include <math.h>
int Gauss(double (*A)[2], double *B, int n)    //Solves the system of linear equations by Gaussian Elimination
{
    for(int k=0;k<(n-1);k++)
    {
        for(int i=k+1;i<n;i++)
        {
            double r = (*(*(A)+i)+k)/(*(*(A)+k)+k);   //Finds ratio of the leading coefficients of two rows
            for(int j=k+1;j<n;j++)
            {
               (*(*(A+i)+j)) = (*(*(A+i)+j)) - r * (*(*(A+k)+j)); //Converts A into row reduced Echelon Form
            }
            (*(B+i)) = (*(B+i))- r*(*(B+k)); //Stores updated matrix
        }
    }
    *(*(A+1)+0) = 0.0000; //To write A as an upper triangular matrix
}
int Backward(double (*A)[2], double *B, double *R,int n)  //Backward Substitution of RREF to obtain solution
{
    double x[n];
    double sum;
    x[n-1] = (*(B+n-1))/(*(*(A+n-1)+n-1));
    for(int i=n-1;i>=0;i--)
    {
        sum = (*(B+i));
        for(int j=i+1;j<n;j++)
            sum = sum - (*(*(A+i)+j))*x[j];
        x[i] = sum/(*(*(A+i)+i));
        *(R+i) = x[i];
    }
}
int main()
{
    int n = 2;   //Stores the number of unknown variables; here for a straight line it is 2
    int x[11] = {6,7,11,15,17,21,23,29,29,37,39};
    int y[11] = {29,21,29,14,21,15,7,7,13,0,3};
    FILE *pts;
    pts = fopen("Points.txt","w");  //This is done to plot discrete points on a graph
    for(int i=0;i<11;i++)
        fprintf(pts,"%d\t %d\n",x[i],y[i]);
    double a0,a1;  //Stores the values of a0 and a1, the coefficients in line equation y = a0 + a1x
    int s = 11; //Number of entries
    int sx = 0; //Sum of all x entries
    int sy = 0; //Sum of all y entries
    int sxx = 0; //Sum of all x2 entries
    int sxy = 0; //Sum of all xy entries
    double sr = 0; //Stores the value of Sr
    double st = 0; //Stores the value of St
    double mean; //Stores the mean of y coordinates
    for(int i=0;i<11;i++)
    {
        sx = sx + x[i];
        sy = sy + y[i];
        sxx = sxx + (x[i])*(x[i]);
        sxy = sxy + (x[i])*(y[i]);
    }
    double A[n][n];  //Stores the Matrix A satisfying AX=B
    double B [n];    //Stores the Matrix B satisfying AX=B
    A[0][0] = s;
    A[0][1] = sx;
    A[1][0] = sx;
    A[1][1] = sxx;
    B[0] = sy;
    B[1] = sxy;
    mean = ((double) sy/11);
    printf("The mean is %lf\n",mean);
    double R[n];   //Stores the resultant matrix
    Gauss(A,B,n);
    Backward(A,B,R,n);
    for(int i=0;i<n;i++)
    {
        printf("The value of R %d is %lf\n",i,R[i]);
    }
    for(int i=0;i<11;i++)
    {
        sr = sr + (y[i]-R[0]-R[1]*(x[i]))*(y[i]-R[0]-R[1]*(x[i]));
    }
    printf("The value of Sr is %lf\n",sr);
    for(int i=0;i<11;i++)
    {
        st = st + (y[i]-mean)*(y[i]-mean);
    }
    printf("The value of St is %lf\n",st);
    a0 = R[0];
    a1 = R[1];
    printf("The equation of line is y = %lf + %lf x\n",a0,a1);
    double r2; //Stores the value of coefficient of determination
    double r; //stores the value of coefficient of correlation
    r2 = (st-sr)/st;
    r = sqrt(r2);
    double Y,X;
    X = 10;
    Y = a0 + a1*X;
    double std = sr/(9); //To compute standard deviation
    std = sqrt(std);
    printf("The value of standard error is %lf\n",std);
    printf("The value of Y when X is 10 is %lf\n",Y);
    printf("The coefficient of correlation r is %lf\n",r);
    return 0;
}
