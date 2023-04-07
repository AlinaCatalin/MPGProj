//==============================================================================
//
// Title:		MpgIOdata
// Purpose:		Digital IO driver for MPG.
//
// Created on:	6.01.2022 at 11:25:55 by Robert Lupu.
// Copyright:	Kober LTD. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <advanlys.h>
#include <ansi_c.h>
#include <utility.h>
#include <nidaqmx.h>
#include "MpgTemplateWnd.h"
#include "ErrorCodes.h"
#include "MpgIOdata.h"
#include "asynctmr.h"
#include "userint.h"

//==============================================================================
// Symbolic constants
#define MPG_DI_READ_TIME 				0.001 /*time period for digital input readings*/
#define MPG_DO_WRITE_TIME 				0.001 /*time period for digital input readings*/
#define MPG_UIR_WRITE_TIME 				0.01 /*time period for digital input readings*/
#define HW_LINE_DEBOUNCING_TIME			5	/*parametru de preconfigurare al driverului*/

const unsigned long long int HW_LINE_DEBOUNCING_MASK	= ~((~(0x0000000000000000)) << HW_LINE_DEBOUNCING_TIME);


//==============================================================================
// Types

typedef struct
{
	unsigned char state; 
	
	long long int thisTime;
	long long int transTime;
}Line;

typedef struct
{
	char			m_deviceName[32];
	TaskHandle 		m_task;
	int 			m_samplesRead;
	int 			m_bytesRead;
	int 			m_nChannels;
	unsigned char 			*m_lines;
	unsigned long long int 	*m_hwLines;

	unsigned char 			*m_oldLines;

	int 			callResult;
	int 			m_errCode;
	char 			m_errInfo[256];
}DioTaskHandle;

typedef struct
{
	int m_panel;
	int m_pictSystem;
	
	int m_idcLed0;
	int m_idcLed1;
	int m_idcLed2;
	int m_idcLed3;
	int m_idcLed4;
	int m_idcLed5;
	int m_idcLed6;
	int m_idcLed7;
	
	int m_idcKey0;
	int m_idcKey1;
	int m_idcKey2;
	int m_idcKey3;
	
}MpgWnd;
	
typedef struct
{
	volatile unsigned int 	m_diTimerFreeToClose; 	///flag to indicate user is exiting (used in data async timer callback function)
	volatile unsigned int 	m_doTimerFreeToClose; 	///flag to indicate user is exiting (used in data async timer callback function)
	volatile unsigned int 	m_uirTimerFreeToClose; 	///flag to indicate user is exiting (used in data async timer callback function)
	volatile unsigned int 	m_diSafeToRead;		   	///flad to indicate that is safe to read data
	volatile unsigned int 	m_doSafeToWrite;		   	///flad to indicate that is safe to read data
}MpgFlags;

typedef struct
{
	DioTaskHandle 	m_diTask1;
	DioTaskHandle 	m_diTask2;
	DioTaskHandle 	m_diTask3;
	DioTaskHandle 	m_doTask;
		
	MpgWnd			m_wnd;
	int 			m_diTimer;
	int 			m_doTimer;
	int 			m_uirTimer;
	//int 			m_lock;

	MpgFlags		m_flags;
	
	int 			m_simMode;
	
}MpgDioTaskHandle;


//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int CVICALLBACK DIAsyncReadTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
static int CVICALLBACK DOAsyncWriteTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
static int CVICALLBACK UirTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
static int CVICALLBACK MpgPanelCB (int panel, int event, void *callbackData, int eventData1, int eventData2);
static int CVICALLBACK OnReadKeyCB (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
static int ConstructMpgWindow(MpgDioTaskHandle *task);

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int Your_Functions_Here (int x)
{
	return x;
}

//==============================================================================
// DLL main entry-point functions
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
				return 0;	  /* out of memory */
			break;
		case DLL_PROCESS_DETACH:
			CloseCVIRTE ();
			break;
	}
	
	return 1;
}

