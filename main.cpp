#include <iostream>
#include <string>

#include "answer.h"

int main(int argc, const char *argv[])
{
    std::string question;
    while (true)
    {
        std::cout << "Enter a question index (i.e. A1) "
                  << "or enter something else to exit: ";
        std::cin >> question;
        if (question == "A1")
        {
            runAnswerA1();
        }
        else if (question == "A2")
        {
            runAnswerA2();
        }
        else if (question == "A3")
        {
            runAnswerA3();
        }
        else if (question == "A4")
        {
            runAnswerA4();
        }
        else if (question == "B1")
        {
            runAnswerB1();
        }
        else if (question == "B2")
        {
            runAnswerB2();
        }
        else if (question == "B3")
        {
            runAnswerB3();
        }
        else if (question == "C1")
        {
            runAnswerC1();
        }
        else if (question == "C2")
        {
            runAnswerC2();
        }
        else
        {
            break;
        }
        std::cout << "\n";
    }
    return EXIT_SUCCESS;
}
