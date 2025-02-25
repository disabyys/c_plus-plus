#include "func.h"

int main()
{
    Matrix my_matrix("matrix.txt");
    my_matrix.print();
    std::cout << my_matrix.determinant(&my_matrix) << std::endl;
    if (my_matrix.determinant(&my_matrix) == 0)
    {
        std::cout << "The matrix is degenerate! the Gaussian method is not effective!" << std::endl;
        exit(EXIT_FAILURE);
    }
    my_matrix.gaussian_method();
    return 0;
}
