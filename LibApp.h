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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Lib.h"
#include "Publication.h"
#include "Book.h"
namespace sdds {
   class LibApp {
   private:
       bool m_changed; //A flag to keep track of changes(ask if user like the changes to be saved or discarded)
       Menu m_mainMenu;
       Menu m_exitMenu;
       //By having an instance of Menu as a private member within another class, it suggests that the other class needs to interact with or utilize the functionalities provided by the Menu class.
       
       //a Menu to the LibApp for selection of publication type
       Menu m_publicationType;
       //Add an array of 256 characters to hold the publication data file name
       char m_fileName[MAX_TITLE_PUBLICATION + 1] {};
       //array of Publication pointers(PPA)
       Publication* m_PPA[SDDS_LIBRARY_CAPACITY];
       //an integer to hold the number of Publications loaded into the PPA
       int m_NOLP;
       //an integer to hold the last library reference number read from the data file
       int m_LLRN;
       
       bool confirm(const char* message);
       void load();  // prints: "Loading Data"<NEWLINE>
       void save();  // prints: "Saving Data"<NEWLINE>
       int search(int searchType);  // prints: "Searching for publication"<NEWLINE>
       
       void returnPub();  /*  Calls the search() method.
                              prints "Returning publication"<NEWLINE>
                              prints "Publication returned"<NEWLINE>
                              sets m_changed to true;
                          */
       void newPublication();
       void removePublication();
       void checkOutPub();
       

       
   public:
       LibApp(const char* fileName = nullptr);
       void run();
       // Return the address of a Publication object in the PPA that has the library reference number matching the "libRef" argument.
       Publication* getPub(int libRef);
       ~LibApp();
   };
}
#endif // !SDDS_LIBAPP_H

