#include "answer.h"

#include <cmath>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

void runAnswerA1()
{
    const int rows = 3;
    const int cols = 3;
    const int mat_size = rows * cols;
    int *A = new int[mat_size]{3, 2, 8, 1, 7, 5, 4, 6, 9};
    int *B = new int[mat_size]{2, 3, 6, 6, 1, 9, 8, 4, 7};
    int *C = new int[mat_size];

    for (int i = 0; i < mat_size; i++)
    {
        C[i] = A[i] + B[i];
    }

    std::cout << "Matrix C = A + B:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << C[i * cols + j] << " ";
        }
        std::cout << "\n";
    }

    delete[] A;
    delete[] B;
    delete[] C;
}

void runAnswerA2()
{
    int one, two;
    do
    {
        std::cout << "Enter an integer greater than 0: ";
        std::cin >> one;
    } while (one <= 0);
    do
    {
        std::cout << "Enter an integer greater than 0 and less than the previous one ("
                  << one << "): ";
        std::cin >> two;
    } while ((two <= 0) || (two > one));

    if ((one % two) == 0)
    {
        std::cout << "The first integer (" << one
                  << ") is divisible by the second integer (" << two
                  << ")\n";
    }
    else
    {
        std::cout << "The first integer (" << one
                  << ") is not divisible by the second integer (" << two
                  << ")\n";
    }
}

std::string replace(std::string str, char to_change, char change_to)
{
    const int n = str.size();
    for (int i = 0; i < n; i++)
    {
        if (str[i] == to_change)
        {
            str[i] = change_to;
        }
    }
    return str;
}

void runAnswerA3()
{
    std::string str;
    char to_change, change_to;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);
    std::cout << "Enter character to change: ";
    std::cin >> to_change;
    std::cout << "Enter character to change to: ";
    std::cin >> change_to;
    std::cout << "Result: " << replace(str, to_change, change_to) << std::endl;
}

class Point3D
{
public:
    Point3D() : x(0.0), y(0.0), z(0.0) {}

    void readCoordinates()
    {
        std::cout << "Coordinate x: ";
        std::cin >> x;
        std::cout << "Coordinate y: ";
        std::cin >> y;
        std::cout << "Coordinate z: ";
        std::cin >> z;
    }

    double computeDistance(const Point3D &pt) const
    {
        double dx = this->x - pt.x;
        double dy = this->y - pt.y;
        double dz = this->z - pt.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

private:
    double x, y, z;
};

void runAnswerA4()
{
    Point3D one, two;
    std::cout << "Enter the coordinates of the first point:\n";
    one.readCoordinates();
    std::cout << "Enter the coordinates of the second point:\n";
    two.readCoordinates();
    std::cout << "Distance between the two points is: "
              << one.computeDistance(two) << std::endl;
}

class Contact
{
public:
    Contact(const std::string &first_name = "",
            const std::string &second_name = "",
            const std::string &telephone_number = "")
        : first_name(first_name),
          second_name(second_name),
          telephone_number(telephone_number) {}

    void readInData()
    {
        std::cout << "Enter the person's first name: ";
        std::cin.clear();
        std::cin >> this->first_name;
        std::cout << "Enter the person's second name: ";
        std::cin.clear();
        std::cin >> this->second_name;
        std::cout << "Enter the person's telephone number: ";
        std::cin.clear();
        std::cin >> this->telephone_number;
    }

    bool matchSurName(const std::string &surname)
    {
        return (this->second_name == surname);
    }

    // save data to a file
    void save(std::ofstream &fs)
    {
        fs << first_name << '\n'
           << second_name << '\n'
           << telephone_number << '\n';
    }

