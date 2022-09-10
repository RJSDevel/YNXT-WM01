/**************************************************************************************************
Filename:       zcl_genericapp.c
Revised:        $Date: 2014-10-24 16:04:46 -0700 (Fri, 24 Oct 2014) $
Revision:       $Revision: 40796 $


Description:    Zigbee Cluster Library - sample device application.


Copyright 2006-2014 Texas Instruments Incorporated. All rights reserved.

IMPORTANT: Your use of this Software is limited to those specific rights
granted under the terms of a software license agreement between the user
who downloaded the software, his/her employer (which must be your employer)
and Texas Instruments Incorporated (the "License").  You may not use this
Software unless you agree to abide by the terms of the License. The License
limits your use, and you acknowledge, that the Software may not be modified,
copied or distributed unless embedded on a Texas Instruments microcontroller
or used solely and exclusively in conjunction with a Texas Instruments radio
frequency transceiver, which is integrated into your product.  Other than for
the foregoing purpose, you may not use, reproduce, copy, prepare derivative
works of, modify, distribute, perform, display or sell this Software and/or
its documentation for any purpose.

YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

Should you have any questions regarding your right to use this Software,
contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

/*********************************************************************
This application is a template to get started writing an application
from scratch.

Look for the sections marked with "YNXT_WATER_METER_TODO" to add application
specific code.

Note: if you would like your application to support automatic attribute
reporting, include the BDB_REPORTING compile flag.
*********************************************************************/

/*********************************************************************
* INCLUDES
*/
#include "ZComDef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "MT_SYS.h"

#include "nwk_util.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"
#include "zcl_diagnostic.h"
#include "zcl_se.h"
#include "zcl_ms.h"
#include "zcl_ynxt_water_meter.h"

#include "bdb.h"
#include "bdb_interface.h"
#include "gp_interface.h"

#include "onboard.h"

/* HAL */
#include "hal_led.h"
#include "hal_key.h"
#include "hal_drivers.h"

#include "buzzer.h"

/*********************************************************************
* MACROS
*/


/*********************************************************************
* CONSTANTS
*/


/*********************************************************************
* TYPEDEFS
*/

/*********************************************************************
* GLOBAL VARIABLES
*/
byte zclYnxtWaterMeter_TaskID;


/*********************************************************************
* GLOBAL FUNCTIONS
*/

/*********************************************************************
* LOCAL VARIABLES
*/
uint8 gPermitDuration = 0;    // permit joining default to disabled

devStates_t zclYnxtWaterMeter_NwkState = DEV_INIT;

static uint32 seqNum = 0;

/*********************************************************************
* LOCAL FUNCTIONS
*/
static void zclYnxtWaterMeter_load_nvm(void);

static void zclYnxtWaterMeter_HandleKeys(byte keys);

static void zclYnxtWaterMeter_BasicResetCB_EP_First( void );
static void zclYnxtWaterMeter_BasicResetCB_EP_Second( void );
static void zclYnxtWaterMeter_BasicResetCB_EP_Third( void );
static void zclYnxtWaterMeter_BasicResetCB( void );

static void zclYnxtWaterMeter_OnOffCB( uint8 cmd );

static void zclYnxtWaterMeter_ProcessIdentifyTimeChange( uint8 endpoint );

static void zclYnxtWaterMeter_BindNotification( bdbBindNotificationData_t *data );

static void zclYnxtWaterMeter_ProcessCommissioningStatus(bdbCommissioningModeMsg_t *bdbCommissioningModeMsg);


// Functions to process ZCL Foundation incoming Command/Response messages
static void zclYnxtWaterMeter_ProcessIncomingMsg( zclIncomingMsg_t *msg );
#ifdef ZCL_READ
static uint8 zclYnxtWaterMeter_ProcessInReadRspCmd( zclIncomingMsg_t *pInMsg );
#endif
#ifdef ZCL_WRITE
static uint8 zclYnxtWaterMeter_ProcessInWriteRspCmd( zclIncomingMsg_t *pInMsg );
#endif
static uint8 zclYnxtWaterMeter_ProcessInDefaultRspCmd( zclIncomingMsg_t *pInMsg );
#ifdef ZCL_DISCOVER
static uint8 zclYnxtWaterMeter_ProcessInDiscCmdsRspCmd( zclIncomingMsg_t *pInMsg );
static uint8 zclYnxtWaterMeter_ProcessInDiscAttrsRspCmd( zclIncomingMsg_t *pInMsg );
static uint8 zclYnxtWaterMeter_ProcessInDiscAttrsExtRspCmd( zclIncomingMsg_t *pInMsg );
#endif

static void zclSampleApp_BatteryWarningCB( uint8 voltLevel);

static void zclYnxtWaterMeter_ReportWaterFlow( uint8 endPoint, uint16* value );

static ZStatus_t zclYnxtAuthorizeDirtyHackUpdateEnableStatesCB( afAddrType_t *srcAddr, zclAttrRec_t *pAttr, uint8 oper );

void prepare_for_wait_start_measure(void);
void start_measuring(void);

void halProcessKeyInterrupt(void);