/*******************************************************************************
	configure and start a digital input task
*******************************************************************************/
static int MpgDio_StartTaskDigitalInput(int *result, int *errCode, char *errInfo, unsigned int const devId, char const *lines, void *taskOut, unsigned long int *reserved)
{
	char diLines[2048] = {0};
	char tmpLines[512] = {0};
	char strTmp[32] = {0};
	char *pLine = 0;
	
		///local variable for error code
	int error = 0;
		///the task handle for digital output line
	TaskHandle *task = (TaskHandle*)taskOut;

	strcpy(tmpLines, lines);
	pLine = strtok(tmpLines, ", ");
	while(pLine != 0)
	{
		sprintf(strTmp, "Dev%d/line%s,", devId, pLine);
		strcat(diLines, strTmp);
		pLine = strtok(NULL, ", ");
	}
	diLines[strlen(diLines) - 1] = 0; 
	//DebugPrintf("%s\n", diLines);
		///create the task and check for error
	if((error = DAQmxCreateTask( "", task )) < 0 )
	{
			///the task cannot be created, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
			/// set the task handle to null
		*((TaskHandle*)taskOut) = 0;
	}   ///create digital input channel and check for error
	else if(( error = DAQmxCreateDIChan( *task, diLines, "", DAQmx_Val_ChanPerLine )) < 0)
	{
			///the digital input channel cannot be created, clear the task resources
		DAQmxClearTask( *task );
			///the digital input channel cannot be created, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
		*((TaskHandle*)taskOut) = 0;
	}	///start the created task
	else if(( error = DAQmxStartTask( *task )) < 0 )
	{
		///the task cannot be started, clear the task
		DAQmxClearTask( *task );
			///the task cannot be started, the function call is a fail
		*result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
		*((TaskHandle*)taskOut) = NULL;
	}	///read a value from channel
	else
	{
			///the function call is a success
        *result = TS_PASS;
			///set no error code
		*errCode = MPGENoError;
			///set no error text
		strcpy( errInfo, MPGENoErrorTxt);
	}

	return *errCode;
}

/*******************************************************************************
	configure and start a digital output task
*******************************************************************************/
static int MpgDio_StartTaskDigitalOutput(int *result, int *errCode, char *errInfo, unsigned int const devId, char const *lines, void *taskOut, unsigned long int *reserved)
{
	char doLines[2048] = {0};
	char tmpLines[512] = {0};
	char strTmp[32] = {0};
	char *pLine = 0;

		///local variable for error code
	int error = 0;
		///the task handle for digital output line

	TaskHandle *task = (TaskHandle*)taskOut;
	strcpy(tmpLines, lines);
	pLine = strtok(tmpLines, ", ");
	while(pLine != 0)
	{
		sprintf(strTmp, "Dev%d/line%s,", devId, pLine);
		strcat(doLines, strTmp);
		pLine = strtok(NULL, ", ");
	}
	doLines[strlen(doLines) - 1] = 0; 
	//DebugPrintf("%s\n", diLines);

		///create the task and check for error
	if((error = DAQmxCreateTask( "", task )) < 0 )
	{
			///the task cannot be created, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
			/// set the task handle to null
		*((TaskHandle*)taskOut) = 0;
	}   ///create digital output channel and check for error
	else if(( error = DAQmxCreateDOChan( *task, doLines, "", DAQmx_Val_ChanPerLine )) < 0)
	{
			///the digital output channel cannot be created, clear the task resources
		DAQmxClearTask( *task );
			///the digital output channel cannot be created, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
		*((TaskHandle*)taskOut) = 0;
	}	///start the created task
	else if(( error = DAQmxStartTask( *task )) < 0 )
	{
		///the task cannot be started, clear the task
		DAQmxClearTask( *task );
			///the task cannot be started, the function call is a fail
		*result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
		*((TaskHandle*)taskOut) = NULL;
	}	///read a value from channel
	else
	{
			///the function call is a success
        *result = TS_PASS;
			///set no error code
		*errCode = MPGENoError;
			///set no error text
		strcpy( errInfo, MPGENoErrorTxt);
	}

	return *errCode;
}

