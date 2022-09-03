/**************************************************************************************************
  Filename:       zcl_genericapp.h
  Revised:        $Date: 2014-06-19 08:38:22 -0700 (Thu, 19 Jun 2014) $
  Revision:       $Revision: 39101 $

  Description:    This file contains the ZigBee Cluster Library Home
                  Automation Sample Application.


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
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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

#ifndef ZCL_YNXT_WATER_METER_H
#define ZCL_YNXT_WATER_METER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "zcl.h"

/*********************************************************************
 * CONSTANTS
 */
typedef struct {
  uint32 lsb;
  uint16 msb;
} uint48;
  
#define WATER_METER_ENDPOINT_FIRST              1
#define WATER_METER_ENDPOINT_SECOND             2
#define WATER_METER_ENDPOINT_THIRD              3
#define WATER_METER_ENDPOINT_FOURTH             4


// Application Events
#define YNXT_WATER_METER_NWK_ACTION               0x0001
#define YNXT_WATER_METER_END_DEVICE_REJOIN_EVT    0x0002  
  
/* YNXT_WATER_METER_TODO: define app events here */
  
#define YNXT_WATER_METER_MEASUREMENT              0x0004

  
#define YNXT_WATER_METER_END_DEVICE_REJOIN_DELAY 60000

#define YNXT_CLUSTER_ID_CUSTOM 0xFC00
#define ATTRID_YNXT_CORRECTION_CURR_SUMM_DLVD 0x00

#define NV_ENABLED_FIRST_ID HAL_NV_PAGE_BEG + 1
#define NV_CSD_FIRST_ID HAL_NV_PAGE_BEG + 2

#define NV_ENABLED_SECOND_ID HAL_NV_PAGE_BEG + 3
#define NV_CSD_SECOND_ID HAL_NV_PAGE_BEG + 4

#define NV_ENABLED_THIRD_ID HAL_NV_PAGE_BEG + 5
#define NV_CSD_THIRD_ID HAL_NV_PAGE_BEG + 6



/*********************************************************************
 * MACROS
 */
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * VARIABLES
 */

extern SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_First;
extern SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Second;
extern SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Third;
extern SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Fourth;

extern CONST zclCommandRec_t zclYnxtWaterMeterCmds_EP_Fourth[];
extern CONST uint8 zclCmdsArraySize_EP_Fourth;

// attribute list
extern CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_First[];
extern CONST uint8 zclYnxtWaterMeter_NumAttributes_EP_First;

extern CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Second[];
extern CONST uint8 zclYnxtWaterMeter_NumAttributes_EP_Second;

extern CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Third[];
extern CONST uint8 zclYnxtWaterMeter_NumAttributes_EP_Third;

extern CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Fourth[];
extern CONST uint8 zclYnxtWaterMeter_NumAttributes_EP_Fourth;

extern uint8 zclYnxtWaterMeter_DeviceEnable_EP_First;
extern uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_First;
extern uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_First;

extern uint8 zclYnxtWaterMeter_DeviceEnable_EP_Second;
extern uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second;
extern uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_Second;

extern uint8 zclYnxtWaterMeter_DeviceEnable_EP_Third;
extern uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third;
extern uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_Third;

// Identify attributes
extern uint16 zclYnxtWaterMeter_IdentifyTime;

extern uint8 zclYnxtWaterMeter_Ext_OnOff;

// YNXT_WATER_METER_TODO: Declare application specific attributes here


/*********************************************************************
 * FUNCTIONS
 */

 /*
  * Initialization for the task
  */
extern void zclYnxtWaterMeter_Init( byte task_id );

/*
 *  Event Process for the task
 */
extern UINT16 zclYnxtWaterMeter_event_loop( byte task_id, UINT16 events );

/*
 *  Reset all writable attributes to their default values.
 */
extern void zclYnxtWaterMeter_ResetAttributesToDefaultValues(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* ZCL_YNXT_WATER_METER_H */
