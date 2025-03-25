#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

#define FREE_ABSOLUTE_ACCURACY 0.001
#define INACCURACY 0.01
#define ZERO_APPROXIMATION  0

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
    void set_element(int h, int w, double value) { numbers[h][w] = value; }
    int get_size() { return size; }
    bool get_flag() { return is_extended_matrix; }
    void set_size(int new_size) { size = new_size; }

    //constructors & destructor
    Matrix(const std::string& path);
    Matrix(Matrix* parent, int h, int w);
    Matrix(int size, bool flag);
    ~Matrix();

    //general methods
    double determinant(Matrix* matrix);
    void gaussian_method();
    double addition(int h, int w);
    Matrix *reverse_matrix();
    void transposition();
    double mark_norm(int type_matrix);  //0 - source, 1 - tranformed, 2 - reversed
    double beta();
    double* tranform_for_iteration();


    //support methods
    void init(std::ifstream &file);
    void print();
    void copy(Matrix &source);
};

void allocatiom_memory(Matrix *my_matrix);
int read_line(std::string &line);
bool is_matrix_square(std::ifstream &file, Matrix* my_matrix);
void file_handling(const std::string &path, Matrix* my_matrix);
double max(double *vector, int size);
double abs_err(double reverse_mark_norm);
double rel_err(double mark_norm, double reverse_mark_norm, double beta);
int number_iterations(double mark_norm, double x1);
void iterations(double *vector, Matrix *system, int k);
