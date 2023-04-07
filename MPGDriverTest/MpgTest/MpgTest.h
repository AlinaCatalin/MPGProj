/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_IDC_LED_T3                 2       /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LED_T2                 3       /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LED_T1                 4       /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LED_T0                 5       /* control type: LED, callback function: (none) */
#define  PANEL_IDC_BTT_SET_LINE_7         6       /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_6         7       /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_5         8       /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_4         9       /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_3         10      /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_2         11      /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_1         12      /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDC_BTT_SET_LINE_0         13      /* control type: binary, callback function: OnSetLineCB */
#define  PANEL_IDT_KEY_READ_TIMER         14      /* control type: timer, callback function: OnKeyReadTimer */
#define  PANEL_IDC_DRIVER_WND             15      /* control type: textButton, callback function: OnDriverWindowCB */
#define  PANEL_IDC_LT_1                   16      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LT_4                   17      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LT_3                   18      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LT_2                   19      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LT_0                   20      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_LOUT                   21      /* control type: LED, callback function: (none) */
#define  PANEL_IDC_SW_LINE                22      /* control type: binary, callback function: (none) */
#define  PANEL_DECORATION                 23      /* control type: deco, callback function: (none) */
#define  PANEL_DIGGRAPH                   24      /* control type: digitalGraph, callback function: (none) */
#define  PANEL_IDC_TIMER_LINE_STATE       25      /* control type: timer, callback function: OnLineStateTimerCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnDriverWindowCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnKeyReadTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLineStateTimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSetLineCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif