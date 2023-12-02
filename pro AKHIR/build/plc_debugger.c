/*
 * DEBUGGER code
 * 
 * On "publish", when buffer is free, debugger stores arbitrary variables 
 * content into, and mark this buffer as filled
 * 
 * 
 * Buffer content is read asynchronously, (from non real time part), 
 * and then buffer marked free again.
 *  
 * 
 * */
#ifdef TARGET_DEBUG_AND_RETAIN_DISABLE

void __init_debug    (void){}
void __cleanup_debug (void){}
void __retrieve_debug(void){}
void __publish_debug (void){}

#else

#include "iec_types_all.h"
#include "POUS.h"
/*for memcpy*/
#include <string.h>
#include <stdio.h>

typedef unsigned int dbgvardsc_index_t;
typedef unsigned short trace_buf_offset_t;

#define BUFFER_EMPTY 0
#define BUFFER_FULL 1

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_BUFFER_SIZE 4096
#define TRACE_LIST_SIZE 1024

/* Atomically accessed variable for buffer state */
static long trace_buffer_state = BUFFER_EMPTY;

typedef struct trace_item_s {
    dbgvardsc_index_t dbgvardsc_index;
} trace_item_t;

trace_item_t trace_list[TRACE_LIST_SIZE];
char trace_buffer[TRACE_BUFFER_SIZE];

/* Trace's cursor*/
static trace_item_t *trace_list_collect_cursor = trace_list;
static trace_item_t *trace_list_addvar_cursor = trace_list;
static const trace_item_t *trace_list_end = 
    &trace_list[TRACE_LIST_SIZE-1];
static char *trace_buffer_cursor = trace_buffer;
static const char *trace_buffer_end = trace_buffer + TRACE_BUFFER_SIZE;



#define FORCE_BUFFER_SIZE 1024
#define FORCE_LIST_SIZE 256

typedef struct force_item_s {
    dbgvardsc_index_t dbgvardsc_index;
    void *value_pointer_backup;
} force_item_t;

force_item_t force_list[FORCE_LIST_SIZE];
char force_buffer[FORCE_BUFFER_SIZE];

/* Force's cursor*/
static force_item_t *force_list_apply_cursor = force_list;
static force_item_t *force_list_addvar_cursor = force_list;
static const force_item_t *force_list_end = 
    &force_list[FORCE_LIST_SIZE-1];
static char *force_buffer_cursor = force_buffer;
static const char *force_buffer_end = force_buffer + FORCE_BUFFER_SIZE;


#endif

/***
 * Declare programs 
 **/
extern PROGRAM0 RES0__INSTANCE0;
extern WAREHOUSE RES0__INSTANCE1;
extern CONVEYORZ RES0__INSTANCE2;

/***
 * Declare global variables from resources and conf 
 **/
extern __IEC_BOOL_t RES0__START;
extern __IEC_BOOL_t RES0__STOP;
extern       PROGRAM0   RES0__INSTANCE0;
extern       WAREHOUSE   RES0__INSTANCE1;
extern       CONVEYORZ   RES0__INSTANCE2;

typedef const struct {
    void *ptr;
    __IEC_types_enum type;
} dbgvardsc_t;

