// Fig. 19.23: viewcart.cpp
// Program to view books in the shopping cart.
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::ios;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;
using std::atoi;
using std::exit;

void displayShoppingCart( const string & );

int main()
{
   char query[ 1024 ] = ""; // variable to store query string
   string cartData; // variable to hold contents of cart

   string dataString = "";
   string cookieString = "";
   string isbnEntered = "";
   int contentLength = 0;

   // retrieve cookie data               
   if ( getenv( "HTTP_COOKIE" ) )        
   {                                     
      cartData = getenv( "HTTP_COOKIE" );
      cookieString = cartData;           
   } // end if                           
   
   // data was entered
   if ( getenv( "CONTENT_LENGTH" ) ) 
   {
      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
      cin.read( query, contentLength );
      dataString = query;
      
      // find location of isbn value
      int addLocation = dataString.find( "add=" ) + 4;
      int endAdd = dataString.find( "&isbn" );
      int isbnLocation = dataString.find( "isbn=" ) + 5;

      // retrieve isbn number to add to cart
      isbnEntered = dataString.substr( isbnLocation );
      
      // write cookie
      string expires = "Friday, 14-MAY-10 16:00:00 GMT";
      int cartLocation = cookieString.find( "CART=" ) + 5;
      
      if ( cartLocation > 4 ) // cookie exists              
         cookieString = cookieString.substr( cartLocation );

      if ( cookieString == "" ) // no cookie data exists
         cookieString = isbnEntered;
      else // cookie data exists
         cookieString += "," + isbnEntered;
      
      // set cookie                                              
      cout << "Set-Cookie: CART=" << cookieString << "; expires="
         << expires << "; path=\n";                              
   } // end if
   
   cout << "Content-Type: text/html\n\n"; // output HTTP header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  
   
   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Shopping Cart</title></head>"
      << "<body><center><p>Here is your current order:</p>";

   if ( cookieString != "" ) // cookie data exists
      displayShoppingCart( cookieString );                
   else                                           
      cout << "The shopping cart is empty.";      

   // output links back to book list and to check out 
   cout << "</center><br/>";
   cout << "<a href=\"/cgi-bin/shop.cgi\">Back to book list</a><br/>";
   cout << "<a href=\"/cgi-bin/checkout.cgi\">Check Out</a>";
   cout << "</body></html>\n";
   return 0;
} // end main

// function to display items in shopping cart
void displayShoppingCart( const string &cookieRef )
{
   char book[ 50 ] = "";
   char year[ 50 ] = "";
   char isbn[ 50 ] = "";
   char price[ 50 ] = "";

   string bookString = "";
   string yearString = "";
   string isbnString = "";
   string priceString = "";

   ifstream userData( "catalog.txt", ios::in ); // open file for input

   if ( !userData ) // file could not be opened
   {
      cerr << "Could not open database.";
      exit( 1 );
   } // end if

   cout << "<table border = 1 cellpadding = 7 >";  
   cout << "<tr><td>Title</td><td>Copyright</td><td>ISBN</td>" 
      << "<td>Price</td><td>Count</td></tr>";

   // file is open
   while ( !userData.eof() ) 
   {
      // retrieve book information
      userData.getline( book, 50 );
      bookString = book;

      // retrieve year information
      userData.getline( year, 50 );
      yearString = year;

      // retrieve isbn number
      userData.getline( isbn, 50 );
      isbnString = isbn;

      // retrieve price
      userData.getline( price, 50 );
      priceString = price;
         
      int match = cookieRef.find( isbnString, 0 );
      int count = 0;

      // match has been made
      while ( match >= 0 && isbnString != "" ) 
      {
         count++;
         match = cookieRef.find( isbnString, match + 13 );
      } // end while

      // output table row with book information  
      if ( count != 0 )
         cout << "<tr><td>" << bookString << "</td><td>" << yearString 
            << "</td><td>" << isbnString << "</td><td>" << priceString 
            << "</td><td>" << count << "</td></tr>";
   } // end while

   cout << "</table>"; // end table
} // end function displayShoppingCart


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
