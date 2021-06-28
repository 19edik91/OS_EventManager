/* ========================================
 *
 * Copyright Eduard Kraemer, 2019
 *
 * ========================================
*/
#include "OS_EventManager.h"

#include "TargetConfig.h"
#ifdef ESPRESSIF_ESP8266
#include <Arduino.h>
#endif

/****************************************** Defines ******************************************************/

/****************************************** Variables ****************************************************/
// array to hold all pending events
static tsEventMsg EventQueue[MAX_EVENT_QUEUE];

// pointer to the next free entry
static u8 ucPutIdx = 0;

// pointer to the topmost entry to get
static u8 ucGetIdx = 0;

// counter of stored in queue events
static u8 ucEventsCnt = 0;

// For test case to get max used messages count
#ifdef EVENT_QUEUE_LOG_MAX_USED
    static u8 ucMaxUsed = 0;
#endif

/****************************************** Function prototypes ******************************************/
static bool PutEvent(teEventID eEventId, uiEventParam1 uiEvtParam1, ulEventParam2 ulEvtParam2);


/****************************************** loacl functiones *********************************************/
//********************************************************************************
/*!
\author     Kraemer E
\date       20.01.2019
\brief      Insert a new event at the end of the queue, and fills in the information
            given in the parameters.
            Function is not interrupt safe, and should be called only from inside
            the module.
\return     bReturnVal  - True if event could be inserted, false if not (queue full)
\param      eEventId    - Id of the new event
\param      uiEvtParam1 - parameter1 of the event
\param      ulEvtParam2 - parameter2 of the event
***********************************************************************************/
static bool PutEvent(teEventID eEventId, uiEventParam1 uiEvtParam1, ulEventParam2 ulEvtParam2)
{
    bool bReturnVal = false;
    
    /* Check if event-queue isn't full and the EventId is valid */
    if(ucEventsCnt < MAX_EVENT_QUEUE 
        && eEventId != eEvtNone 
        && eEventId < eEvtLast)
    {
        tsEventMsg* psEvtMsgSet = &EventQueue[ucPutIdx];

        psEvtMsgSet->eEventID = eEventId;
        psEvtMsgSet->param1 = uiEvtParam1;
        psEvtMsgSet->param2 = ulEvtParam2;

        /* Check if put index reached the buffer limit */
        if(++ucPutIdx >= MAX_EVENT_QUEUE)
        {
            ucPutIdx = 0;
        }

        /* Increment event counter */
        ucEventsCnt++;

        bReturnVal = true;
    
        #ifdef EVENT_QUEUE_LOG_MAX_USED
            if(ucMaxUsed < ucEventsCnt)
                ucMaxUsed = ucEventsCnt;
        #endif
    }
    return bReturnVal;
}


/****************************************** External visible functiones **********************************/

//********************************************************************************
/*!
\author     Kraemer E
\date       20.01.2019
\brief      Gets the event at the front of the queue an removes it. Tha data is
            copied into the buffer given as parameter.
            Function is interrupt safe.
\return     bReturnVal - true if an event was retrieved, false if not
\param      psEventMsg *pEvt - pointer to the event structure which is to be filled
***********************************************************************************/
bool OS_EVT_GetEvent(tsEventMsg* psEventMsgGet)
{
    bool bReturnVal = false;
    
    /* Check if some events are in the queue */
    if(ucEventsCnt)
    {
        //Save interrupts first
        const u32 ulSavedIntrStatus = EnterCritical();

        tsEventMsg* psEventMsgFromQueue = &EventQueue[ucGetIdx];

        /* Copy the event from the event queue into the given structure */
        *psEventMsgGet = *psEventMsgFromQueue;
        
        /* Clear the event ID from the queue */
        psEventMsgFromQueue->eEventID = eEvtNone;

        /* Check if get-index reached the limit */
        if(++ucGetIdx >= MAX_EVENT_QUEUE)
        {
            ucGetIdx = 0;
        }
        
        /* Decrement event counter */
        ucEventsCnt--;        
        bReturnVal = true;

        /* Enable interrupts again */
        LeaveCritical(ulSavedIntrStatus);
    }
    
    return bReturnVal;
}


//********************************************************************************
/*!
\author     Kraemer E
\date       20.01.2019
\brief      Puts a new event at the end of the event queue, given the information
            from the parameters.
            Function is interrupt safe.
\return     u8              - 1 if event could be inserted, 0 if not (queue full)
\param      EVENT_ID id     - id of the new event
\param      EVENT_PARAM1 p1 - parameter1 of the event (can be any 16-bit data)
\param      EVENT_PARAM2 p2 - parameter2 of the event (can be any 32-bit data)
***********************************************************************************/
bool OS_EVT_PostEvent(teEventID eEventId, uiEventParam1 uiEventParam1, ulEventParam2 ulEventParam2)
{   
    bool bReturnVal = false;

    /* Enter critical section -> save interrupts */
    const u32 ulSavedIntrStatus = EnterCritical();

    /* Put event into queue and save status */
    bReturnVal = PutEvent(eEventId, uiEventParam1, ulEventParam2);

    /* Leave critival section -> enable interrupts again */
    LeaveCritical(ulSavedIntrStatus);
    
    return bReturnVal;
}
