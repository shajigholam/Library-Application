////***********************************************************************
// Intro. to Object Oriented Programming
// Final Project Milestone 3
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Jul 22, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/
#include <iostream>
#include "Streamable.h"
namespace sdds {

    Streamable::~Streamable() {}

    std::ostream& operator<<(std::ostream& os, const Streamable& st)
    {
        if (st) {
            st.write(os);
        }
        
        
        return os;
    }
    std::istream& operator>>(std::istream& is, Streamable& st)
    {
        st.read(is);
        return is;
    }

}