static const dbgvardsc_t dbgvardsc[] = {
{&(RES0__START), BOOL_ENUM},
{&(RES0__STOP), BOOL_ENUM},
{&(RES0__INSTANCE0.START), BOOL_P_ENUM},
{&(RES0__INSTANCE0.STOP), BOOL_P_ENUM},
{&(RES0__INSTANCE0.CNCSEN1), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCSEN2), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCSEN1B), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCSEN2B), BOOL_ENUM},
{&(RES0__INSTANCE0.MCHNSTS), BOOL_ENUM},
{&(RES0__INSTANCE0.MCHNSTS2), BOOL_ENUM},
{&(RES0__INSTANCE0.RDRCTSNS), BOOL_ENUM},
{&(RES0__INSTANCE0.SENSOR1GREENLID), BOOL_ENUM},
{&(RES0__INSTANCE0.SENSOR2GREENBASE), BOOL_ENUM},
{&(RES0__INSTANCE0.SENSOR1BLUELID), BOOL_ENUM},
{&(RES0__INSTANCE0.SENSOR2BLUEBASE), BOOL_ENUM},
{&(RES0__INSTANCE0.RSTCNT), BOOL_ENUM},
{&(RES0__INSTANCE0.LIDS), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCCON1), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCCON2), BOOL_ENUM},
{&(RES0__INSTANCE0.CNC1), BOOL_ENUM},
{&(RES0__INSTANCE0.CNC2), BOOL_ENUM},
{&(RES0__INSTANCE0.RDRCT), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPGREENLID), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPGREENBASE), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPGREENRISE), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPLIDBLUE), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPBASEBLUE), BOOL_ENUM},
{&(RES0__INSTANCE0.CLAMPBLUERISE), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER1Z), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER1X), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER1G), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER2Z), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER2X), BOOL_ENUM},
{&(RES0__INSTANCE0.PICKER2G), BOOL_ENUM},
{&(RES0__INSTANCE0.CONVEYORPCK), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR1), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR2), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR3), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR4), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR5), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR6), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR7), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR8), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR9), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR10), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR11), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR12), BOOL_ENUM},
{&(RES0__INSTANCE0.VIR13), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON1.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON1.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON1.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON1.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON1.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON2.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON2.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON2.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON2.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON2.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON2.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON2.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON2.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON2.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON3.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON3.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON3.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON3.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON3.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON3.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON3.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON3.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON3.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON3.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON4.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON4.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON4.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON4.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON4.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON4.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON4.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON4.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON4.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON4.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON5.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON5.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON5.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON5.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON5.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON5.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON5.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON5.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON5.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON5.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON6.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON6.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON6.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON6.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON6.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON6.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON6.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON6.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON6.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON6.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON7.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON7.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON7.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON7.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON7.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON7.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON7.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON7.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON7.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON7.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON8.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON8.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON8.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON8.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON8.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON8.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON8.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON8.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON8.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON8.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON9.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON9.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON9.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON9.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON9.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON9.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON9.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON9.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON9.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON9.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON10.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON10.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON10.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON10.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON10.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON10.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON10.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON10.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON10.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON10.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON11.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON11.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON11.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON11.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON11.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON11.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON11.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON11.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON11.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON11.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON12.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON12.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON12.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON12.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON12.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON12.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON12.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON12.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON12.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON12.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON13.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON13.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON13.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON13.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON13.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON13.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON13.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON13.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON13.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON13.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON14.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON14.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON14.IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON14.PT), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON14.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON14.ET), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON14.STATE), SINT_ENUM},
{&(RES0__INSTANCE0.CNCTON14.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE0.CNCTON14.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CNCTON14.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE0.CTU0.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CU), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.R), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.PV), INT_ENUM},
{&(RES0__INSTANCE0.CTU0.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CV), INT_ENUM},
{&(RES0__INSTANCE0.CTU0.CU_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CU_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CU_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CU_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.CTU0.CU_T.M), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.EN), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.CLK), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.Q), BOOL_ENUM},
{&(RES0__INSTANCE0.R_TRIG1.M), BOOL_ENUM},
{&(RES0__INSTANCE1.START), BOOL_P_ENUM},
{&(RES0__INSTANCE1.STOP), BOOL_P_ENUM},
{&(RES0__INSTANCE1.RESET), BOOL_ENUM},
{&(RES0__INSTANCE1.SENSOR), BOOL_ENUM},
{&(RES0__INSTANCE1.X), BOOL_ENUM},
{&(RES0__INSTANCE1.Z), BOOL_ENUM},
{&(RES0__INSTANCE1.SENSORSTRT), BOOL_ENUM},
{&(RES0__INSTANCE1.ENTRYCON), BOOL_ENUM},
{&(RES0__INSTANCE1.LOADCON), BOOL_ENUM},
{&(RES0__INSTANCE1.ANGKAT), BOOL_ENUM},
{&(RES0__INSTANCE1.KIRI), BOOL_ENUM},
{&(RES0__INSTANCE1.KANAN), BOOL_ENUM},
{&(RES0__INSTANCE1.TARGET), INT_ENUM},
{&(RES0__INSTANCE1.DIGITALDIS), INT_ENUM},
{&(RES0__INSTANCE1.DIGITALDIS0), INT_ENUM},
{&(RES0__INSTANCE1.VIR1), BOOL_ENUM},
{&(RES0__INSTANCE1.VIR2), BOOL_ENUM},
{&(RES0__INSTANCE1.VIR3), BOOL_ENUM},
{&(RES0__INSTANCE1.VIR4), BOOL_ENUM},
{&(RES0__INSTANCE1.VIR10), BOOL_ENUM},
{&(RES0__INSTANCE1.VIRBLOKX), BOOL_ENUM},
{&(RES0__INSTANCE1.VIRBLOKZ), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON0.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON0.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON0.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON0.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON0.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON1.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON1.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON1.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON1.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON1.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON1.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON1.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON1.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON1.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.CTU0.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CU), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.R), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.PV), INT_ENUM},
{&(RES0__INSTANCE1.CTU0.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CV), INT_ENUM},
{&(RES0__INSTANCE1.CTU0.CU_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CU_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CU_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CU_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU0.CU_T.M), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON2.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON2.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON2.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON2.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON2.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON7.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON7.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON7.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON7.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON7.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON7.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON7.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON7.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON7.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON7.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON4.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON4.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON4.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON4.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON4.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON4.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON4.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON4.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON4.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON4.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON6.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON6.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON6.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON6.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON6.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON6.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON6.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON6.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON6.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON6.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON3.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON3.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.TON3.IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON3.PT), TIME_ENUM},
{&(RES0__INSTANCE1.TON3.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.TON3.ET), TIME_ENUM},
{&(RES0__INSTANCE1.TON3.STATE), SINT_ENUM},
{&(RES0__INSTANCE1.TON3.PREV_IN), BOOL_ENUM},
{&(RES0__INSTANCE1.TON3.CURRENT_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.TON3.START_TIME), TIME_ENUM},
{&(RES0__INSTANCE1.CTU1.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CU), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.R), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.PV), INT_ENUM},
{&(RES0__INSTANCE1.CTU1.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CV), INT_ENUM},
{&(RES0__INSTANCE1.CTU1.CU_T.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CU_T.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CU_T.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CU_T.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.CTU1.CU_T.M), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG1.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG1.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG1.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG1.M), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG1.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG1.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG1.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG1.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG1.M), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG2.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG2.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG2.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG2.M), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG3.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG3.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG3.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG3.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.F_TRIG3.M), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG2.EN), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG2.ENO), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG2.CLK), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG2.Q), BOOL_ENUM},
{&(RES0__INSTANCE1.R_TRIG2.M), BOOL_ENUM},
{&(RES0__INSTANCE1._TMP_AND69_OUT), BOOL_ENUM},
{&(RES0__INSTANCE1._TMP_ADD46_ENO), BOOL_ENUM},
{&(RES0__INSTANCE1._TMP_ADD46_OUT), INT_ENUM},
{&(RES0__INSTANCE2.START), BOOL_P_ENUM},
{&(RES0__INSTANCE2.STOP), BOOL_P_ENUM},
{&(RES0__INSTANCE2.CONVEYOR1), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR2), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR3), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR4), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR5), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR6), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR7), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR8), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR9), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR10), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR11), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR12), BOOL_ENUM},
{&(RES0__INSTANCE2.CONVEYOR13), BOOL_ENUM},
{&(RES0__INSTANCE2.VIR1), BOOL_ENUM}
};

