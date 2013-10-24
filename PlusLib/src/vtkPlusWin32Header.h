/*=Plus=header=begin======================================================
  Program: Plus
  Copyright (c) Laboratory for Percutaneous Surgery. All rights reserved.
  See License.txt for details.
=========================================================Plus=header=end*/

#ifndef __vtkPlusWin32Header_h
#define __vtkPlusWin32Header_h
	#include "PlusConfigure.h"
	#ifdef _WIN32
		#if defined(PLUS_EXPORTS)
			#  define PLUS_EXPORT __declspec(dllexport)
		# else
			#  define PLUS_EXPORT __declspec(dllimport)
		# endif  /* PLUS_EXPORT */
	#else
		/* unix needs nothing */
		#define PLUS_EXPORT 
	#endif
#endif
