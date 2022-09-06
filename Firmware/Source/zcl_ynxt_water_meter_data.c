/**************************************************************************************************
Filename:       zcl_genericapp_data.c
Revised:        $Date: 2014-05-12 13:14:02 -0700 (Mon, 12 May 2014) $
Revision:       $Revision: 38502 $


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
* INCLUDES
*/

#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "ZDConfig.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_se.h"
#include "zcl_ha.h"
#include "zcl_ms.h"

/* YNXT_WATER_METER_TODO: Include any of the header files below to access specific cluster data
#include "zcl_poll_control.h"
#include "zcl_electrical_measurement.h"
#include "zcl_diagnostic.h"
#include "zcl_meter_identification.h"
#include "zcl_appliance_identification.h"
#include "zcl_appliance_events_alerts.h"
#include "zcl_power_profile.h"
#include "zcl_appliance_control.h"
#include "zcl_appliance_statistics.h"
#include "zcl_hvac.h"
*/

#include "zcl_ynxt_water_meter.h"

/*********************************************************************
* CONSTANTS
*/
#define YNXT_WATER_METER_DEVICE_VERSION     0
#define YNXT_WATER_METER_FLAGS              0

#define YNXT_WATER_METER_HWVERSION          1
#define YNXT_WATER_METER_ZCLVERSION         1

/*********************************************************************
* TYPEDEFS
*/

/*********************************************************************
* MACROS
*/

/*********************************************************************
* GLOBAL VARIABLES
*/
// Global attributes
const uint16 zclYnxtWaterMeter_clusterRevision_all = 0x0001; 

// Basic Cluster
const uint8 zclYnxtWaterMeter_HWRevision = YNXT_WATER_METER_HWVERSION;
const uint8 zclYnxtWaterMeter_ZCLVersion = YNXT_WATER_METER_ZCLVERSION;
const uint8 zclYnxtWaterMeter_ManufacturerName[] = { 4, 'Y','N','X','T' };
const uint8 zclYnxtWaterMeter_ModelId[] = { 5, 'W','M','-','0','1' };
const uint8 zclYnxtWaterMeter_DateCode[] = { 8, '2','0','2','2','0','5','1','0' };
const uint8 zclYnxtWaterMeter_PowerSource = POWER_SOURCE_BATTERY;

uint8 zclYnxtWaterMeter_DeviceEnable_EP_First = DEVICE_ENABLED;
uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_First = {0, 0};
uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_First = 0;

uint8 zclYnxtWaterMeter_DeviceEnable_EP_Second = DEVICE_DISABLED;
uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second = {0, 0};
uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_Second = 0;

uint8 zclYnxtWaterMeter_DeviceEnable_EP_Third = DEVICE_DISABLED;
uint48 zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third = {0, 0};
uint16 zclYnxtWaterMeter_FlowMeasuredValue_EP_Third = 0;

uint8 zclYnxtWaterMeter_Ext_OnOff = 0;


// Identify Cluster
uint16 zclYnxtWaterMeter_IdentifyTime = 0;

/* YNXT_WATER_METER_TODO: declare attribute variables here. If its value can change,
* initialize it in zclYnxtWaterMeter_ResetAttributesToDefaultValues. If its
* value will not change, initialize it here.
*/

#if ZCL_DISCOVER
CONST zclCommandRec_t zclYnxtWaterMeterCmds_EP_Fourth[] =
{
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    COMMAND_BASIC_RESET_FACT_DEFAULT,
    CMD_DIR_SERVER_RECEIVED
  },
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    COMMAND_OFF,
    CMD_DIR_SERVER_RECEIVED
  },
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    COMMAND_ON,
    CMD_DIR_SERVER_RECEIVED
  },
};

CONST uint8 zclCmdsArraySize_EP_Fourth = ( sizeof(zclYnxtWaterMeterCmds_EP_Fourth) / sizeof(zclYnxtWaterMeterCmds_EP_Fourth[0]) );
#endif // ZCL_DISCOVER

/*********************************************************************
* ATTRIBUTE DEFINITIONS - Uses REAL cluster IDs
*/
CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_First[] =
{
  // *** General Basic Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_BASIC,             // Cluster IDs - defined in the foundation (ie. zcl.h)
    {  // Attribute record
      ATTRID_BASIC_HW_VERSION,            // Attribute ID - Found in Cluster Library header (ie. zcl_general.h)
      ZCL_DATATYPE_UINT8,                 // Data Type - found in zcl.h
      ACCESS_CONTROL_READ,                // Variable access control - found in zcl.h
      (void *)&zclYnxtWaterMeter_HWRevision  // Pointer to attribute variable
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_ZCL_VERSION,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&zclYnxtWaterMeter_ZCLVersion
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_MANUFACTURER_NAME,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)zclYnxtWaterMeter_ManufacturerName
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_MODEL_ID,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)zclYnxtWaterMeter_ModelId
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_DATE_CODE,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)zclYnxtWaterMeter_DateCode
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_POWER_SOURCE,
      ZCL_DATATYPE_ENUM8,
      ACCESS_CONTROL_READ,
      (void *)&zclYnxtWaterMeter_PowerSource
    }
  },
