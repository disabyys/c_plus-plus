#include "func.h"

int main()
{
    Matrix my_matrix("matrix.txt");
    Matrix matrix_copy(my_matrix.get_size(), 1);
    matrix_copy.copy(my_matrix);
    std::cout << "Исходная система: " << std::endl;
    my_matrix.print();

    std::cout << "Определитель: " << my_matrix.determinant(&my_matrix) << std::endl;
    if (my_matrix.determinant(&my_matrix) == 0)
    {
        std::cout << "Метод Гауса не эффективен" << std::endl;
        exit(EXIT_FAILURE);
    }
    my_matrix.gaussian_method();

    Matrix* rev_matrix = my_matrix.reverse_matrix();
    std::cout << "Обратная матрица: " << std::endl;
    rev_matrix->print();

    double mark_norm = my_matrix.mark_norm(1);
    double rev_mark_norm = rev_matrix->mark_norm(0);
    double beta = my_matrix.beta();
    printf("Абсолютная погрешность решения: %f\n", abs_err(rev_mark_norm));
    printf("Относительная погрешность решения: %f\n", rel_err(mark_norm, rev_mark_norm, beta));

    double* arr = matrix_copy.tranform_for_iteration();
    if(matrix_copy.mark_norm(1) >= 1)
    {
        std::cout << "Условия сходимости не выполнены - систему нельзя решить методом итераций." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Преобразованная система для метода итераций: " << std::endl;
    matrix_copy.print();
    std::cout << "Вектор на нулевой итерации:  " ;
    for (int i = 0; i < matrix_copy.get_size(); i++)
    {
        printf("%f ", arr[i]);
    }
    std::cout << std::endl;
    int k = number_iterations(matrix_copy.mark_norm(1), arr[0]);
    printf("k = %d\n", k);
    iterations(arr, &matrix_copy, k);
    return 0;
}
