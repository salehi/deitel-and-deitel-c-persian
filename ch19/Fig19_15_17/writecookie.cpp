// Fig. 19.16: writecookie.cpp
// Program to write a cookie to a client's machine.
#include <iostream>
using std::cin;
using std::cout;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;
using std::atoi;

int main()
{
   char query[ 1024 ] = "";
   string dataString = "";
   string nameString = "";
   string ageString = "";
   string colorString = "";
   int contentLength = 0;
   
   // expiration date of cookie                      
   string expires = "Friday, 14-MAY-10 16:00:00 GMT";
   
   // data was entered
   if ( getenv( "CONTENT_LENGTH" ) ) 
   {
      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
      cin.read( query, contentLength ); // read data from standard input
      dataString = query;

      // search string for data and store locations
      int nameLocation = dataString.find( "name=" ) + 5;
      int endName = dataString.find( "&" );
      int ageLocation = dataString.find( "age=" ) + 4;
      int endAge = dataString.find( "&color" );
      int colorLocation = dataString.find( "color=" ) + 6;
      int endColor = dataString.find( "&button" );
      
      // get value for user's name
      nameString = dataString.substr(  
         nameLocation, endName - nameLocation );
      
      if ( ageLocation > 0 ) // get value for user's age
         ageString = dataString.substr( 
            ageLocation, endAge - ageLocation );
      
      if ( colorLocation > 0 ) // get value for user's favorite color
         colorString = dataString.substr( 
            colorLocation, endColor - colorLocation );

      // set cookie                                      
      cout << "Set-Cookie: Name=" << nameString << "age:"
         << ageString << "color:" << colorString       
         << "; expires=" << expires << "; path=\n";    
   } // end if
      
   cout << "Content-Type: text/html\n\n"; // output HTTP header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Cookie Saved</title></head><body>";
   
   // output user's information
   cout << "<p>A cookie has been set with the following"
      << " data:</p><p>Name: " << nameString  << "<br/></p>"
      << "<p>Age: " << ageString << "<br/></p>"
      << "<p>Color: " << colorString << "<br/></p>"
      << "<p>Click <a href=\"/cgi-bin/readcookie.cgi\">"
      << "here</a> to read saved cookie data.</p></body></html>";
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
