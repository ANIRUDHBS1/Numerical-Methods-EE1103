#include <stdio.h>
#include <math.h>
int Gauss(double (*A)[3], double *B, int n) //Solves the system of linear equations by Gaussian Elimination
{
    for(int k=0;k<(n-1);k++)
    {
        for(int i=k+1;i<n;i++)
        {
            double r = (*(*(A+i)+k))/(*(*(A+k)+k)); //Finds ratio of the leading coefficients of two rows
            for(int j=k+1;j<n;j++)
            {
               (*(*(A+i)+j)) = (*(*(A+i)+j)) - r * (*(*(A+k)+j)); //Converts A into row reduced Echelon Form
            }
            (*(B+i)) = (*(B+i))- r*(*(B+k)); //Stores updated matrix
        }
    }
    *(*(A+1)+0) = 0.0000; //To write A as an upper triangular matrix
    *(*(A+2)+0) = 0.0000; //To write A as an upper triangular matrix
    *(*(A+2)+1) = 0.0000; //To write A as an upper triangular matrix 
}
int Backward(double (*A)[3], double *B, double *R,int n) //Backward Substitution of RREF to obtain solution
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
    int n = 3; //Stores the number of unknown variables; here for a parabola it is 3
    printf("Enter the number of data points you will enter\n");
    int m=6; //Stores number of data points given in Question
    double x[6]={0,5,10,20,30,40}; 
    double y[6] = {1.787, 1.519,1.307,1.002,0.7975,0.6529};
    double a0,a1,a2; //Stores the values of a0,a1 and a2 the coefficients in parabola equation y = a0 + a1x + a2x2
    double s = (double) m; //Number of entries
    double sx = 0; //Sum of all x entries
    double sy = 0; //Sum of all xy entries
    double sxx = 0; //Sum of all xx entries
    double sxy = 0; //Sum of all xy entries
    double sxxy = 0; //Sum of all xxy entries
    double sxxx = 0; //Sum of all xxx entries
    double sxxxx = 0; //Sum of all xxxx entries
    double sr = 0; //Stores the value of Sr
    double st = 0; //Stores the value of St
    double mean; //Stores the mean of y coordinates
    for(int i=0;i<m;i++)
    {
        sx = sx + x[i];
        sy = sy + y[i];
        sxx = sxx + (x[i])*(x[i]);
        sxy = sxy + (x[i])*(y[i]);
        sxxy = sxxy + (x[i])*(x[i])*(y[i]);
        sxxx = sxxx + (x[i])*(x[i])*(x[i]);
        sxxxx = sxxxx + (x[i])*(x[i])*(x[i])*(x[i]);
    }
    double A[n][n]; //Stores the Matrix A satisfying AX=B
    double B [n]; //Stores the Matrix B satisfying AX=B
    A[0][0] = s;
    A[0][1] = sx;
    A[0][2] = sxx;
    A[1][0] = sx;
    A[1][1] = sxx;
    A[1][2] = sxxx;
    A[2][0] = sxx;
    A[2][1] = sxxx;
    A[2][2] = sxxxx;
    printf("The matrix A is\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%lf\t",A[i][j]);
        }
        printf("\n");
    }
    B[0] = sy;
    B[1] = sxy;
    B[2] = sxxy;
    printf("The matrix B is\n");
    for(int i=0;i<n;i++)
        printf("%lf\t",B[i]);
    printf("\n");
    mean = ((double) sy/m);
    printf("The mean is %lf\n",mean);
    double R[n]; //Stores the resultant matrix
    Gauss(A,B,n);
    Backward(A,B,R,n);
    for(int i=0;i<n;i++)
    {
        printf("The value of R %d is %0.12lf\n",i,R[i]);
    }
    for(int i=0;i<m;i++)
    {
        sr = sr + (y[i]-R[0]-R[1]*(x[i])-R[2]*(x[i])*(x[i]))*(y[i]-R[0]-R[1]*(x[i])-R[2]*(x[i])*(x[i]));
    }
    printf("The value of Sr is %lf\n",sr);
    for(int i=0;i<m;i++)
    {
        st = st + (y[i]-mean)*(y[i]-mean);
    }
    printf("The value of St is %lf\n",st);
    double r2;  //Stores the value of coefficient of determination
    r2 = (st-sr)/st;
    double r; //stores the value of coefficient of correlation
    r = sqrt(r2);
    printf("The value of r2 is %lf\n",r2);
    printf("The value of r is %lf\n",r);
    a0 = R[0];
    a1 = R[1];
    a2 = R[2];
    printf("The equation of curve is y = %lf + %lf x + %lf x^2\n",a0,a1,a2);
    double YY,XX; //To store the value of y at x = 7.5
    XX = 7.5;
    YY = a0 + a1*XX + a2*XX*XX;
    printf("The value of y when x = 7.5 is %lf\n",YY);

    return 0;
}
