// Fig. 19.5: localtime.cpp
// Displays the current date and time in a Web browser.
#include <iostream>
using std::cout;

#include <ctime> // definitions of time_t, time, localtime and asctime
using std::time_t;
using std::time;
using std::localtime;
using std::asctime;

int main()
{
   time_t currentTime; // variable for storing time
   
   cout << "Content-Type: text/html\n\n"; // output HTTP header
   
   // output XML declaration and DOCTYPE                   
   cout << "<?xml version = \"1.0\"?>"                     
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";

   time( &currentTime ); // store time in currentTime
   
   // output html element and some of its contents             
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"   
      << "<head><title>Current date and time</title></head>" 
      << "<body><p>" << asctime( localtime( &currentTime ) ) 
      << "</p></body></html>";                               
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
