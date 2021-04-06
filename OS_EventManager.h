//********************************************************************************
/*!
\author     Kraemer E
\date       20.01.2019

\file       EventMgr.h
\brief      Supports the concept of an event queue, with function for putting and
            getting events.

***********************************************************************************/


#ifndef _EVENTMGR_H_
#define _EVENTMGR_H_

#include <project.h>
#include "BaseTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Maximum number of events in the queue
#define MAX_EVENT_QUEUE 16

#define EVT_EnterCritical()  CyDisableInts()
#define EVT_LeaveCritical(A) CyEnableInts(A)

typedef enum
{
    eEvtNone ,
    eEvtTimer ,
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

bool EVT_GetEvent(tsEventMsg* psEventMsg);
bool EVT_PostEvent(teEventID eEvtID, uiEventParam1 uiEvtParam1, ulEventParam2 uiEvtParam2);

#ifdef __cplusplus
}
#endif

#endif // _EVENTMGR_H_