/*********************************************************************
* ZCL General Profile Callback table
*/
static zclGeneral_AppCallbacks_t zclYnxtWaterMeter_CmdCallbacks_EP_First =
{
  zclYnxtWaterMeter_BasicResetCB_EP_First,      // Basic Cluster Reset command
  NULL,                                         // Identify Trigger Effect command
  NULL,                                         // On/Off cluster commands
  NULL,                                         // On/Off cluster enhanced command Off with Effect
  NULL,                                         // On/Off cluster enhanced command On with Recall Global Scene
  NULL,                                         // On/Off cluster enhanced command On with Timed Off
  NULL,                                         // RSSI Location command
  NULL                                          // RSSI Location Response command
};
static zclGeneral_AppCallbacks_t zclYnxtWaterMeter_CmdCallbacks_EP_Second =
{
  zclYnxtWaterMeter_BasicResetCB_EP_Second,     // Basic Cluster Reset command
  NULL,                                         // Identify Trigger Effect command
  NULL,                                         // On/Off cluster commands
  NULL,                                         // On/Off cluster enhanced command Off with Effect
  NULL,                                         // On/Off cluster enhanced command On with Recall Global Scene
  NULL,                                         // On/Off cluster enhanced command On with Timed Off
  NULL,                                         // RSSI Location command
  NULL                                          // RSSI Location Response command
};
static zclGeneral_AppCallbacks_t zclYnxtWaterMeter_CmdCallbacks_EP_Third =
{
  zclYnxtWaterMeter_BasicResetCB_EP_Third,      // Basic Cluster Reset command
  NULL,                                         // Identify Trigger Effect command
  NULL,                                         // On/Off cluster commands
  NULL,                                         // On/Off cluster enhanced command Off with Effect
  NULL,                                         // On/Off cluster enhanced command On with Recall Global Scene
  NULL,                                         // On/Off cluster enhanced command On with Timed Off
  NULL,                                         // RSSI Location command
  NULL                                          // RSSI Location Response command
};
static zclGeneral_AppCallbacks_t zclYnxtWaterMeter_CmdCallbacks =
{
  zclYnxtWaterMeter_BasicResetCB,         // Basic Cluster Reset command
  NULL,                                   // Identify Trigger Effect command
  zclYnxtWaterMeter_OnOffCB,              // On/Off cluster commands
  NULL,                                   // On/Off cluster enhanced command Off with Effect
  NULL,                                   // On/Off cluster enhanced command On with Recall Global Scene
  NULL,                                   // On/Off cluster enhanced command On with Timed Off
  NULL,                                   // RSSI Location command
  NULL                                    // RSSI Location Response command
};

#define HAL_KEY_DEBOUNCE_VALUE  25
static uint8 halKeySavedKeys = 0;
void ynxt_HalKeyPoll(void);

#define U0CFG BV(0) // USART 0 - Alt 2
#define U1CFG BV(1) // USART 1 - Alt 2

#define MODE_FREE_RUNNING BV(0)
#define DIV_128 BV(2) | BV(3)
#define CAPTURE_FALLING_EDGE BV(1)
#define CAPTURE_OFF ~(BV(0) | BV(1))

#define ZERO_FLOW_SECONDS_SLEEP_TRIGGER 3

static volatile uint16 last_capture_ch0 = 0;
static volatile uint16 last_capture_ch1 = 0;
static volatile uint16 last_capture_ch2 = 0;

static volatile uint8 zero_flow_count = 0;