#ifdef ZCL_IDENTIFY
  // *** Identify Cluster Attribute ***
  {
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    { // Attribute record
      ATTRID_IDENTIFY_TIME,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&zclYnxtWaterMeter_IdentifyTime
    }
  },
#endif
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {  // Attribute record
      ATTRID_CLUSTER_REVISION,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&zclYnxtWaterMeter_clusterRevision_all
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    {  // Attribute record
      ATTRID_CLUSTER_REVISION,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&zclYnxtWaterMeter_clusterRevision_all
    }
  },
  // *** ZCL_CLUSTER_ID_SE_METERING ***
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_AUTH_WRITE),
      (void *)&zclYnxtWaterMeter_DeviceEnable_EP_First
    }
  },
  // *** ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT ***
  {
    ZCL_CLUSTER_ID_SE_METERING,
    {  // Attribute record
      ATTRID_SE_METERING_CURR_SUMM_DLVD,
      ZCL_DATATYPE_UINT48,
      (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
      (void *)&zclYnxtWaterMeter_CurrentSummationDelivered_EP_First
    }
  },
  {
    ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT,
    {  // Attribute record
      ATTRID_MS_FLOW_MEASUREMENT_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
      (void *)&zclYnxtWaterMeter_FlowMeasuredValue_EP_First
    }
  }
};

CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Second[] =
{
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_AUTH_WRITE),
      (void *)&zclYnxtWaterMeter_DeviceEnable_EP_Second
    }
  },
  {
    ZCL_CLUSTER_ID_SE_METERING,
    {  // Attribute record
      ATTRID_SE_METERING_CURR_SUMM_DLVD,
      ZCL_DATATYPE_UINT48,
      ACCESS_CONTROL_READ | ACCESS_REPORTABLE,
      (void *)&zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second
    }
  },
  // *** ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT ***
  {
    ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT,
    {  // Attribute record
      ATTRID_MS_FLOW_MEASUREMENT_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
      (void *)&zclYnxtWaterMeter_FlowMeasuredValue_EP_Second
    }
  }
};

CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Third[] =
{
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    { // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_AUTH_WRITE),
      (void *)&zclYnxtWaterMeter_DeviceEnable_EP_Third
    }
  },
  {
    ZCL_CLUSTER_ID_SE_METERING,
    {  // Attribute record
      ATTRID_SE_METERING_CURR_SUMM_DLVD,
      ZCL_DATATYPE_UINT48,
      (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
      (void *)&zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third
    }
  },
  // *** ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT ***
  {
    ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT,
    {  // Attribute record
      ATTRID_MS_FLOW_MEASUREMENT_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
      (void *)&zclYnxtWaterMeter_FlowMeasuredValue_EP_Third
    }
  }
};

CONST zclAttrRec_t zclYnxtWaterMeter_Attrs_EP_Fourth[] =
{
  // *** On/Off Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    { // Attribute record
      ATTRID_ON_OFF,
      ZCL_DATATYPE_BOOLEAN,
      ACCESS_CONTROL_READ,
      (void *)&zclYnxtWaterMeter_Ext_OnOff
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    {
      ATTRID_CLUSTER_REVISION,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ | ACCESS_CLIENT,
      (void *)&zclYnxtWaterMeter_clusterRevision_all
    }
  }
};

uint8 CONST zclYnxtWaterMeter_NumAttributes_EP_First = ( sizeof(zclYnxtWaterMeter_Attrs_EP_First) / sizeof(zclYnxtWaterMeter_Attrs_EP_First[0]) );
uint8 CONST zclYnxtWaterMeter_NumAttributes_EP_Second = ( sizeof(zclYnxtWaterMeter_Attrs_EP_Second) / sizeof(zclYnxtWaterMeter_Attrs_EP_Second[0]) );
uint8 CONST zclYnxtWaterMeter_NumAttributes_EP_Third = ( sizeof(zclYnxtWaterMeter_Attrs_EP_Third) / sizeof(zclYnxtWaterMeter_Attrs_EP_Third[0]) );
uint8 CONST zclYnxtWaterMeter_NumAttributes_EP_Fourth = ( sizeof(zclYnxtWaterMeter_Attrs_EP_Fourth) / sizeof(zclYnxtWaterMeter_Attrs_EP_Fourth[0]) );

/*********************************************************************
* SIMPLE DESCRIPTOR
*/
// This is the Cluster ID List and should be filled with Application
// specific cluster IDs.
const cId_t zclYnxtWaterMeter_InClusterList_EP_First[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_SE_METERING,
  ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT
};

#define ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_FIRST   (sizeof(zclYnxtWaterMeter_InClusterList_EP_First) / sizeof(zclYnxtWaterMeter_InClusterList_EP_First[0]))

const cId_t zclYnxtWaterMeter_InClusterList_EP_Second[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_SE_METERING,
  ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT
};

#define ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_SECOND   (sizeof(zclYnxtWaterMeter_InClusterList_EP_Second) / sizeof(zclYnxtWaterMeter_InClusterList_EP_Second[0]))

const cId_t zclYnxtWaterMeter_InClusterList_EP_Third[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_SE_METERING,
  ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT
};

