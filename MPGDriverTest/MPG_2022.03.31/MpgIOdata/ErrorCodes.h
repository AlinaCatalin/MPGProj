//==============================================================================
//
// Title:		ErrorCodes.h
// Purpose:		A short description of the interface.
//
// Created on:	1/20/2022 at 11:40:15 AM by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __ErrorCodes_H__
#define __ErrorCodes_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define TS_FAIL													0 	/*The function call did not produce the expected results. This output argument value is used by TEST STAND*/
#define TS_PASS													1	/*The function call produce the expected results. This output argument value is used by TEST STAND*/
		
#define MPGENoError												0 
	#define MPGENoErrorTxt											"Success" 

#define MPGENull												-1 
	#define MPGENullTxt											"MPG drivel null" 
		

//==============================================================================
// Types

		
//==============================================================================
// External variables

//==============================================================================
// Global functions


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __ErrorCodes_H__ */
