//==============================================================================
//
// Title:		MpgIOdata
// Purpose:		A short description of the interface.
//
// Created on:	1/20/2022 at 11:25:55 AM by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MpgIOdata_H__
#define __MpgIOdata_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef void*	MpgTaskHandle;



typedef struct
{
	char out0;
	char out1;
	char out2;
	char out3;
	char out4;
	char out5;
	char out6;
	char out7;
	char in0;
	char in1;
	char in2;
	char in3;
}MpgTaskData;

typedef struct
{
	unsigned char in0;
	unsigned char in1;
	unsigned char in2;
	unsigned char in3;
}MpgTaskDataIn;

typedef struct
{
	unsigned char out0;
	unsigned char out1;
	unsigned char out2;
	unsigned char out3;
	unsigned char out4;
	unsigned char out5;
	unsigned char out6;
	unsigned char out7;
}MpgTaskDataOut;

//==============================================================================
// External variables

//==============================================================================
// Global functions

void __declspec(dllexport) __stdcall MpgStart(int *result, int *errCode, char *errInfo, MpgTaskHandle *mpgTask, int simMode, unsigned long int *reserved);
void __declspec(dllexport) __stdcall MpgStop(int *result, int *errCode, char *errInfo, MpgTaskHandle *mpgTask, unsigned long int *reserved);
void __declspec(dllexport) __stdcall DisplayDriverWnd(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned long int *reserved);
void __declspec(dllexport) __stdcall HideDriverWnd(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned long int *reserved);
void __declspec(dllexport) __stdcall GetCmdsState(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, MpgTaskDataOut *lines, unsigned long int *reserved);
void __declspec(dllexport) __stdcall GetSensorsState(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, MpgTaskDataIn *lines, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine0(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine1(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine2(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine3(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine4(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine5(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine6(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);
void __declspec(dllexport) __stdcall SetCmdLine7(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MpgIOdata_H__ */