/*******************************************************************************
	stop task to read multiple digital input lines
*******************************************************************************/
int KtsDio_StopTaskDigital(int *result, int *errCode, char *errInfo, void *taskDIO, unsigned long int *reserved)
{
		///local variable for error code
	int error = 0;
		///the task handle for digital output line
	TaskHandle *task = (TaskHandle*)taskDIO;

	if((error = DAQmxStopTask( *task )) < 0)
	{
			///the task cannot be be stoped, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
	}	///clear the task resources
	else if(( error = DAQmxClearTask( *task )) < 0 )
	{	   
			///error on clear operation. This not supose to hapen	
			///the task cannot be be cleared, the function call is a fail
        *result = TS_FAIL;
			///set the error code
		*errCode = error;
			///set error description
		DAQmxGetExtendedErrorInfo( errInfo, 256 );
	}
    else
	{
			///the function call is a success
        *result = TS_PASS;
			///set no error code
		*errCode = MPGENoError;
			///set no error text
		strcpy( errInfo, MPGENoErrorTxt);
			///put task handle to null
		*((TaskHandle*)taskDIO) = NULL;
	}

	return *errCode;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall MpgStart(int *result, int *errCode, char *errInfo, MpgTaskHandle *mpgTask, int simMode, unsigned long int *reserved)
{	
	MpgDioTaskHandle *task = (MpgDioTaskHandle*)malloc(sizeof(MpgDioTaskHandle));
	task->m_simMode = simMode;

	ConstructMpgWindow(task);

	if(task->m_simMode == 0)
	{
		MpgDio_StartTaskDigitalInput(&(task->m_diTask1.callResult), &(task->m_diTask1.m_errCode), task->m_diTask1.m_errInfo, 1, "8,9,10,11", &(task->m_diTask1.m_task), NULL);
		DAQmxGetTaskAttribute(task->m_diTask1.m_task, DAQmx_Task_NumChans, &(task->m_diTask1.m_nChannels));
	}
	else
	{
		//atentie la numerul de canale
		task->m_diTask1.m_nChannels = 4;	
	}
		task->m_diTask1.m_lines = (unsigned char*)calloc(task->m_diTask1.m_nChannels, sizeof(unsigned char));
		task->m_diTask1.m_hwLines = (unsigned long long int*)calloc(task->m_diTask1.m_nChannels, sizeof(unsigned long long int));
		task->m_diTask1.m_oldLines = (unsigned char*)calloc(task->m_diTask1.m_nChannels, sizeof(unsigned char));
		
		for(int i = 0; i < task->m_diTask1.m_nChannels; i++)
		{
			task->m_diTask1.m_lines[i] = 0;	
			task->m_diTask1.m_oldLines[i] = 0;
			task->m_diTask1.m_hwLines[i] = 0;
		}
	
	if(task->m_simMode == 0)
	{
		MpgDio_StartTaskDigitalOutput(&(task->m_doTask.callResult), &(task->m_doTask.m_errCode), task->m_doTask.m_errInfo, 1, "0,1,2,3,4,5,6,7", &(task->m_doTask.m_task), NULL);
		DAQmxGetTaskAttribute(task->m_doTask.m_task, DAQmx_Task_NumChans, &(task->m_doTask.m_nChannels));
	}
	else
	{
		//atentie la numarul de canale
		task->m_doTask.m_nChannels = 8;	
	}
		task->m_doTask.m_lines = (unsigned char*)calloc(task->m_doTask.m_nChannels, sizeof(unsigned char));
		task->m_doTask.m_oldLines = (unsigned char*)calloc(task->m_doTask.m_nChannels, sizeof(unsigned char));
		task->m_doTask.m_hwLines = 0;
		for(int i = 0; i < task->m_doTask.m_nChannels; i++)
		{
			task->m_doTask.m_lines[i] = 0;
			task->m_doTask.m_oldLines[i] = 0;
		}
		
	if(task->m_simMode == 0)
	{
		uInt8 uInt8Data[128];
		DAQmxReadDigitalLines(task->m_diTask1.m_task, 1, -1, DAQmx_Val_GroupByChannel, uInt8Data, task->m_diTask1.m_nChannels, &(task->m_diTask1.m_samplesRead), &(task->m_diTask1.m_bytesRead), 0);
		
		for(int i = 0; i < task->m_diTask1.m_nChannels; i++)
		{
			//task->m_diTask1.m_hwLines[i] = ((task->m_diTask1.m_hwLines[i] << 1) | (uInt8Data[i] & 0x01)) & HW_LINE_DEBOUNCING_MASK;
			//task->m_diTask1.m_lines[i] = (task->m_diTask1.m_hwLines[i] == HW_LINE_DEBOUNCING_MASK)? 1 : ((task->m_diTask1.m_hwLines[i] == 0)? 0 : task->m_diTask1.m_lines[i]);	
			task->m_diTask1.m_hwLines[i] = uInt8Data[i];
			task->m_diTask1.m_lines[i] = uInt8Data[i];
			task->m_diTask1.m_oldLines[i] = uInt8Data[i];
		}
		
		DAQmxReadDigitalLines(task->m_doTask.m_task, 1, -1, DAQmx_Val_GroupByChannel, uInt8Data, task->m_doTask.m_nChannels, &(task->m_doTask.m_samplesRead), &(task->m_doTask.m_bytesRead), 0);
		
		for(int i = 0; i < task->m_doTask.m_nChannels; i++)
		{
			//task->m_doTask.m_hwLines[i] = uInt8Data[i];
			task->m_doTask.m_lines[i] = uInt8Data[i];
			task->m_doTask.m_oldLines[i] = uInt8Data[i];
		}
		
	}	

	task->m_flags.m_uirTimerFreeToClose = TRUE;
	task->m_flags.m_diTimerFreeToClose 	= TRUE;
	task->m_flags.m_doTimerFreeToClose 	= TRUE;
	task->m_flags.m_diSafeToRead		= TRUE;
	task->m_flags.m_doSafeToWrite		= TRUE;
	
	task->m_diTimer = NewAsyncTimer(MPG_DI_READ_TIME, -1, 1, DIAsyncReadTimerCB, task);
	task->m_doTimer = NewAsyncTimer(MPG_DO_WRITE_TIME, -1, 1, DOAsyncWriteTimerCB, task);
	task->m_uirTimer = NewAsyncTimer(MPG_UIR_WRITE_TIME, -1, 1, UirTimerCB, task);
	
	*((MpgDioTaskHandle**)mpgTask) = task;
	
	//DisplayPanel(task->m_wnd.m_panel);
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall MpgStop(int *result, int *errCode, char *errInfo, MpgTaskHandle *mpgTask, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);
	
	SetAsyncTimerAttribute( task->m_doTimer, ASYNC_ATTR_ENABLED, 0);
	SetAsyncTimerAttribute( task->m_diTimer, ASYNC_ATTR_ENABLED, 0);
	SetAsyncTimerAttribute( task->m_uirTimer, ASYNC_ATTR_ENABLED, 0);
	while(!task->m_flags.m_diTimerFreeToClose);
	while(!task->m_flags.m_doTimerFreeToClose);
	while(!task->m_flags.m_uirTimerFreeToClose);
	while(!task->m_flags.m_diSafeToRead);
	if(task->m_simMode == 0)
	{
		KtsDio_StopTaskDigital(&(task->m_diTask1.callResult), &(task->m_diTask1.m_errCode), task->m_diTask1.m_errInfo, &(task->m_diTask1.m_task), NULL);
		KtsDio_StopTaskDigital(&(task->m_doTask.callResult), &(task->m_doTask.m_errCode), task->m_doTask.m_errInfo, &(task->m_doTask.m_task), NULL);

		free(task->m_diTask1.m_hwLines);
		task->m_diTask1.m_hwLines = 0;
		
		free(task->m_diTask1.m_lines);
		task->m_diTask1.m_lines = 0;
		
		free(task->m_diTask1.m_oldLines);
		task->m_diTask1.m_oldLines = 0;

		free(task->m_doTask.m_lines);
		task->m_doTask.m_lines = 0;

		free(task->m_doTask.m_oldLines);
		task->m_doTask.m_oldLines = 0;
	}
	DiscardPanel(task->m_wnd.m_panel);
	free(*mpgTask);
	*mpgTask = 0;
	return;
}

/*******************************************************************************
	the callback asynchronous timer
*******************************************************************************/
static int CVICALLBACK DIAsyncReadTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	switch( event )
	{
		case EVENT_TIMER_TICK:/**/
			//CmtGetLock(((MpgDioTaskHandle *)callbackData)->m_lock);
				///hods the resources needed for this mpg task
			MpgDioTaskHandle *task = (MpgDioTaskHandle*)callbackData;	
			
				///a semaphore flag used to wait de panel discard until this callback function returns 
				///is set to FALSE to close
			task->m_flags.m_diTimerFreeToClose = FALSE;
		///the output of DAQmxreadDigitalLines regarding the number of samples readed per channel
		
			uInt8 uInt8Data[128];
			
			if(task->m_simMode == 0)
			{
				DAQmxReadDigitalLines(task->m_diTask1.m_task, 1, -1, DAQmx_Val_GroupByChannel, uInt8Data, task->m_diTask1.m_nChannels, &(task->m_diTask1.m_samplesRead), &(task->m_diTask1.m_bytesRead), 0);
				
				for(int i = 0; i < task->m_diTask1.m_nChannels; i++)
				{
					task->m_diTask1.m_hwLines[i] = ((task->m_diTask1.m_hwLines[i] << 1) | (uInt8Data[i] & 0x01)) & HW_LINE_DEBOUNCING_MASK;
					task->m_diTask1.m_lines[i] = (task->m_diTask1.m_hwLines[i] == HW_LINE_DEBOUNCING_MASK)? 1 : ((task->m_diTask1.m_hwLines[i] == 0)? 0 : task->m_diTask1.m_lines[i]);
				}
			}
			//while(!task->m_flags.m_diSafeToRead);
			task->m_flags.m_diSafeToRead = FALSE;
			memcpy(task->m_diTask1.m_oldLines, task->m_diTask1.m_lines, task->m_diTask1.m_nChannels * sizeof(unsigned char));
			task->m_flags.m_diSafeToRead = TRUE;

			//DAQmxWriteDigitalU8(task->m_doTask.m_task, 1, 0, -1, DAQmx_Val_GroupByChannel, uInt8Data, &(task->m_doTask.m_samplesRead), NULL);
				///now it is clear to close (discard the panel)
			task->m_flags.m_diTimerFreeToClose = TRUE;/**/ 
			//CmtReleaseLock(task->m_lock);

			break;
	}
	return 0;
}

