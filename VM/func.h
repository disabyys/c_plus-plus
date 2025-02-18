#include <iostream>

using namespace std;

class Matrix
{
private:
    double **numbers = nullptr;
    int width;
    int height;

public:
    Matrix(int init_width, int init_height);
    Matrix();
    double **get_pointer() { return numbers; }
    void set_pointer(double **new_p) { numbers = new_p; }
    double get_element(int h, int w) { return numbers[h][w]; }
    double get_height() { return height; }
    double get_width() { return width; }
    void init();
    void print();
};

void allocatiom_memory(Matrix *m);
