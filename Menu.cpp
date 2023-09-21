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
using namespace std;
#include "Menu.h"
#include "Utils.h"
namespace sdds
{
    MenuItem::MenuItem()
    {
        m_menuContent = nullptr;
    }
    MenuItem::MenuItem(const char* content)
    {
        if (content != nullptr && content[0] != '\0')
        {
            m_menuContent = new char[strlen(content) + 1];
            strcpy(m_menuContent, content);
        }
        else
        {
            m_menuContent = nullptr;
        }
    }
    MenuItem::~MenuItem()
    {
        delete [] m_menuContent;
    }
    MenuItem::operator bool() const
    {
        return (m_menuContent != nullptr);
    }
    MenuItem::operator const char*() const
    {
        return m_menuContent;
    }
    ostream& MenuItem::displayContent(ostream& os) const
    {
        if (m_menuContent != nullptr && m_menuContent[0] != '\0')
        {
            os << m_menuContent;
        }
        return os;
    }

    //Menu implementation
    Menu::Menu()
    {
        m_numItems = 0;
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            m_menuItems[i] = nullptr;
        }
    }
    //Using a constructor parameter
    Menu::Menu(const char* title) :m_title(title)
    {
        m_numItems = 0;
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            m_menuItems[i] = nullptr;
        }
    }

    Menu::~Menu()
    {
        for (unsigned int i = 0; i < m_numItems; i++)
        {
            delete m_menuItems[i];
        }
    }
    ostream& Menu::displayTitle(ostream& os) const
    {

        if (m_title)
        {
            
            m_title.displayContent(os);
            
        }
        return os;
    }
    ostream& Menu::displayMenu(ostream& os) const
    {
        if(m_title){
            displayTitle(os);
            os << endl;
        }
        if (*this)
        {
            for (unsigned int i = 0; i < m_numItems; i++)
            {
                os << setw(2) << right << setfill(' ') << i + 1 << "- ";
                m_menuItems[i]->displayContent(os);
                os << endl;
            }
            os << setw(2) << setfill(' ') << 0 << "- Exit" << endl;
            os << "> ";
        }
        
        return os;
    }
    ostream& operator<<(ostream& os, const Menu& menu)
    {
        menu.displayTitle(os);
        //menu.displayMenu(os);

        return os;
        //return (menu.displayMenu(os));
    }
    unsigned int Menu::run()
    {
        displayMenu();
        unsigned int userInput = 0;
        userInput = getInput(0, m_numItems, "Invalid Selection, try again: ");
        return userInput;

    }
    unsigned int Menu::operator~()
    {
        return run();
    }
    //dynamically create a MenuItem out of the content received through the operator argument and then store the address in the available spot
    Menu& Menu::operator<<(const char* menuitemConent)
    {
        if (m_numItems < MAX_MENU_ITEMS) {
            m_menuItems[m_numItems] = new MenuItem(menuitemConent);
            m_numItems++;
        }
        return *this;
    }
    Menu::operator int() const
    {
        return m_numItems;
    }
    Menu::operator unsigned int() const
    {
        //return static_cast<unsigned int>(m_numItems);
        return m_numItems;
    }
    Menu::operator bool() const
    {
        return (m_numItems > 0);
    }
    //access the content of the MenuItem object through the operator[]
    const char* Menu::operator[](unsigned index)const
    {
            if (index >= m_numItems) {
                index %= m_numItems;
            }
            return static_cast<const char*>(*m_menuItems[index]);
    }

}
