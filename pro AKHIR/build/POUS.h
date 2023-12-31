#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// FUNCTION_BLOCK PYTHON_EVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_EVAL;

void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain);
// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__);
// FUNCTION_BLOCK PYTHON_POLL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_POLL;

void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain);
// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__);
// FUNCTION_BLOCK PYTHON_GEAR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(UINT,N)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  PYTHON_EVAL PY_EVAL;
  __DECLARE_VAR(UINT,COUNTER)
  __DECLARE_VAR(UINT,_TMP_ADD10_OUT)
  __DECLARE_VAR(BOOL,_TMP_EQ13_OUT)
  __DECLARE_VAR(UINT,_TMP_SEL15_OUT)
  __DECLARE_VAR(BOOL,_TMP_AND7_OUT)

} PYTHON_GEAR;

void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain);
// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__);
// PROGRAM WAREHOUSE
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,START)
  __DECLARE_EXTERNAL(BOOL,STOP)
  __DECLARE_VAR(BOOL,RESET)
  __DECLARE_VAR(BOOL,SENSOR)
  __DECLARE_VAR(BOOL,X)
  __DECLARE_VAR(BOOL,Z)
  __DECLARE_VAR(BOOL,SENSORSTRT)
  __DECLARE_VAR(BOOL,ENTRYCON)
  __DECLARE_VAR(BOOL,LOADCON)
  __DECLARE_VAR(BOOL,ANGKAT)
  __DECLARE_VAR(BOOL,KIRI)
  __DECLARE_VAR(BOOL,KANAN)
  __DECLARE_VAR(INT,TARGET)
  __DECLARE_VAR(INT,DIGITALDIS)
  __DECLARE_VAR(INT,DIGITALDIS0)
  __DECLARE_VAR(BOOL,VIR1)
  __DECLARE_VAR(BOOL,VIR2)
  __DECLARE_VAR(BOOL,VIR3)
  __DECLARE_VAR(BOOL,VIR4)
  __DECLARE_VAR(BOOL,VIR10)
  __DECLARE_VAR(BOOL,VIRBLOKX)
  __DECLARE_VAR(BOOL,VIRBLOKZ)
  TON TON0;
  TON TON1;
  CTU CTU0;
  TON TON2;
  TON TON7;
  TON TON4;
  TON TON6;
  TON TON3;
  CTU CTU1;
  R_TRIG R_TRIG1;
  F_TRIG F_TRIG1;
  F_TRIG F_TRIG2;
  F_TRIG F_TRIG3;
  R_TRIG R_TRIG2;
  __DECLARE_VAR(BOOL,_TMP_AND69_OUT)
  __DECLARE_VAR(BOOL,_TMP_ADD46_ENO)
  __DECLARE_VAR(INT,_TMP_ADD46_OUT)

} WAREHOUSE;

