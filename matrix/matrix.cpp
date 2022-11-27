#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double value[] = { 12,10,6,7,9,2,5,2,4,1,3,1,12,6,3,1,2,5,0,4,7,5,6,7,8,9,10,2 };
double value2[] = { 2,3,4,5,6,9,5,6,7,8,3,4,4,6,1,12,4,5,5,3,5,10,9,0,6,7,9,2,13,8,9,1,6,0,0,3,1,2,3,4,5,5 };

typedef struct
{
	int row, line;		//lineΪ��,rowΪ��
	double* data;
}Matrix;

Matrix* InitMatrix(Matrix* matrix, int row, int line);		//��ʼ������
void ValueMatrix(Matrix* matrix, double* array);				//��һ������ֵ
int SizeMatrix(Matrix* matrix);								//���һ������Ĵ�С
void FreeMatrix(Matrix* matrix);							//�ͷ�һ������
void CopyMatrix(Matrix* matrix_A, Matrix* matrix_B);		//����һ�������ֵ
void PrintMatrix(Matrix* matrix);							//��ӡһ������

//����Ļ�������
Matrix* AddMatrix(Matrix* matrix_A, Matrix* matrix_B);		//����ļӷ�
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B);		//����ĳ˷�
void TransMatrix(Matrix* matrix);			//����Ϊ����

int main(int argc, char* argv[])
{
	Matrix* matrix1 = InitMatrix(matrix1, 4, 7);
	Matrix* matrix2 = InitMatrix(matrix2, 7, 6);

	ValueMatrix(matrix1, value);
	// CopyMatrix(matrix1,matrix2);	//���Ƹ�ֵ
	ValueMatrix(matrix2, value2);

	printf("����1 ���� ����2: \n");
	Matrix* matrix3 = MulMatrix(matrix1, matrix2);	//�˷�
	PrintMatrix(matrix3);
	printf("����1 ���� ����2: \n");
	Matrix* matrix4 = AddMatrix(matrix1, matrix2);	//�ӷ�
	PrintMatrix(matrix4);
	printf("����1����ת��: \n");
	TransMatrix(matrix1);					//ת��
	PrintMatrix(matrix1);

	return 0;
}

Matrix* InitMatrix(Matrix* matrix, int row, int line)				//��ʼ��һ������
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

void ValueMatrix(Matrix* matrix, double* array) 		//������ֵ
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
	free(matrix->data);		//�ͷŵ������data�洢��
	matrix->data = NULL;
	printf("�ͷųɹ�\n");
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
//�ӷ�
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
		printf("�������\n");
		return NULL;
	}
}

//�˷�
Matrix* MulMatrix(Matrix* matrix_A, Matrix* matrix_B)
{
		if (matrix_A->row == matrix_B->line)		//��==��
		{
	Matrix* matrix_C = InitMatrix(matrix_C, matrix_B->row, matrix_A->line);
	// matrix_C->line = matrix_A->line;		//A��
	// matrix_C->row = matrix_B->row;			//B��
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
			printf("�������\n");
			return NULL;
		}
}

//����ת��
void TransMatrix(Matrix* matrix)			//����Ϊ����
{
	if (matrix->row == matrix->line)
	{
		Matrix* matrixTemp = InitMatrix(matrixTemp, matrix->row, matrix->line);       	//����һ����ʱ����
		CopyMatrix(matrix, matrixTemp);	//��Ŀ������data���Ƹ���ʱ����

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
		printf("ת�õľ������Ϊ����\n");
	}
}

