#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

class Matrix
{
private:
    double **numbers = nullptr;
    int size;
    bool is_extended_matrix = false;

public:
    //getters & setters
    double **get_pointer() { return numbers; }
    void set_pointer(double **new_p) { numbers = new_p; }
    double get_element(int h, int w) { return numbers[h][w]; }
    double get_size() { return size; }
    bool get_flag() { return is_extended_matrix; }
    void set_size(int new_size) { size = new_size; }

    //constructors
    Matrix(const std::string& path);
    Matrix(int size);

    //general methods
    double determinant(Matrix* matrix);
    void gaussian_method();
    void init(std::ifstream &file);
    void print();
};

void allocatiom_memory(Matrix *my_matrix);
int read_line(std::string &line);
bool is_matrix_square(std::ifstream &file, Matrix* my_matrix);
void file_handling(const std::string &path, Matrix* my_matrix);
