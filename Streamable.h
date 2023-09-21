////***********************************************************************
// Intro. to Object Oriented Programming
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Jul 22, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/
#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <iostream>

//interface
namespace sdds {
    class Streamable {
    public:
        virtual std::ostream& write(std::ostream& os)const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual bool conIO(std::ios& io) const= 0;
        virtual operator bool() const = 0;
        virtual ~Streamable();
    };
    std::ostream& operator<<(std::ostream& os, const Streamable& st);
    std::istream& operator>>(std::istream& is, Streamable& st);
}
#endif /* Streamable_h */