void WAREHOUSE_init__(WAREHOUSE *data__, BOOL retain);
// Code part
void WAREHOUSE_body__(WAREHOUSE *data__);
// PROGRAM PROGRAM0
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,START)
  __DECLARE_EXTERNAL(BOOL,STOP)
  __DECLARE_VAR(BOOL,CNCSEN1)
  __DECLARE_VAR(BOOL,CNCSEN2)
  __DECLARE_VAR(BOOL,CNCSEN1B)
  __DECLARE_VAR(BOOL,CNCSEN2B)
  __DECLARE_VAR(BOOL,MCHNSTS)
  __DECLARE_VAR(BOOL,MCHNSTS2)
  __DECLARE_VAR(BOOL,RDRCTSNS)
  __DECLARE_VAR(BOOL,SENSOR1GREENLID)
  __DECLARE_VAR(BOOL,SENSOR2GREENBASE)
  __DECLARE_VAR(BOOL,SENSOR1BLUELID)
  __DECLARE_VAR(BOOL,SENSOR2BLUEBASE)
  __DECLARE_VAR(BOOL,RSTCNT)
  __DECLARE_VAR(BOOL,LIDS)
  __DECLARE_VAR(BOOL,CNCCON1)
  __DECLARE_VAR(BOOL,CNCCON2)
  __DECLARE_VAR(BOOL,CNC1)
  __DECLARE_VAR(BOOL,CNC2)
  __DECLARE_VAR(BOOL,RDRCT)
  __DECLARE_VAR(BOOL,CLAMPGREENLID)
  __DECLARE_VAR(BOOL,CLAMPGREENBASE)
  __DECLARE_VAR(BOOL,CLAMPGREENRISE)
  __DECLARE_VAR(BOOL,CLAMPLIDBLUE)
  __DECLARE_VAR(BOOL,CLAMPBASEBLUE)
  __DECLARE_VAR(BOOL,CLAMPBLUERISE)
  __DECLARE_VAR(BOOL,PICKER1Z)
  __DECLARE_VAR(BOOL,PICKER1X)
  __DECLARE_VAR(BOOL,PICKER1G)
  __DECLARE_VAR(BOOL,PICKER2Z)
  __DECLARE_VAR(BOOL,PICKER2X)
  __DECLARE_VAR(BOOL,PICKER2G)
  __DECLARE_VAR(BOOL,CONVEYORPCK)
  __DECLARE_VAR(BOOL,VIR1)
  __DECLARE_VAR(BOOL,VIR2)
  __DECLARE_VAR(BOOL,VIR3)
  __DECLARE_VAR(BOOL,VIR4)
  __DECLARE_VAR(BOOL,VIR5)
  __DECLARE_VAR(BOOL,VIR6)
  __DECLARE_VAR(BOOL,VIR7)
  __DECLARE_VAR(BOOL,VIR8)
  __DECLARE_VAR(BOOL,VIR9)
  __DECLARE_VAR(BOOL,VIR10)
  __DECLARE_VAR(BOOL,VIR11)
  __DECLARE_VAR(BOOL,VIR12)
  __DECLARE_VAR(BOOL,VIR13)
  TON CNCTON1;
  TON CNCTON2;
  TON CNCTON3;
  TON CNCTON4;
  TON CNCTON5;
  TON CNCTON6;
  TON CNCTON7;
  TON CNCTON8;
  TON CNCTON9;
  TON CNCTON10;
  TON CNCTON11;
  TON CNCTON12;
  TON CNCTON13;
  TON CNCTON14;
  CTU CTU0;
  R_TRIG R_TRIG1;

} PROGRAM0;

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain);
// Code part
void PROGRAM0_body__(PROGRAM0 *data__);
// PROGRAM CONVEYORZ
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,START)
  __DECLARE_EXTERNAL(BOOL,STOP)
  __DECLARE_VAR(BOOL,CONVEYOR1)
  __DECLARE_VAR(BOOL,CONVEYOR2)
  __DECLARE_VAR(BOOL,CONVEYOR3)
  __DECLARE_VAR(BOOL,CONVEYOR4)
  __DECLARE_VAR(BOOL,CONVEYOR5)
  __DECLARE_VAR(BOOL,CONVEYOR6)
  __DECLARE_VAR(BOOL,CONVEYOR7)
  __DECLARE_VAR(BOOL,CONVEYOR8)
  __DECLARE_VAR(BOOL,CONVEYOR9)
  __DECLARE_VAR(BOOL,CONVEYOR10)
  __DECLARE_VAR(BOOL,CONVEYOR11)
  __DECLARE_VAR(BOOL,CONVEYOR12)
  __DECLARE_VAR(BOOL,CONVEYOR13)
  __DECLARE_VAR(BOOL,VIR1)

} CONVEYORZ;

void CONVEYORZ_init__(CONVEYORZ *data__, BOOL retain);
// Code part
void CONVEYORZ_body__(CONVEYORZ *data__);
#endif //__POUS_H
