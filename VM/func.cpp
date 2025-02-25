#include "func.h"

Matrix ::Matrix(const std::string& path)
{
    std::ifstream file(path);
    file_handling(path, this);
    this->is_extended_matrix = true;
    allocatiom_memory(this);
    init(file);
}

Matrix :: Matrix(const Matrix* parent, int sub_matrix_size)
{
    int parent_size = parent->size;
    double **par_mat = parent->numbers;
    this->size = sub_matrix_size;
    allocatiom_memory(this);
    double **sub_mat = this->numbers;
    for (int i = 0; i < sub_matrix_size; i++)
    {
        for (int j = 0; j < sub_matrix_size; j++)
        {
            sub_mat[i][j] = par_mat[parent_size - sub_matrix_size + i][parent_size - sub_matrix_size + j];
        }
    }
}

double Matrix :: determinant(Matrix* matrix)
{
    int size = matrix->size;
    double **parent_matrix = matrix->numbers;
    if (size == 1) {
        return parent_matrix[0][0];
    }
    if (size == 2) {
        return parent_matrix[0][0] * parent_matrix[1][1] - parent_matrix[0][1] * parent_matrix[1][0];
    }

    double det = 0;
    for (int j = 0; j < size; j++) 
    {
        Matrix sub_matrix(this, size - 1);
        double **sub_matrix_num = sub_matrix.numbers;
        for (int x = 1; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if (y < j) 
                {
                    sub_matrix_num[x - 1][y] = parent_matrix[x][y];
                }
                else if (y > j)
                {
                    sub_matrix_num[x - 1][y - 1] = parent_matrix[x][y];
                }
            }
        }
        det += parent_matrix[0][j] * determinant(&sub_matrix) * (j % 2 == 0 ? 1 : -1);
    }
    return det;
}

void Matrix ::init(std::ifstream& file)
{
    int row, line;
    row=line=0;
    std::string cur_line;
    while(getline(file, cur_line))
    {
        std::istringstream stream(cur_line);
        int cur_num;
        while(stream >> cur_num)
        {
            *((*(numbers+line))+row) = cur_num;
            row++;
        }
        if(row<size)
        {
            for(int i=row; i<size; i++)
            {
                *((*(numbers+line))+i) = 0;
            }
        }
        row = 0;
        line++;
    }
}

void Matrix ::print()
{
    int add_row = 0;
    if(this->is_extended_matrix)
    {
        add_row++;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size + add_row; j++)
        {
            if (j == size)
            {
                std::cout << "=";
            }
            printf("|%-6.1f", numbers[i][j]);
        }
        std::cout << "|" << std::endl;
    }
}

void allocatiom_memory(Matrix *m)
{
    double **matrix;
    int size = m->get_size();
    int add_row = 0;
    if(m->get_flag())
    {
        add_row++;
    }
    matrix = new double *[size];
    for (int i = 0; i < size; i++)
    {
        *(matrix + i) = new double[size+add_row];
    }
    m->set_pointer(matrix);
}

void file_handling(const std::string& path, Matrix* my_matrix)
{
    std::ifstream in_file(path);
    if(!in_file)
    {
        std::cerr << "file reading error: " << path << std::endl;
    }
    if(!is_matrix_square(in_file, my_matrix))
    {
        std::cout << "the matrix is not square! Check your textfile." << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool is_matrix_square(std::ifstream& file, Matrix* my_matrix)
{
    int rows, lines;
    rows = lines = 0;
    int max_rows = rows;
    std::string cur_line;
    while (getline(file, cur_line))
    {
        rows = read_line(cur_line);
        if(rows>max_rows)
        {
            max_rows = rows;
            rows = 0;
        }
        lines++;
    }
    if((max_rows!=lines+1) || (lines == 0))
    {
        return false;
    }
    my_matrix->set_size(lines);
    return true;
}

int read_line(std::string& line)
{
    std::istringstream stream(line);
    int number, ct_num=0;
    while (stream >> number)
    {
        ct_num++;
    }
    return ct_num;
}