/*******************************************************************************
	the callback asynchronous timer
*******************************************************************************/
static int CVICALLBACK DOAsyncWriteTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	switch( event )
	{
		case EVENT_TIMER_TICK:/**/
			//CmtGetLock(((MpgDioTaskHandle *)callbackData)->m_lock);
				///hods the resources needed for this mpg task
			MpgDioTaskHandle *task = (MpgDioTaskHandle*)callbackData;	
			
				///a semaphore flag used to wait de panel discard until this callback function returns 
				///is set to FALSE to close
			task->m_flags.m_doTimerFreeToClose = FALSE;
			memcpy(task->m_doTask.m_oldLines, task->m_doTask.m_lines, task->m_doTask.m_nChannels * sizeof(unsigned char));
			task->m_flags.m_doTimerFreeToClose = TRUE;
			
			uInt8 uInt8Data[128] = {0};
			for(int i = 0; i < task->m_doTask.m_nChannels; i++)
			{
				//uInt8Data[i] = *(((char*)(task->m_data)) + i);
				uInt8Data[i] = task->m_doTask.m_oldLines[i];
			}
			if(task->m_simMode == 0)
			{
				DAQmxWriteDigitalLines(task->m_doTask.m_task, 1, 1, -1, DAQmx_Val_GroupByChannel, uInt8Data, &(task->m_diTask1.m_samplesRead), NULL);
			}
			
				///now it is clear to close (discard the panel)
			/**/ 

			break;
	}
	return 0;
}

