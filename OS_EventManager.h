//********************************************************************************
/*!
\author     Kraemer E
\date       20.01.2019

\file       EventMgr.h
\brief      Supports the concept of an event queue, with function for putting and
            getting events.

***********************************************************************************/
#ifndef _OS_EVENTMANAGER_H_
#define _OS_EVENTMANAGER_H_

/********************************* includes **********************************/
#include "OS_Config.h"
#include "BaseTypes.h"
#include "Project_Config.h"
    
/***************************** defines / macros ******************************/
// Maximum number of events in the queue
#ifndef MAX_EVENT_QUEUE
    #define MAX_EVENT_QUEUE 16
#endif

/* Create events for serial uart */
#if USE_OS_SERIAL_UART
#define EVT_SERIAL_UART \
    eEvtSerialMsgReceived,\
    eEvtSerialMsgSend,
#else
#define EVT_SERIAL_UART
#endif

/* Create empty user events when not defined */
#ifndef USER_EVENT_LIST
    #define USER_EVENT_LIST    
#endif

#ifndef USER_EVENTPARAM_LIST
    #define USER_EVENTPARAM_LIST
#endif

/****************************** type definitions *****************************/
typedef enum
{
    eEvtNone,   
    EVT_SERIAL_UART
    eEvtPower,
    eEvtEnterBoot,
    eEvtError,
    eEvtSendError,
    eEvtSoftwareTimer ,
    eEvtSoftwareTimerCreate,
    eEvtSoftwareTimerAsyncCreate,
    eEvtSoftwareTimerDelete,
    eEvtSoftwareTimerStart,
    eEvtSoftwareTimerSuspend,
    eEvtEnterResetState,
    eEvtState_Request,    
    eEvtErrorHandling,   
    eEvtExecuteSoftwareReset,
    USER_EVENT_LIST 
    eEvtLast
}teEventID;

typedef u16 uiEventParam1;
typedef u32 ulEventParam2;

typedef struct
{
  teEventID     eEventID;
  uiEventParam1  param1;
  ulEventParam2  param2;
}tsEventMsg;

typedef enum
{
    eEvtParam_None = 0,
    eEvtParam_OverTemperatureDeactivation,
    eEvtParam_FaultPins,
    eEvtParam_RegulationValueStartTimer,
    eEvtParam_RegulationValueSaveInFlash,
    eEvtParam_RegulationStart,
    eEvtParam_RegulationStop,
    eEvtParam_StandbyTimeout,
    eEvtParam_EnterStandby,    
    eEvtParam_ExitStandby,
    eEvtParam_StandbyStateMeasure,
    eEvtParam_StandbyStateMessageRec,
    eEvtParam_InitRegulationStart,
    eEvtParam_InitRegulationDone,
    eEvtParam_TimeFromNtpClient,
    eEvtParam_TimeFromRtc,
    eEvtParam_ErrorToManyErrors,
    eEvtParam_ErrorInvalidSlot,
    USER_EVENTPARAM_LIST
    eEvtParam_Last
} teEventParam;
/***************************** global variables ******************************/


/************************ externally visible functions ***********************/
#ifdef __cplusplus
extern "C"
{
#endif

bool OS_EVT_GetEvent(tsEventMsg* psEventMsg);
bool OS_EVT_PostEvent(teEventID eEvtID, uiEventParam1 uiEvtParam1, ulEventParam2 uiEvtParam2);

#ifdef __cplusplus
}
#endif

#endif // _OS_EVENTMANAGER_H_