/*********************************************************************
* @fn          zclYnxtWaterMeter_Init
*
* @brief       Initialization function for the zclGeneral layer.
*
* @param       none
*
* @return      none
*/
void zclYnxtWaterMeter_Init( byte task_id )
{
  zclYnxtWaterMeter_TaskID = task_id;
  
  zclYnxtWaterMeter_load_nvm();
  
#ifdef ZCL_DISCOVER
  zclGeneral_RegisterCmdCallbacks( WATER_METER_ENDPOINT_FIRST, &zclYnxtWaterMeter_CmdCallbacks_EP_First);
  zcl_registerCmdList( WATER_METER_ENDPOINT_FIRST, zclCmdsArraySize_EP_First, zclYnxtWaterMeterCmds_EP_First);
  
  zclGeneral_RegisterCmdCallbacks( WATER_METER_ENDPOINT_SECOND, &zclYnxtWaterMeter_CmdCallbacks_EP_Second);
  zcl_registerCmdList( WATER_METER_ENDPOINT_SECOND, zclCmdsArraySize_EP_Second, zclYnxtWaterMeterCmds_EP_Second);
  
  zclGeneral_RegisterCmdCallbacks( WATER_METER_ENDPOINT_THIRD, &zclYnxtWaterMeter_CmdCallbacks_EP_Third);
  zcl_registerCmdList( WATER_METER_ENDPOINT_THIRD, zclCmdsArraySize_EP_Third, zclYnxtWaterMeterCmds_EP_Third);
  
  zclGeneral_RegisterCmdCallbacks( WATER_METER_ENDPOINT_FOURTH, &zclYnxtWaterMeter_CmdCallbacks);
  zcl_registerCmdList( WATER_METER_ENDPOINT_FOURTH, zclCmdsArraySize_EP_Fourth, zclYnxtWaterMeterCmds_EP_Fourth);
#endif
  
  bdb_RegisterSimpleDescriptor( &zclYnxtWaterMeter_SimpleDesc_EP_First );
  zcl_registerAttrList( WATER_METER_ENDPOINT_FIRST, zclYnxtWaterMeter_NumAttributes_EP_First, zclYnxtWaterMeter_Attrs_EP_First );
  zcl_registerReadWriteCB( WATER_METER_ENDPOINT_FIRST, NULL, zclYnxtAuthorizeDirtyHackUpdateEnableStatesCB);
  
  bdb_RegisterSimpleDescriptor( &zclYnxtWaterMeter_SimpleDesc_EP_Second );
  zcl_registerAttrList( WATER_METER_ENDPOINT_SECOND, zclYnxtWaterMeter_NumAttributes_EP_Second, zclYnxtWaterMeter_Attrs_EP_Second );
  zcl_registerReadWriteCB( WATER_METER_ENDPOINT_SECOND, NULL, zclYnxtAuthorizeDirtyHackUpdateEnableStatesCB);
  
  bdb_RegisterSimpleDescriptor( &zclYnxtWaterMeter_SimpleDesc_EP_Third );
  zcl_registerAttrList( WATER_METER_ENDPOINT_THIRD, zclYnxtWaterMeter_NumAttributes_EP_Third, zclYnxtWaterMeter_Attrs_EP_Third );
  zcl_registerReadWriteCB( WATER_METER_ENDPOINT_THIRD, NULL, zclYnxtAuthorizeDirtyHackUpdateEnableStatesCB);
  
  bdb_RegisterSimpleDescriptor( &zclYnxtWaterMeter_SimpleDesc_EP_Fourth );
  zcl_registerAttrList( WATER_METER_ENDPOINT_FOURTH, zclYnxtWaterMeter_NumAttributes_EP_Fourth, zclYnxtWaterMeter_Attrs_EP_Fourth );
  
  // Register the Application to receive the unprocessed Foundation command/response messages
  zcl_registerForMsg( zclYnxtWaterMeter_TaskID );
  zcl_registerForMsgExt( zclYnxtWaterMeter_TaskID, AF_PREPROCESS );
  
  //ZDO_RegisterForZDOMsg(zclYnxtWaterMeter_TaskID, Node_Desc_rsp);
  
  // Register low voltage NV memory protection application callback
  RegisterVoltageWarningCB( zclSampleApp_BatteryWarningCB );
  
  // Register for all key events - This app will handle all key events
  RegisterForKeys( zclYnxtWaterMeter_TaskID );
  
  bdb_RegisterCommissioningStatusCB( zclYnxtWaterMeter_ProcessCommissioningStatus );
  bdb_RegisterIdentifyTimeChangeCB( zclYnxtWaterMeter_ProcessIdentifyTimeChange );
  bdb_RegisterBindNotificationCB( zclYnxtWaterMeter_BindNotification );
  
  PERCFG |= U0CFG | U1CFG;
  
  KEY_INP &= ~KEY_BV;
  KEY_SEL &= ~KEY_BV;
  KEY_DIR &= ~KEY_BV;
  KEY_IEN |= KEY_BV;
  
  CAPTURE0_DIR &= ~CAPTURE0_BV;
  CAPTURE1_DIR &= ~CAPTURE1_BV;
  CAPTURE2_DIR &= ~CAPTURE2_BV;
  
  CAPTURE0_INP |= CAPTURE0_BV;
  CAPTURE1_INP |= CAPTURE1_BV;
  CAPTURE2_INP |= CAPTURE2_BV;
  
  P2INP |= BV(5);
  PICTL &= ~BV(0);
  
  //BuzzerInit();
  //BuzzerOn(zclYnxtWaterMeter_TaskID, 3000, 0);
  //osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_HOLD);
  
  prepare_for_wait_start_measure();
}

void zclYnxtWaterMeter_load_nvm() 
{
  if (osal_nv_item_init(NV_ENABLED_FIRST_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_First), &zclYnxtWaterMeter_DeviceEnable_EP_First) == SUCCESS) {
    osal_nv_read(NV_ENABLED_FIRST_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_First), &zclYnxtWaterMeter_DeviceEnable_EP_First);
  }
  
  if (osal_nv_item_init(NV_CSD_FIRST_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_First), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_First) == SUCCESS) {
    osal_nv_read(NV_CSD_FIRST_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_First), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_First);
  }
  
  if (osal_nv_item_init(NV_ENABLED_SECOND_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Second), &zclYnxtWaterMeter_DeviceEnable_EP_Second) == SUCCESS) {
    osal_nv_read(NV_ENABLED_SECOND_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Second), &zclYnxtWaterMeter_DeviceEnable_EP_Second);
  }
  
  if (osal_nv_item_init(NV_CSD_SECOND_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second) == SUCCESS) {
    osal_nv_read(NV_CSD_SECOND_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second);
  }
  
  if (osal_nv_item_init(NV_ENABLED_THIRD_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Third), &zclYnxtWaterMeter_DeviceEnable_EP_Third) == SUCCESS) {
    osal_nv_read(NV_ENABLED_THIRD_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Third), &zclYnxtWaterMeter_DeviceEnable_EP_Third);
  }
  
  if (osal_nv_item_init(NV_CSD_THIRD_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third) == SUCCESS) {
    osal_nv_read(NV_CSD_THIRD_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third);
  }
}

ZStatus_t zclYnxtAuthorizeDirtyHackUpdateEnableStatesCB(afAddrType_t *srcAddr, zclAttrRec_t *pAttr, uint8 oper)
{
  if (pAttr->attr.attrId == ATTRID_BASIC_DEVICE_ENABLED && oper == ZCL_OPER_WRITE) {
    osal_start_timerEx(zclYnxtWaterMeter_TaskID, YNXT_UPDATE_ENABLED_ATTR, 2000);
  }
  return ZSuccess;
}