#define ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_THIRD   (sizeof(zclYnxtWaterMeter_InClusterList_EP_Third) / sizeof(zclYnxtWaterMeter_InClusterList_EP_Third[0]))

const cId_t zclYnxtWaterMeter_InClusterList_EP_Fourth[] =
{
    ZCL_CLUSTER_ID_GEN_ON_OFF
};

#define ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_FOURTH   (sizeof(zclYnxtWaterMeter_InClusterList_EP_Fourth) / sizeof(zclYnxtWaterMeter_InClusterList_EP_Fourth[0]))


const cId_t zclYnxtWaterMeter_OutClusterList[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  // TODO: Add application specific Output Clusters Here. 
  //       See zcl.h for Cluster ID definitions
};
#define ZCLYNXT_WATER_METER_MAX_OUTCLUSTERS  (sizeof(zclYnxtWaterMeter_OutClusterList) / sizeof(zclYnxtWaterMeter_OutClusterList[0]))

SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_First =
{
  WATER_METER_ENDPOINT_FIRST,                           //  int Endpoint;
  ZCL_HA_PROFILE_ID,                                    //  uint16 AppProfId;
  ZCL_HA_DEVICEID_METER_INTERFACE,                      //  uint16 AppDeviceId; 
  YNXT_WATER_METER_DEVICE_VERSION,                      //  int   AppDevVer:4;
  YNXT_WATER_METER_FLAGS,                               //  int   AppFlags:4;
  ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_FIRST,          //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_InClusterList_EP_First,    //  byte *pAppInClusterList;
  0,                                                    //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_OutClusterList             //  byte *pAppInClusterList;
};

SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Second =
{
  WATER_METER_ENDPOINT_SECOND,                          //  int Endpoint;
  ZCL_HA_PROFILE_ID,                                    //  uint16 AppProfId;
  ZCL_HA_DEVICEID_METER_INTERFACE,                      //  uint16 AppDeviceId; 
  YNXT_WATER_METER_DEVICE_VERSION,                      //  int   AppDevVer:4;
  YNXT_WATER_METER_FLAGS,                               //  int   AppFlags:4;
  ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_SECOND,         //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_InClusterList_EP_Second,   //  byte *pAppInClusterList;
  0,                                                    //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_OutClusterList             //  byte *pAppInClusterList;
};

SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Third =
{
  WATER_METER_ENDPOINT_THIRD,                           //  int Endpoint;
  ZCL_HA_PROFILE_ID,                                    //  uint16 AppProfId;
  ZCL_HA_DEVICEID_METER_INTERFACE,                      //  uint16 AppDeviceId; 
  YNXT_WATER_METER_DEVICE_VERSION,                      //  int   AppDevVer:4;
  YNXT_WATER_METER_FLAGS,                               //  int   AppFlags:4;
  ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_THIRD,          //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_InClusterList_EP_Third,    //  byte *pAppInClusterList;
  0,                                                    //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_OutClusterList             //  byte *pAppInClusterList;
};

SimpleDescriptionFormat_t zclYnxtWaterMeter_SimpleDesc_EP_Fourth =
{
  WATER_METER_ENDPOINT_FOURTH,                           //  int Endpoint;
  ZCL_HA_PROFILE_ID,                                     //  uint16 AppProfId;
  ZCL_HA_DEVICEID_ON_OFF_SWITCH,                         //  uint16 AppDeviceId; 
  YNXT_WATER_METER_DEVICE_VERSION,                       //  int   AppDevVer:4;
  YNXT_WATER_METER_FLAGS,                                //  int   AppFlags:4;
  ZCLYNXT_WATER_METER_MAX_INCLUSTERS_EP_FOURTH,          //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_InClusterList_EP_Fourth,    //  byte *pAppInClusterList;
  0,                                                     //  byte  AppNumInClusters;
  (cId_t *)zclYnxtWaterMeter_OutClusterList              //  byte *pAppInClusterList;
};

/*********************************************************************
* GLOBAL FUNCTIONS
*/

/*********************************************************************
* LOCAL FUNCTIONS
*/

void zclYnxtWaterMeter_ResetAttributesToDefaultValues(void)
{
#ifdef ZCL_IDENTIFY
  zclYnxtWaterMeter_IdentifyTime = 0;
#endif
  
  zclYnxtWaterMeter_CurrentSummationDelivered_EP_First.lsb = 0;
  zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second.lsb = 0;
  zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third.lsb = 0;
  
  osal_nv_delete(NV_ENABLED_FIRST_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_First));
  osal_nv_delete(NV_ENABLED_SECOND_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Second));
  osal_nv_delete(NV_ENABLED_THIRD_ID, sizeof(zclYnxtWaterMeter_DeviceEnable_EP_Third));
  
  osal_nv_delete(NV_CSD_FIRST_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_First));
  osal_nv_delete(NV_CSD_SECOND_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Second));
  osal_nv_delete(NV_CSD_THIRD_ID, sizeof(zclYnxtWaterMeter_CurrentSummationDelivered_EP_Third));
}

/****************************************************************************
****************************************************************************/


