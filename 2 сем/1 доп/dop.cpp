#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

	void print()
	{
		for (int r = 0; r < this->get_size_row(); r++)
		{
			for (int c = 0; c < this->get_size_colunm(); c++)
			{
				printf("%15.5lf ", this->get_value(r, c));
			}
			printf("\n");
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


double f_test(Matrix a, Matrix b)
{
	if ((a.get_size_colunm() == 1 || a.get_size_row() == 1) && (b.get_size_colunm() == 1 || b.get_size_row() == 1))
	{
		if (a.get_size_row() == 1) a = a.get_transposition();
		if (b.get_size_row() == 1) b = b.get_transposition();
		if (a.get_size_row() == b.get_size_row())
		{
			double a_sr = 0, b_sr = 0;
			for (int i = 0; i < a.get_size_row(); i++)
			{
				a_sr += a.get_value(i, 0);
				b_sr += b.get_value(i, 0);
			}
			a_sr /= a.get_size_row();
			b_sr /= b.get_size_row();

			double S_a = 0, S_b = 0;

			for (int i = 0; i < a.get_size_row(); i++)
			{
				S_a += pow(a.get_value(i, 0) - a_sr, 2);
				S_b += pow(b.get_value(i, 0) - b_sr, 2);
			}
			S_a /= a.get_size_row();
			S_b /= b.get_size_row();
			return S_a / S_b;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

int main()
{
	FILE* file = fopen("dataX1_X2_Y.txt", "r");
	Matrix x_2(50, 2);
	Matrix y_2(50, 1);
	for (int r = 0; r < 50; r++)
	{
		double a;
		fscanf(file, "%lf", &a);
		fscanf(file, "%lf", &a);
		x_2.set_value(r, 0, a);
		fscanf(file, "%lf", &a);
		x_2.set_value(r, 1, a);
		fscanf(file, "%lf", &a);
		y_2.set_value(r, 0, a);
	}
	fclose(file);
	Matrix b_2 = (x_2.get_transposition() * x_2).get_inverse() * x_2.get_transposition() * y_2;



	file = fopen("dataX1_X2_Y.txt", "r");
	Matrix x_3(50, 3);
	Matrix y_3(50, 1);
	for (int r = 0; r < 50; r++)
	{
		double a;
		fscanf(file, "%lf", &a);
		fscanf(file, "%lf", &a);
		x_3.set_value(r, 0, 1);
		x_3.set_value(r, 1, a);
		fscanf(file, "%lf", &a);
		x_3.set_value(r, 2, a);
		fscanf(file, "%lf", &a);
		y_3.set_value(r, 0, a);
	}
	fclose(file);
	Matrix b_3 = (x_3.get_transposition() * x_3).get_inverse() * x_3.get_transposition() * y_3;

	b_2.print();
	printf("\n");
	b_3.print();
	printf("\n");

	Matrix y_ras_2(50, 1);
	Matrix y_ras_3(50, 1);


	printf("      y_exp              y_ras_2            y_ras_3         |y_exp-y_ras_2|    |y_exp-y_ras_3|\n");
	for (int i = 0; i < 50; i++)
	{
		y_ras_2.set_value(i, 0, b_2.get_value(0, 0) * x_2.get_value(i, 0) + b_2.get_value(1, 0) * x_2.get_value(i, 1));
		y_ras_3.set_value(i, 0, b_3.get_value(0, 0) + b_3.get_value(1, 0) * x_3.get_value(i, 1) + b_3.get_value(2, 0) * x_3.get_value(i, 2));

		printf("%15.5fl   %15.5fl   %15.5fl   %15.5fl   %15.5fl   \n",
			y_2.get_value(i, 0),
			y_ras_2.get_value(i, 0),
			y_ras_3.get_value(i, 0),
			fabs(y_2.get_value(i, 0) - y_ras_2.get_value(i, 0)),
			fabs(y_2.get_value(i, 0) - y_ras_3.get_value(i, 0)));

	}
	printf("F(y_exp, y_ras_2)=%lf    F(y_exp, y_ras_3)=%lf", f_test(y_2, y_ras_2), f_test(y_3, y_ras_3));
}