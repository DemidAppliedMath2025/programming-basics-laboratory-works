#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

void delete_table(int rows, double **array)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] array[i];
    }

    delete[] array;
}

double **copy_table(int rows, int columns, double **table)
{
    double **new_table = new double *[rows];

    for (int i = 0; i < rows; ++i)
    {
        new_table[i] = new double[columns];

        for (int j = 0; j < columns; ++j)
        {
            new_table[i][j] = table[i][j];
        }
    }

    return new_table;
}

double **copy_table(double table[3][3])
{
    double **new_table = new double *[3];

    for (int i = 0; i < 3; ++i)
    {
        new_table[i] = new double[3];

        for (int j = 0; j < 3; ++j)
        {
            new_table[i][j] = table[i][j];
        }
    }

    return new_table;
}

class Matrix
{
public:
    int rows;
    int columns;
    double **table;

    Matrix(int rows_count, int columns_count, double **array)
    {
        rows = rows_count;
        columns = columns_count;
        table = copy_table(rows_count, columns_count, array);
    }

    Matrix(int rows_count, int columns_count, double array[3][3])
    {
        rows = rows_count;
        columns = columns_count;
        table = copy_table(array);
    }

    void clear()
    {
        delete_table(rows, table);
    }

    Matrix operator*(const Matrix other) const
    {
        if (columns != other.rows)
        {
            throw std::runtime_error("IncompatibleMatricesError");
        }

        double **new_table = new double*[rows];

        for (int i = 0; i < rows; ++i)
        {
            new_table[i] = new double[other.columns];

            for (int j = 0; j < other.columns; ++j)
            {
                for (int k = 0; k < columns; ++k)
                {
                    new_table[i][j] += table[i][k] * other.table[k][j];
                }
            }
        }

        return {rows, other.columns, new_table};
    }

    Matrix operator*(const double number) const
    {
        Matrix new_table(rows, columns, table);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                new_table.table[i][j] *= number;
            }
        }

        return new_table;
    }

    Matrix operator+(const Matrix other) const
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw std::runtime_error("MatrixHasDifferentSizeError");
        }

        Matrix new_table(rows, columns, table);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                new_table.table[i][j] += other.table[i][j];
            }
        }

        return new_table;
    }

    Matrix operator-(const Matrix other) const
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw std::runtime_error("MatrixHasDifferentSizeError");
        }

        Matrix new_table(rows, columns, table);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                new_table.table[i][j] -= other.table[i][j];
            }
        }

        return new_table;
    }

    Matrix inverse_matrix()
    {
        double **algebraic_complements = new double *[rows];
        double det = determinant();

        if (det == 0)
        {
            throw std::runtime_error("MatrixDeterminantIsZeroError");
        }

        for (int i = 0; i < rows; ++i)
        {
            algebraic_complements[i] = new double[columns];

            for (int j = 0; j < columns; ++j)
            {
                double **decreased_table = new double *[rows - 1];

                for (int a = 0; a < rows; ++a)
                {
                    if (a != i)
                    {
                        int row_index = a - (a > i);

                        decreased_table[row_index] = new double[rows - 1];

                        for (int b = 0; b < columns; ++b)
                        {
                            if (b != j)
                            {
                                int column_index = b - (b > j);

                                decreased_table[row_index][column_index] = table[a][b];
                            }
                        }
                    }
                }

                algebraic_complements[i][j] =
                    pow(-1, i + j) * _determinant(rows - 1, columns - 1, decreased_table) + 0.0;

                delete[] decreased_table;
            }
        }

        double **inverse_matrix_table = copy_table(rows, columns, algebraic_complements);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                inverse_matrix_table[i][j] = algebraic_complements[j][i] / det;
            }
        }

        delete_table(rows, algebraic_complements);

        return {rows, columns, inverse_matrix_table};
    }

    double determinant()
    {
        return _determinant(rows, columns, table) + 0.0;
    }

    void print()
    {
        _zerofy();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                std::cout << table[i][j] << " ";
            }

            std::cout << "\n";
        }
    }

    static Matrix random(int size)
    {
        double **table = new double *[size];
        srand(time(nullptr));

        for (int i = 0; i < size; ++i)
        {
            table[i] = new double[size];

            for (int j = 0; j < size; ++j)
            {
                table[i][j] = std::rand() % 101 * pow(-1, std::rand() % 101);
            }
        }

        return {size, size, table};
    }

    static Matrix identity_matrix(int size)
    {
        double **table = new double *[size];
        int diagonal_index = 0;

        for (int i = 0; i < size; ++i)
        {
            table[i] = new double[size]();

            table[i][diagonal_index++] = 1;
        }

        return {size, size, table};
    }