    // overload << operator
    friend std::ostream &operator<<(std::ostream &os, const Contact &contact);

private:
    std::string first_name;
    std::string second_name;
    std::string telephone_number;
};

std::ostream &operator<<(std::ostream &os, const Contact &contact)
{
    os << "First name: " << contact.first_name
       << "\nSecond name: " << contact.second_name
       << "\nTelephone number: " << contact.telephone_number;
    return os;
}

void runAnswerB1()
{
    int num_contacts;
    char query;
    std::string surname;
    std::cout << "Number of contacts: ";
    std::cin >> num_contacts;
    if (num_contacts < 0)
    {
        return;
    }
    Contact *contacts = new Contact[num_contacts];
    std::ofstream fs("contacts.txt");
    for (int i = 0; i < num_contacts; i++)
    {
        std::cout << "Enter contact information for person " << i << ":" << std::endl;
        contacts[i].readInData();
        contacts[i].save(fs);
    }
    fs.close();
    do
    {
        std::cout << "Do you wish to search for a surname? [y/n]: ";
        std::cin >> query;
        if (query != 'y')
        {
            break;
        }
        std::cout << "Enter the surname: ";
        std::cin >> surname;
        for (int i = 0; i < num_contacts; i++)
        {
            if (contacts[i].matchSurName(surname))
            {
                std::cout << contacts[i] << std::endl;
            }
        }
    } while (true);
    delete[] contacts;
}

void countAppearances(int *arr, int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Array size is less than or equal to 0");
    }
    const int kUpperBound = 1000000;
    int max_num = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            throw std::invalid_argument("Array element less than 0");
        }
        if (arr[i] > kUpperBound)
        {
            throw std::invalid_argument("Array element exceeds the upper bound");
        }
        max_num = std::max(max_num, arr[i]);
    }
    int *appearances = new int[max_num + 1];
    memset(appearances, 0, sizeof(int) * (max_num + 1));
    for (int i = 0; i < n; i++)
    {
        appearances[arr[i]]++;
    }
    int max_appearances = 0;
    for (int i = 0; i <= max_num; i++)
    {
        max_appearances = std::max(appearances[i], max_appearances);
    }
    int *appearances_count = new int[max_appearances + 1];
    memset(appearances_count, 0, sizeof(int) * (max_appearances + 1));
    for (int i = 0; i <= max_num; i++)
    {
        appearances_count[appearances[i]]++;
    }
    for (int i = 1; i <= max_appearances; i++)
    {
        std::cout << appearances_count[i] << " number/s appear " << i << " times\n";
    }
    std::cout << "No numbers appear more than " << max_appearances << " times\n";
    delete[] appearances;
    delete[] appearances_count;
}

void runAnswerB2()
{
    const int n = 13;
    int arr[n]{3, 1, 14, 1, 2, 7, 1, 3, 11, 14, 7, 4, 8};
    countAppearances(arr, n);
}

int EuclidianDivision(int dividend, int divisor)
{
    if (dividend < 0)
    {
        dividend = -dividend;
    }
    if (divisor < 0)
    {
        divisor = -divisor;
    }
    if (dividend < divisor)
    {
        return EuclidianDivision(divisor, dividend);
    }
    if (divisor == 0)
    {
        return dividend;
    }
    int remainder = dividend % divisor;
    return EuclidianDivision(divisor, remainder);
}

void runAnswerB3()
{
    int one, two, gcd;
    char terminate = 'n';
    std::ofstream fs("Euclidian.txt");
    do
    {
        std::cout << "First integer: ";
        std::cin >> one;
        std::cout << "Second integer: ";
        std::cin >> two;
        gcd = EuclidianDivision(one, two);
        std::cout << "The greatest common divisor of " << one
                  << " and " << two << " is " << gcd << std::endl;
        std::cout << "Do you wish to repeat the calculation? [y/n]: ";
        fs << one << ' ' << two << ' ' << gcd << '\n';
        std::cin >> terminate;
    } while (terminate == 'y');
    fs.close();
}

void runAnswerC1()
{
    //
}

void runAnswerC2()
{
    //
}