/*******************************************************************************
	the callback asynchronous timer
*******************************************************************************/
static int CVICALLBACK UirTimerCB (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	switch( event )
	{
		case EVENT_TIMER_TICK:/**/
			//CmtGetLock(((MpgDioTaskHandle *)callbackData)->m_lock);
				///hods the resources needed for this mpg task
			MpgDioTaskHandle *task = (MpgDioTaskHandle*)callbackData;	
			
				///a semaphore flag used to wait de panel discard until this callback function returns 
				///is set to FALSE to close
			task->m_flags.m_uirTimerFreeToClose = FALSE;
			
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed0, task->m_doTask.m_lines[0]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed1, task->m_doTask.m_lines[1]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed2, task->m_doTask.m_lines[2]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed3, task->m_doTask.m_lines[3]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed4, task->m_doTask.m_lines[4]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed5, task->m_doTask.m_lines[5]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed6, task->m_doTask.m_lines[6]);
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcLed7, task->m_doTask.m_lines[7]);
			
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcKey0,  task->m_diTask1.m_lines[0]);	
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcKey1,  task->m_diTask1.m_lines[1]);	
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcKey2,  task->m_diTask1.m_lines[2]);	
			SetCtrlVal(task->m_wnd.m_panel, task->m_wnd.m_idcKey3,  task->m_diTask1.m_lines[3]);	
			
						
				///now it is clear to close (discard the panel)
			task->m_flags.m_uirTimerFreeToClose = TRUE;/**/ 

			break;
	}
	return 0;
}


/*******************************************************************************
	
*******************************************************************************/
static int CVICALLBACK MpgPanelCB (int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
	{
		HidePanel(panel);
	}
	return 0;
}

