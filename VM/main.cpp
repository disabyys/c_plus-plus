#include "func.h"

int main()
{
    Matrix my_matrix("matrix.txt");
    my_matrix.print();
    std::cout << my_matrix.determinant(&my_matrix);
    return 0;
}
