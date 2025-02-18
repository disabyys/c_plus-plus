#include "func.h"

Matrix ::Matrix(int init_width, int init_height)
{
    height = init_height;
    width = init_width;
    allocatiom_memory(this);
}

Matrix ::Matrix()
{
    cout << "Enter height of matrix:___\b\b\b";
    cin >> height;
    cout << "Enter width of matrix:___\b\b\b";
    cin >> width;
    allocatiom_memory(this);
}

void Matrix ::init()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cin >> numbers[i][j];
        }
    }
}

void allocatiom_memory(Matrix *m)
{
    double **matrix;
    int h = m->get_height();
    int w = m->get_width();
    matrix = new double *[h];
    for (int i = 0; i < h; i++)
    {
        *(matrix + i) = new double[w];
    }
    m->set_pointer(matrix);
}

void Matrix ::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << "|" << numbers[i][j];
        }
        cout << "|" << endl;
    }
}
