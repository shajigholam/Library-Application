////***********************************************************************
// Intro. to Object Oriented Programming
//Name: Samaneh Hajigholam
//email: shajigholam@myseneca.ca
//studentID: 119751220
//Date of completion: Jul 14, 2023
//OOP244-NEE
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////
//***********************************************************************/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
#include "Utils.h"
namespace sdds
{
    const unsigned int MAX_MENU_ITEMS = 20;

    class MenuItem
    {
    private:
        char* m_menuContent {nullptr};
        MenuItem();
        MenuItem(const char* content);
        MenuItem(const MenuItem& src) = delete;
        MenuItem& operator=(const MenuItem& src) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char*() const;
        std::ostream& displayContent(std::ostream& os) const;
        
        friend class Menu; //the friend class can access and manipulate the private and protected members of the class as if it were a member of that class itself. so it says that Menu can access my private members.
    };

    class Menu
    {
    private:
        MenuItem m_title;
        MenuItem* m_menuItems[MAX_MENU_ITEMS];// { nullptr };
        unsigned int m_numItems;
        
    public:
        Menu();
        Menu(const char* title);
        Menu(const Menu& src) = delete;
        Menu& operator=(const Menu& src) = delete;
        std::ostream& displayTitle(std::ostream& os = std::cout) const;
        std::ostream& displayMenu(std::ostream& os = std::cout) const;
        unsigned int run();
        unsigned int operator~();
        Menu& operator<<(const char* menuitemConent);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        const char* operator[](unsigned index)const;
        ~Menu();
        
    };
std::ostream& operator<<(std::ostream& os, const Menu& menu);

}



#endif

