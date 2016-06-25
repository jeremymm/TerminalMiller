//***************************************************************************//
// Implementation to Console class.
//
// Created By: Jeremy M Miller on March 20, 2005
// 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2006, Terminal Miller"
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Beta"
//***************************************************************************//

//***************************************************************************//
#include "Console.hpp"
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
Console::Console()
{
  //-------------------------------------------------------------------------//
  // Create Console
  AllocConsole();
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Set handles to standard input, output and error
  mStdErrorHandle   = GetStdHandle(STD_ERROR_HANDLE);
  mStdInputHandle   = GetStdHandle(STD_INPUT_HANDLE);
  mStdOutputHandle  = GetStdHandle(STD_OUTPUT_HANDLE);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Display message box if we could not get input, output or error handles
  if (mStdInputHandle  == INVALID_HANDLE_VALUE || 
      mStdOutputHandle == INVALID_HANDLE_VALUE || 
      mStdErrorHandle  == INVALID_HANDLE_VALUE ) 
  {
    MessageBoxA(nullptr, "GetStdHandle", "Console Error", MB_OK);
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

//***************************************************************************//
Console::~Console()
{
  //-------------------------------------------------------------------------//
  // Release Console
  FreeConsole();
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

//***************************************************************************//
void Console::SetTitle(char* title)
{
  //-------------------------------------------------------------------------//
  // Set title of console
  SetConsoleTitleA(title);
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

//***************************************************************************//
int Console::Read(char* inputBuffer, const unsigned short bufferSize)
{
  //-------------------------------------------------------------------------//
  // This assertaion is thrown if bufferSize is larger than MAX_CONSOLE_INPUT_BUFFER_SIZE
  // The buffer size must be smaller then MAX_CONSOLE_INPUT_BUFFER_SIZE or 
  // ReadConsole will fail
  assert(bufferSize <= MAX_CONSOLE_INPUT_BUFFER_SIZE);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Create a pionter and some space so that ReadConsole can set the size of 
  // buffer read
  LPDWORD pNumberOfBytesRead = new DWORD;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Zero out buffer
  memset(inputBuffer, 0, bufferSize);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Read from the console this function will block until the enter key is pressed
  ReadConsole(mStdInputHandle, static_cast<void*>(inputBuffer), bufferSize, pNumberOfBytesRead, nullptr);
  //-------------------------------------------------------------------------//
  
  //-------------------------------------------------------------------------//
  // Store the number of bytes read in to a temp variable so that it can be returned
  // ans destroy pNumberOfBytesRead craeted above
  int iReturnValue = static_cast<int>(*pNumberOfBytesRead);
  delete pNumberOfBytesRead;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Return the Number of bytes read
  return iReturnValue;
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

//***************************************************************************//
int Console::Write(void const* outputBuffer, unsigned short bufferSize, const bool writeToStdError)
{
  //-------------------------------------------------------------------------//
  // The default of bufferSize is zero.  If this is value passed assume a NULL
  // terminated string is in outputBuffer and set the buffer lenght to the 
  // length of that string
  if(bufferSize == 0)
    bufferSize = static_cast<unsigned short>(strlen(reinterpret_cast<char const*>(outputBuffer)));
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Used to get the number of bytes written
  DWORD numWritten;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // If writeToStdError is true; write to standard error otherwise write to 
  // standard output
  if(writeToStdError)
    WriteConsole(mStdOutputHandle, outputBuffer, bufferSize, &numWritten, nullptr);
  else
    WriteConsole(mStdErrorHandle, outputBuffer, bufferSize, &numWritten, nullptr);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Return the number of bytes written
  return static_cast<int>(numWritten);
  //-------------------------------------------------------------------------//
}
//***************************************************************************//
