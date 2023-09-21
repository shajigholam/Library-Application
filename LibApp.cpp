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
#include "LibApp.h"
#include "PublicationSelector.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Utils.h"
using namespace std;
namespace sdds
{
    LibApp::LibApp(const char* fileName) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationType("Choose the type of publication:")
    {
        if (fileName) {
            strncpy(m_fileName, fileName, MAX_TITLE_PUBLICATION); //??
        }
        m_changed = false;
        m_NOLP = 0; //jump
        //The << operator overload allow chaining multiple calls together
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationType << "Book" << "Publication";
        
        load();
    }
    bool LibApp::confirm(const char* message)
    {
        bool result = false;
        Menu confirmMenu(message);
        confirmMenu << "Yes";

        int returnedValue = confirmMenu.run();
        if (returnedValue == 1) {
            result = true;
        }

        return result;
//        Menu confirmMenu(message);
//        confirmMenu << "Yes";
//        return (confirmMenu.Menu::run() == 1); //correct?
    }
    void LibApp::load() {
        
         char pType;
         cout << "Loading Data" << endl;
         ifstream file(m_fileName);
         Publication* p{};
         m_NOLP = 0;
         while (file) {
            p = nullptr;
            pType = file.get();
            file.ignore();
            if (pType == 'P') {
               p = new Publication;
            }
            else if (pType == 'B') {
               p = new Book;
            }
            if (p) {
               file >> *p;
               if(file) m_PPA[m_NOLP++] = p;
               file.ignore(100, '\n');
            }
         }
         if(m_NOLP) m_LLRN= m_PPA[m_NOLP-1]->getRef();
    }
    void LibApp::save()
    {
        cout << "Saving Data" << endl;
        //open the data file stream for overwriting
        ofstream out_file(m_fileName);
        //Go through the elements of PPA up to the N0LP
        for (int i = 0; i < m_NOLP; i++)
        {
            //Insert all elements into the ofstream object except those with 0 (zero) as Library Reference Number. (return value of getRef() method)
            if (m_PPA[i]->getRef() != 0)
            {
                out_file << *m_PPA[i] << endl;
            }
        }
        out_file.close();
    }
    int LibApp::search(int searchType)
    {
        //cout << "Searching for publication" << endl;
        //use an instance of PublicationSelector class
        PublicationSelector pubSelect("Select one of the following found matches:", 15);
        char tempTitle[MAX_TITLE_PUBLICATION]{};
        char type = ' ';
        int selectType = 0;
        int libRef = 0;
        selectType = m_publicationType.run();
        if (selectType == 1) {
            type = 'B';
        }
        else if (selectType == 2)
        {
            type = 'P';
        }
        //cin.ignore(1000, '\n');
        cout << "Publication Title: ";
        cin.getline(tempTitle, MAX_TITLE_PUBLICATION);
        // if the publication (pointed by the PPA element) is not deleted and type matches the selection of the user and the title contains the title the user entered
        if (searchType == 1) {
            for (int i = 0; i < m_NOLP; i++) {
                if (m_PPA[i]->operator==(tempTitle) && type == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
                    //insert it into the PublicationSelector object
                    pubSelect << m_PPA[i];
                }
            }
        }

        else if (searchType == 2) {
            for (int i = 0; i < m_NOLP; i++) {
                if (m_PPA[i]->operator==(tempTitle) && m_PPA[i]->onLoan() && type == m_PPA[i]->type() && m_PPA[i]->getRef() != 0)
                {
                    pubSelect << m_PPA[i];
                }
            }
        }

        else if (searchType == 3) {
            for (int i = 0; i < m_NOLP; i++)
            {
                if (m_PPA[i]->operator==(tempTitle) && !m_PPA[i]->onLoan() && type == m_PPA[i]->type() && m_PPA[i]->getRef() != 0)
                {
                    pubSelect << m_PPA[i];
                }
            }
        }
        if (pubSelect) {
            pubSelect.sort();
            libRef = pubSelect.run();

            if (libRef > 0)
            {
                cout << *getPub(libRef) << endl;
            }
            else {
                std::cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }

        return libRef;
    }
    void LibApp::returnPub() //do i need abort?? //change if?/
    {
        bool abort = false;
        cout << "Return publication to the library" << endl;
        //Search for "on loan" publications only
        int searchResult = search(2);
        if (!(searchResult > 0)) {
            abort = true;
        }
        //if (!abort) { //change if condition??
        if (!abort && confirm("Return Publication?")) {
        //If the publication is more than 15 days on loan, a 50 cents per day penalty will be calculated for the number of days exceeding the 15 days.
            int daysOnLoan = Date() - getPub(searchResult)->checkoutDate();
            if (daysOnLoan > SDDS_MAX_LOAN_DAYS) {
                int lateDays = daysOnLoan - SDDS_MAX_LOAN_DAYS;
                double penalty = lateDays * 0.5;
                cout << fixed << setprecision(2) << "Please pay $" << penalty << " penalty for being " << lateDays << " days late!" << endl;
            }
            //set the membership number of the publication to 0 (zero)
            getPub(searchResult)->set(0);
            m_changed = true;
        //}
            cout << "Publication returned" << endl;
        }
    }
    void LibApp::newPublication()
    {
        bool full = false;
        if (m_NOLP >= SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
            full = true;
            //and exit?
        }
        if (!full) {
            cout << "Adding new publication to the library" << endl;
            //get the publication type from the user.
            int publicationType = m_publicationType.run();
            //cin.ignore(1000, '\n');
            //in a publication pointer, instantiate a dynamic "Publication" or "Book" based on the user's choice.
            Publication* p = nullptr;
            
            if (publicationType == 0) {
                cout << "Aborted!" << endl;
                full = true;
            }
            else if (publicationType == 1) {
                p = new Book;
                //Read the instantiated object from the cin object.
                cin >> *p;
            }
            else if (publicationType == 2) {
                p = new Publication;
                cin >> *p;
            }
            if (cin.fail()) {
                cin.ignore(1000, '\n');
                cin.clear();
                cout << "Aborted!" << endl;
                //and exit?
                exit(0);
            }
            else {
                //After the user confirms, if the publication object is valid
                if (!full && confirm("Add this publication to the library?")) //!full?
                {
                    if (*p) {
                        m_LLRN++;
                        //set the library reference number to the value
                        p->setRef(m_LLRN);
                        //Add the publication object's address to the end of the PPA
                        m_PPA[m_NOLP] = p;
                        m_NOLP++;
                        m_changed = true;
                        cout << "Publication added" << endl;
                    }
                    else {
                        cout << "Failed to add publication!" << endl;
                        delete p;
                    }
                }
//                else {
//                    cout << "Aborted!" << endl;
//                    //and exit?
//                    exit(0);
//                }
            }
        }
    }
    void LibApp::removePublication()
    {
        cout << "Removing publication from the library" << endl;
        //Search all the publications
        int searchResult = search(1);
        if (searchResult) {
            if (confirm("Remove this publication from the library?"))
            {
                //Set the library reference of the selected publication to 0 (zero)
                getPub(searchResult)->setRef(0);
                
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
    }
    void LibApp::checkOutPub()
    {
        cout << "Checkout publication from the library" << endl;
        //Search in available publications only
        int searchResult = search(3);
        
        if (searchResult > 0 && confirm("Check out publication?")) { //change if condition??
            cout << "Enter Membership number: ";
            int input = getInput(10000, 99999, "Invalid membership number, try again: ");
            
            getPub(searchResult)->set(input);
            m_changed = true;
            cout << "Publication checked out" << endl;
        }
    }
    void LibApp::run()
    {
        bool done = false;
        
        while (!done)
        {
            unsigned int selection = m_mainMenu.run();
            if (selection == 1)
            {
                newPublication();
            }
            else if (selection == 2)
            {
                removePublication();
            }
            else if (selection == 3)
            {
                checkOutPub();
            }
            else if (selection == 4)
            {
                returnPub();
            }
            else if (selection == 0)
            {
                if (m_changed)
                {
                    unsigned int choice = m_exitMenu.run();
                    if (choice == 1)
                    {
                        save();
                        done = true;
                    }
                    else if (choice == 2)
                    {
                        //
                    }
                    else if (choice == 0)
                    {
                        if (confirm("This will discard all the changes are you sure?"))
                        {
                            done = true;
                        }
                    }

                }
                else
                {
                    done = true;
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }
    // Return the address of a Publication object in the PPA that has the library reference number matching the "libRef" argument.
    Publication* LibApp::getPub(int libRef)
    {
        Publication* result = nullptr;
        for (int i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() == libRef) {
                result = m_PPA[i];
            }
        }
        return result;
    }
    LibApp::~LibApp()
    {
        for (int i = 0; i < m_NOLP; i++) {
            delete m_PPA[i]; //*
        }
    }
}
