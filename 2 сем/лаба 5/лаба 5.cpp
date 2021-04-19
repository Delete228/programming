#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 6
#define M N+1

#define R 2
#define C 9

class Matrix
{
private:
	double** matrix;
	int colunm, row;
public:
	Matrix(int Row, int Colunm)
	{
		this->colunm = Colunm;
		this->row = Row;
		this->matrix = new double* [Row];
		for (int i = 0; i < Row; i++)
		{
			this->matrix[i] = new double[Colunm];
		}
	}

	double get_value(int Row, int Colunm)
	{
		return (this->matrix[Row][Colunm]);
	}
	void set_value(int Row, int Colunm, double a)
	{
		this->matrix[Row][Colunm] = a;
	}
	int get_size_colunm()
	{
		return (this->colunm);
	}
	int get_size_row()
	{
		return (this->row);
	}

	Matrix get_transposition()
	{
		Matrix m(this->colunm, this->row);
		for (int r = 0; r < m.get_size_row(); r++)
		{
			for (int c = 0; c < m.get_size_colunm(); c++)
			{
				m.set_value(r, c, this->get_value(c, r));
			}
		}
		return m;
	}

	double get_determinant()
	{
		if (this->colunm == this->row && this->row >= 1)
		{
			double d = 0.0;

			if (this->colunm == 1)
			{
				return this->get_value(0, 0);
			}
			else if (this->colunm == 2)
			{
				return (this->get_value(0, 0)) * (this->get_value(1, 1)) - (this->get_value(0, 1)) * (this->get_value(1, 0));
			}
			else {

				for (int i = 0; i < this->colunm; i++)
				{
					Matrix m((this->colunm) - 1, (this->colunm) - 1);

					for (int r = 1; r < this->get_size_row(); r++)
					{
						for (int c = 0; c < this->get_size_colunm(); c++)
						{
							if (c != i)
							{
								m.set_value(r - 1, (c < i) ? c : c - 1, this->get_value(r, c));
							}
						}
					}
					//printf("%d: %d |", i, m.get_determinant());
					if (i % 2 == 1)
					{
						d -= this->get_value(0, i) * m.get_determinant();
					}
					else {
						d += this->get_value(0, i) * m.get_determinant();
					}
					//d+= (i%2==0)?m.get_determinant(): -1*(m.get_determinant());

				}
				return d;
			}
		}
		else {
			return 0;
		}
	}

	Matrix get_minor_matrix()
	{
		if (this->colunm == this->row)
		{
			Matrix m(this->colunm, this->colunm);

			for (int r = 0; r < m.get_size_row(); r++)
			{
				for (int c = 0; c < m.get_size_colunm(); c++)
				{
					Matrix n((this->colunm) - 1, (this->colunm) - 1);
					for (int r1 = 0; r1 < m.get_size_row(); r1++)
					{
						for (int c1 = 0; c1 < m.get_size_colunm(); c1++)
						{
							if (r1 != r && c1 != c)
							{
								n.set_value((r1 < r) ? r1 : r1 - 1, (c1 < c) ? c1 : c1 - 1, this->get_value(r1, c1));
							}

						}
					}
					m.set_value(r, c, n.get_determinant());
				}
			}

			return m;
		}
		else {

			return Matrix(0, 0);
		}
	}

	Matrix get_alg_dop()
	{
		if (this->colunm == this->row)
		{
			Matrix m = this->get_minor_matrix();
			for (int r = 0; r < m.get_size_row(); r++)
			{
				for (int c = 0; c < m.get_size_colunm(); c++)
				{
					m.set_value(r, c, pow(-1, (r + c)) * m.get_value(r, c));
				}
			}
			return m;
		}
		else {
			return Matrix(0, 0);
		}
	}



	Matrix operator * (Matrix c2)
	{
		if (this->get_size_colunm() == c2.get_size_row())
		{
			Matrix m(this->get_size_row(), c2.get_size_colunm());

			for (int r = 0; r < m.get_size_row(); r++)
			{
				for (int c = 0; c < m.get_size_colunm(); c++)
				{
					m.set_value(r, c, 0);
					for (int i = 0; i < this->get_size_colunm(); i++)
					{
						m.set_value(r, c, m.get_value(r, c) + (this->get_value(r, i)) * (c2.get_value(i, c)));
					}
				}
			}

			return m;
		}
		else {

			return Matrix(0, 0);
		}


	}

	Matrix operator * (double c2)
	{
		Matrix m = *this;
		for (int r = 0; r < m.get_size_row(); r++)
		{
			for (int c = 0; c < m.get_size_colunm(); c++)
			{
				m.set_value(r, c, c2 * m.get_value(r, c));
			}
		}
		return m;
	}

