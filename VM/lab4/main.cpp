#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void file_handling(const std::string &path, std::vector<double> &x_arr, std::vector<double> &y_arr);
int read_line(const std::string &cur_string, std::vector<double> &val);
double Lagrange_polynom(std::vector<double> &x_arr, std::vector<double> &y_arr, double point);

int main()
{
    std::vector<double> x_arr, y_arr;
    file_handling("in.txt", x_arr, y_arr);
    for (int i = 0; (size_t)i < x_arr.size(); i++)
    {
        std::cout << x_arr[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; (size_t)i < y_arr.size(); i++)
    {
        std::cout << y_arr[i] << " ";
    }
    std::cout << "\n";
    std::cout << Lagrange_polynom(x_arr, y_arr, 2) << std::endl;
    return 0;
}

void file_handling(const std::string& path, std::vector<double>& x_arr, std::vector<double>& y_arr)
{
    std::ifstream file(path);
    if(!file)
    {
        std::cerr << "File opening error." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string cur_string;
    int amount_val = 0;
    if (getline(file, cur_string))
    {
        amount_val = read_line(cur_string, x_arr);
    }
    else
    {
        std::cerr << "File reading error." << std::endl;
        exit(EXIT_FAILURE);
    }
    if(getline(file, cur_string))
    {
        if(amount_val != read_line(cur_string, y_arr))
        {
            std::cerr << "The file must contaimn same number of dots and values." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "File reading error." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int read_line(const std::string& cur_string, std::vector<double>& val)
{
    std::istringstream stream(cur_string);
    int ct_val = 0;
    double cur_num = 0;
    while (stream >> cur_num)
    {
        val.push_back(cur_num);
        ct_val++;
    }
    return ct_val;
}


double Lagrange_polynom(std::vector<double>& x_arr, std::vector<double>& y_arr, double point)
{
    double value = 0;
    for (int i = 0; (size_t)i < x_arr.size(); i++)
    {
        double L = 1;
        for (int j = 0; (size_t)j < x_arr.size(); j++)
        {
            if(j==i){continue;}
            double xi = x_arr[j];
            double xk = x_arr[i];
            L *= (point - xi) / (xk - xi);
        }
        value += y_arr[i] * L;
    }
    return value;
}