/*********************************************************************
* @fn          zclSample_event_loop
*
* @brief       Event Loop Processor for zclGeneral.
*
* @param       none
*
* @return      none
*/
uint16 zclYnxtWaterMeter_event_loop( uint8 task_id, uint16 events )
{
  afIncomingMSGPacket_t *MSGpkt;
  
  (void)task_id;  // Intentionally unreferenced parameter
  
  if ( events & SYS_EVENT_MSG )
  {
    while ((MSGpkt = (afIncomingMSGPacket_t *) osal_msg_receive( zclYnxtWaterMeter_TaskID )))
    {
      switch ( MSGpkt->hdr.event )
      {
      case ZCL_INCOMING_MSG:
        // Incoming ZCL Foundation command/response messages
        zclYnxtWaterMeter_ProcessIncomingMsg( (zclIncomingMsg_t *)MSGpkt );
        break;
        /*
      case ZDO_CB_MSG: 
        if (MSGpkt->clusterId == Node_Desc_rsp) {
        ZDO_Config_Node_Descriptor.ManufacturerCode[0] = 0xCC;
        ZDO_Config_Node_Descriptor.ManufacturerCode[1] = 0xCC;
      }
        break;
        */
      case ZDO_STATE_CHANGE:
        zclYnxtWaterMeter_NwkState = (devStates_t)(MSGpkt->hdr.status);
        
        switch(zclYnxtWaterMeter_NwkState) {
          // now on the network
        case DEV_INIT:
        case DEV_END_DEVICE: 
          osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_HOLD);
          HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
          break;
        case DEV_NWK_DISC:
          HalLedBlink(HAL_LED_1, 100, HAL_LED_DEFAULT_DUTY_CYCLE, HAL_LED_DEFAULT_FLASH_TIME);
          break;
        case DEV_NWK_JOINING: 
          HalLedBlink(HAL_LED_1, 5, HAL_LED_DEFAULT_DUTY_CYCLE, 200);
          break;
        }
        break;
      default:
        break;
      }
      
      // Release the memory
      osal_msg_deallocate( (uint8 *)MSGpkt );
    }
    
    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }
  
  if (events & HAL_KEY_EVENT)
  {
    ynxt_HalKeyPoll();
    return events ^ HAL_KEY_EVENT;
  }
  
  if ( events & YNXT_WATER_METER_NWK_ACTION )
  {
    if (bdbAttributes.bdbNodeIsOnANetwork)
    {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
      bdb_resetLocalAction();
    } 
    else 
    {
      bdb_StartCommissioning(BDB_COMMISSIONING_MODE_NWK_STEERING | BDB_COMMISSIONING_MODE_FINDING_BINDING);
    }
    return ( events ^ YNXT_WATER_METER_NWK_ACTION );
  }
  
  if ( events & YNXT_WATER_METER_END_DEVICE_REJOIN_EVT )
  {
    bdb_ZedAttemptRecoverNwk();
    return ( events ^ YNXT_WATER_METER_END_DEVICE_REJOIN_EVT );
  }
  
  if (events &  YNXT_UPDATE_ENABLED_ATTR)
  {
    uint8 deviceEnable_EP_First;
    osal_nv_read(NV_ENABLED_FIRST_ID, 0, sizeof(deviceEnable_EP_First), &deviceEnable_EP_First);
    
    if (zclYnxtWaterMeter_DeviceEnable_EP_First != deviceEnable_EP_First) {
      if (zclYnxtWaterMeter_DeviceEnable_EP_First) {
        CAPTURE0_SEL &= ~CAPTURE0_BV;
        CAPTURE0_IEN |= CAPTURE0_BV;
        T1CCTL0 &= CAPTURE_OFF;
      } else {
        CAPTURE0_SEL &= ~CAPTURE0_BV;
        CAPTURE0_IEN |= CAPTURE0_BV;
      }
      
      osal_nv_write(NV_ENABLED_FIRST_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_First), &zclYnxtWaterMeter_DeviceEnable_EP_First);
      
      return ( events ^  YNXT_UPDATE_ENABLED_ATTR);
    }
    
    uint8 deviceEnable_EP_Second;
    osal_nv_read(NV_ENABLED_SECOND_ID, 0, sizeof(deviceEnable_EP_Second), &deviceEnable_EP_Second);
    
    if (zclYnxtWaterMeter_DeviceEnable_EP_Second != deviceEnable_EP_Second) 
    {
      if (zclYnxtWaterMeter_DeviceEnable_EP_Second) {
        CAPTURE1_SEL &= ~CAPTURE1_BV;
        CAPTURE1_IEN |= CAPTURE1_BV;
        T1CCTL1 &= CAPTURE_OFF;
      } else {
        CAPTURE1_SEL &= ~CAPTURE1_BV;
        CAPTURE1_IEN |= CAPTURE1_BV;
      }
      
      osal_nv_write(NV_ENABLED_SECOND_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Second), &zclYnxtWaterMeter_DeviceEnable_EP_Second);
      
      return ( events ^  YNXT_UPDATE_ENABLED_ATTR);
    }
    
    uint8 deviceEnable_EP_Third;
    osal_nv_read(NV_ENABLED_THIRD_ID, 0, sizeof(deviceEnable_EP_Third), &deviceEnable_EP_Third);
    
    if (zclYnxtWaterMeter_DeviceEnable_EP_Third != deviceEnable_EP_Third) {
      if (zclYnxtWaterMeter_DeviceEnable_EP_Third) {
        CAPTURE2_SEL &= ~CAPTURE2_BV;
        CAPTURE2_IEN |= CAPTURE2_BV;
        T1CCTL2 &= CAPTURE_OFF;
      } else {
        CAPTURE2_SEL &= ~CAPTURE2_BV;
        CAPTURE2_IEN &= ~CAPTURE2_BV;
      }
      
      osal_nv_write(NV_ENABLED_THIRD_ID, 0, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Third), &zclYnxtWaterMeter_DeviceEnable_EP_Third);
    }
    
    
    return ( events ^  YNXT_UPDATE_ENABLED_ATTR);
  }
  
  if ( events & YNXT_WATER_METER_MEASUREMENT )
  { 
    bool firstEnabled = zclYnxtWaterMeter_DeviceEnable_EP_First == DEVICE_ENABLED;
    bool secondEnabled = zclYnxtWaterMeter_DeviceEnable_EP_Second == DEVICE_ENABLED;
    bool thirdEnabled = zclYnxtWaterMeter_DeviceEnable_EP_Third == DEVICE_ENABLED;
    
    uint16 flow0_report = 0;
    uint16 flow1_report = 0;
    uint16 flow2_report = 0;
    
    if (firstEnabled) {
      float flow_per_sec = last_capture_ch0 * COUNTER_PULSE_WEIGHT_PER_SEC;
      flow0_report = (uint16) (flow_per_sec * 10);
      zclYnxtWaterMeter_CurrentSummationDelivered_EP_First.lsb += (flow_per_sec / 60.0) * 1000; // Why 1000? Because if flow is less than 0.4, result can't reach integer part
    }
    
    last_capture_ch0 = 0;
    
    if (secondEnabled) {
      float flow_per_sec = last_capture_ch1 * COUNTER_PULSE_WEIGHT_PER_SEC;
      flow1_report = (uint16) (flow_per_sec * 10);
      zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second.lsb += (flow_per_sec / 60.0) * 1000;
    }
    
    last_capture_ch1 = 0;
    
    if (thirdEnabled) {
      float flow_per_sec = last_capture_ch2 * COUNTER_PULSE_WEIGHT_PER_SEC;
      flow2_report = (uint16) (flow_per_sec * 10);
      zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third.lsb += (flow_per_sec / 60.0) * 1000;
    }
    
    last_capture_ch2 = 0;
    
    if (zclYnxtWaterMeter_FlowMeasuredValue_EP_First != flow0_report) {
      zclYnxtWaterMeter_FlowMeasuredValue_EP_First = flow0_report;
      zclYnxtWaterMeter_ReportWaterFlow(WATER_METER_ENDPOINT_FIRST, &zclYnxtWaterMeter_FlowMeasuredValue_EP_First);
    }
    
    if (zclYnxtWaterMeter_FlowMeasuredValue_EP_Second != flow1_report) {
      zclYnxtWaterMeter_FlowMeasuredValue_EP_Second = flow1_report;
      zclYnxtWaterMeter_ReportWaterFlow(WATER_METER_ENDPOINT_SECOND, &zclYnxtWaterMeter_FlowMeasuredValue_EP_Second);
    }
    
    if (zclYnxtWaterMeter_FlowMeasuredValue_EP_Third != flow2_report) {
      zclYnxtWaterMeter_FlowMeasuredValue_EP_Third = flow1_report;
      zclYnxtWaterMeter_ReportWaterFlow(WATER_METER_ENDPOINT_THIRD, &zclYnxtWaterMeter_FlowMeasuredValue_EP_Third);
    }
    
    if (flow0_report == 0 && flow1_report == 0 && flow2_report == 0) {
      if (zero_flow_count++ == ZERO_FLOW_SECONDS_SLEEP_TRIGGER) {
        zero_flow_count = 0;
        
        bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_FIRST, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
        bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_SECOND, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
        bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_THIRD, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
        
        osal_nv_write(NV_CSD_FIRST_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_First), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_First);
        osal_nv_write(NV_CSD_SECOND_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second);
        osal_nv_write(NV_CSD_THIRD_ID, 0, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third), &zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third);
        
        prepare_for_wait_start_measure();
      }
    }
    
    return ( events ^ YNXT_WATER_METER_MEASUREMENT );
  }
  
  // Discard unknown events
  return 0;
}

