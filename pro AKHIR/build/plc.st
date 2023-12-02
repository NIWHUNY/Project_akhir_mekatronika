TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK



FUNCTION_BLOCK python_eval
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_poll
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_gear
  VAR_INPUT
    N : UINT;
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    py_eval : python_eval;
    COUNTER : UINT;
    _TMP_ADD10_OUT : UINT;
    _TMP_EQ13_OUT : BOOL;
    _TMP_SEL15_OUT : UINT;
    _TMP_AND7_OUT : BOOL;
  END_VAR

  _TMP_ADD10_OUT := ADD(COUNTER, 1);
  _TMP_EQ13_OUT := EQ(N, _TMP_ADD10_OUT);
  _TMP_SEL15_OUT := SEL(_TMP_EQ13_OUT, _TMP_ADD10_OUT, 0);
  COUNTER := _TMP_SEL15_OUT;
  _TMP_AND7_OUT := AND(_TMP_EQ13_OUT, TRIG);
  py_eval(TRIG := _TMP_AND7_OUT, CODE := CODE);
  ACK := py_eval.ACK;
  RESULT := py_eval.RESULT;
END_FUNCTION_BLOCK


PROGRAM warehouse
  VAR_EXTERNAL
    start : BOOL;
    stop : BOOL;
  END_VAR
  VAR
    Reset : BOOL;
    Sensor : BOOL;
    X : BOOL;
    Z : BOOL;
    sensorstrt : BOOL;
    EntryCon : BOOL;
    LoadCon : BOOL;
    angkat : BOOL;
    kiri : BOOL;
    kanan : BOOL;
    Target : INT;
    DigitalDis : INT;
    DigitalDis0 : INT;
    VIR1 : BOOL;
    VIR2 : BOOL;
    VIR3 : BOOL;
    VIR4 : BOOL;
    VIR10 : BOOL;
    VIRblokx : BOOL;
    VIRblokz : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TON1 : TON;
    CTU0 : CTU;
    TON2 : TON;
    TON7 : TON;
    TON4 : TON;
    TON6 : TON;
    TON3 : TON;
    CTU1 : CTU;
    R_TRIG1 : R_TRIG;
    F_TRIG1 : F_TRIG;
    F_TRIG2 : F_TRIG;
    F_TRIG3 : F_TRIG;
    R_TRIG2 : R_TRIG;
    _TMP_AND69_OUT : BOOL;
    _TMP_ADD46_ENO : BOOL;
    _TMP_ADD46_OUT : INT;
  END_VAR

  IF VIR1 THEN
    kiri := TRUE; (*set*)
  END_IF;
  TON0(IN := VIR1, PT := T#1500ms);
  IF TON0.Q THEN
    angkat := TRUE; (*set*)
  END_IF;
  TON1(IN := TON0.Q, PT := T#1500ms);
  IF TON1.Q THEN
    kiri := FALSE; (*reset*)
  END_IF;
  VIR2 := TON1.Q OR TON1.Q;
  IF sensorstrt THEN
    LoadCon := TRUE; (*set*)
  END_IF;
  IF sensorstrt THEN
    EntryCon := TRUE; (*set*)
  END_IF;
  IF Sensor THEN
    LoadCon := FALSE; (*reset*)
  END_IF;
  IF Sensor THEN
    EntryCon := FALSE; (*reset*)
  END_IF;
  TON2(IN := VIR2, PT := T#1500ms);
  IF TON2.Q THEN
    VIR3 := TRUE; (*set*)
  END_IF;
  IF NOT(stop) THEN
    LoadCon := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    EntryCon := FALSE; (*reset*)
  END_IF;
  IF TON2.Q THEN
    VIR1 := FALSE; (*reset*)
  END_IF;
  R_TRIG1(CLK := TON2.Q);
  CTU0(CU := R_TRIG1.Q, PV := 54);
  Target := CTU0.CV;
  DigitalDis := CTU0.CV;
  IF Sensor THEN
    VIR1 := TRUE; (*set*)
  END_IF;
  IF VIR10 AND VIR3 THEN
    kanan := TRUE; (*set*)
  END_IF;
  TON4(IN := VIR10 AND VIR3, PT := T#1500ms);
  IF TON4.Q THEN
    angkat := FALSE; (*reset*)
  END_IF;
  IF TON4.Q THEN
    VIR4 := TRUE; (*set*)
  END_IF;
  TON7(IN := VIR1, PT := T#4400ms);
  IF TON7.Q THEN
    VIR10 := FALSE; (*reset*)
  END_IF;
  F_TRIG1(CLK := X);
  IF F_TRIG1.Q THEN
    VIRblokx := TRUE; (*set*)
  END_IF;
  TON3(IN := VIR4, PT := T#1000ms);
  IF TON3.Q THEN
    kanan := FALSE; (*reset*)
  END_IF;
  IF TON3.Q THEN
    VIR3 := FALSE; (*reset*)
  END_IF;
  IF TON3.Q THEN
    VIR3 := FALSE; (*reset*)
  END_IF;
  IF TON3.Q THEN
    VIR4 := FALSE; (*reset*)
  END_IF;
  F_TRIG2(CLK := Z);
  F_TRIG3(CLK := Z);
  R_TRIG2(CLK := F_TRIG3.Q);
  CTU1(CU := R_TRIG2.Q, R := Start, PV := 2);
  IF F_TRIG2.Q AND CTU1.Q THEN
    VIRblokz := TRUE; (*set*)
  END_IF;
  DigitalDis0 := CTU1.CV;
  _TMP_AND69_OUT := AND(VIRblokz, VIRblokx);
  IF _TMP_AND69_OUT THEN
    VIR10 := TRUE; (*set*)
  END_IF;
  TON6(IN := VIR10, PT := T#4500ms);
  _TMP_ADD46_OUT := ADD(EN := TON6.Q, IN1 := Target, IN2 := 55, ENO => _TMP_ADD46_ENO);
  IF _TMP_ADD46_ENO THEN
      Target := _TMP_ADD46_OUT;
  END_IF;
  IF _TMP_AND69_OUT THEN
    VIRblokx := FALSE; (*reset*)
  END_IF;
  IF _TMP_AND69_OUT THEN
    VIRblokz := FALSE; (*reset*)
  END_IF;
END_PROGRAM

PROGRAM program0
  VAR_EXTERNAL
    start : BOOL;
    stop : BOOL;
  END_VAR
  VAR
    cncsen1 : BOOL;
    cncsen2 : BOOL;
    cncsen1B : BOOL;
    cncsen2B : BOOL;
    mchnsts : BOOL;
    mchnsts2 : BOOL;
    rdrctsns : BOOL;
    sensor1greenlid : BOOL;
    sensor2greenbase : BOOL;
    sensor1bluelid : BOOL;
    sensor2bluebase : BOOL;
    rstcnt : BOOL;
    lids : BOOL;
    cnccon1 : BOOL;
    cnccon2 : BOOL;
    cnc1 : BOOL;
    cnc2 : BOOL;
    rdrct : BOOL;
    clampgreenlid : BOOL;
    clampgreenbase : BOOL;
    clampgreenrise : BOOL;
    clamplidblue : BOOL;
    clampbaseblue : BOOL;
    clampbluerise : BOOL;
    picker1z : BOOL;
    picker1x : BOOL;
    picker1G : BOOL;
    picker2z : BOOL;
    picker2x : BOOL;
    picker2g : BOOL;
    conveyorpck : BOOL;
    VIR1 : BOOL;
    VIR2 : BOOL;
    VIR3 : BOOL;
    VIR4 : BOOL;
    VIR5 : BOOL;
    VIR6 : BOOL;
    VIR7 : BOOL;
    VIR8 : BOOL;
    VIR9 : BOOL;
    VIR10 : BOOL;
    VIR11 : BOOL;
    VIR12 : BOOL;
    VIR13 : BOOL;
  END_VAR
  VAR
    cncton1 : TON;
    cncton2 : TON;
    cncton3 : TON;
    cncton4 : TON;
    cncton5 : TON;
    cncton6 : TON;
    cncton7 : TON;
    cncton8 : TON;
    cncton9 : TON;
    cncton10 : TON;
    cncton11 : TON;
    cncton12 : TON;
    cncton13 : TON;
    cncton14 : TON;
    CTU0 : CTU;
    R_TRIG1 : R_TRIG;
  END_VAR

  IF cncsen2 AND stop THEN
    VIR1 := FALSE; (*reset*)
  END_IF;
  cnccon1 := NOT(VIR1) AND NOT(mchnsts) AND (cncsen2 AND stop OR start AND stop);
  IF start THEN
    VIR13 := TRUE; (*set*)
  END_IF;
  cncton1(IN := VIR2, PT := T#500ms);
  IF cncton1.Q THEN
    VIR1 := TRUE; (*set*)
  END_IF;
  IF cncton1.Q THEN
    VIR2 := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    VIR13 := FALSE; (*reset*)
  END_IF;
  IF cncsen1 THEN
    VIR2 := TRUE; (*set*)
  END_IF;
  cnc1 := VIR13 AND VIR1;
  lids := TRUE;
  IF cncsen2B AND stop THEN
    VIR3 := FALSE; (*reset*)
  END_IF;
  cnccon2 := NOT(VIR3) AND NOT(mchnsts2) AND (cncsen2B AND stop OR start AND stop);
  cncton2(IN := VIR4, PT := T#500ms);
  IF cncton2.Q THEN
    VIR3 := TRUE; (*set*)
  END_IF;
  IF cncton2.Q THEN
    VIR4 := FALSE; (*reset*)
  END_IF;
  IF cncsen1B THEN
    VIR4 := TRUE; (*set*)
  END_IF;
  cnc2 := VIR13 AND VIR3;
  rdrct := rdrctsns;
  IF NOT(stop) THEN
    picker1G := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    picker1z := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    picker1x := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clampgreenbase := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clampgreenlid := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clampgreenrise := FALSE; (*reset*)
  END_IF;
  IF sensor2greenbase THEN
    clampgreenbase := TRUE; (*set*)
  END_IF;
  IF sensor2greenbase THEN
    VIR7 := TRUE; (*set*)
  END_IF;
  IF sensor1greenlid THEN
    clampgreenlid := TRUE; (*set*)
  END_IF;
  IF sensor1greenlid THEN
    VIR8 := TRUE; (*set*)
  END_IF;
  cncton3(IN := VIR7, PT := T#1s);
  IF cncton3.Q THEN
    picker1z := TRUE; (*set*)
  END_IF;
  cncton4(IN := cncton3.Q, PT := T#1s);
  IF cncton4.Q THEN
    picker1G := TRUE; (*set*)
  END_IF;
  IF cncton4.Q THEN
    picker1z := FALSE; (*reset*)
  END_IF;
  IF cncton4.Q THEN
    clampgreenlid := FALSE; (*reset*)
  END_IF;
  IF cncton4.Q THEN
    VIR5 := TRUE; (*set*)
  END_IF;
  IF VIR5 THEN
    VIR7 := FALSE; (*reset*)
  END_IF;
  cncton5(IN := VIR5, PT := T#1s);
  IF cncton5.Q THEN
    picker1x := TRUE; (*set*)
  END_IF;
  cncton6(IN := VIR8 AND cncton5.Q, PT := T#1s);
  IF cncton6.Q THEN
    picker1z := TRUE; (*set*)
  END_IF;
  cncton7(IN := cncton6.Q, PT := T#1s);
  IF cncton7.Q THEN
    VIR6 := TRUE; (*set*)
  END_IF;
  IF VIR6 THEN
    VIR5 := FALSE; (*reset*)
  END_IF;
  IF VIR6 THEN
    VIR8 := FALSE; (*reset*)
  END_IF;
  IF VIR6 THEN
    picker1G := FALSE; (*reset*)
  END_IF;
  IF VIR6 THEN
    picker1z := FALSE; (*reset*)
  END_IF;
  IF VIR6 THEN
    clampgreenbase := FALSE; (*reset*)
  END_IF;
  IF VIR6 THEN
    clampgreenrise := TRUE; (*set*)
  END_IF;
  cncton8(IN := VIR6, PT := T#1s);
  IF cncton8.Q THEN
    picker1x := FALSE; (*reset*)
  END_IF;
  IF cncton8.Q THEN
    clampgreenrise := FALSE; (*reset*)
  END_IF;
  IF cncton8.Q THEN
    VIR6 := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    picker2g := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    picker2x := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    picker2z := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clampbaseblue := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clampbluerise := FALSE; (*reset*)
  END_IF;
  IF NOT(stop) THEN
    clamplidblue := FALSE; (*reset*)
  END_IF;
  IF sensor2bluebase THEN
    clampbaseblue := TRUE; (*set*)
  END_IF;
  IF sensor2bluebase THEN
    VIR11 := TRUE; (*set*)
  END_IF;
  IF sensor1bluelid THEN
    clamplidblue := TRUE; (*set*)
  END_IF;
  IF sensor1bluelid THEN
    VIR12 := TRUE; (*set*)
  END_IF;
  cncton9(IN := VIR11, PT := T#1s);
  IF cncton9.Q THEN
    picker2z := TRUE; (*set*)
  END_IF;
  cncton10(IN := cncton9.Q, PT := T#1s);
  IF cncton10.Q THEN
    picker2g := TRUE; (*set*)
  END_IF;
  IF cncton10.Q THEN
    picker2z := FALSE; (*reset*)
  END_IF;
  IF cncton10.Q THEN
    clamplidblue := FALSE; (*reset*)
  END_IF;
  IF cncton10.Q THEN
    VIR9 := TRUE; (*set*)
  END_IF;
  IF VIR9 THEN
    VIR11 := FALSE; (*reset*)
  END_IF;
  cncton11(IN := VIR9, PT := T#1s);
  IF cncton11.Q THEN
    picker2x := TRUE; (*set*)
  END_IF;
  cncton12(IN := VIR12 AND cncton11.Q, PT := T#1s);
  IF cncton12.Q THEN
    picker2z := TRUE; (*set*)
  END_IF;
  cncton13(IN := cncton12.Q, PT := T#1s);
  IF cncton13.Q THEN
    VIR10 := TRUE; (*set*)
  END_IF;
  IF VIR10 THEN
    VIR9 := FALSE; (*reset*)
  END_IF;
  IF VIR10 THEN
    VIR12 := FALSE; (*reset*)
  END_IF;
  IF VIR10 THEN
    picker2g := FALSE; (*reset*)
  END_IF;
  IF VIR10 THEN
    picker2z := FALSE; (*reset*)
  END_IF;
  IF VIR10 THEN
    clampbaseblue := FALSE; (*reset*)
  END_IF;
  IF VIR10 THEN
    clampbluerise := TRUE; (*set*)
  END_IF;
  cncton14(IN := VIR10, PT := T#1s);
  IF cncton14.Q THEN
    picker2x := FALSE; (*reset*)
  END_IF;
  IF cncton14.Q THEN
    clampbluerise := FALSE; (*reset*)
  END_IF;
  IF cncton14.Q THEN
    VIR10 := FALSE; (*reset*)
  END_IF;
  R_TRIG1(CLK := cncton14.Q);
  CTU0(CU := R_TRIG1.Q, R := rstcnt, PV := 4);
  conveyorpck := CTU0.Q;
END_PROGRAM

PROGRAM conveyorz
  VAR_EXTERNAL
    start : BOOL;
    stop : BOOL;
  END_VAR
  VAR
    conveyor1 : BOOL;
    conveyor2 : BOOL;
    conveyor3 : BOOL;
    conveyor4 : BOOL;
    conveyor5 : BOOL;
    conveyor6 : BOOL;
    conveyor7 : BOOL;
    conveyor8 : BOOL;
    conveyor9 : BOOL;
    conveyor10 : BOOL;
    conveyor11 : BOOL;
    conveyor12 : BOOL;
    conveyor13 : BOOL;
    VIR1 : BOOL;
  END_VAR

  conveyor1 := VIR1;
  conveyor2 := VIR1;
  conveyor3 := VIR1;
  conveyor4 := VIR1;
  conveyor5 := VIR1;
  conveyor6 := VIR1;
  conveyor7 := VIR1;
  conveyor8 := VIR1;
  conveyor9 := VIR1;
  conveyor10 := VIR1;
  conveyor11 := VIR1;
  conveyor12 := VIR1;
  conveyor13 := VIR1;
  IF start THEN
    VIR1 := TRUE; (*set*)
  END_IF;
  IF NOT(stop) THEN
    VIR1 := FALSE; (*reset*)
  END_IF;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      start : BOOL;
      stop : BOOL;
    END_VAR
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    TASK task1(INTERVAL := T#20ms,PRIORITY := 0);
    TASK task2(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
    PROGRAM instance1 WITH task1 : warehouse;
    PROGRAM instance2 WITH task2 : conveyorz;
  END_RESOURCE
END_CONFIGURATION
