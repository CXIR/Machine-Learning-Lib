# include <stdio.h>
# include <stdlib.h>
# include <math.h> 


extern "C" {
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

		result = multiplyMatrixWithNumber(result, 2, 2, (1 / det));

		return result;
	}

	double** arrayToMatrix(double *array, int rows, int cols) {
		//INIT MATRIX
		double **matrix;
		matrix = (double **)malloc(rows * sizeof(double*));
		for (int i = 0; i < rows; i++)
			matrix[i] = (double *)malloc(cols * sizeof(double));

		//VALUES
		for (int i = 0; i < rows*cols; i++)
		{
			int k = i / cols;
			int l = i % cols;
			*(*(matrix + k) + l) = *(array + i);
		}

		return matrix;
	}

	double* matrixToArray(double **matrix, int rows, int cols) {

		double *array = (double *)malloc(rows * sizeof(double));

		int cursor = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				*(array + cursor) = *(*(matrix + i) + j);
				cursor++;
			}
		}

		return array;
	}


	//__declspec(dllexport)
	double* linearRegression(double *Xvalues, double *Yvalues, int numberOfParam, int numberOfObject)
	{
		// INIT MATRIX X
		double **Xmatrix = arrayToMatrix(Xvalues, numberOfObject, numberOfParam);

		// INIT MATRIX Y
		double **Ymatrix = arrayToMatrix(Yvalues, numberOfObject, 1);

		// INIT MATRIX W -> ouput matrix 2x1
		double **Wmatrix;
		Wmatrix = (double **)malloc(2 * sizeof(double*));
		for (int i = 0; i < 1; i++)
			Wmatrix[i] = (double *)malloc(1 * sizeof(double));

		//INIT VALUES
		int Xrows = numberOfObject;
		int Xcols = numberOfParam;
		int Yrows = numberOfObject;
		int Ycols = 1;

		//Tranpose[X]
		double **XmatrixTranposed = tranposeMatrix(Xmatrix, Xrows, Xcols);

		//LINEAR REGRESSION --> matrix 2x1
		Wmatrix = multiplyMatrix(multiplyMatrix(inverseMatrixDim2(multiplyMatrix(XmatrixTranposed, Xcols, Xrows, Xmatrix, Xrows, Xcols)), 2, 2, XmatrixTranposed, Xcols, Xrows), 2, Xrows, Ymatrix, Yrows, Ycols);

		//CONVERT OUTPUT
		double *output = matrixToArray(Wmatrix, 2, 1);

		return output;
	}
}