void prepare_for_wait_start_measure() {
  osal_stop_timerEx(zclYnxtWaterMeter_TaskID, YNXT_WATER_METER_MEASUREMENT);
  
  T1CCTL0 &= CAPTURE_OFF;
  T1CCTL1 &= CAPTURE_OFF;
  T1CCTL2 &= CAPTURE_OFF;
  
  P0IE = 0;
  IEN2 &= ~BV(4); // P1IE
  
  P0IFG = 0;
  P0IF = 0;
  P1IFG = 0;
  P1IF = 0;
  
  CAPTURE0_SEL &= ~CAPTURE0_BV;
  CAPTURE1_SEL &= ~CAPTURE1_BV;
  CAPTURE2_SEL &= ~CAPTURE2_BV;
  
  if (zclYnxtWaterMeter_DeviceEnable_EP_First) CAPTURE0_IEN |= CAPTURE0_BV;
  else CAPTURE0_IEN &= ~CAPTURE0_BV;
  
  if (zclYnxtWaterMeter_DeviceEnable_EP_Second) CAPTURE1_IEN |= CAPTURE2_BV;
  else CAPTURE1_IEN &= ~CAPTURE1_BV;
  
  if (zclYnxtWaterMeter_DeviceEnable_EP_Third) CAPTURE2_IEN |= CAPTURE2_BV;
  else CAPTURE2_IEN &= ~CAPTURE2_BV;
  
  P0IE = 1;
  IEN2 |= BV(4); // P1IE
  
  osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_CONSERVE);
}

