// Fig. 19.12: post.cpp
// Demonstrates POST method with XHTML form.
#include <iostream>
using std::cout;
using std::cin;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;
using std::atoi;

int main()
{
   char postString[ 1024 ] = ""; // variable to hold POST data
   string dataString = "";
   string nameString = "";
   string wordString = "";
   int contentLength = 0;
   
   // content was submitted
   if ( getenv( "CONTENT_LENGTH" ) ) 
   {
      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
      cin.read( postString, contentLength );
      dataString = postString;
   } // end if

   cout << "Content-Type: text/html\n\n"; // output header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output XHTML element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Using POST with Forms</title></head><body>";
   
   // output XHTML form
   cout << "<p>Enter one of your favorite words here:</p>"
      << "<form method = \"post\" action = \"post.cgi\">"
      << "<input type = \"text\" name = \"word\" />"
      << "<input type = \"submit\" value = \"Submit Word\" /></form>";
   
   // data was sent using POST
   if ( contentLength > 0 ) 
   {
      int nameLocation = dataString.find_first_of( "word=" ) + 5;
      int endLocation = dataString.find_first_of( "&" ) - 1;
      
      // retrieve entered word
      wordString = dataString.substr( 
         nameLocation, endLocation - nameLocation );
      
      if ( wordString == "" ) // no data was entered in text field
         cout << "<p>Please enter a word.</p>";
      else // output word
         cout << "<p>Your word is: " << wordString << "</p>";
   } // end if
   else // no data was sent
      cout << "<p>Please enter a word.</p>";
   
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
