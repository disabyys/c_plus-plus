#include <iostream>

using namespace std;

class Matrix
{
private:
    double **numbers = nullptr;
    int size;

public:
    Matrix(int size);
    Matrix();
    double **get_pointer() { return numbers; }
    void set_pointer(double **new_p) { numbers = new_p; }
    double get_element(int h, int w) { return numbers[h][w]; }
    double get_size() { return size; }
    void init();
    void print();
};

void allocatiom_memory(Matrix *m);