	Matrix get_inverse()
	{
		if (this->colunm == this->row)
		{
			Matrix m = this->get_alg_dop();
			m = m.get_transposition();
			double q = (this->get_determinant());
			return (m * (1 / q));
		}
		else {
			return Matrix(0, 0);
		}
	}
};
Matrix operator * (double c2, Matrix m)
{
	for (int r = 0; r < m.get_size_row(); r++)
	{
		for (int c = 0; c < m.get_size_colunm(); c++)
		{
			m.set_value(r, c, c2 * m.get_value(r, c));
		}
	}
	return m;
}


void method_Gauss(double a[N][M], double result[N])
{
	int q = 1;
	while (q > 0)
	{
		q = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (a[i][i] == 0)
			{
				q++;
				for (int j = 0; j < M; j++)
				{
					double c = a[i][j];
					a[i][j] = a[i + 1][j];
					a[i + 1][j] = c;
				}
			}
		}
		if (a[N - 1][N - 1] == 0)
		{
			q++;
			for (int j = 0; j < M; j++)
			{
				double c = a[N - 1][j];
				a[N - 1][j] = a[0][j];
				a[0][j] = c;
			}
		}
	}



	for (int i = 0; i < N; i++)
	{

		double v = a[i][i];
		for (int j = 0; j < M; j++)
		{
			a[i][j] /= v;
		}

		if (i < N - 1)
		{

			for (int j = i + 1; j < N; j++)
			{
				double r = a[j][i];
				for (int y = 0; y < M; y++)
				{
					a[j][y] -= a[i][y] * r;
				}
			}
		}

	}

	for (int i = N - 1; i >= 0; i--)
	{
		result[i] = a[i][M - 1];
		for (int j = i + 1; j < M - 1; j++)
		{
			result[i] -= a[i][j] * result[j];
		}
	}
}

void method_mnk(double exp[R][C], double result[N])
{
	double a[N][M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (j == M - 1)
			{
				a[i][j] = 0;
				for (int c = 0; c < C; c++)
				{
					a[i][j] += exp[1][c] * pow(exp[0][c], i);
				}
			}
			else {
				a[i][j] = 0;
				for (int c = 0; c < C; c++)
				{
					a[i][j] += pow(exp[0][c], i + j);
				}

			}
		}
	}

	/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%13.3lf ", a[i][j]);
		}
		printf("\n");
	}
	*/
	method_Gauss(a, result);
	for (int i = 0; i < N; i++)
	{
		printf("%lf ", result[i]);
	}
	printf("\n");
}

void method_martix_mnk(double exp[R][C], double result[N])
{
	Matrix x(C, N);
	Matrix y(C, 1);
	for (int r = 0; r < C; r++)
	{
		y.set_value(r, 0, exp[1][r]);

		for (int i = 0; i < N; i++)
		{
			x.set_value(r, i, pow(exp[0][r], i));
		}
	}

	Matrix b = (x.get_transposition() * x).get_inverse() * x.get_transposition() * y;

	for (int c = 0; c < N; c++)
	{
		result[c] = b.get_value(c, 0);
		printf("%lf ", result[c]);
	}
	printf("\n");
	//for (int i = 0; i < C; i++)
	//{
	//	for (int j = 0; j < N; j++)
	//	{
	//		printf("%13.3lf ", x.get_value(i,j));
	//	}
	//	printf("\n");
	//}


}

void read_data(double exp[R][C])
{
	FILE* file = fopen("data.txt", "r");
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			fscanf(file, "%lf", &exp[i][j]);
	fclose(file);
}



int main()
{
	double exp[R][C], result[N], result_matrix[N];
	read_data(exp);
	method_mnk(exp, result);
	method_martix_mnk(exp, result_matrix);

	double dy_mnk_sr = 0, dy_matrix_mnk_sr = 0, R_y = 0;
	for (int i = 0; i < C; i++)
	{
		double y_mnk = 0, y_matrix_mnk = 0;

		for (int j = 0; j < N; j++)
		{
			y_mnk += result[j] * pow(exp[0][i], j);
			y_matrix_mnk += result_matrix[j] * pow(exp[0][i], j);
		}
		R_y += pow(exp[1][i] - y_matrix_mnk, 2);
		dy_mnk_sr += fabs(exp[1][i] - y_mnk);
		dy_matrix_mnk_sr += fabs(exp[1][i] - y_matrix_mnk);
		printf("%15.5lf  %15.5lf  %15.5lf  %15.5lf  %15.5lf  %15.5lf  \n",
			exp[0][i],
			exp[1][i],
			y_mnk,
			y_matrix_mnk,
			fabs(exp[1][i] - y_mnk),
			fabs(exp[1][i] - y_matrix_mnk));
	}
	printf("dy_mnk_sr=%lf    dy_matrix_mnk_sr=%lf    R=%lf", dy_mnk_sr / C, dy_matrix_mnk_sr / C, R_y);

}