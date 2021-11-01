#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

double findSumOfElements(vector<double> numbers)
{
    double sum = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        sum += numbers.at(i);
    }
    return sum;
}

double findAverage(vector<double> numbers)
{
    return findSumOfElements(numbers) / (double)numbers.size();
}

double findSumOfErrorSquares(vector<double> numbers, double average)
{
    double result = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        result += pow((numbers.at(i) - average), 2.0);
    }
    return result;
}

double find_sum_of_d_squares(vector<double> x_values, vector<double> y_values, double m, double b)
{
    double sum = 0;
    for (int i = 0; i < x_values.size(); i++)
    {
        sum += pow(y_values.at(i) - m * x_values.at(i) - b, 2.0);
    }
    return sum;
}

int main()
{
    vector<double> x_values(0);
    vector<double> y_values(0);
    vector<double> predicted_y_values(0);

    double average_of_x_values = 0;
    double average_of_y_values = 0;
    double m = 0;
    double b = 0;
    double error_of_m = 0;
    double error_of_b = 0;
    double sum_of_error_square_x = 0;
    double sum_of_error_square_y = 0;
    double sum_of_d_squares = 0;

    double average_of_predicted_y_values = 0;

    {
        std::cout << ("Enter x values: \n");
        string value = "";
        double data = 0;

        try
        {
            while (1)
            {
                cout << x_values.size() + 1 << ". ";
                cin >> value;
                data = stod(value);
                x_values.push_back(data);
            }
        }
        catch (invalid_argument e)
        {
        }
    }

    {
        std::cout << ("Enter y values: \n");
        string value = "";
        double data = 0;

        try
        {
            while (1)
            {
                cout << y_values.size() + 1 << ". ";
                cin >> value;
                data = stod(value);
                y_values.push_back(data);
                if (y_values.size() >= x_values.size())
                {
                    invalid_argument i("");
                    throw i;
                }
            }
        }
        catch (invalid_argument e)
        {
            if (y_values.size() != x_values.size())
            {
                cout << "The number of y and x values are different!\n\n";
                exit(0);
            }
        }
    }

    average_of_x_values = findAverage(x_values);
    average_of_y_values = findAverage(y_values);

    sum_of_error_square_x = findSumOfErrorSquares(x_values, average_of_x_values);
    sum_of_error_square_y = findSumOfErrorSquares(y_values, average_of_y_values);

    std::cout << "Avearge of x values: " << average_of_x_values << endl;
    std::cout << "Average of y values: " << average_of_y_values << endl;

    {
        double temp = 0;
        for (int i = 0; i < x_values.size(); i++)
        {
            temp += (x_values.at(i) - average_of_x_values) * y_values.at(i);
        }
        m = temp / sum_of_error_square_x;
    }
    b = average_of_y_values - m * average_of_x_values;

    std::cout << "m: " << m << endl;
    std::cout << "b: " << b << endl;

    sum_of_d_squares = find_sum_of_d_squares(x_values, y_values, m, b);
    error_of_m = pow(sum_of_d_squares / ((x_values.size() - 2) * sum_of_error_square_x), 0.5);

    {
        double temp = ((1.0 / x_values.size()) + ((pow(average_of_x_values, 2.0)) / sum_of_error_square_x));
        temp = (temp * sum_of_d_squares) / (x_values.size() - 2);
        error_of_b = pow(temp, 0.5);
    }

    std::cout << "error of m: " << error_of_m << endl;
    std::cout << "error of b: " << error_of_b << endl;

    for (double x : x_values)
    {
        predicted_y_values.push_back(x * m + b);
    }
    average_of_predicted_y_values = findAverage(predicted_y_values);

    cout << "zaribe regression: " << pow(findSumOfErrorSquares(predicted_y_values, average_of_y_values) / findSumOfErrorSquares(y_values, average_of_predicted_y_values) , 0.5);

    return 0;
}