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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Book.h"

using namespace std;
namespace sdds {
    Book::Book() : Publication()
    {
        //no need for constructor of the base?
        m_authorName = nullptr;
    }
    Book::~Book()
    {
        delete[] m_authorName;
        m_authorName = nullptr;
    }
    Book::Book(const Book& other)
    {
        //is it enough or do i need to use the base class copy constr?
        *this = other;
    }
    Book& Book::operator=(const Book& other)
    {
        //first use copy assignment operator of the base class
        Publication::operator=(other);
        if (this != &other)
        {
            if (other.m_authorName && other.m_authorName[0] != '\0') {
                if (m_authorName) {
                    delete [] m_authorName;
                    m_authorName = nullptr;
                }
                m_authorName = new char[strlen(other.m_authorName) + 1 ];
                strcpy(m_authorName, other.m_authorName);
            }
        }
        else
        {
            m_authorName = nullptr;
        }
        return *this;
    }
    char Book::type()const
    {
        return 'B';
    }
    ostream& Book::write(ostream& os)const
    {
        //First, it will invoke the write of its Base class.
        Publication::write(os);
        if (conIO(os)) {
            os << " ";
            char tempAuthor[SDDS_AUTHOR_WIDTH + 1] = { 0 };
            strncpy(tempAuthor, m_authorName, SDDS_AUTHOR_WIDTH);
            os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ')<<  tempAuthor << " |";
        }
        else
        {
            os << "\t" << m_authorName;
        }
        return os;
    }
    istream& Book::read(istream& is)
    {
        char tempAuthorName[MAX_TITLE_PUBLICATION] = { 0 };
        //First, invoke the read of the Base class.
        Publication::read(is);
        if (m_authorName) {
            delete [] m_authorName;
            m_authorName = nullptr;
        }
        if (conIO(is)) {
            is.ignore(); //ignore one character
            cout << "Author: ";
            //read the author's name
            //is.getline(tempAuthorName, MAX_TITLE_PUBLICATION);
        }
        else
        {
            is.ignore();
            //is.getline(tempAuthorName, MAX_TITLE_PUBLICATION);
        }
        is.get(tempAuthorName, MAX_TITLE_PUBLICATION);
        if (is) {
            m_authorName = new char[strlen(tempAuthorName) + 1];
            strcpy(m_authorName, tempAuthorName);
        }
        return is;
    }
    void Book::set(int member_id)
    {
        //invoke the set of the base class to set the member id
        Publication::set(member_id);
        //reset the date to the current date
        Publication::resetDate();
    }
    Book::operator bool() const
    {
        return (m_authorName && m_authorName[0]
                != '\0' && Publication::operator bool());
    }
}
