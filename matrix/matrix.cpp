#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double value[] = { 12,10,6,7,9,2,5,2,4,1,3,1,12,6,3,1,2,5,0,4,7,5,6,7,8,9,10,2 };
double value2[] = { 2,3,4,5,6,9,5,6,7,8,3,4,4,6,1,12,4,5,5,3,5,10,9,0,6,7,9,2,13,8,9,1,6,0,0,3,1,2,3,4,5,5 };

typedef struct
{
	int row, line;		//line为行,row为列
	double* data;
}Matrix;

Matrix* InitMatrix(Matrix* matrix, int row, int line);		//初始化矩阵
void ValueMatrix(Matrix* matrix, double* array);				//给一个矩阵赋值
int SizeMatrix(Matrix* matrix);								//获得一个矩阵的大小
void FreeMatrix(Matrix* matrix);							//释放一个矩阵
void CopyMatrix(Matrix* matrix_A, Matrix* matrix_B);		//复制一个矩阵的值
void PrintMatrix(Matrix* matrix);							//打印一个矩阵

//矩阵的基本运算
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B);		//矩阵的加法
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B);		//矩阵的乘法
void TransMatrix(Matrix* matrix);			//条件为方阵

int main(int argc, char* argv[])
{
	Matrix* matrix1 = InitMatrix(matrix1, 4, 7);
	Matrix* matrix2 = InitMatrix(matrix2, 7, 6);

	ValueMatrix(matrix1, value);
	// CopyMatrix(matrix1,matrix2);	//复制赋值
	ValueMatrix(matrix2, value2);

	printf("矩阵1 乘以 矩阵2: \n");
	Matrix* matrix3 = MulMatrix(matrix1, matrix2);	//乘法
	PrintMatrix(matrix3);
	printf("矩阵1 加上 矩阵2: \n");
	Matrix* matrix4 = AddMatrix(matrix1, matrix2);	//加法
	PrintMatrix(matrix4);
	printf("矩阵1进行转置: \n");
	TransMatrix(matrix1);					//转置
	PrintMatrix(matrix1);

	return 0;
}

Matrix* InitMatrix(Matrix* matrix, int row, int line)				//初始化一个矩阵
{
	if (row > 0 && line > 0)
	{
		matrix = (Matrix*)malloc(sizeof(Matrix));
		matrix->row = row;
		matrix->line = line;
		matrix->data = (double*)malloc(sizeof(double) * row * line);
		memset(matrix->data, 0, sizeof(double) * row * line);
		return matrix;
	}
	else
		return NULL;
}

void ValueMatrix(Matrix* matrix, double* array) 		//给矩阵赋值
{
	if (matrix->data != NULL)
	{
		memcpy(matrix->data, array, matrix->row * matrix->line * sizeof(double));
	}
}

int SizeMatrix(Matrix* matrix)
{
	return matrix->row * matrix->line;
}

void FreeMatrix(Matrix* matrix)
{
	free(matrix->data);		//释放掉矩阵的data存储区
	matrix->data = NULL;
	printf("释放成功\n");
}

void CopyMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
	matrix_B->row = matrix_A->row;
	matrix_B->line = matrix_A->line;
	memcpy(matrix_B->data, matrix_A->data, SizeMatrix(matrix_A) * sizeof(double));
}

void PrintMatrix(Matrix* matrix)
{
	for (int i = 0; i < SizeMatrix(matrix); i++)
	{
		printf("%lf\t", matrix->data[i]);
		if ((i + 1) % matrix->line == 0)
			printf("\n");
	}

}
//加法
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
	if (matrix_A->row == matrix_B->row && matrix_A->line == matrix_B->line)
	{
		Matrix* matrix_C = InitMatrix(matrix_C, matrix_A->row, matrix_A->line);
		for (int i = 0; i < matrix_A->line; i++)
		{
			for (int j = 0; j < matrix_A->row; j++)
			{
				matrix_C->data[i * matrix_C->row + j] = \
					matrix_A->data[i * matrix_A->row + j] + matrix_B->data[i * matrix_A->row + j];
			}
		}
		return matrix_C;
	}
	else
	{
		printf("不可相加\n");
		return NULL;
	}
}

//乘法
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
		if (matrix_A->row == matrix_B->line)		//列==行
		{
	Matrix* matrix_C = InitMatrix(matrix_C, matrix_B->row, matrix_A->line);
	// matrix_C->line = matrix_A->line;		//A行
	// matrix_C->row = matrix_B->row;			//B列
	for (int i = 0; i < matrix_A->row; i++)
	{
		for (int j = 0; j < matrix_B->line; j++)
		{
			for (int k = 0; k < matrix_A->line; k++)
			{
				matrix_C->data[i * matrix_C->line + j] += \
					matrix_A->data[i * matrix_A->line + k] * matrix_B->data[k * matrix_B->row + j];
			}
		}
	}
	return matrix_C;
		}
		else
		{
			printf("不可相乘\n");
			return NULL;
		}
}

//矩阵转置
void TransMatrix(Matrix* matrix)			//条件为方阵
{
	if (matrix->row == matrix->line)
	{
		Matrix* matrixTemp = InitMatrix(matrixTemp, matrix->row, matrix->line);       	//创建一个临时矩阵
		CopyMatrix(matrix, matrixTemp);	//将目标矩阵的data复制给临时矩阵

		for (int i = 0; i < matrix->row; i++)
		{
			for (int j = 0; j < matrix->line; j++)
			{
				matrix->data[i * matrix->row + j] = matrixTemp->data[j * matrix->row + i];
			}
		}
	}
	else
	{
		printf("转置的矩阵必须为方阵\n");
	}
}

