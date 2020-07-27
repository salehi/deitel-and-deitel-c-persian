// Fig. 19.17: readcookie.cpp
// Program to read cookie data.
#include <iostream>
using std::cin;
using std::cout;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;

int main()
{
   string dataString = "";
   string nameString = "";
   string ageString = "";
   string colorString = "";
   
   dataString = getenv( "HTTP_COOKIE" ); // get cookie data
   
   // search through cookie data string              
   int nameLocation = dataString.find( "Name=" ) + 5;
   int endName = dataString.find( "age:" );          
   int ageLocation = dataString.find( "age:" ) + 4;
   int endAge = dataString.find( "color:" );       
   int colorLocation = dataString.find( "color:" ) + 6;
   
   // store cookie data in strings
   nameString = dataString.substr( 
      nameLocation, endName - nameLocation );
   ageString = dataString.substr( 
      ageLocation, endAge - ageLocation );
   colorString = dataString.substr( colorLocation );
   
   cout << "Content-Type: text/html\n\n"; // output HTTP header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
        << "<head><title>Read Cookies</title></head><body>";
   
   if ( dataString != "" ) // data was found
      cout << "<h3>The following data is saved in a cookie on"
         << " your computer</h3><p>Name: " << nameString << "<br/></p>"
         << "<p>Age: " << ageString << "<br/></p>"
         << "<p>Color: " << colorString << "<br/></p>";
   else // no data was found
      cout << "<p>No cookie data.</p>";
   
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