void start_measuring() {
  
  if (CAPTURE0_IFG & CAPTURE0_BV) {
    last_capture_ch0++;
    
    CAPTURE0_IEN &= ~CAPTURE0_BV;
    CAPTURE0_SEL |= CAPTURE0_BV;
    
    T1STAT &= ~BV(0);
    T1CCTL0 |= CAPTURE_FALLING_EDGE;
  }
  
  if (CAPTURE1_IFG & CAPTURE1_BV) {
    last_capture_ch1++;
    
    CAPTURE1_IEN &= ~CAPTURE1_BV;
    CAPTURE1_SEL |= CAPTURE1_BV;
    
    T1STAT &= ~BV(1);
    T1CCTL1 |= CAPTURE_FALLING_EDGE;
  }
  
  if (CAPTURE2_IFG & CAPTURE2_BV) {
    last_capture_ch2++;
    
    CAPTURE2_IEN &= ~CAPTURE2_BV;
    CAPTURE2_SEL |= CAPTURE2_BV;
    
    T1STAT &= ~BV(2);
    T1CCTL2 |= CAPTURE_FALLING_EDGE;
  }
  
  T1IE = 1;
  DMAIE = 1;
  T1CTL = MODE_FREE_RUNNING | DIV_128;
  
  osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_HOLD);
  osal_start_reload_timer( zclYnxtWaterMeter_TaskID, YNXT_WATER_METER_MEASUREMENT, 1000);
}

HAL_ISR_FUNCTION( captureIsr, T1_VECTOR )
{
  HAL_ENTER_ISR();
  
  if(T1STAT & BV(0))
  {
    last_capture_ch0++;
    T1STAT &= ~BV(0);
  }
  
  if(T1STAT & BV(1))
  {
    last_capture_ch1++;
    T1STAT &= ~BV(1);
  }
  
  if(T1STAT & BV(2))
  {
    last_capture_ch2++;
    T1STAT &= ~BV(2);
  }
  
  T1IF = 0;
  CLEAR_SLEEP_MODE();
  HAL_EXIT_ISR();
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_HandleKeys
*
* @brief   Handles all key events for this device.
*
* @param   shift - true if in shift/alt.
* @param   keys - bit field for key events. Valid entries:
* @return  none
*/
static void zclYnxtWaterMeter_HandleKeys(byte keys)
{ 
  if ( keys & HAL_KEY_SW_1 )
  {
    HalLedSet(HAL_LED_1, HAL_LED_MODE_ON);
    osal_start_timerEx(zclYnxtWaterMeter_TaskID, YNXT_WATER_METER_NWK_ACTION, 2000);
  } else {
    osal_stop_timerEx(zclYnxtWaterMeter_TaskID, HAL_KEY_EVENT);
    if (osal_get_timeoutEx(zclYnxtWaterMeter_TaskID, YNXT_WATER_METER_NWK_ACTION) != 0) {
      HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
      HAL_SYSTEM_RESET();
    }
  } 
}

void ynxt_HalKeyPoll(void)
{
  uint8 keys = 0;
  
  if (HAL_PUSH_KEY())
  {
    osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_HOLD);
    keys |= HAL_KEY_SW_1;
  }
  
  if (keys == halKeySavedKeys) {
    return;
  }
  
  halKeySavedKeys = keys;
  
  zclYnxtWaterMeter_HandleKeys(keys);
}

