#include <stdio.h>
#include <math.h>
int Gauss(double (*A)[2], double *B, int n)  //Solves the system of linear equations by Gaussian Elimination
{
    for(int k=0;k<(n-1);k++)
    {
        for(int i=k+1;i<n;i++)
        {
            double r = (*(*(A)+i)+k)/(*(*(A)+k)+k);  //Finds ratio of the leading coefficients of two rows
            for(int j=k+1;j<n;j++)
            {
               (*(*(A+i)+j)) = (*(*(A+i)+j)) - r * (*(*(A+k)+j)); //Converts A into row reduced Echelon Form
            }
            (*(B+i)) = (*(B+i))- r*(*(B+k)); //Stores updated matrix
        }
    }
    *(*(A+1)+0) = 0.0000;  //To write A as an upper triangular matrix
}
int Backward(double (*A)[2], double *B, double *R,int n) //Backward Substitution of RREF to obtain solution
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
int Power (double *x, double *y, int m)
{
   for(int i=0;i<m;i++)
    {
       *(x+i) = log (*(x+i));
       *(y+i) = log (*(y+i));
    }
}
int Saturate (double *x, double *y,int m)
{
    for(int i=0;i<m;i++)
    {
       *(x+i) = 1/(*(x+i));
       *(y+i) = 1/(*(y+i));
    }
}
int main()
{
    int n = 2;      //Stores the number of unknown variables; here for a straight line it is 2
    int m = 10;     //Stores the number of data points that are given in the problem
    double x[10] = {5,10,15,20,25,30,35,40,45,50};
    double y[10] = {17,24,31,33,37,37,40,40,42,41};
    FILE *pts;
    pts = fopen("Points.txt","w");  //This is done to plot discrete points on a graph
    for(int i=0;i<10;i++)
        fprintf(pts,"%lf\t %lf\n",x[i],y[i]);
    double X[10] = {5,10,15,20,25,30,35,40,45,50};  //Replica of array x[i] used later
    double Y[10] = {17,24,31,33,37,37,40,40,42,41}; //Replica of array y[i] used later
    double a0,a1;   //Stores the values of a0 and a1, the coefficients in line equation y = a0 + a1x
    double s = m;   //Number of entries
    double sx = 0; //Sum of all x entries
    double sy = 0; //Sum of all y entries
    double sxx = 0; //Sum of all x2 entries
    double sxy = 0; //Sum of all xy entries
    double sr = 0; //Stores the value of Sr
    double mean; //Stores the mean of y coordinates
    for(int i=0;i<10;i++)
    {
        sy = sy + Y[i];
    }
    mean = sy/10;
    sy = 0;
    double st = 0; //Stores the value of St
    for(int i=0;i<10;i++)
    {
        st = st + (Y[i]-mean)*(Y[i]-mean);
    }
    double r2; //Stores the value of coefficient of determination
    double r; //stores the value of coefficient of correlation
    double a2,b2,a3,b3; //Stores variables required to specify a curve completely in cases of power equation and saturation curve.
    double R[n]; //Array to store result
    double A[n][n]; //Stores the Matrix A satisfying AX=B
    double B [n];  //Stores the Matrix B satisfying AX=B
    int sw;        //Switching variable
    printf("Choose one from the following\n");
    printf("1. Straight Line\n");
    printf("2. Power Equation\n");
    printf("3. Saturation Growth-rate equation\n");
    scanf("%d",&sw);
    switch (sw) {
    case 1:
    for(int i=0;i<m;i++)
    {
        sx = sx + x[i];
        sy = sy + y[i];
        sxx = sxx + (x[i])*(x[i]);
        sxy = sxy + (x[i])*(y[i]);
    }
    A[0][0] = s;
    A[0][1] = sx;
    A[1][0] = sx;
    A[1][1] = sxx;
    B[0] = sy;
    B[1] = sxy;
    Gauss(A,B,n);
    Backward(A,B,R,n);
    for(int i=0;i<n;i++)
    {
        printf("The value of R %d is %lf\n",i,R[i]);
    }
    mean = (double) sy/10;
    for(int i=0;i<10;i++)
    {
        sr = sr + (y[i]-R[0]-R[1]*(x[i]))*(y[i]-R[0]-R[1]*(x[i]));
    }
    r2 = (st-sr)/st;
    r = sqrt(r2);
    printf("The coefficient of determination r2 is %lf\n",r2);
    printf("The coefficient of correlation r is %lf\n",r);
    a0 = R[0];
    a1 = R[1];
    printf("The equation of line is y = %lf + %lf x\n",a0,a1);
    break;
    case 2:
    Power(x,y,m);
    for(int i=0;i<m;i++)
    {
        sx = sx + x[i];
        sy = sy + y[i];
        sxx = sxx + (x[i])*(x[i]);
        sxy = sxy + (x[i])*(y[i]);
    }
    A[0][0] = s;
    A[0][1] = sx;
    A[1][0] = sx;
    A[1][1] = sxx;
    B[0] = sy;
    B[1] = sxy;
    Gauss(A,B,n);
    Backward(A,B,R,n);
    for(int i=0;i<n;i++)
    {
        printf("The value of R %d is %lf\n",i,R[i]);
    }
    a2 = exp(R[0]);
    b2 = R[1];
    for(int i=0;i<10;i++)
    {
        sr = sr + (Y[i]-a2*pow(X[i],b2))*(Y[i]-a2*pow(X[i],b2));
    }
    r2 = (st-sr)/st;
    r = sqrt(r2);
    printf("The coefficient of determination r2 is %lf\n",r2);
    printf("The coefficient of correlation r is %lf\n",r);
    printf("The value of a2 is %lf\n",a2);
    printf("The value of b2 is %lf\n",b2);
    printf("The equation of power equation is y = %lf x ^(%lf)\n",a2,b2);
    break;
    case 3:
    Saturate(x,y,m);
    for(int i=0;i<m;i++)
    {
        sx = sx + x[i];
        sy = sy + y[i];
        sxx = sxx + (x[i])*(x[i]);
        sxy = sxy + (x[i])*(y[i]);
    }
    A[0][0] = s;
    A[0][1] = sx;
    A[1][0] = sx;
    A[1][1] = sxx;
    B[0] = sy;
    B[1] = sxy;
    Gauss(A,B,n);
    Backward(A,B,R,n);
    for(int i=0;i<n;i++)
    {
        printf("The value of R %d is %lf\n",i,R[i]);
    }
    a3 = 1/R[0];
    b3 = R[1]/R[0];
    for(int i=0;i<10;i++)
    {
        sr = sr + (Y[i]-a3*(X[i]/(b3+X[i])))*(Y[i]-a3*(X[i]/(b3+X[i])));
    }
    r2 = (st-sr)/st;
    r = sqrt(r2);
    printf("The coefficient of determination r2 is %lf\n",r2);
    printf("The coefficient of correlation r is %lf\n",r);
    printf("The value of a3 is %lf\n",a3);
    printf("The value of b3 is %lf\n",b3);
    printf("The equation of saturation curve is y = %lf x / (%lf + x)\n",a3,b3);
    break;
    default:
    printf("Please enter a correct choice");
    }
    return 0;
}