static const dbgvardsc_index_t retain_list[] = {

};
static unsigned int retain_list_collect_cursor = 0;
static const unsigned int retain_list_size = sizeof(retain_list)/sizeof(dbgvardsc_index_t);

typedef void(*__for_each_variable_do_fp)(dbgvardsc_t*);
void __for_each_variable_do(__for_each_variable_do_fp fp)
{
    unsigned int i;
    for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){
        dbgvardsc_t *dsc = &dbgvardsc[i];
        if(dsc->type != UNKNOWN_ENUM) 
            (*fp)(dsc);
    }
}

#define __Unpack_desc_type dbgvardsc_t


#define __Unpack_case_t(TYPENAME)                                           \
        case TYPENAME##_ENUM :                                              \
            if(flags) *flags = ((__IEC_##TYPENAME##_t *)varp)->flags;       \
            if(value_p) *value_p = &((__IEC_##TYPENAME##_t *)varp)->value;  \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Unpack_case_p(TYPENAME)                                           \
        case TYPENAME##_O_ENUM :                                            \
        case TYPENAME##_P_ENUM :                                            \
            if(flags) *flags = ((__IEC_##TYPENAME##_p *)varp)->flags;       \
            if(value_p) *value_p = ((__IEC_##TYPENAME##_p *)varp)->value;   \
		    if(size) *size = sizeof(TYPENAME);                              \
            break;

#define __Is_a_string(dsc) (dsc->type == STRING_ENUM)   ||\
                           (dsc->type == STRING_P_ENUM) ||\
                           (dsc->type == STRING_O_ENUM)

static int UnpackVar(__Unpack_desc_type *dsc, void **value_p, char *flags, size_t *size)
{
    void *varp = dsc->ptr;
    /* find data to copy*/
    switch(dsc->type){
        __ANY(__Unpack_case_t)
        __ANY(__Unpack_case_p)
    default:
        return 0; /* should never happen */
    }
    return 1;
}



void Remind(unsigned int offset, unsigned int count, void * p);

extern int CheckRetainBuffer(void);
extern void InitRetain(void);

void __init_debug(void)
{
    /* init local static vars */
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    trace_list_addvar_cursor = trace_list;
    trace_list_collect_cursor = trace_list;
    trace_buffer_state = BUFFER_EMPTY;

    force_buffer_cursor = force_buffer;
    force_list_addvar_cursor = force_list;
    force_list_apply_cursor = force_list;
#endif

    InitRetain();
    /* Iterate over all variables to fill debug buffer */
    if(CheckRetainBuffer()){
        static unsigned int retain_offset = 0;
        retain_list_collect_cursor = 0;

        /* iterate over retain list */
        while(retain_list_collect_cursor < retain_list_size){
            void *value_p = NULL;
            size_t size;
            char* next_cursor;

            dbgvardsc_t *dsc = &dbgvardsc[
                retain_list[retain_list_collect_cursor]];

            UnpackVar(dsc, &value_p, NULL, &size);

            printf("Reminding %d %ld \n", retain_list_collect_cursor, size);

            /* if buffer not full */
            Remind(retain_offset, size, value_p);
            /* increment cursor according size*/
            retain_offset += size;

            retain_list_collect_cursor++;
        }
    }else{
        char mstr[] = "RETAIN memory invalid - defaults used";
        LogMessage(LOG_WARNING, mstr, sizeof(mstr));
    }
}

extern void InitiateDebugTransfer(void);
extern void CleanupRetain(void);

extern unsigned long __tick;

void __cleanup_debug(void)
{
#ifndef TARGET_ONLINE_DEBUG_DISABLE
    trace_buffer_cursor = trace_buffer;
    InitiateDebugTransfer();
#endif    

    CleanupRetain();
}

void __retrieve_debug(void)
{
}

void Retain(unsigned int offset, unsigned int count, void * p);

/* Return size of all retain variables */
unsigned int GetRetainSize(void)
{
    unsigned int retain_size = 0;
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        retain_size += size;
        retain_list_collect_cursor++;
    }

    printf("Retain size %d \n", retain_size);
            
    return retain_size;
}


extern void PLC_GetTime(IEC_TIME*);
extern int TryEnterDebugSection(void);
extern long AtomicCompareExchange(long*, long, long);
extern long long AtomicCompareExchange64(long long* , long long , long long);
extern void LeaveDebugSection(void);
extern void ValidateRetainBuffer(void);
extern void InValidateRetainBuffer(void);

#define __ReForceOutput_case_p(TYPENAME)                                                            \
        case TYPENAME##_P_ENUM :                                                                    \
        case TYPENAME##_O_ENUM :                                                                    \
            {                                                                                       \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);                         \
                if(next_cursor <= force_buffer_end ){                                               \
                    /* outputs real value must be systematically forced */                          \
                    if(vartype == TYPENAME##_O_ENUM)                                                \
                        /* overwrite value pointed by backup */                                     \
                        *((TYPENAME *)force_list_apply_cursor->value_pointer_backup) =  \
                            *((TYPENAME *)force_buffer_cursor);                                     \
                    /* inc force_buffer cursor */                                                   \
                    force_buffer_cursor = next_cursor;                                              \
                }else{                                                                              \
                    stop = 1;                                                                       \
                }                                                                                   \
            }                                                                                       \
            break;
void __publish_debug(void)
{
    InValidateRetainBuffer();
    
#ifndef TARGET_ONLINE_DEBUG_DISABLE 
    /* Check there is no running debugger re-configuration */
    if(TryEnterDebugSection()){
        /* Lock buffer */
        long latest_state = AtomicCompareExchange(
            &trace_buffer_state,
            BUFFER_EMPTY,
            BUFFER_FULL);
            
        /* If buffer was free */
        if(latest_state == BUFFER_EMPTY)
        {
            int stop = 0;
            /* Reset force list cursor */
            force_list_apply_cursor = force_list;

            /* iterate over force list */
            while(!stop && force_list_apply_cursor < force_list_addvar_cursor){
                dbgvardsc_t *dsc = &dbgvardsc[
                    force_list_apply_cursor->dbgvardsc_index];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;
                switch(vartype){
                    __ANY(__ReForceOutput_case_p)
                default:
                    break;
                }
                force_list_apply_cursor++;                                                      \
            }

            /* Reset buffer cursor */
            trace_buffer_cursor = trace_buffer;
            /* Reset trace list cursor */
            trace_list_collect_cursor = trace_list;

            /* iterate over trace list */
            while(trace_list_collect_cursor < trace_list_addvar_cursor){
                void *value_p = NULL;
                size_t size;
                char* next_cursor;

                dbgvardsc_t *dsc = &dbgvardsc[
                    trace_list_collect_cursor->dbgvardsc_index];

                UnpackVar(dsc, &value_p, NULL, &size);

                /* copy visible variable to buffer */;
                if(__Is_a_string(dsc)){
                    /* optimization for strings */
                    /* assume NULL terminated strings */
                    size = ((STRING*)value_p)->len + 1;
                }

                /* compute next cursor positon.*/
                next_cursor = trace_buffer_cursor + size;
                /* check for buffer overflow */
                if(next_cursor < trace_buffer_end)
                    /* copy data to the buffer */
                    memcpy(trace_buffer_cursor, value_p, size);
                else
                    /* stop looping in case of overflow */
                    break;
                /* increment cursor according size*/
                trace_buffer_cursor = next_cursor;
                trace_list_collect_cursor++;
            }
            
            /* Leave debug section,
             * Trigger asynchronous transmission 
             * (returns immediately) */
            InitiateDebugTransfer(); /* size */
        }
        LeaveDebugSection();
    }
#endif
    static unsigned int retain_offset = 0;
    /* when not debugging, do only retain */
    retain_list_collect_cursor = 0;

    /* iterate over retain list */
    while(retain_list_collect_cursor < retain_list_size){
        void *value_p = NULL;
        size_t size;
        char* next_cursor;

        dbgvardsc_t *dsc = &dbgvardsc[
            retain_list[retain_list_collect_cursor]];

        UnpackVar(dsc, &value_p, NULL, &size);

        /* if buffer not full */
        Retain(retain_offset, size, value_p);
        /* increment cursor according size*/
        retain_offset += size;

        retain_list_collect_cursor++;
    }
    ValidateRetainBuffer();
}

#ifndef TARGET_ONLINE_DEBUG_DISABLE

#define TRACE_LIST_OVERFLOW    1
#define FORCE_LIST_OVERFLOW    2
#define FORCE_BUFFER_OVERFLOW  3

#define __ForceVariable_case_t(TYPENAME)                                                \
        case TYPENAME##_ENUM :                                                          \
            /* add to force_list*/                                                      \
            force_list_addvar_cursor->dbgvardsc_index = idx;                            \
            ((__IEC_##TYPENAME##_t *)varp)->flags |= __IEC_FORCE_FLAG;                  \
            ((__IEC_##TYPENAME##_t *)varp)->value = *((TYPENAME *)force);               \
            break;
#define __ForceVariable_case_p(TYPENAME)                                                \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            {                                                                           \
                char *next_cursor = force_buffer_cursor + sizeof(TYPENAME);             \
                if(next_cursor <= force_buffer_end ){                                   \
                    /* add to force_list*/                                              \
                    force_list_addvar_cursor->dbgvardsc_index = idx;                    \
                    /* save pointer to backup */                                        \
                    force_list_addvar_cursor->value_pointer_backup =                    \
                        ((__IEC_##TYPENAME##_p *)varp)->value;                          \
                    /* store forced value in force_buffer */                            \
                    *((TYPENAME *)force_buffer_cursor) = *((TYPENAME *)force);          \
                    /* replace pointer with pointer to force_buffer */                  \
                    ((__IEC_##TYPENAME##_p *)varp)->value =                             \
                        (TYPENAME *)force_buffer_cursor;                                \
                    /* mark variable as forced */                                       \
                    ((__IEC_##TYPENAME##_p *)varp)->flags |= __IEC_FORCE_FLAG;          \
                    /* inc force_buffer cursor */                                       \
                    force_buffer_cursor = next_cursor;                                  \
                    /* outputs real value must be systematically forced */              \
                    if(vartype == TYPENAME##_O_ENUM)                                    \
                        *(((__IEC_##TYPENAME##_p *)varp)->value) = *((TYPENAME *)force);\
                } else {                                                                \
                    error_code = FORCE_BUFFER_OVERFLOW;                                 \
                    goto error_cleanup;                                                 \
                }                                                                       \
            }                                                                           \
            break;


void ResetDebugVariables(void);

int RegisterDebugVariable(dbgvardsc_index_t idx, void* force)
{
    int error_code = 0;
    if(idx < sizeof(dbgvardsc)/sizeof(dbgvardsc_t)){
        /* add to trace_list, inc trace_list_addvar_cursor*/
        if(trace_list_addvar_cursor <= trace_list_end){
            trace_list_addvar_cursor->dbgvardsc_index = idx;
            trace_list_addvar_cursor++;
        } else {
            error_code = TRACE_LIST_OVERFLOW;
            goto error_cleanup;
        }
        if(force){
            if(force_list_addvar_cursor <= force_list_end){
                dbgvardsc_t *dsc = &dbgvardsc[idx];
                void *varp = dsc->ptr;
                __IEC_types_enum vartype = dsc->type;

                switch(vartype){
                    __ANY(__ForceVariable_case_t)
                    __ANY(__ForceVariable_case_p)
                default:
                    break;
                }
                /* inc force_list cursor */
                force_list_addvar_cursor++;
            } else {
                error_code = FORCE_LIST_OVERFLOW;
                goto error_cleanup;
            }
        }
    }
    return 0;

error_cleanup:
    ResetDebugVariables();
    trace_buffer_state = BUFFER_EMPTY;
    return error_code;
    
}

#define ResetForcedVariable_case_t(TYPENAME)                                            \
        case TYPENAME##_ENUM :                                                          \
            ((__IEC_##TYPENAME##_t *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* for local variable we don't restore original value */                    \
            /* that can be added if needed, but it was like that since ever */          \
            break;

#define ResetForcedVariable_case_p(TYPENAME)                                            \
        case TYPENAME##_P_ENUM :                                                        \
        case TYPENAME##_O_ENUM :                                                        \
            ((__IEC_##TYPENAME##_p *)varp)->flags &= ~__IEC_FORCE_FLAG;                 \
            /* restore backup to pointer */                                             \
            ((__IEC_##TYPENAME##_p *)varp)->value =                                     \
                force_list_apply_cursor->value_pointer_backup;                          \
            break;

void ResetDebugVariables(void)
{
    /* Reset trace list */
    trace_list_addvar_cursor = trace_list;

    force_list_apply_cursor = force_list;
    /* Restore forced variables */
    while(force_list_apply_cursor < force_list_addvar_cursor){
        dbgvardsc_t *dsc = &dbgvardsc[
            force_list_apply_cursor->dbgvardsc_index];
        void *varp = dsc->ptr;
        switch(dsc->type){
            __ANY(ResetForcedVariable_case_t)
            __ANY(ResetForcedVariable_case_p)
        default:
            break;
        }
        /* inc force_list cursor */
        force_list_apply_cursor++;
    } /* else TODO: warn user about failure to force */ 

    /* Reset force list */
    force_list_addvar_cursor = force_list;
    /* Reset force buffer */
    force_buffer_cursor = force_buffer;
}

void FreeDebugData(void)
{
    /* atomically mark buffer as free */
    AtomicCompareExchange(
        &trace_buffer_state,
        BUFFER_FULL,
        BUFFER_EMPTY);
}
int WaitDebugData(unsigned long *tick);
/* Wait until debug data ready and return pointer to it */
int GetDebugData(unsigned long *tick, unsigned long *size, void **buffer){
    int wait_error = WaitDebugData(tick);
    if(!wait_error){
        *size = trace_buffer_cursor - trace_buffer;
        *buffer = trace_buffer;
    }
    return wait_error;
}
#endif
#endif

