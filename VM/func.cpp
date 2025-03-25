#include "func.h"

Matrix ::Matrix(const std::string& path)
{
    std::ifstream file(path);
    file_handling(path, this);
    this->is_extended_matrix = true;
    allocatiom_memory(this);
    init(file);
}

Matrix :: Matrix(Matrix* parent, int h, int w)
{
    int parent_size = parent->get_size();
    if (h > parent->get_size() || h < 0)
    {
        fprintf(stderr, "Высота недопустима.\n");
    }
    if(w > parent->get_size() || w < 0)
    {
        fprintf(stderr, "Ширина недопустима.\n");
    }
    this->set_size(parent_size - 1);
    allocatiom_memory(this);
    int cur_h = 0;
    int cur_w = 0;
    for (int i = 0; i < parent_size; i++)
    {
        for (int j = 0; j < parent_size; j++)
        {
            if(i != h && j != w)
            {
                this->set_element(cur_h, cur_w++, parent->get_element(i, j));
            }
            if(cur_w == this->get_size())
            {
                cur_h++;
                cur_w = 0;
            }
        }

    }
}

Matrix :: Matrix(int size, bool flag)
{
    is_extended_matrix = flag;
    this->set_size(size);
    allocatiom_memory(this);
}

Matrix :: ~Matrix()
{
    for (int i = 0; i < size; i++)
    {
        delete *(numbers + i);
    }
    delete numbers;
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
        Matrix sub_matrix(matrix, 0, j);
        det += parent_matrix[0][j] * determinant(&sub_matrix) * (j % 2 == 0 ? 1 : -1);
    }
    return det;
}

void Matrix :: gaussian_method()
{
    double tmp_el;
    if (!is_extended_matrix)
    {
        std::cout << "Отсутствует дополнительный столбец в матрице" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)                  //Прямой ход, верхнетреугольный вид
    {
        tmp_el = numbers[i][i];                    
        for (int j = size; j >= i; j--)             //деление строки на элемент диагонали
        {
            numbers[i][j] /= tmp_el;
        }
        print();
        for (int k = i + 1; k < size; k++) // Спуск по строкам матрицы
        {
            tmp_el = numbers[k][i];                 //Элмент с этим значение нужно занулить 
            for (int z = size; z >= i; z--)
            {
                numbers[k][z] -= tmp_el * numbers[i][z];
            }
            print();
        }
    }
    double solutions[size];
    solutions[size-1] = numbers[size - 1][size];
    for (int i = size - 2; i >= 0; i--)             //обратный ход
    {
        solutions[i] = numbers[i][size];
        for (int j = i + 1; j < size; j++)
            solutions[i] -= numbers[i][j] * solutions[j];
    }
    for (int i = 0; i < size; i++)
    {
        std::cout << "x" << i + 1 << " = " << solutions[i] << std::endl;
    }
}

void Matrix ::init(std::ifstream& file)
{
    int row, line;
    row=line=0;
    std::string cur_line;
    while(getline(file, cur_line))
    {
        std::istringstream stream(cur_line);
        double cur_num;
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
    if(is_extended_matrix)
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
            printf("|%-6.3f", numbers[i][j]);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void Matrix:: copy(Matrix &source)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < ((this->get_flag()) ? size+1 : size); j++)
        {
            this->set_element(i, j, source.get_element(i, j));
        }
    }
}

double Matrix :: addition(int h, int w)
{
    Matrix sub_matrix = Matrix(this, h, w);
    return (pow(-1, (h + 1) + (w + 1)) * determinant(&sub_matrix));
}

Matrix* Matrix :: reverse_matrix()
{
    Matrix* rev_matrix = new Matrix(size, 0);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            rev_matrix->set_element(i, j, this->addition(i, j));
        }
    }
    rev_matrix->transposition();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            rev_matrix->set_element(i, j, (rev_matrix->get_element(i, j) * (1 / this->determinant(this))));
        }
    }
    return rev_matrix;
}

void Matrix :: transposition()
{
    Matrix* temp = new Matrix(size, 0);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp->set_element(i, j, this->get_element(j, i));
        }
    }
    this->copy(*temp);
    delete temp;
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

double Matrix :: mark_norm(int type_matrix)
{
    double sum_list[size] = {0};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(type_matrix == 1)
            {
                if(i == j){continue;}
            }
            sum_list[i] += (type_matrix < 2 ) ? fabs(numbers[i][j]) : numbers[i][j];
        }
    }
    return max(sum_list, size);
}

double Matrix :: beta()
{
    double add_coll[size];
    for (int i = 0; i < size; i++)
    {
        add_coll[i] = fabs(numbers[i][size]);
    }
    return FREE_ABSOLUTE_ACCURACY / max(add_coll, size);
}

double* Matrix :: tranform_for_iteration()
{
    for (int i = 0; i < size; i++)
    {
        double devider = numbers[i][i];
        for (int j = 0; j < size+1; j++)
        {
            numbers[i][j] /= (j != size) ? -devider : devider;
        }
    }
    double *add_coll = new double[size];
    for (int i = 0; i < size; i++)
    {
        *(add_coll + i) = numbers[i][size];
    }
    return add_coll;
}

double abs_err(double reverse_mark_norm)
{
    return reverse_mark_norm * FREE_ABSOLUTE_ACCURACY;
}

double rel_err(double mark_norm, double reverse_mark_norm, double beta)
{
    return mark_norm * reverse_mark_norm * beta;
}

double max(double* vector, int size)
{
    double maxi = *(vector);
    for (int i = 0; i < size; i++)
    {
        if(*(vector+i) > maxi)
        {
            maxi = *(vector + i);
        }
    }
    return maxi;
}

int number_iterations(double mark_norm, double x1)
{
    return ceil(log(INACCURACY * (1 - mark_norm) / (x1 - ZERO_APPROXIMATION)) / log(mark_norm));
}

void file_handling(const std::string& path, Matrix* my_matrix)
{
    std::ifstream in_file(path);
    if(!in_file)
    {
        std::cerr << "Ошибка чтения файла " << path << std::endl;
    }
    if(!is_matrix_square(in_file, my_matrix))
    {
        std::cout << "Матрица не квадратная." << std::endl;
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
    int ct_num=0;
    double number;
    while (stream >> number)
    {
        ct_num++;
    }
    return ct_num;
}

void iterations(double *vector, Matrix *system, int k)
{
    double c[system->get_size()];
    double temp[system->get_size()];
    for (int i = 0; i < system->get_size(); i++)
    {
        c[i] = vector[i];
    }
    for (int i = 0; i < system->get_size(); i++)
    {
        temp[i] = vector[i];
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < system->get_size(); j++)
        {
            int ind_vec = 0;
            double sum = 0;
            for (int z = 0; z < system->get_size(); z++)
            {
                if (j == z)
                {
                    ind_vec++;
                    continue;
                }
                sum += vector[ind_vec] * system->get_element(j, z);
                ind_vec++;
            }
            temp[j] = sum + c[j];
        }
        std::cout << "Вектор на итерации " << i + 1 << ":   ";
        for (int i = 0; i < system->get_size(); i++)
        {
            vector[i] = temp[i];
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }
}
