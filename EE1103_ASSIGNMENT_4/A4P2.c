#include <stdio.h>
int getLU(double (*A)[3], double (*L)[3])  //We shall use this function to decompose Matrix M into lower triangular matrix L and upper triangular matrix U.
{
for(int k=0;k<2;k++)   //Looping variable k
    {
        for(int i=k+1;i<3;i++) //Looping variable i
        {
            double r = (*(*(A+i)+k))/(*(*(A+k)+k));  //Stores ratio of starting elements of two rows for which we want to row reduce into Echelon form
            for(int j=k+1;j<3;j++) //Looping variable j
            {
                (*(*(A+i)+j)) = (*(*(A+i)+j)) - r * (*(*(A+k)+j));
            }
            *(*(L+i)+k) = r;
        }
    }
    *(*(A+1)+0) = 0.0000;  //To convert A into a upper triangular matrix
    *(*(A+2)+0) = 0.0000;
    *(*(A+2)+1) = 0.0000;
    for(int i=0;i<3;i++)  //To convert L into Lower triangular matrix
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
                *(*(L+i)+j) = 1;
            if(j>i)
                *(*(L+i)+j) = 0;
        }
    }
    return 0;
}
int Forward(double (*L)[3], double *I, double *D)  //Function for forward elimination
{
    double x[3];  //Stores answers of forward elimination
    double sum;
    x[0] = (*I)/(**L);
    for(int i=0;i<3;i++)
    {
        sum = 0;
        for(int j=0;j<i;j++)
            sum = sum + (*(*(L+i)+j))*(*(x+j));
        x[i] = ((*(I+i))-sum)/(*(*(L+i)+i));
        *(D+i) = x[i];
    }

}
int Backward(double (*U)[3], double *D, double *R)  //Function for Backward substitution
{
    double x[3];      //Stores answers of Backward substitution
    double sum;
    x[2] = (*(D+2))/(*(*(U+2)+2));
    for(int i=2;i>=0;i--)
    {
        sum = (*(D+i));
        for(int j=i+1;j<3;j++)
            sum = sum - (*(*(U+i)+j))*x[j];
        x[i] = sum/(*(*(U+i)+i));
        *(R+i) = x[i];
    }
}
int Multiply(double (*M)[3], double *P,double *Output) //Function to multiply two matrices
{
    for(int i=0;i<3;i++)
    {
        *(Output+i) = 0;
        for(int j=0;j<3;j++)
        {
            *(Output+i) = *(Output+i) + (*(*(M+i)+j))*(*(P+j));
        }
        printf("%0.0lf\n",*(Output+i));
    }
}
char Letter(double a)  //Function that converts numerical figures to characters according to the one-one map in the question
{
    if(a==27.0000)
        printf(" ");
    else
    {
       double x = 64.0000 + a;
       int y = (int) x;
       char q = (char) y;
       printf("%c",q);
    }
}
int main()
{
   double L[3][3]; //Stores lower triangular matrix L
   double A[3][3] = {{1,4,-3},{-2,8,5},{3,4,7}}; //Stores matrix M in the question initially, later on stores upper triangular matrix U
   getLU(A,L); //Converts A into Upper triangular matrix U and L as lower triangular matrix of A
   double invA[3][3]; //Stores the inverse of A
   double D[3]; //Stores solution of LD = B where B are columns of identity matrix of order 3
   double I[3]; //Stores identity matrix  column wise
   double Result[3]; //Stores the result
   printf("\n");
   printf("The matrix L is\n");
   for (int i=0;i<3;i++)
    {
       for(int j=0;j<3;j++)
       {
          printf("%lf\t",L[i][j]);
          }
        printf("\n");
    }
    printf("\n");
    printf("The matrix U is\n");
   for (int i=0;i<3;i++)
    {
       for( int j=0;j<3;j++)
       {
          printf("%lf\t",A[i][j]);
          }
        printf("\n");
    }
    for(int m=0;m<3;m++)
    {
        for(int n=0;n<3;n++)
        {
            if(n==m)
            I[n] = 1;
            else
            I[n] = 0;
        }
        Forward(L,I,D); //Forward Elimination
        Backward(A,D,Result); //Backward Elimination
        for(int p=0;p<3;p++)
        {
            invA[p][m] = Result[p];
        }
    }
    printf("\n");
    printf("The inverse of M is \n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%lf\t",invA[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    double Q[3];  //takes a column matrix input
    printf("Enter the three numbers\n");
    for(int i = 0;i<3;i++)
    {
        scanf("%lf",Q+i);
    }
    double X[3];
    Multiply(invA,Q,X); //Multiply two matrices
    for(int i=0;i<3;i++)
    {
        Letter(X[i]);
    }
}