private:
    static double _determinant(int rows_count, int columns_count, double **table)
    {
        if (rows_count == columns_count && columns_count == 1)
        {
            return table[0][0];
        }
        else if (rows_count == columns_count && columns_count == 2)
        {
            return table[0][0] * table[1][1] - table[0][1] * table[1][0];
        }
        else if (rows_count == columns_count && rows_count > 2)
        {
            double determinant = 0;

            for (int e = 0; e < columns_count; ++e)
            {
                double element = table[0][e];
                int deleted_column_index = e;
                double **decreased_table = new double *[rows_count - 1];

                for (int i = 1; i < rows_count; ++i)
                {
                    decreased_table[i - 1] = new double[columns_count - 1];

                    for (int j = 0; j < columns_count; ++j)
                    {
                        if (j < deleted_column_index)
                        {
                            decreased_table[i - 1][j] = table[i][j];
                        }
                        else if (j > deleted_column_index)
                        {
                            decreased_table[i - 1][j - 1] = table[i][j];
                        }
                    }
                }

                determinant += pow(-1, e) * element * _determinant(rows_count - 1, columns_count - 1, decreased_table);

                for (int i = 0; i < rows_count - 1; ++i)
                {
                    delete[] decreased_table[i];
                }

                delete[] decreased_table;
            }

            return determinant;
        }
        else
        {
            throw std::runtime_error("NotASquareMatrixError");
        }
    }

    void _zerofy()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (fabs(table[i][j]) < 0.000000001)
                {
                    table[i][j] = 0;
                }
            }
        }
    }
};

int n, m;

double array_max_element(int array_length, double *array)
{
    double max_elem = INT64_MIN;

    for (int i = 0; i < array_length; ++i)
    {
        max_elem = std::max(max_elem, array[i]);
    }

    return max_elem + 0.0;
}

double **get_table_from_file(const char *file_path)
{
    std::fstream in(file_path);

    in >> n >> m;

    double **table = new double *[n];

    for (int i = 0; i < n; ++i)
    {
        table[i] = new double[m];

        for (int j = 0; j < m; ++j)
        {
            in >> table[i][j];
        }
    }

    in.close();

    return table;
}

void write_matrix_to_file_trunc(const char *file_path, Matrix matrix)
{
    std::ofstream out(file_path, std::ios::trunc);

    for (int i = 0; i < matrix.rows; ++i)
    {
        for (int j = 0; j < matrix.columns; ++j)
        {
            out << matrix.table[i][j] << " ";
        }

        out << "\n";
    }

    out.close();
}

void write_matrix_to_file_app(const char *file_path, Matrix matrix)
{
    std::ofstream out(file_path, std::ios::app);

    for (int i = 0; i < matrix.rows; ++i)
    {
        for (int j = 0; j < matrix.columns; ++j)
        {
            out << matrix.table[i][j] << " ";
        }

        out << "\n";
    }

    out << "\n";

    out.close();
}

