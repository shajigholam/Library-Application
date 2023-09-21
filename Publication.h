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
#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <iostream>
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

namespace sdds  {

    class Publication : public Streamable {
    private:
        char* m_title; //m_title is a c-string to hold a dynamic title for the publication
        char m_shelfId[SDDS_SHELF_ID_LEN + 1];
        int m_membership; //5 digit membership number
        int m_libRef;
        Date m_date;
        
        
    public:
        Publication();
        virtual void set(int member_id);
           // Sets the membership attribute to either zero or a five-digit integer.
        void setRef(int value);
           // Sets the **libRef** attribute value
        void resetDate();
           // Sets the date to the current date of the system.
        virtual char type()const;
           //Returns the character 'P' to identify this object as a "Publication object"
        bool onLoan()const;
           //Returns true is the publication is checkout (membership is non-zero)
        Date checkoutDate()const;
           //Returns the date attribute
        bool operator==(const char* title)const;
           //Returns true if the argument title appears anywhere in the title of the
           //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        operator const char* ()const;
           //Returns the title attribute
        int getRef()const;
           //Returns the libRef attirbute.
        bool conIO(std::ios& io) const;
        virtual std::ostream& write(std::ostream& os)const;
        virtual std::istream& read(std::istream& is);
        virtual operator bool() const;
        Publication(const Publication& src);
        Publication& operator=(const Publication& src);
        ~Publication();
        void setEmpty();
    };
}


#endif /* Publication_h */

//publication must have read and write functions because it is inheriting from the Streamable class(interface). Date class also has read and write functions but because it is not inheriting from Publication class in the publication we don't need to make these 2 functions virtual in other words publication is not a base class too.
