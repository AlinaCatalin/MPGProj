        ��  ��                  �       �� ��     0 	        <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" />      �� ��     0 	        4   V S _ V E R S I O N _ I N F O     ���                 ?                         d   S t r i n g F i l e I n f o   @   0 4 0 9 0 4 b 0   D   C o m p a n y N a m e     S . C .   K o b e r   S . R . L .   X   F i l e D e s c r i p t i o n     M p g I O d a t a   ( R e l e a s e   x 8 6 )   (   F i l e V e r s i o n     1 . 0   4 
  I n t e r n a l N a m e   M p g I O d a t a   h "  L e g a l C o p y r i g h t   C o p y r i g h t     S . C .   K o b e r   S . R . L .   2 0 2 2   D   O r i g i n a l F i l e n a m e   M p g I O d a t a . d l l   X   P r o d u c t N a m e     S . C .   K o b e r   S . R . L .   M p g I O d a t a   ,   P r o d u c t V e r s i o n   1 . 0   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	�t  X   C V I D L L P R O T O T Y P E S   C V I D L L E X P O R T S         0 	        int DiscardAsyncTimer(int timerId);
void DisplayDriverWnd(int *result, int *errCode, char *errInfo, void *const *mpgTask, unsigned long *reserved) __declspec(dllexport);
int DllMain(struct HINSTANCE__ *hinstDLL, unsigned long fdwReason, void *lpvReserved);
int GetAsyncTimerAttribute(int timerId, int attribute, void *value);
int GetAsyncTimerResolution(double *resolutionInSecs);
void HideDriverWnd(int *result, int *errCode, char *errInfo, void *const *mpgTask, unsigned long *reserved) __declspec(dllexport);
int KtsDio_StopTaskDigital(int *result, int *errCode, char *errInfo, void *taskDIO, unsigned long *reserved);
int MpgPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
void MpgStart(int *result, int *errCode, char *errInfo, void **mpgTask, struct MpgTaskData *mpgData, int simMode, unsigned long *reserved) __declspec(dllexport);
void MpgStop(int *result, int *errCode, char *errInfo, void **mpgTask, unsigned long *reserved) __declspec(dllexport);
int NewAsyncTimer(double doubleInterval, int count, int status, int (*callbackFunc)(int, int, int, void *, int, int), void *callbackData);
int NewAsyncTimerWithPriority(double doubleInterval, int count, int status, int (*callbackFunc)(int, int, int, void *, int, int), void *callbackData, int threadPriority);
int OnReadKeyCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int ResumeAsyncTimerCallbacks();
int SetAsyncTimerAttribute(int timerId, int attribute, ...);
int SetAsyncTimerAttributeFromParmInfo(int timerId, int attribute, char *parmInfo);
int SuspendAsyncTimerCallbacks();
int Your_Functions_Here(int x);
         �� ��     0	                                        