namespace task_1
{
    void task_1()
    {
        double **table = get_table_from_file(R"(C:\Users\Fenek\CLionProjects\lab_3\task_1_input.txt)");
        Matrix matrix = Matrix(n, m, table);

        Matrix result = (matrix * matrix * matrix * matrix * matrix) * 3 - (matrix * matrix * matrix * matrix) * 4
            - (matrix * matrix * matrix) * 10 + (matrix * matrix) * 3 - Matrix::identity_matrix(n) * 7;

        result.print();

        write_matrix_to_file_trunc(
            R"(C:\Users\Fenek\CLionProjects\lab_3\task_1_output.txt)",
            result
        );

        matrix.clear();
        result.clear();
        delete_table(n, table);
    }
}

namespace task_2
{
    void write_number_to_file(const char *file_path, double number)
    {
        std::ofstream out(file_path, std::ios::trunc);

        out << number;

        out.close();
    }

    void task_2()
    {
        double **table = get_table_from_file(R"(C:\Users\Fenek\CLionProjects\lab_3\task_2_input.txt)");
        Matrix matrix = Matrix(n, m, table);

        write_number_to_file(
            R"(C:\Users\Fenek\CLionProjects\lab_3\task_2_output.txt)",
            matrix.determinant()
        );

        matrix.clear();
        delete_table(n, table);
    }
}

namespace task_3
{
    void task_3()
    {
        double e_array[3][3] = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };
        double a_array[3][3] = {
            {-14, 1, 4},
            {-12, -4, 6},
            {11, -1, -10}
        };
        double b_array[3][3] = {
            {1, -2, 3},
            {3, -2, 1},
            {1, 0, 1}
        };

        Matrix e_5 = Matrix(3, 3, e_array) * 5;
        Matrix a = Matrix(3, 3, a_array);
        Matrix b = Matrix(3, 3, b_array);

        Matrix c = a + e_5;
        Matrix c_inverse = c.inverse_matrix();
        Matrix x = b * c_inverse;

        x.print();

        e_5.clear();
        c_inverse.clear();
        x.clear();
    }
}

namespace task_4
{
    Matrix input_matrix_from_console()
    {
        int n, m;

        std::cin >> n >> m;

        double **table = new double *[n];

        for (int i = 0; i < n; ++i)
        {
            table[i] = new double[m];

            for (int j = 0; j < m; ++j)
            {
                std::cin >> table[i][j];
            }
        }

        return {n, m, table};
    }

    int matrix_characteristic(Matrix matrix)
    {
        int count = 0;

        for (int i = 0; i < matrix.rows; ++i)
        {
            if (!((matrix.table[i][i] >= 0) || array_max_element(matrix.columns, matrix.table[i]) < 0))
            {
                return 1;
            }
            else
            {
                count++;
            }
        }

        return 0;
    }

    int array_find_index_of_number(int array_length, const double *array, double number)
    {
        for (int i = 0; i < array_length; ++i)
        {
            if (array[i] == number)
            {
                return i;
            }
        }

        return -1;
    }

    Matrix transform_matrix(Matrix matrix)
    {
        double **new_table = copy_table(matrix.rows, matrix.columns, matrix.table);

        for (int i = 0; i < matrix.rows; ++i)
        {
            for (int j = 0; j < matrix.columns; ++j)
            {
                bool number_is_found_in_first_line =
                    array_find_index_of_number(matrix.columns, matrix.table[0], matrix.table[i][j]) != -1;

                if ((i + j) % 2 == 0 && number_is_found_in_first_line)
                {
                    new_table[i][j] = 0;
                }
                else
                {
                    new_table[i][j] = matrix.table[i][j];
                }
            }
        }

        return {matrix.rows, matrix.columns, new_table};
    }

    void task_4()
    {
        int input = 1;
        double **placeholder = new double *[1];
        Matrix current_matrix = Matrix(1, 1, placeholder);
        Matrix current_transformed_matrix = Matrix(1, 1, placeholder);

        while (input >= 1 && input <= 10)
        {
            std::cout << "Choose one of the 10 following options\n";
            std::cout << "1) Generate random square matrix\n";
            std::cout << "2) Print current matrix in console\n";
            std::cout << "3) Write matrix to file\n";
            std::cout << "4) Read matrix from console\n";
            std::cout << "5) Read matrix from file\n";
            std::cout << "6) Calculate characteristic\n";
            std::cout << "7) Transform matrix\n";
            std::cout << "8) Print current transformed matrix in console\n";
            std::cout << "9) Write transformed matrix to file\n";
            std::cout << "10) Exit the program\n";

            std::cin >> input;

            switch (input)
            {
                case 1:
                    current_matrix = Matrix::random(std::rand() % 6);

                    break;
                case 2:
                    current_matrix.print();

                    break;
                case 3:
                    write_matrix_to_file_trunc(
                        R"(C:\Users\Fenek\CLionProjects\lab_3\task_4_output.txt)",
                        current_matrix
                    );

                    break;
                case 4:
                    current_matrix = input_matrix_from_console();

                    break;
                case 5:
                    current_matrix = Matrix(n, m, get_table_from_file(R"(C:\\Users\\Fenek\\CLionProjects\\lab_3\\task_4_input.txt)"));

                    break;
                case 6:
                    std::cout << matrix_characteristic(current_matrix) << "\n";

                    break;
                case 7:
                    current_transformed_matrix = transform_matrix(current_matrix);

                    break;
                case 8:
                    current_transformed_matrix.print();

                    break;
                case 9:
                    write_matrix_to_file_trunc(
                        R"(C:\Users\Fenek\CLionProjects\lab_3\task_4_transformed_output.txt)",
                        current_transformed_matrix);

                    break;
                default:
                    current_matrix.clear();
                    current_transformed_matrix.clear();
                    delete_table(1, placeholder);

                    return;
            }

            std::cout << "\n";
        }
    }
}

namespace task_5
{
    double ***read_3d_matrix_from_file()
    {
        double ***matrix_3d = new double **[3];
        std::fstream in(R"(C:\Users\Fenek\CLionProjects\lab_3\task_5_input.txt)");

        in >> n >> m;

        for (int i = 0; i < 3; ++i)
        {
            matrix_3d[i] = new double *[n];

            for (int j = 0; j < n; ++j)
            {
                matrix_3d[i][j] = new double[n];

                for (int k = 0; k < m; ++k)
                {
                    in >> matrix_3d[i][j][k];
                }
            }
        }

        return matrix_3d;
    }

    bool is_prime(double number)
    {
        if (round(number) != number || number == 1 || number < 0)
        {
            return false;
        }

        for (int d = 2; d < round(sqrt(number)) + 1; ++d)
        {
            if (fmod(number, d) == 0)
            {
                return false;
            }
        }

        return true;
    }

    void task_5()
    {
        double ***matrix_3d = read_3d_matrix_from_file();
        int red_cubes_count = 0;

        for (int i = 0; i < 3; ++i)
        {
            Matrix matrix = Matrix(n, m, matrix_3d[i]);

            write_matrix_to_file_app(
                R"(C:\Users\Fenek\CLionProjects\lab_3\task_5_output.txt)",
                matrix
            );
        }

        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                for (int z = 0; z < 3; ++z)
                {
                    if (fmod(x, 2) == 0 && fmod(y, 2) != 0 && is_prime(z))
                    {
                        red_cubes_count++;
                        std::cout << "*" << matrix_3d[x][y][z] << " ";
                    }
                    else
                    {
                        std::cout << matrix_3d[x][y][z] << " ";
                    }

                }

                std::cout << "\n";
            }

            std::cout << "\n";
        }

        std::cout << red_cubes_count;

        for (int i = 0; i < 3; ++i)
        {
            delete_table(n, matrix_3d[i]);
        }
    }
}

int main()
{
    task_5::task_5();
}