/*******************************************************************************
	
*******************************************************************************/
static int CVICALLBACK OnReadKeyCB (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	MpgDioTaskHandle *task = (MpgDioTaskHandle *)callbackData;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &val);
			if(control == task->m_wnd.m_idcKey0)
			{
				task->m_diTask1.m_lines[0] = (unsigned char)val;
			}
			else if(control == task->m_wnd.m_idcKey1)
			{
				task->m_diTask1.m_lines[1] = (unsigned char)val;	
			}
			else if(control == task->m_wnd.m_idcKey2)
			{
				task->m_diTask1.m_lines[2] = (unsigned char)val;	
			}
			else if(control == task->m_wnd.m_idcKey3)
			{
				task->m_diTask1.m_lines[3] = (unsigned char)val;	
			}
			break;
	}
	return 0;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall DisplayDriverWnd(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);
	int error = 0;;
	
	if(task != NULL)
	{
		error = DisplayPanel(task->m_wnd.m_panel);
		if(error == 0)
		{
				///the function call is a success
	        *result = TS_PASS;
				///set no error code
			*errCode = MPGENoError;
				///set no error text
			strcpy( errInfo, MPGENoErrorTxt);	
		}
		else
		{
				///the function call is a fail
	        *result = TS_FAIL;
				///set no error code
			*errCode = error;
				///set no error text
			DAQmxGetExtendedErrorInfo( errInfo, 256 );
		}
	}
	else
	{
			///the function call is a success
        *result = TS_FAIL;
			///set no error code
		*errCode = MPGENull;
			///set no error text
		strcpy( errInfo, MPGENullTxt);
	}
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall HideDriverWnd(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);
	int error = 0;
	
	if(task != NULL)
	{
		error = HidePanel(task->m_wnd.m_panel);
		if(error == 0)
		{
				///the function call is a success
	        *result = TS_PASS;
				///set no error code
			*errCode = MPGENoError;
				///set no error text
			strcpy( errInfo, MPGENoErrorTxt);	
		}
		else
		{
				///the function call is a fail
	        *result = TS_FAIL;
				///set no error code
			*errCode = error;
				///set no error text
			DAQmxGetExtendedErrorInfo( errInfo, 256 );
		}
	}
	else
	{
			///the function call is a success
        *result = TS_FAIL;
			///set no error code
		*errCode = MPGENull;
			///set no error text
		strcpy( errInfo, MPGENullTxt);
	}
	return;
}

/*******************************************************************************
	
*******************************************************************************/
static int ConstructMpgWindow(MpgDioTaskHandle *task)
{
	int error = 0;

//panel
	task->m_wnd.m_panel = NewPanel(0, "MPG driver", 100, 100, 558, 955);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_CALLBACK_FUNCTION_POINTER, MpgPanelCB);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_CALLBACK_DATA, task);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_CONFORM_TO_SYSTEM_THEME, 1);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_CONFORM_TO_SYSTEM, 1);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_CAN_MAXIMIZE, 0);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_SIZABLE, 0);
	SetPanelAttribute(task->m_wnd.m_panel, ATTR_HAS_TASKBAR_BUTTON, 1);

//System
	task->m_wnd.m_pictSystem = NewCtrl(task->m_wnd.m_panel, CTRL_PICTURE_LS, "", 0, 0);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_pictSystem, ATTR_HEIGHT, 556);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_pictSystem, ATTR_WIDTH, 952);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_pictSystem, ATTR_FRAME_VISIBLE, 0);
	DisplayImageFile (task->m_wnd.m_panel, task->m_wnd.m_pictSystem, "BandaMPG.png");

	