HAL_ISR_FUNCTION( halKeyPort0Isr, P0INT_VECTOR )
{
  HAL_ENTER_ISR();
  
  if (HAL_PUSH_KEY()) {
    osal_start_reload_timer(zclYnxtWaterMeter_TaskID, HAL_KEY_EVENT, HAL_KEY_DEBOUNCE_VALUE);
  } else {
    start_measuring();
  }
  
  P0IFG = 0;
  P0IF = 0;
  
  HAL_EXIT_ISR();
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessCommissioningStatus
*
* @brief   Callback in which the status of the commissioning process are reported
*
* @param   bdbCommissioningModeMsg - Context message of the status of a commissioning process
*
* @return  none
*/
static void zclYnxtWaterMeter_ProcessCommissioningStatus(bdbCommissioningModeMsg_t *bdbCommissioningModeMsg)
{
  switch(bdbCommissioningModeMsg->bdbCommissioningMode)
  {
  case BDB_COMMISSIONING_NWK_STEERING:
    if(bdbCommissioningModeMsg->bdbCommissioningStatus == BDB_COMMISSIONING_SUCCESS)
    {
      //YOUR JOB:
      //We are on the nwk, what now?
      osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_CONSERVE);
    }
    else if (bdbCommissioningModeMsg->bdbCommissioningStatus != BDB_COMMISSIONING_IN_PROGRESS)
    {
      //See the possible errors for nwk steering procedure
      //No suitable networks found
      //Want to try other channels?
      //try with bdb_setChannelAttribute
      osal_pwrmgr_task_state(zclYnxtWaterMeter_TaskID, PWRMGR_CONSERVE);
    }
    break;
  case BDB_COMMISSIONING_FINDING_BINDING:
    if(bdbCommissioningModeMsg->bdbCommissioningStatus == BDB_COMMISSIONING_SUCCESS)
    {
      //YOUR JOB:
    }
    break;
  case BDB_COMMISSIONING_INITIALIZATION:
    
    //Initialization notification can only be successful. Failure on initialization
    //only happens for ZED and is notified as BDB_COMMISSIONING_PARENT_LOST notification
    
    //YOUR JOB:
    //We are on a network, what now?
    
    break;
  case BDB_COMMISSIONING_PARENT_LOST:
    if(bdbCommissioningModeMsg->bdbCommissioningStatus == BDB_COMMISSIONING_NETWORK_RESTORED)
    {
      //We did recover from losing parent
    }
    else
    {
      //Parent not found, attempt to rejoin again after a fixed delay
      osal_start_timerEx(zclYnxtWaterMeter_TaskID, YNXT_WATER_METER_END_DEVICE_REJOIN_EVT, YNXT_WATER_METER_END_DEVICE_REJOIN_DELAY);
    }
    break;
  }
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessIdentifyTimeChange
*
* @brief   Called to process any change to the IdentifyTime attribute.
*
* @param   endpoint - in which the identify has change
*
* @return  none
*/
static void zclYnxtWaterMeter_ProcessIdentifyTimeChange( uint8 endpoint )
{
  
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_BindNotification
*
* @brief   Called when a new bind is added.
*
* @param   data - pointer to new bind data
*
* @return  none
*/
static void zclYnxtWaterMeter_BindNotification( bdbBindNotificationData_t *data )
{
  // YNXT_WATER_METER_TODO: process the new bind information
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_BasicResetCB
*
* @brief   Callback from the ZCL General Cluster Library
*          to set all the Basic Cluster attributes to default values.
*
* @param   none
*
* @return  none
*/
static void zclYnxtWaterMeter_BasicResetCB_EP_First( void ) {
  zclYnxtWaterMeter_ResetAttributesToDefaultValues_EP_First();
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_FIRST, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
}

static void zclYnxtWaterMeter_BasicResetCB_EP_Second( void ) {
  zclYnxtWaterMeter_ResetAttributesToDefaultValues_EP_Second();
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_SECOND, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
}

static void zclYnxtWaterMeter_BasicResetCB_EP_Third( void ) {
  zclYnxtWaterMeter_ResetAttributesToDefaultValues_EP_Third();
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_THIRD, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
}

static void zclYnxtWaterMeter_BasicResetCB( void )
{
  zclYnxtWaterMeter_BasicResetCB_EP_First();
  zclYnxtWaterMeter_BasicResetCB_EP_Second();
  zclYnxtWaterMeter_BasicResetCB_EP_Third();
  zclYnxtWaterMeter_ResetAttributesToDefaultValues();
  
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_FIRST, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_SECOND, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
  bdb_RepChangedAttrValue(WATER_METER_ENDPOINT_THIRD, ZCL_CLUSTER_ID_SE_METERING, ATTRID_SE_METERING_CURR_SUMM_DLVD);
}
/*********************************************************************
* @fn      zclSampleApp_BatteryWarningCB
*
* @brief   Called to handle battery-low situation.
*
* @param   voltLevel - level of severity
*
* @return  none
*/
void zclSampleApp_BatteryWarningCB( uint8 voltLevel )
{
  if ( voltLevel == VOLT_LEVEL_CAUTIOUS )
  {
    // Send warning message to the gateway and blink LED
  }
  else if ( voltLevel == VOLT_LEVEL_BAD )
  {
    // Shut down the system
  }
}

/******************************************************************************
*
*  Functions for processing ZCL Foundation incoming Command/Response messages
*
*****************************************************************************/

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessIncomingMsg
*
* @brief   Process ZCL Foundation incoming message
*
* @param   pInMsg - pointer to the received message
*
* @return  none
*/
static void zclYnxtWaterMeter_ProcessIncomingMsg( zclIncomingMsg_t *pInMsg )
{
  switch ( pInMsg->zclHdr.commandID )
  {
#ifdef ZCL_READ
  case ZCL_CMD_READ_RSP:
    zclYnxtWaterMeter_ProcessInReadRspCmd( pInMsg );
    break;
#endif
#ifdef ZCL_WRITE
  case ZCL_CMD_WRITE_RSP:
    zclYnxtWaterMeter_ProcessInWriteRspCmd( pInMsg );
    break;
#endif
  case ZCL_CMD_CONFIG_REPORT:
  case ZCL_CMD_CONFIG_REPORT_RSP:
  case ZCL_CMD_READ_REPORT_CFG:
  case ZCL_CMD_READ_REPORT_CFG_RSP:
  case ZCL_CMD_REPORT:
    //bdb_ProcessIncomingReportingMsg( pInMsg );
    break;
    
  case ZCL_CMD_DEFAULT_RSP:
    zclYnxtWaterMeter_ProcessInDefaultRspCmd( pInMsg );
    break;
#ifdef ZCL_DISCOVER
  case ZCL_CMD_DISCOVER_CMDS_RECEIVED_RSP:
    zclYnxtWaterMeter_ProcessInDiscCmdsRspCmd( pInMsg );
    break;
    
  case ZCL_CMD_DISCOVER_CMDS_GEN_RSP:
    zclYnxtWaterMeter_ProcessInDiscCmdsRspCmd( pInMsg );
    break;
    
  case ZCL_CMD_DISCOVER_ATTRS_RSP:
    zclYnxtWaterMeter_ProcessInDiscAttrsRspCmd( pInMsg );
    break;
    
  case ZCL_CMD_DISCOVER_ATTRS_EXT_RSP:
    zclYnxtWaterMeter_ProcessInDiscAttrsExtRspCmd( pInMsg );
    break;
#endif
  default:
    break;
  }
  
  if ( pInMsg->attrCmd )
    osal_mem_free( pInMsg->attrCmd );
}

#ifdef ZCL_READ
/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInReadRspCmd
*
* @brief   Process the "Profile" Read Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInReadRspCmd( zclIncomingMsg_t *pInMsg )
{
  
  return ( TRUE );
}
#endif // ZCL_READ

#ifdef ZCL_WRITE
/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInWriteRspCmd
*
* @brief   Process the "Profile" Write Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInWriteRspCmd( zclIncomingMsg_t *pInMsg )
{
  zclWriteRspCmd_t *writeRspCmd;
  uint8 i;
  
  writeRspCmd = (zclWriteRspCmd_t *)pInMsg->attrCmd;
  for ( i = 0; i < writeRspCmd->numAttr; i++ )
  {
    // Notify the device of the results of the its original write attributes
    // command.
  }
  
  return ( TRUE );
}
#endif // ZCL_WRITE

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInDefaultRspCmd
*
* @brief   Process the "Profile" Default Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInDefaultRspCmd( zclIncomingMsg_t *pInMsg )
{
  // zclDefaultRspCmd_t *defaultRspCmd = (zclDefaultRspCmd_t *)pInMsg->attrCmd;
  
  // Device is notified of the Default Response command.
  (void)pInMsg;
  
  return ( TRUE );
}

#ifdef ZCL_DISCOVER
/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInDiscCmdsRspCmd
*
* @brief   Process the Discover Commands Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInDiscCmdsRspCmd( zclIncomingMsg_t *pInMsg )
{
  zclDiscoverCmdsCmdRsp_t *discoverRspCmd;
  uint8 i;
  
  discoverRspCmd = (zclDiscoverCmdsCmdRsp_t *)pInMsg->attrCmd;
  for ( i = 0; i < discoverRspCmd->numCmd; i++ )
  {
    // Device is notified of the result of its attribute discovery command.
  }
  
  return ( TRUE );
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInDiscAttrsRspCmd
*
* @brief   Process the "Profile" Discover Attributes Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInDiscAttrsRspCmd( zclIncomingMsg_t *pInMsg )
{
  zclDiscoverAttrsRspCmd_t *discoverRspCmd;
  uint8 i;
  
  discoverRspCmd = (zclDiscoverAttrsRspCmd_t *)pInMsg->attrCmd;
  for ( i = 0; i < discoverRspCmd->numAttr; i++ )
  {
    // Device is notified of the result of its attribute discovery command.
  }
  
  return ( TRUE );
}

/*********************************************************************
* @fn      zclYnxtWaterMeter_ProcessInDiscAttrsExtRspCmd
*
* @brief   Process the "Profile" Discover Attributes Extended Response Command
*
* @param   pInMsg - incoming message to process
*
* @return  none
*/
static uint8 zclYnxtWaterMeter_ProcessInDiscAttrsExtRspCmd( zclIncomingMsg_t *pInMsg )
{
  zclDiscoverAttrsExtRsp_t *discoverRspCmd;
  uint8 i;
  
  discoverRspCmd = (zclDiscoverAttrsExtRsp_t *)pInMsg->attrCmd;
  for ( i = 0; i < discoverRspCmd->numAttr; i++ )
  {
    // Device is notified of the result of its attribute discovery command.
  }
  
  return ( TRUE );
}
#endif // ZCL_DISCOVER
/****************************************************************************
****************************************************************************/

static afAddrType_t addr;

static void zclYnxtWaterMeter_OnOffCB( uint8 cmd ) 
{
  afIncomingMSGPacket_t *pPtr = zcl_getRawAFMsg();
  
  if (cmd == COMMAND_ON) {
    LED2_SBIT = LED2_POLARITY(1);
  } else if (cmd == COMMAND_OFF) {
    LED2_SBIT = LED2_POLARITY(0);
  }
  
  zclYnxtWaterMeter_Ext_OnOff = cmd;
  
  //addr.addr.shortAddr = pPtr->srcAddr.addr.shortAddr;
}

static void zclYnxtWaterMeter_ReportWaterFlow(uint8 endPoint, uint16* value) 
{
  zclReportCmd_t *pReportCmd = osal_mem_alloc(sizeof(zclReportCmd_t) + sizeof(zclReport_t));
  
  if (pReportCmd != NULL) {
    pReportCmd->numAttr = 1;
    pReportCmd->attrList[0].attrID = ATTRID_MS_FLOW_MEASUREMENT_MEASURED_VALUE;
    pReportCmd->attrList[0].dataType = ZCL_DATATYPE_UINT16;
    pReportCmd->attrList[0].attrData = (void *)value;
    
    addr.addrMode = (afAddrMode_t)Addr16Bit;
    addr.addr.shortAddr = 0;
    addr.endPoint = 1;
    
    zcl_SendReportCmd(endPoint, &addr,
                      ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT, pReportCmd,
                      ZCL_FRAME_CLIENT_SERVER_DIR, true, seqNum++);
  }
  
  osal_mem_free(pReportCmd);
}
