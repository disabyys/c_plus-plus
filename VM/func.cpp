#include "func.h"

Matrix ::Matrix(int init_size)
{
    size = init_size;
    allocatiom_memory(this);
}

Matrix ::Matrix()
{
    cout << "Enter size of matrix:___\b\b\b";
    cin >> size;
    allocatiom_memory(this);
}

void Matrix ::init()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            cin >> numbers[i][j];
        }
    }
}

void allocatiom_memory(Matrix *m)
{
    double **matrix;
    int h = m->get_size();
    int w = m->get_size() + 1;
    matrix = new double *[h];
    for (int i = 0; i < h; i++)
    {
        *(matrix + i) = new double[w];
    }
    m->set_pointer(matrix);
}

void Matrix ::print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            if (j == size)
            {
                cout << "=";
            }
            printf("|%-6.1f", numbers[i][j]);
        }
        cout << "|" << endl;
    }
}
