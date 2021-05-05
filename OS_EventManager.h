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


#include "BaseTypes.h"
#include "OS_Config.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Maximum number of events in the queue
#ifndef MAX_EVENT_QUEUE
    #define MAX_EVENT_QUEUE 16
#endif


typedef enum
{
    eEvtNone,
    eEvtSoftwareTimer ,
    eEvtSerialMsgReceived,
    eEvtSerialMsgSend,
    eEvtNewRegulationValue,
    eEvtInitRegulationValue,
    eEvtPower,
    eEvtEnterBoot,
    eEvtError,
    eEvtSendError,
    eEvtStandby,
    eEvtTimeReceived,
    eEvtCommTimeout,
    eEvtSoftwareTimerCreate,
    eEvtSoftwareTimerAsyncCreate,
    eEvtSoftwareTimerDelete,
    eEvtSoftwareTimerStart,
    eEvtSoftwareTimerSuspend,
    eEvtEnterResetState,
    eEvtState_Request,
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
    eEvtParam_TimeFromRtc
} teEventParam;

bool OS_EVT_GetEvent(tsEventMsg* psEventMsg);
bool OS_EVT_PostEvent(teEventID eEvtID, uiEventParam1 uiEvtParam1, ulEventParam2 uiEvtParam2);

#ifdef __cplusplus
}
#endif

#endif // _OS_EVENTMANAGER_H_
