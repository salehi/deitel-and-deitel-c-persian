// Fig. 19.11: getquery.cpp
// Demonstrates GET method with XHTML form.
#include <iostream>
using std::cout;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;

int main()
{
   string nameString = "";
   string wordString = "";
   string query = "";
   
   if ( getenv( "QUERY_STRING" ) ) // QUERY_STRING variable exists
      query = getenv( "QUERY_STRING" ); // retrieve QUERY_STRING value
   
   cout << "Content-Type: text/html\n\n"; // output HTTP header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Using GET with Forms</title></head><body>";
   
   // output xhtml form
   cout << "<p>Enter one of your favorite words here:</p>"
      << "<form method = \"get\" action = \"getquery.cgi\">"
      << "<input type = \"text\" name = \"word\"/>"
      << "<input type = \"submit\" value = \"Submit Word\"/></form>";
   
   if ( query == "" ) // query is empty
      cout << "<p>Please enter a word.</p>";
   else // user entered query string
   {
      int wordLocation = query.find_first_of( "word=" ) + 5;
      wordString = query.substr( wordLocation );
      
      if ( wordString == "" ) // no word was entered
         cout << "<p>Please enter a word.</p>";
      else // word was entered
         cout << "<p>Your word is: " << wordString << "</p>";
   } // end else
   
   cout << "</body></html>";
   return 0;
} // end main


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
