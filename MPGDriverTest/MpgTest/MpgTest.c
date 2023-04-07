//==============================================================================
//
// Title:		MpgTest
// Purpose:		A short description of the application.
//
// Created on:	1/20/2022 at 5:24:44 PM by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "MpgTest.h"
#include "toolbox.h"
#include "..\MpgIOdata\MpgIOdata.h"
#include "..\MpgIOdata\ErrorCodes.h"

//==============================================================================
// Constants

//==============================================================================
// Types
#define HW_LINE_DEBOUNCING_TIME		5
const unsigned long long int HW_LINE_DEBOUNCING_MASK	= ~((~(0x0000000000000000)) << HW_LINE_DEBOUNCING_TIME);

//==============================================================================
// Static global variables

static int panelHandle = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
MpgTaskHandle 	task;
MpgTaskData 	taskData;
MpgTaskDataIn 	sensorLines;
MpgTaskDataOut 	cmdLines;

//==============================================================================
// Global functions

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	int result = 0;
	int errCode = 0;
	char errInfo[256] = {0};
	//DebugPrintf("Sizeof(unsigned int): %d\n", sizeof(unsigned int));
	//DebugPrintf("Sizeof(unsigned long int): %d\n", sizeof(unsigned long int));
	//DebugPrintf("Sizeof(unsigned long long int): %d\n", sizeof(unsigned long long int));
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "MpgTest.uir", PANEL));
	
	MpgStart(&result, &errCode, errInfo, &task, 1, NULL);
	GetSensorsState(&result, &errCode, errInfo, &task, &sensorLines, NULL);
	SetCtrlVal(panelHandle, PANEL_IDC_LED_T0, sensorLines.in0);	
	SetCtrlVal(panelHandle, PANEL_IDC_LED_T1, sensorLines.in1);	
	SetCtrlVal(panelHandle, PANEL_IDC_LED_T2, sensorLines.in2);	
	SetCtrlVal(panelHandle, PANEL_IDC_LED_T3, sensorLines.in3);	
	
	GetCmdsState(&result, &errCode, errInfo, &task, &cmdLines, NULL);
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_0, cmdLines.out0);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_1, cmdLines.out1);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_2, cmdLines.out2);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_3, cmdLines.out3);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_4, cmdLines.out4);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_5, cmdLines.out5);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_6, cmdLines.out6);	
	SetCtrlVal(panelHandle, PANEL_IDC_BTT_SET_LINE_7, cmdLines.out7);	
	
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	MpgStop(&result, &errCode, errInfo, &task, NULL);
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}

int CVICALLBACK OnKeyReadTimer (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int result = 0;
	int errCode = 0;
	char errInfo[256] = {0};

	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetSensorsState(&result, &errCode, errInfo, &task, &sensorLines, NULL);
			SetCtrlVal(panelHandle, PANEL_IDC_LED_T0, sensorLines.in0);	
			SetCtrlVal(panelHandle, PANEL_IDC_LED_T1, sensorLines.in1);	
			SetCtrlVal(panelHandle, PANEL_IDC_LED_T2, sensorLines.in2);	
			SetCtrlVal(panelHandle, PANEL_IDC_LED_T3, sensorLines.in3);	
			break;
	}
	return 0;
}

int CVICALLBACK OnSetLineCB (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int result = 0;
	int errCode = 0;
	char errInfo[256] = {0};
	
	int val = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &val);
			switch(control)
			{
				case PANEL_IDC_BTT_SET_LINE_0:
					SetCmdLine0(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_1:
					SetCmdLine1(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_2:
					SetCmdLine2(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);taskData.out2 = (unsigned char)val;
					break;
				case PANEL_IDC_BTT_SET_LINE_3:
					SetCmdLine3(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_4:
					SetCmdLine4(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_5:
					SetCmdLine5(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_6:
					SetCmdLine6(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
				case PANEL_IDC_BTT_SET_LINE_7:
					SetCmdLine7(&result, &errCode, errInfo, &task, (unsigned char)val, NULL);
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnDriverWindowCB (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	int result = 0;
	int errCode = 0;
	char errInfo[256] = {0};
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &val);
			if(val)
			{
				DisplayDriverWnd(&result, &errCode, errInfo, &task, NULL);
			}
			else
			{
				HideDriverWnd(&result, &errCode, errInfo, &task, NULL);
			}
			break;
	}
	return 0;
}



int CVICALLBACK OnLineStateTimerCB (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	unsigned int val = 0;
	static unsigned int hwLine = 0;
	static int line = 0;
	
	static unsigned char inputLine[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static unsigned char outputLine[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char graphData[20];
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetCtrlVal(panel, PANEL_IDC_SW_LINE, &val);
			
			hwLine = ((hwLine << 1) | (val & 0x01)) & HW_LINE_DEBOUNCING_MASK;
			line = (hwLine == HW_LINE_DEBOUNCING_MASK)? 1 : ((hwLine == 0)? 0 : line);
			
			for(int i = 0; i < 9; i++)
			{
				inputLine[i] = inputLine[i + 1];
				outputLine[i] =  outputLine[i + 1];	
			}

			inputLine[9] = (unsigned char)val;
			outputLine[9] = (unsigned char)line;
			
			SetCtrlVal(panel, PANEL_IDC_LT_0, hwLine & 0x10); 
			SetCtrlVal(panel, PANEL_IDC_LT_1, hwLine & 0x08); 
			SetCtrlVal(panel, PANEL_IDC_LT_2, hwLine & 0x04); 
			SetCtrlVal(panel, PANEL_IDC_LT_3, hwLine & 0x02); 
			SetCtrlVal(panel, PANEL_IDC_LT_4, hwLine & 0x01);
			SetCtrlVal(panel, PANEL_IDC_LOUT, line);

			for(int i = 0, j = 0; i < 10; i++)
			{
				graphData[j] = inputLine[i];
				j++;
				graphData[j] = outputLine[i];
				j++;
			}
			PlotDigitalLines(panel, PANEL_DIGGRAPH, graphData, 20, VAL_UNSIGNED_CHAR, 2);
			break;
	}
	return 0;
}