//Sensors
	task->m_wnd.m_idcKey0 = NewCtrl(task->m_wnd.m_panel, CTRL_SQUARE_LED_LS, "", 55, 10);
	if(task->m_simMode)	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_ON_COLOR, VAL_GREEN);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_HEIGHT, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_WIDTH, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_CALLBACK_FUNCTION_POINTER, OnReadKeyCB);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_CALLBACK_DATA, task);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey0, ATTR_TOOLTIP_TEXT, "Digital input senzor 0");
 
	task->m_wnd.m_idcKey1 = NewCtrl(task->m_wnd.m_panel, CTRL_SQUARE_LED_LS, "", 12, 73); 
	if(task->m_simMode)	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_ON_COLOR, VAL_GREEN);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_HEIGHT, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_WIDTH, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_CALLBACK_FUNCTION_POINTER, OnReadKeyCB);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_CALLBACK_DATA, task);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey1, ATTR_TOOLTIP_TEXT, "Digital input senzor 1");

	task->m_wnd.m_idcKey2 = NewCtrl(task->m_wnd.m_panel, CTRL_SQUARE_LED_LS, "", 19, 400); 
	if(task->m_simMode)	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_ON_COLOR, VAL_GREEN);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_HEIGHT, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_WIDTH, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_CALLBACK_FUNCTION_POINTER, OnReadKeyCB);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_CALLBACK_DATA, task);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey2, ATTR_TOOLTIP_TEXT, "Digital input senzor 2");	
	
	task->m_wnd.m_idcKey3 = NewCtrl(task->m_wnd.m_panel, CTRL_SQUARE_LED_LS, "", 37, 472); 
	if(task->m_simMode)	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_CTRL_MODE, VAL_HOT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_ON_COLOR, VAL_GREEN);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_HEIGHT, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_WIDTH, 30);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_CALLBACK_FUNCTION_POINTER, OnReadKeyCB);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_CALLBACK_DATA, task);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcKey3, ATTR_TOOLTIP_TEXT, "Digital input senzor 3");


//efectors
	task->m_wnd.m_idcLed0 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L0", 365, 257); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed0, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed0, ATTR_TOOLTIP_TEXT, "Digital output efector 0");
	
	task->m_wnd.m_idcLed1 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L1", 262, 748); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed1, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed1, ATTR_TOOLTIP_TEXT, "Digital output efector 1");
	
	task->m_wnd.m_idcLed2 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L2", 252, 631); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed2, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed2, ATTR_TOOLTIP_TEXT, "Digital output efector 2");
	
	task->m_wnd.m_idcLed3 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L3", 201, 580); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed3, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed3, ATTR_TOOLTIP_TEXT, "Digital output efector 3");
	
	task->m_wnd.m_idcLed4 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L4", 133, 470); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed4, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed4, ATTR_TOOLTIP_TEXT, "Digital output efector 4");
	
	task->m_wnd.m_idcLed5 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L5", 195, 273); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed5, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed5, ATTR_TOOLTIP_TEXT, "Digital output efector 5");
	
	task->m_wnd.m_idcLed6 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L6", 213, 241); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed6, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed6, ATTR_TOOLTIP_TEXT, "Digital output efector 6");
	
	task->m_wnd.m_idcLed7 = NewCtrl(task->m_wnd.m_panel, CTRL_ROUND_LED_LS, "L7", 239, 193); 
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed7, ATTR_LABEL_BGCOLOR, VAL_TRANSPARENT);	
	SetCtrlAttribute(task->m_wnd.m_panel, task->m_wnd.m_idcLed7, ATTR_TOOLTIP_TEXT, "Digital output efector 7");
	
	return error;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall GetCmdsState(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, MpgTaskDataOut *lines, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	for(int i = 0; i < task->m_doTask.m_nChannels; i++)
	{
		*(((unsigned char*)lines) + i) = task->m_doTask.m_lines[i];
	}
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall GetSensorsState(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, MpgTaskDataIn *lines, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	if(!task->m_flags.m_diSafeToRead)
	{
		for(int i = 0; i < task->m_diTask1.m_nChannels; i++)
		{
			*(((unsigned char*)lines) + i) = task->m_diTask1.m_lines[i];
		}
	}
	else
	{
		for(int i = 0; i < task->m_diTask1.m_nChannels; i++)
		{
			*(((unsigned char*)lines) + i) = task->m_diTask1.m_oldLines[i];
		}
	}
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine0(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[0] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine1(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[1] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine2(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[2] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine3(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[3] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine4(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[4] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine5(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[5] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine6(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[6] = state;
	
	return;
}

/*******************************************************************************
	
*******************************************************************************/
void __declspec(dllexport) __stdcall SetCmdLine7(int *result, int *errCode, char *errInfo, const MpgTaskHandle *mpgTask, unsigned char state, unsigned long int *reserved)
{
	MpgDioTaskHandle *task = *((MpgDioTaskHandle**)mpgTask);

	while(!task->m_flags.m_doTimerFreeToClose);
	task->m_doTask.m_lines[7] = state;
	
	return;
}
