#include <stdio.h>
int main()
{
    double A[3][3] = {{0.5833,-0.3333,-0.25},{-0.3333,1.4762,-0.1429},{-0.25,-0.1429,0.5929}}; //This is the matrix obtained from Kirchoff's KCL Law
    double B[3] = {-11, 3, 25};   //This is matrix B to which we will equate to
    double r;  //We shall use this to find ratio at each stage.
    int i,j,k;  //These are looping variables
    for(k=0;k<2;k++)
    {
        for(i=k+1;i<3;i++)
        {
            r = A[i][k]/A[k][k];
            for(j=k+1;j<3;j++)
            {
                A[i][j] = A[i][j] - r * A[k][j]; //Standard algorithm to reduce Matrix A into its row-reduced echelon form
            }
            B[i] = B[i]- r*B[k];
        }
    }
    A[1][0] = 0.0000; //This is done so that A becomes an upper triangular matrix
    A[2][0] = 0.0000;
    A[2][1] = 0.0000;
    printf("\n");
    printf("The matrix A is \n");
    for(int i=0;i<3;i++)
    {
        for(int j =0;j<3;j++)
        {
            printf("%lf\t",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("The matrix B is \n");
    for(int i=0;i<3;i++)
        printf("%lf\n",B[i]);
    double x[3];
    double sum;
    x[2] = B[2]/A[2][2];  //Back Substitution begins here
    printf("\n");
    printf("The unknown voltages are \n");
    for(i=2;i>=0;i--)
    {
        sum = B[i];
        for(j=i+1;j<3;j++)
            sum = sum - A[i][j]*x[j];   //We are back substituting the variables into the equations to get previous unknowns.
        x[i] = sum/A[i][i];
        printf("The value of V %d is %lf\n",(i+1), x[i]);
    }
}


