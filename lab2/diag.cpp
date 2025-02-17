#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int **genMatrix(int size);
void printMatrix(int **matrix, int size);
void diag_fill_left(int **matrix, int *array, int size, int corner);

int main()
{
    int size, corner;
    printf("Enter size of matrix and array:___\b\b\b");
    scanf("%d", &size);
    printf("Enter index of corner(ind = 0 or size-1):___\b\b\b");
    scanf("%d", &corner);
    cout << endl;
    int **matrix = genMatrix(size);
    printMatrix(matrix, size);
    int array[size * size];
    diag_fill_left(matrix, array, size, corner);
    cout << endl;
    for (int i = 0; i < size * size; i++)
    {
        printf("|%-2d|", array[i]);
    }
    cout << endl;
    return 0;
}

int **genMatrix(int size)
{
    int **matrix = new int *[size];
    if (matrix == nullptr)
    {
        cerr << "memory allocation error!" << endl;
        delete[] matrix;
        exit(EXIT_FAILURE);
    }
    for (int str = 0; str < size; str++)
    {
        *(matrix + str) = new int[size];
        if (*(matrix + str) == nullptr)
        {
            cerr << "memory allocation error!" << endl;
            delete[] *(matrix + str);
            exit(EXIT_FAILURE);
        }
    }
    for (int str = 0; str < size; str++)
    {
        for (int row = 0; row < size; row++)
        {
            matrix[str][row] = str * size + row;
        }
    }
    return matrix;
}

void printMatrix(int **matrix, int size)
{
    for (int str = 0; str < size; str++)
    {
        for (int row = 0; row < size; row++)
        {
            printf("|%-2d|", matrix[str][row]);
        }
        cout << endl;
    }
}

void diag_fill_left(int **matrix, int *array, int size, int corner)
{
    int ct = 0;
    for (int nb_diag = 0, line = 0, collumn = corner; nb_diag < size * 2 - 1; nb_diag++)
    {
        if (nb_diag <= size - 1)
        {
            for (int fir_half = 0, str = line, row = collumn; fir_half <= line; fir_half++)
            {
                array[ct++] = matrix[str][row];
                str--;
                row = (corner!=0)?row-1:row+1;
            }
            line++;
        }
        else
        {
            for (int sec_half = corner-1, str = line - 1, row = (corner!=0)?corner-1:corner+1; sec_half > 0; sec_half--)
            {
                array[ct++] = matrix[str][row];
                str--;
                row = (corner!=0)?row-1:row+1;
            }
            collumn = (corner!=0)?collumn-1:collumn+1;
        }
    }
}
