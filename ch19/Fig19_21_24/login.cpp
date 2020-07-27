// Fig. 19.21: login.cpp
// Program to output an XHTML form, verify the
// username and password entered, and add members.
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::ios;

#include <fstream>
using std::fstream;

#include <string>
using std::string;

#include <cstdlib>
using std::getenv;
using std::atoi;
using std::exit;

void header();
void writeCookie();

int main()
{
   char query[ 1024 ] = "";
   string dataString = "";
   
   // strings to store username and password
   string userName = "";
   string passWord = "";
   
   int contentLength = 0;
   bool newMember = false;
   
   // data was posted
   if ( getenv( "CONTENT_LENGTH" ) ) 
   {
      // retrieve query string
      contentLength = atoi( getenv( "CONTENT_LENGTH" ) );
      cin.read( query, contentLength );
      dataString = query;
      
      // find username location
      int userLocation = dataString.find( "user=" ) + 5;
      int endUser = dataString.find( "&" );
      
      // find password location
      int passwordLocation = dataString.find( "password=" ) + 9;
      int endPassword = dataString.find( "&new" );
      
      if ( endPassword > 0 ) // new membership requested       
      {
         newMember = true;
         passWord = dataString.substr(                         
            passwordLocation, endPassword - passwordLocation );
      } // end if
      else // existing member
         passWord = dataString.substr( passwordLocation );

      userName = dataString.substr(             
         userLocation, endUser - userLocation );
   } // end if
   
   // no data was retrieved
   if ( dataString == "" ) 
   {
      header();
      cout << "<p>Please login.</p>";
      
      // output login form                                   
      cout << "<form method = \"post\" action = \"/cgi-bin/login.cgi\">"
         << "<p>User Name: <input type = \"text\" name = \"user\"/><br/>"
         << "Password: <input type = \"password\" name = \"password\"/>"
         << "<br/>New? <input type = \"checkbox\" name = \"new\""
         << " value = \"1\"/></p>"
         << "<input type = \"submit\" value = \"login\"/></form>";
   } // end if
   else // process entered data
   {
      string fileUsername = "";
      string filePassword = "";
      bool userFound = false;
     
      // open user data file for reading and writing
      fstream userData( "userdata.txt", ios::in | ios::out);
     
      if ( !userData ) // could not open file
      {
         cerr << "Could not open database.";
         exit( 1 );
      } // end if

      // add new member 
      if ( newMember ) 
      {         
         // read username and password from file
         while ( !userFound && userData >> fileUsername >> filePassword ) 
         {
            if ( userName == fileUsername ) // name is already taken
               userFound = true;                                    
         } // end while
         
         if ( userFound ) // user name is taken
         {
            header();
            cout << "<p>This name has already been taken.</p>"   
               << "<a href=\"/cgi-bin/login.cgi\">Try Again</a>";
         } // end if
         else // process data
         {
            writeCookie(); // write cookie
            header();
            
            // write user data to file
            userData.clear(); // clear eof, allow write at end of file
            userData << "\n" << userName << "\n" << passWord;
            
            cout << "<p>Your information has been processed."            
               << "<a href=\"/cgi-bin/shop.cgi\">Start Shopping</a></p>";
         } // end else
      } // end if
      else // search for password if entered
      {
         bool authenticated = false;
         
         // read in user data
         while ( !userFound && userData >> fileUsername >> filePassword ) 
         {
            // username was found
            if ( userName == fileUsername )
            {
               userFound = true;

               // determine whether password is correct 
               // and assign bool result to authenticated
               authenticated = ( passWord == filePassword );
            } // end if
         } // end while 
         
         // user is authenticated
         if ( authenticated ) 
         {
            writeCookie();
            header();

            cout << "<p>Thank you for returning, " << userName << "!</p>"
               << "<a href=\"/cgi-bin/shop.cgi\">Start Shopping</a>";    
         } // end if
         else // user not authenticated
         {
            header();
            
            if ( userFound ) // password is incorrect
               cout << "<p>You have entered an incorrect password. "    
                  << "Please try again.</p>"                            
                  << "<a href=\"/cgi-bin/login.cgi\">Back to login</a>";
            else // user is not registered
               cout << "<p>You are not a registered user.</p>"     
                  << "<a href=\"/cgi-bin/login.cgi\">Register</a>";
         } // end else 
      } // end else 
   } // end else
   
   cout << "</body>\n</html>\n";
   return 0;
} // end main

// function to output header
void header()
{
   cout << "Content-Type: text/html\n\n"; // output header
   
   // output XML declaration and DOCTYPE                       
   cout << "<?xml version = \"1.0\"?>"                         
      << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
      << "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";  

   // output html element and some of its contents
   cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
      << "<head><title>Login Page</title></head><body>";
} // end function header

// function to write cookie data
void writeCookie()
{
   string expires = "Friday, 14-MAY-10 16:00:00 GMT";
   cout << "Set-Cookie: CART=; expires=" << expires << "; path=\n";
} // end function writeCookie


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
