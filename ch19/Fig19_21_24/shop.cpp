// Fig. 19.22: shop.cpp
// Program to display available books.
#include <iostream>
using std::cerr;
using std::cout;
using std::ios;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

void header();

int main()
{
   // variables to store product information
   char book[ 50 ] = "";
   char year[ 50 ] = "";
   char isbn[ 50 ] = "";
   char price[ 50 ] = "";
   
   string bookString = "";
   string yearString = "";
   string isbnString = "";
   string priceString = "";

   ifstream userData( "catalog.txt", ios::in ); // open file for input

   // file could not be opened
   if ( !userData ) 
   {
      cerr << "Could not open database.";
      exit( 1 );
   } // end if
   
   header(); // output header
   
   // output available books                                     
   cout << "<center><br/>Books available for sale<br/><br/>"          
      << "<table border = \"1\" cellpadding = \"7\" >";          
   
   // file is open
   while ( userData ) 
   {
      // retrieve data from file
      userData.getline( book, 50 );
      bookString = book;

      userData.getline( year, 50 );
      yearString = year;

      userData.getline( isbn, 50 );
      isbnString = isbn;

      userData.getline( price, 50 );
      priceString = price;
      
      cout << "<tr><td>" << bookString << "</td><td>" << yearString 
         << "</td><td>" << isbnString << "</td><td>" << priceString 
         << "</td>";
           
      // file is still open after reads
      if ( userData ) 
      {
         // output form with buy button                              
         cout << "<td><form method=\"post\" "                        
            << "action=\"/cgi-bin/viewcart.cgi\">"                   
            << "<input type=\"hidden\" name=\"add\" value=\"true\"/>"
            << "<input type=\"hidden\" name=\"isbn\" value=\""       
            << isbnString << "\"/>" << "<input type=\"submit\" "     
            << "value=\"Add to Cart\"/>\n</form></td>\n";             
      } // end if

      cout << "</tr>\n";
   } // end while
   
   cout << "</table></center><br/>"
      << "<a href=\"/cgi-bin/checkout.cgi\">Check Out</a>"
      << "</body></html>";
   return 0;
} // end main

// function to output header information
void header()
{
   cout << "Content-Type: text/html\n\n"; // output header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Shop Page</title></head><body>";
} // end function header


/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
