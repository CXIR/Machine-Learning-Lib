# include <stdio.h>
# include <stdlib.h>
# include <math.h>


extern "C" {

void printMatrix(double **matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%3f  ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

}

double** tranposeMatrix(double **matrix, int rows, int cols) {

    double **new_matrix;

    new_matrix = (double **)malloc(cols * sizeof(double*)); //rows = number of cols from original matrix
    for (int i = 0; i < cols; i++)
        new_matrix[i] = (double *)malloc(rows * sizeof(double)); //cols = number of rows from original matrix

    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            *(*(new_matrix + j) + i) = *(*(matrix + i) + j);
        }
    }

    return new_matrix;
}

double** multiplyMatrix(double **Xmatrix, int X_rows, int X_cols, double **Ymatrix, int Y_rows, int Y_cols) {
    int i, j, k;
    double **matrix = (double **)malloc(X_rows * sizeof(double*));
    for (int i = 0; i < X_rows; i++)
        matrix[i] = (double *)malloc(Y_cols * sizeof(double));

    if (X_cols == Y_rows) {

        for (i = 0; i < X_rows; i++) {
            for (j = 0; j < Y_cols; j++)
            {
                *(*(matrix + i) + j) = 0;
                for (k = 0; k < X_cols; k++) {
                    *(*(matrix + i) + j) += *(*(Xmatrix + i) + k) * *(*(Ymatrix + k) + j);
                }
            }
        }

    }
    else {
        printf("ERROR");
    }

    return matrix;
}

double** multiplyMatrixWithNumber(double **matrix, int rows, int cols, double number) {
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            (*(*(matrix + i) + j)) = number * (*(*(matrix + i) + j));
        }
    }

    return matrix;
}

double determinantMatrixDim2(double **matrix) {

    return (*(*(matrix + 0) + 0)**(*(matrix + 1) + 1)) - (*(*(matrix + 0) + 1)**(*(matrix + 1) + 0));
}

double** inverseMatrixDim2(double **matrix) {
    double **result;
    result = (double **)malloc(2 * sizeof(double*));
    for (int i = 0; i < 2; i++)
        result[i] = (double *)malloc(2 * sizeof(double));

    *(*(result + 0) + 0) = *(*(matrix + 1) + 1);
    *(*(result + 0) + 1) = *(*(matrix + 0) + 1)*-1;
    *(*(result + 1) + 0) = *(*(matrix + 1) + 0)*-1;
    *(*(result + 1) + 1) = *(*(matrix + 0) + 0);

    double det = determinantMatrixDim2(matrix);

    result = multiplyMatrixWithNumber(result, 2, 2, (1/det));

    return result;
}

#ifdef __WIN32
__declspec(dllexport)
#endif
double** regressionlineaire(double **Xmatrix, int Xrows, int Xcols, double **Ymatrix, int Yrows, int Ycols)
{
    double **Wmatrix;
    Wmatrix = (double **)malloc(2 * sizeof(double*));
    for (int i = 0; i < 1; i++)
        Wmatrix[i] = (double *)malloc(1 * sizeof(double));

    double **XmatrixTranposed = tranposeMatrix(Xmatrix, Xrows, Xcols);

    //W = Inverse[(Transpose[X].X)].Transpose[X].Y --> matrix of 2x1
    Wmatrix = multiplyMatrix(multiplyMatrix(inverseMatrixDim2(multiplyMatrix(XmatrixTranposed, Xcols, Xrows, Xmatrix, Xrows, Xcols)), 2, 2, XmatrixTranposed, Xcols, Xrows), 2, Xrows, Ymatrix, Yrows, Ycols);

    return Wmatrix;
}

}

