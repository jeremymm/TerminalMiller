//***************************************************************************//
// Interface to console class.
// This object controls and creation/destruction and reading/writting
// to a Microsoft Windows Console.
// This class was designed to give GUI based applications a way to display
// debug information outside the Visual Studio IDE
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

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

//***************************************************************************//
// Included to give access to windows types and methods
#include <windows.h>
//***************************************************************************//

//***************************************************************************//
// Maximum size of read buffer
#define MAX_CONSOLE_INPUT_BUFFER_SIZE 16384 // 16K
//***************************************************************************//

//***************************************************************************//
class Console
{
private:
  //*************************************************************************//
  HANDLE mStdErrorHandle;
  HANDLE mStdInputHandle;
  HANDLE mStdOutputHandle;
  //*************************************************************************//
public:
  //*************************************************************************//
  //-------------------------------------------------------------------------//
  // Constuctor/Destructor
  // Note, the lack of virtual destructor. I do not intend for this class to be
  // derived from. I am not using C++11's final keyword for compatiablity 
  // reasons.
  Console();
  ~Console();
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // Sets the title of the Console window
	static void SetTitle(char* title);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // The below Method will read from the console window and will set cpInputbuffer 
  // to the data read from the console.  The amount of data read can be set
  // by passing it to the method via cusBufferSize.  cusBufferSize must be less 
  // than MAX_CONSOLE_INPUT_BUFFER_SIZE
  int Read(char* inputBuffer, const unsigned short bufferSize = MAX_CONSOLE_INPUT_BUFFER_SIZE);
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  // The below method will write the data in cpOutputBuffer to console window.
  // If usBufferSize is not specified then this method will assum the data in 
  // cpOutputBuffer is null terminated. If bWriteToStdError is true then this
  // mthod will write to standard error otherwise it will write to standard output
  int Write(const void* outputBuffer, unsigned short bufferSize = 0, const bool writeToStdError = false);
  //-------------------------------------------------------------------------//
  //*************************************************************************//
};
//***************************************************************************//

#endif CONSOLE_HPP
