//
// File: myenergy.h
//
// Code generated for Simulink model 'myenergy'.
//
// Model version                  : 1.26
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Tue Aug  1 22:41:27 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_myenergy_h_
#define RTW_HEADER_myenergy_h_
#include <string.h>
#ifndef myenergy_COMMON_INCLUDES_
# define myenergy_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // myenergy_COMMON_INCLUDES_

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Forward declaration for rtModel
typedef struct tag_RTM RT_MODEL;

// Block signals and states (auto storage) for system '<Root>'
typedef struct {
  int32_T BuffOff[12];                 // '<S1>/General Multiplexed Deinterleaver1' 
  int32_T BuffBgn[12];                 // '<S1>/General Multiplexed Deinterleaver1' 
  int32_T u04188ShortenedRSDecoder_GammaZ[17];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_Gamm_h[2];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_Dz[18];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_CCode[255];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_PsiZDe[16];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_d[17];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_tmpQuo[17];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_input[1632];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_outMsg[1504];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T u04188ShortenedRSDecoder_outCNu[8];// '<S2>/(204,188) Shortened RS Decoder' 
  int32_T RegSel;                      // '<S1>/General Multiplexed Deinterleaver1' 
  uint8_T Delay_DSTATE[1020];          // '<Root>/Delay'
  uint8_T DelayElems[1123];            // '<S1>/General Multiplexed Deinterleaver1' 
  boolean_T u04188ShortenedRSDecoder_erasur[1632];// '<S2>/(204,188) Shortened RS Decoder' 
} DW;

// Invariant block signals (auto storage)
typedef const struct tag_ConstB {
  uint8_T DataTypeConversion[1504];    // '<S2>/Data Type Conversion'
} ConstB;

// Constant parameters (auto storage)
typedef struct {
  // Computed Parameter: GeneralMultiplexedDeinterleaver
  //  Referenced by: '<S1>/General Multiplexed Deinterleaver1'

  int32_T GeneralMultiplexedDeinterleaver[12];

  // Computed Parameter: u04188ShortenedRSDecoder_table1
  //  Referenced by: '<S2>/(204,188) Shortened RS Decoder'

  int32_T u04188ShortenedRSDecoder_table1[255];

  // Computed Parameter: u04188ShortenedRSDecoder_table2
  //  Referenced by: '<S2>/(204,188) Shortened RS Decoder'

  int32_T u04188ShortenedRSDecoder_table2[255];
} ConstP;

// External inputs (root inport signals with auto storage)
typedef struct {
  uint8_T In1[1632];                   // '<Root>/In1'
} ExtU;

// External outputs (root outports fed by signals with auto storage)
typedef struct {
  uint8_T Out1[1504];                  // '<Root>/Out1'
} ExtY;

// Real-time Model Data Structure
struct tag_RTM {
  const char_T * volatile errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

extern const ConstB rtConstB;          // constant block i/o

// Constant parameters (auto storage)
extern const ConstP rtConstP;

// Class declaration for model myenergy
class myenergyModelClass {
  // public data and function members
 public:
  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  myenergyModelClass();

  // Destructor
  ~myenergyModelClass();

  // Real-Time Model get method
  RT_MODEL * getRTM();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'myenergy'
//  '<S1>'   : 'myenergy/Convolutional Deinterleaver'
//  '<S2>'   : 'myenergy/descrambler'

#endif                                 // RTW_HEADER_myenergy_h_

//
// File trailer for generated code.
//
// [EOF]
//
