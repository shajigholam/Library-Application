////***********************************************************************
// Intro. to Object Oriented Programming
// Final Project Milestone 2
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Jul 14, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/

#include "Utils.h"
#include <iostream>
using namespace std;
namespace sdds {

    unsigned int getInput(unsigned int minVal, unsigned int maxVal, const char* message)
    {
        bool flag = false;
        unsigned int userInput = 0;
        do {
            cin >> userInput;
            
            if (cin)
            {
                if (cin.get() != '\n')
                {
                    cout << message;
                    cin.ignore(1000, '\n');
                }
                else
                {
                    if (userInput >= minVal && userInput <= maxVal)
                    {
                        flag = true;
                    }
                    else
                    {
                        cout << message;
                    }
                }
            }
            else
            {
                cout << message;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } while (!flag);
        
        return userInput;
    }
}
//"Invalid Selection, try again: "
