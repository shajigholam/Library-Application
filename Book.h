////***********************************************************************
// Intro. to Object Oriented Programming
// Final Project Milestone 4
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Jul 28, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include "Publication.h"
#include "Lib.h"
#include <iostream>
namespace sdds {
    class Book : public Publication {
    private:
        char* m_authorName;
    public:
        Book();
        //The rule of three
        ~Book();
        Book(const Book& other);
        Book& operator=(const Book& other);
        //overridding virtual functions in publication
        char type()const;
        std::ostream& write(std::ostream& os)const;
        std::istream& read(std::istream& is);
        void set(int member_id);
        operator bool() const;
    };
}
#endif
