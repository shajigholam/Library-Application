////***********************************************************************
// Intro. to Object Oriented Programming
// Final Project Milestone 5
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Aug 3, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Publication.h"
using namespace std;
namespace sdds {

    Publication::Publication()
    {
        setEmpty();
    }
    Publication::Publication(const Publication& src)
    {
        *this = src;
    }
    Publication& Publication::operator=(const Publication& src)
    {
        if (this != &src)
        {
            set(src.m_membership);
            setRef(src.m_libRef);
            strcpy(m_shelfId, src.m_shelfId);
            m_date = src.m_date;
            
            if (m_title)
            {
                delete [] m_title;
                m_title = nullptr;
            }
            if (src.m_title != nullptr && src.m_title[0] != '\0')
            {
                m_title = new char[strlen(src.m_title) + 1];
                strcpy(m_title, src.m_title);
            }
            else
            {
                m_title = nullptr;
            }
        }
        return *this;
    }
    void Publication::setEmpty()
    {
    //    if (m_title != nullptr) {
    //        delete [] m_title;
    //    }
        m_title = nullptr;
        m_shelfId[0] = '\0'; //*
        m_membership = 0;
        m_libRef = -1;
        resetDate();
    }
    void Publication::set(int member_id)
    {
        m_membership = member_id;
    }
    void Publication::setRef(int value)
    {
        m_libRef = value;
    }
    void Publication::resetDate()
    {
        m_date = Date(); //coz there is no memory allocation in the Date class we can use the constructor
    }
    char Publication::type()const
    {
        return 'P';
    }
    bool Publication::onLoan()const
    {
        return (m_membership != 0);
    }
    Date Publication::checkoutDate()const
    {
        return m_date;
    }
    bool Publication::operator==(const char* title)const
    {
        return strstr(m_title, title) != nullptr;
    }
    Publication::operator const char* ()const //*
    {
        return m_title;
    }
    int Publication::getRef()const
    {
        return m_libRef;
    }
    bool Publication::conIO(std::ios& io) const
    {
        return &io == &cin || &io == &cout;
    }
    std::ostream& Publication::write(std::ostream& os) const
    {
        char tempTitle[SDDS_TITLE_WIDTH + 1] = { 0 };
        strncpy(tempTitle, m_title, SDDS_TITLE_WIDTH);
        
        if (conIO(os)) {
            os << "| " << m_shelfId << " | " << setw(SDDS_TITLE_WIDTH) << left << setfill('.') << tempTitle << " | ";
            if (m_membership != 0) {
                os << m_membership;
            }
            else {
                os << " N/A ";
            }
            os << " | " << m_date << " |";
        }
        else {
            
            os << type();
            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
            //if (m_membership != 0) {
                os << m_membership;
            //}
//            else {
//                os << "0";
//            }
            os << "\t" << m_date;
        }
        return os;
    }
    std::istream& Publication::read(std::istream& istr)
    {
        //get upto 256 for the title which is MAX_TITLE_PUBLICATION
        char titleTemp[MAX_TITLE_PUBLICATION + 1] = {};
        char shelfTemp[SDDS_SHELF_ID_LEN + 1] = {};
        Date dateTemp;
        int membershipTemp = 0;
        int libRefTemp = -1;
        
        if (m_title) {
            delete [] m_title;
            m_title = nullptr;
        }
        setEmpty();
        if (conIO(istr)) {
            cout << "Shelf No: ";
            istr.getline(shelfTemp, SDDS_SHELF_ID_LEN + 1);
            if (strlen(shelfTemp) != SDDS_SHELF_ID_LEN)
            {
                //set the istr to a fail state manually
                istr.setstate(std::ios::failbit);
            }
            cout << "Title: ";
            istr.getline(titleTemp, MAX_TITLE_PUBLICATION); // \t needed?no
            cout << "Date: ";
            istr >> dateTemp;
        }
        else
        {
            istr >> libRefTemp; //number
            istr.ignore();
            istr.getline(shelfTemp, SDDS_SHELF_ID_LEN + 1, '\t');
            istr.getline(titleTemp, MAX_TITLE_PUBLICATION + 1, '\t');
            istr >> membershipTemp;
            istr.ignore();
            istr >> dateTemp;
        }
        if (!dateTemp) //*
        {
            istr.setstate(std::ios::failbit);
        }
        if (istr)
        {
            m_title = new char[strlen(titleTemp) + 1];
            strcpy(m_title, titleTemp);
            strcpy(m_shelfId, shelfTemp);
            m_membership = membershipTemp;
            m_date = dateTemp;
            m_libRef = libRefTemp;
        }
        return istr;
    }
    Publication::operator bool() const
    {
        bool result = false;
        if (m_title != nullptr && m_shelfId[0] != '\0')
        {
            result = true;
        }
        return result;
    }
    Publication::~Publication()
    {
        delete [] m_title;
    }
}
