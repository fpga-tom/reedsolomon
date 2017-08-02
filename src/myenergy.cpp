//
// File: myenergy.cpp
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
#include "myenergy.h"

// Model step function
void myenergyModelClass::step()
{
  int32_T i;
  int32_T noErrorStatus;
  int32_T currWordIdx;
  int32_T j;
  int32_T inIdx;
  int32_T degGammaZ;
  int32_T nCC;
  boolean_T loopflag;
  int32_T mpow;
  int32_T q;
  int32_T frontA;
  int32_T z;
  int32_T k;
  uint8_T rtb_GeneralMultiplexedDeinterle[1632];
  uint8_T rtb_u04188ShortenedRSDecoder[1504];
  uint8_T rtb_Delay[1632];
  int32_T u04188ShortenedRSDecoder_Errloc[16];
  int32_T u04188ShortenedRSDecoder_TempVe[17];
  int32_T u04188ShortenedRSDecoder_PsiZ[17];
  int32_T u04188ShortenedRSDecoder_OmegaZ[34];
  int32_T u04188ShortenedRSDecoder_Syndro[16];
  int32_T u04188ShortenedRSDecoder_PsiZSt[17];

  // S-Function (scomgenmuxint): '<S1>/General Multiplexed Deinterleaver1' incorporates:
  //   Inport: '<Root>/In1'

  for (i = 0; i < 1632; i++) {
    if (rtConstP.GeneralMultiplexedDeinterleaver[rtDW.RegSel] == 0) {
      rtb_GeneralMultiplexedDeinterle[i] = rtU.In1[i];
    } else {
      rtDW.BuffOff[rtDW.RegSel]++;
      if (rtDW.BuffOff[rtDW.RegSel] ==
          rtConstP.GeneralMultiplexedDeinterleaver[rtDW.RegSel]) {
        rtDW.BuffOff[rtDW.RegSel] = 0;
      }

      currWordIdx = rtDW.BuffBgn[rtDW.RegSel] + rtDW.BuffOff[rtDW.RegSel];
      rtb_GeneralMultiplexedDeinterle[i] = rtDW.DelayElems[currWordIdx];
      rtDW.DelayElems[currWordIdx] = rtU.In1[i];
    }

    rtDW.RegSel++;
    if (rtDW.RegSel == 12) {
      rtDW.RegSel = 0;
    }
  }

  // Delay: '<Root>/Delay'
  memcpy(&rtb_Delay[0], &rtDW.Delay_DSTATE[0], 1020U * sizeof(uint8_T));
  memcpy(&rtb_Delay[1020], &rtb_GeneralMultiplexedDeinterle[0], 612U * sizeof
         (uint8_T));

  // S-Function (scomberlekamp): '<S2>/(204,188) Shortened RS Decoder' incorporates:
  //   S-Function (scomgenmuxint): '<S1>/General Multiplexed Deinterleaver1'

  // start of COMM_DoBerlekamp()
  // The function uses the algorithm  described
  // in Clark and Cain, Error-Correction Coding for Digital Communications, 1981 
  // PART I - ERROR LOCATOR POLYNOMIAL COMPUTATION
  // Compute syndrome series : length = 2*t
  for (currWordIdx = 0; currWordIdx < 8; currWordIdx++) {
    noErrorStatus = 1;

    //  start of assignInputs(): Populate the codeword and erasure vectors with the proper data  
    memset(&rtDW.u04188ShortenedRSDecoder_CCode[0], 0, 51U * sizeof(int32_T));

    // Assign message symbols.
    // If there are erasures, insert zeros in the erased positions.
    inIdx = currWordIdx * 204;
    rtDW.u04188ShortenedRSDecoder_CCode[51] = rtb_Delay[inIdx];
    inIdx++;
    for (i = 0; i < 187; i++) {
      rtDW.u04188ShortenedRSDecoder_CCode[i + 52] = rtb_Delay[inIdx];
      inIdx++;
    }

    // Assign parity symbols, again accounting for erasures
    // no puncturing
    inIdx = currWordIdx * 204;

    //  end of assignInputs()
    // Initialize Gamma(Z) = 1 : ASCENDING ORDER.  length = 2t+1
    rtDW.u04188ShortenedRSDecoder_GammaZ[0U] = 1;
    for (i = 0; i < 16; i++) {
      rtDW.u04188ShortenedRSDecoder_CCode[i + 239] = rtb_Delay[inIdx + 188];
      inIdx++;
      rtDW.u04188ShortenedRSDecoder_GammaZ[i + 1] = 0;
    }

    // Calculate the erasure polynomial GammaZ.GammaZ is the set of coefficients 
    // of the erasure polynomial in ASCENDING order, because the syndrome is
    // calculated in ascending order as well.
    //  start of calculateGammaZ() -- Calculate the erasure locator polynomial
    rtDW.u04188ShortenedRSDecoder_Gamm_h[0U] = 1;

    //  end of calculateGammaZ()
    // Calculate the syndrome by evaluating the codeword at successive
    // powers of alpha.  The syndrome is in ASCENDING order.
    for (i = 0; i < 16; i++) {
      degGammaZ = 0;
      for (j = 254; j >= 0; j += -1) {
        //  start of gf_pow():gf_pow raises x^yd
        inIdx = (1 + i) * j * rtConstP.u04188ShortenedRSDecoder_table2[1] % 255;
        if (inIdx == 0) {
          inIdx = 255;
        }

        //  end of gf_pow()
        // CCode[nfull-1-j] is the current input code symbol.
        // Multiply it by alpha, then get the sum so far.
        //  start of gf_mul: gf_mul multiplies the scalars  a * b
        if ((rtDW.u04188ShortenedRSDecoder_CCode[254 - j] == 0) ||
            (rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1] == 0)) {
          k = 0;
        } else {
          inIdx =
            (rtConstP.u04188ShortenedRSDecoder_table2[rtDW.u04188ShortenedRSDecoder_CCode
             [254 - j] - 1] +
             rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
             [inIdx - 1] - 1]) % 255;
          if (inIdx == 0) {
            inIdx = 255;
          }

          k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
        }

        // end of gf_mul()
        degGammaZ ^= k;
      }

      if ((noErrorStatus != 0) && (degGammaZ != 0)) {
        noErrorStatus = 0;
      }

      u04188ShortenedRSDecoder_Syndro[i] = degGammaZ;
    }

    // Stop if all syndromes == 0 (i.e. input word is already a valid BCH/RS codeword) 
    if (noErrorStatus == 1) {
      //  start of assignOutputs():Populate output vectors with proper data
      // Corrected message.  If there is a decoding failure, return the input message. 
      for (i = 0; i < 188; i++) {
        rtb_u04188ShortenedRSDecoder[currWordIdx * 188 + i] = (uint8_T)
          rtDW.u04188ShortenedRSDecoder_CCode[i + 51];
      }

      // Optional output for # of errors corrected
      // Parity of corrected codeword. If it is punctured, remove the punctured symbols. 
      // If there is a decoding failure, return the input parity.
      //  end of assignOutputs()
    } else {
      // Calculate the error/erasure locator polynomial PsiZ
      //  start of calculatePsiZ(): Calculate the error/erasure locator polynomial PsiZ 
      // Use the diagram in Fig. 5-8 of Clark and Cain to implement the algorithm. 
      // Box 1 -- Initializations
      // kCC is the location of the oldest symbol in the LFSR at the point
      // where the register fails.
      j = -1;

      // discrep is the convolution of PsiZ and the syndrome
      // L is the length of the linear feedback shift register (LFSR)
      // Connection polynomial = 1.  ASCENDING order.  deg(PsiZ) = 2*t.
      // To account for erasures, PsiZ = LambdaZ * GammaZ, where LambdaZ is the
      // error locator polynomial, and GammaZ is the erasure locator polynomial. 
      // NOTE:  PsiZ is the coefficients of the connection polynomial in order of 
      //        ASCENDING powers rather than the conventional descending order.
      //        This is such that after the set of iterations, the inverse of
      //        roots of PsiZ in descending order can be obtained directly by
      //        finding the roots of PsiZ in ascending order.  PsiZ is
      //        initialized as GammaZ in case there are erasures.

      // Initialize Psi(Z) = Gamma(Z) : ASCENDING ORDER.  length = 2t+1
      // Initialize correction polynomial D(z) = z*GammaZ : ASCENDING ORDER.
      //   length = 2t+2
      rtDW.u04188ShortenedRSDecoder_Dz[0U] = 0;
      for (i = 0; i < 17; i++) {
        u04188ShortenedRSDecoder_PsiZ[i] =
          rtDW.u04188ShortenedRSDecoder_GammaZ[i];
        u04188ShortenedRSDecoder_PsiZSt[i] = 0;
        rtDW.u04188ShortenedRSDecoder_Dz[i + 1] =
          rtDW.u04188ShortenedRSDecoder_GammaZ[i];
      }

      // 2*t-numErasPuncs iterations (Diamond 3)
      for (nCC = 0; nCC < 16; nCC++) {
        // Box 2 -- Calculate the discrepancy, which is the sum over i of
        //          PsiZ(i)*Syndrome(n-i) with i going from 0 to L
        degGammaZ = 0;
        for (i = 0; i < noErrorStatus + 1; i++) {
          if (nCC - i >= 0) {
            // Check that syndrome position is valid
            // Multiply the current Psi coefficient by the
            // (nCC-L)'th syndrome value.  Then update sum.
            //  start of gf_mul: gf_mul multiplies the scalars  a * b
            if ((u04188ShortenedRSDecoder_PsiZ[i] == 0) ||
                (u04188ShortenedRSDecoder_Syndro[nCC - i] == 0)) {
              k = 0;
            } else {
              inIdx =
                (rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Syndro
                 [nCC - i] - 1] +
                 rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_PsiZ
                 [i] - 1]) % 255;
              if (inIdx == 0) {
                inIdx = 255;
              }

              k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
            }

            // end of gf_mul()
            degGammaZ ^= k;
          }
        }

        // Diamond 1 -- Continue if the discrepancy is not equal to zero
        if (degGammaZ != 0) {
          // Box 3 -- Connection polynomial
          //          PsiZ(n) = PsiZ(n-1) - discrep(n)*Dz
          for (i = 0; i < 17; i++) {
            u04188ShortenedRSDecoder_TempVe[i] = degGammaZ;
          }

          for (i = 0; i < 16; i++) {
            //  start of gf_mul: gf_mul multiplies the scalars  a * b
            if ((u04188ShortenedRSDecoder_TempVe[i] == 0) ||
                (rtDW.u04188ShortenedRSDecoder_Dz[i] == 0)) {
              k = 0;
            } else {
              inIdx =
                (rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_TempVe
                 [i] - 1] +
                 rtConstP.u04188ShortenedRSDecoder_table2[rtDW.u04188ShortenedRSDecoder_Dz
                 [i] - 1]) % 255;
              if (inIdx == 0) {
                inIdx = 255;
              }

              k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
            }

            // end of gf_mul()
            u04188ShortenedRSDecoder_PsiZSt[i] = u04188ShortenedRSDecoder_PsiZ[i]
              ^ k;
          }

          // Diamond 2
          if (noErrorStatus < nCC - j) {
            // Boxes 4-7 -- Correction polynomial
            //              Dz = PsiZ(n-1) / discrep(n)
            degGammaZ = nCC - j;
            j = nCC - noErrorStatus;
            for (i = 0; i < 17; i++) {
              //  start of gf_div():gf_div divides the scalars x/b
              //  start of gf_mul: gf_mul multiplies the scalars  a * b
              if ((rtConstP.u04188ShortenedRSDecoder_table1[254 -
                   rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_TempVe
                   [i] - 1]] == 0) || (u04188ShortenedRSDecoder_PsiZ[i] == 0)) {
                k = 0;
              } else {
                inIdx =
                  (rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                   [254 -
                   rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_TempVe
                   [i] - 1]] - 1] +
                   rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_PsiZ
                   [i] - 1]) % 255;
                if (inIdx == 0) {
                  inIdx = 255;
                }

                k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
              }

              // end of gf_mul()
              //  end of gf_div()
              rtDW.u04188ShortenedRSDecoder_Dz[i] = k;
            }

            noErrorStatus = degGammaZ;
          }

          // Box 8 -- Reset the error/erasure locator polynomial
          memcpy(&u04188ShortenedRSDecoder_PsiZ[0],
                 &u04188ShortenedRSDecoder_PsiZSt[0], 17U * sizeof(int32_T));
        }

        // Box 9 -- Correction polynomial
        //           Dz = z * Dz
        for (i = 15; i >= 0; i += -1) {
          rtDW.u04188ShortenedRSDecoder_Dz[i + 1] =
            rtDW.u04188ShortenedRSDecoder_Dz[i];
        }

        rtDW.u04188ShortenedRSDecoder_Dz[0U] = 0;
      }

      //  end of calculatePsiZ
      // FIND ERROR LOCATIONS
      // At this point, error/erasure locator polynomial has been found,  which is PsiZ 
      // Find degree of Psi(Z)
      degGammaZ = 0;
      loopflag = true;
      for (i = 16; i >= 0; i += -1) {
        if ((u04188ShortenedRSDecoder_PsiZ[i] > 0) && loopflag) {
          degGammaZ = i;
          loopflag = false;
        }
      }

      // Degree of Psi(Z) must be equal to L and larger than 0
      // (i.e. cannot be a constant)
      if ((degGammaZ != noErrorStatus) || (degGammaZ < 1)) {
        //  start of assignOutputs():Populate output vectors with proper data
        // Corrected message.  If there is a decoding failure, return the input message. 
        memcpy(&rtb_u04188ShortenedRSDecoder[currWordIdx * 188],
               &rtb_Delay[currWordIdx * 204], 188U * sizeof(uint8_T));

        // Optional output for # of errors corrected
        // Parity of corrected codeword. If it is punctured, remove the punctured symbols. 
        // If there is a decoding failure, return the input parity.
        //  end of assignOutputs()
      } else {
        // Initialize contents at pointer Errloc
        memset(&u04188ShortenedRSDecoder_Errloc[0], 0, sizeof(int32_T) << 4U);

        //  start of gf_roots()
        // This function takes in vector X, computes the roots and stores them in roots 
        // it returns the number of roots
        nCC = 17;
        noErrorStatus = 0;
        memcpy(&u04188ShortenedRSDecoder_PsiZSt[0],
               &u04188ShortenedRSDecoder_PsiZ[0], 17U * sizeof(int32_T));
        i = 0;
        while (i < 256) {
          j = 0;
          for (q = 0; q < nCC; q++) {
            rtDW.u04188ShortenedRSDecoder_d[q] = i;
          }

          for (mpow = 0; mpow < nCC; mpow++) {
            //  start of gf_pow():gf_pow raises x^yd
            if (rtDW.u04188ShortenedRSDecoder_d[mpow] == 0) {
              k = (mpow == 0);
            } else {
              inIdx =
                rtConstP.u04188ShortenedRSDecoder_table2[rtDW.u04188ShortenedRSDecoder_d
                [mpow] - 1] * mpow % 255;
              if (inIdx == 0) {
                inIdx = 255;
              }

              k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
            }

            //  end of gf_pow()
            rtDW.u04188ShortenedRSDecoder_d[mpow] = k;
          }

          for (q = 0; q < nCC; q++) {
            //  start of gf_mul: gf_mul multiplies the scalars  a * b
            if ((rtDW.u04188ShortenedRSDecoder_d[q] == 0) ||
                (u04188ShortenedRSDecoder_PsiZSt[q] == 0)) {
              k = 0;
            } else {
              inIdx =
                (rtConstP.u04188ShortenedRSDecoder_table2[rtDW.u04188ShortenedRSDecoder_d
                 [q] - 1] +
                 rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_PsiZSt
                 [q] - 1]) % 255;
              if (inIdx == 0) {
                inIdx = 255;
              }

              k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
            }

            // end of gf_mul()
            j ^= k;
          }

          if (j == 0) {
            u04188ShortenedRSDecoder_Errloc[noErrorStatus] = i;
            noErrorStatus++;

            //  start of gf_div():gf_div divides the scalars x/b
            //  start of gf_mul: gf_mul multiplies the scalars  a * b
            k = rtConstP.u04188ShortenedRSDecoder_table1[254] - 1;

            // end of gf_mul()
            //  end of gf_div()
            //  start of gf_div():gf_div divides the scalars x/b
            //  start of gf_mul: gf_mul multiplies the scalars  a * b
            if (rtConstP.u04188ShortenedRSDecoder_table1[254 -
                rtConstP.u04188ShortenedRSDecoder_table2[i - 1]] == 0) {
              mpow = 0;
            } else {
              inIdx =
                rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                [254 - rtConstP.u04188ShortenedRSDecoder_table2[i - 1]] - 1] %
                255;
              if (inIdx == 0) {
                inIdx = 255;
              }

              mpow = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
            }

            // end of gf_mul()
            //  end of gf_div()
            //  start of gf_deconv --- de-convolves A from B
            frontA = 0;
            for (q = 0; q < nCC; q++) {
              rtDW.u04188ShortenedRSDecoder_tmpQuo[q] = 0;
            }

            for (q = 0; q < nCC - 1; q++) {
              //  start of gf_div():gf_div divides the scalars x/b
              //  start of gf_mul: gf_mul multiplies the scalars  a * b
              if ((rtConstP.u04188ShortenedRSDecoder_table1[254 -
                   rtConstP.u04188ShortenedRSDecoder_table2[k]] == 0) ||
                  (u04188ShortenedRSDecoder_PsiZSt[frontA] == 0)) {
                z = 0;
              } else {
                inIdx =
                  (rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                   [254 - rtConstP.u04188ShortenedRSDecoder_table2[k]] - 1] +
                   rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_PsiZSt
                   [frontA] - 1]) % 255;
                if (inIdx == 0) {
                  inIdx = 255;
                }

                z = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
              }

              // end of gf_mul()
              //  end of gf_div()
              for (j = 1; j < nCC; j++) {
                rtDW.u04188ShortenedRSDecoder_tmpQuo[j - 1] =
                  rtDW.u04188ShortenedRSDecoder_tmpQuo[j];
              }

              rtDW.u04188ShortenedRSDecoder_tmpQuo[nCC - 1] = z;

              //  start of gf_mul: gf_mul multiplies the scalars  a * b
              if ((z == 0) || (k + 1 == 0)) {
                inIdx = 0;
              } else {
                inIdx = (rtConstP.u04188ShortenedRSDecoder_table2[z - 1] +
                         rtConstP.u04188ShortenedRSDecoder_table2[k]) % 255;
                if (inIdx == 0) {
                  inIdx = 255;
                }

                inIdx = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
              }

              // end of gf_mul()
              u04188ShortenedRSDecoder_PsiZSt[frontA] ^= inIdx;

              //  start of gf_mul: gf_mul multiplies the scalars  a * b
              if ((z == 0) || (mpow == 0)) {
                z = 0;
              } else {
                inIdx = (rtConstP.u04188ShortenedRSDecoder_table2[z - 1] +
                         rtConstP.u04188ShortenedRSDecoder_table2[mpow - 1]) %
                  255;
                if (inIdx == 0) {
                  inIdx = 255;
                }

                z = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
              }

              // end of gf_mul()
              u04188ShortenedRSDecoder_PsiZSt[frontA + 1] ^= z;
              frontA++;
            }

            for (q = 0; q < nCC - 1; q++) {
              u04188ShortenedRSDecoder_PsiZSt[q] =
                rtDW.u04188ShortenedRSDecoder_tmpQuo[q + 1];
            }

            //  end of gf_deconv
            nCC--;
            i--;
          }

          i++;
        }

        for (q = 0; q < noErrorStatus; q++) {
          //  start of gf_div():gf_div divides the scalars x/b
          //  start of gf_mul: gf_mul multiplies the scalars  a * b
          if (rtConstP.u04188ShortenedRSDecoder_table1[254 -
              rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
              [q] - 1]] == 0) {
            k = 0;
          } else {
            inIdx =
              rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
              [254 -
              rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
              [q] - 1]] - 1] % 255;
            if (inIdx == 0) {
              inIdx = 255;
            }

            k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
          }

          // end of gf_mul()
          //  end of gf_div()
          u04188ShortenedRSDecoder_Errloc[q] = k;
        }

        //  end of gf_roots()
        // Decoding failure if one of the following conditions is met:
        // (1) Psi(Z) has no roots in this field
        // (2) Number of roots not equal to degree of PsiZ
        if (noErrorStatus != degGammaZ) {
          //  start of assignOutputs():Populate output vectors with proper data
          // Corrected message.  If there is a decoding failure, return the input message. 
          memcpy(&rtb_u04188ShortenedRSDecoder[currWordIdx * 188],
                 &rtb_Delay[currWordIdx * 204], 188U * sizeof(uint8_T));

          // Optional output for # of errors corrected
          // Parity of corrected codeword. If it is punctured, remove the punctured symbols. 
          // If there is a decoding failure, return the input parity.
          //  end of assignOutputs()
        } else {
          // Test if the error locations are unique

          loopflag = true;
          i = 0;
          while ((i < noErrorStatus - 1) && loopflag) {
            j = i + 1;
            while ((j < noErrorStatus) && loopflag) {
              if (u04188ShortenedRSDecoder_Errloc[i] ==
                  u04188ShortenedRSDecoder_Errloc[j]) {
                loopflag = false;
              }

              j++;
            }

            i++;
          }

          if (!loopflag) {
            //  start of assignOutputs():Populate output vectors with proper data 
            // Corrected message.  If there is a decoding failure, return the input message. 
            memcpy(&rtb_u04188ShortenedRSDecoder[currWordIdx * 188],
                   &rtb_Delay[currWordIdx * 204], 188U * sizeof(uint8_T));

            // Optional output for # of errors corrected
            // Parity of corrected codeword. If it is punctured, remove the punctured symbols. 
            // If there is a decoding failure, return the input parity.
            //  end of assignOutputs()
          } else {
            // PART II - FIND ERROR MAGNITUDES AT EACH OF THE ERROR/ERASURE LOCATIONS, 
            // AND CORRECT THEM
            //  start of correctErrors():Calculate the error magnitude in the current error position,  
            //                           and correct the errors.
            memset(&u04188ShortenedRSDecoder_OmegaZ[0], 0, 34U * sizeof(int32_T));

            //  start of gf_conv():gf_conv convolves A with B and stores the result in retValue  
            memset(&u04188ShortenedRSDecoder_OmegaZ[0], 0, sizeof(int32_T) << 5U);
            for (k = 0; k < 17; k++) {
              for (j = 0; j < 16; j++) {
                if ((u04188ShortenedRSDecoder_PsiZ[k] == 0) ||
                    (u04188ShortenedRSDecoder_Syndro[j] == 0)) {
                  inIdx = 0;
                } else {
                  inIdx =
                    (rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_PsiZ
                     [k] - 1] +
                     rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Syndro
                     [j] - 1]) % 255;
                  if (inIdx == 0) {
                    inIdx = 255;
                  }

                  inIdx = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                }

                u04188ShortenedRSDecoder_OmegaZ[k + j] ^= inIdx;
              }
            }

            //  end of gf_conv()
            // Disregard terms of x^(2t) and higher in Omega(Z)
            // because we have no knowledge of such terms in S(Z).
            // That is, retain terms up to x^(2t-1)
            memcpy(&u04188ShortenedRSDecoder_Syndro[0],
                   &u04188ShortenedRSDecoder_OmegaZ[0], sizeof(int32_T) << 4U);

            // Compute derivative of PsiZ
            inIdx = 1;
            for (i = 0; i < 8; i++) {
              rtDW.u04188ShortenedRSDecoder_PsiZDe[inIdx - 1] =
                u04188ShortenedRSDecoder_PsiZ[inIdx];
              rtDW.u04188ShortenedRSDecoder_PsiZDe[inIdx] = 0;
              inIdx += 2;
            }

            // Find error magnitude at each error location.  Use the expression found on pg. 222 of Wicker. 
            for (j = 0; j < noErrorStatus; j++) {
              // Dot product for numerator term
              degGammaZ = 0;
              for (i = 0; i < 16; i++) {
                //  start of gf_pow():gf_pow raises x^yd
                q = -i;
                k = u04188ShortenedRSDecoder_Errloc[j];
                if (-i < 0) {
                  //  start of gf_div():gf_div divides the scalars x/b
                  //  start of gf_mul: gf_mul multiplies the scalars  a * b
                  if (rtConstP.u04188ShortenedRSDecoder_table1[254 -
                      rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
                      [j] - 1]] == 0) {
                    k = 0;
                  } else {
                    inIdx =
                      rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                      [254 -
                      rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
                      [j] - 1]] - 1] % 255;
                    if (inIdx == 0) {
                      inIdx = 255;
                    }

                    k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                  }

                  // end of gf_mul()
                  //  end of gf_div()
                  q = i;
                }

                if (k == 0) {
                  k = (q == 0);
                } else {
                  inIdx = rtConstP.u04188ShortenedRSDecoder_table2[k - 1] * q %
                    255;
                  if (inIdx == 0) {
                    inIdx = 255;
                  }

                  k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                }

                //  end of gf_pow()
                if (u04188ShortenedRSDecoder_Syndro[i] > 0) {
                  //  start of gf_mul: gf_mul multiplies the scalars  a * b
                  if ((u04188ShortenedRSDecoder_Syndro[i] == 0) || (k == 0)) {
                    k = 0;
                  } else {
                    inIdx =
                      (rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Syndro
                       [i] - 1] + rtConstP.u04188ShortenedRSDecoder_table2[k - 1])
                      % 255;
                    if (inIdx == 0) {
                      inIdx = 255;
                    }

                    k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                  }

                  // end of gf_mul()
                  degGammaZ ^= k;
                }
              }

              // Dot product for denominator
              nCC = -1;
              for (i = 0; i < 16; i++) {
                //  start of gf_pow():gf_pow raises x^yd
                q = -i;
                k = u04188ShortenedRSDecoder_Errloc[j];
                if (-i < 0) {
                  //  start of gf_div():gf_div divides the scalars x/b
                  //  start of gf_mul: gf_mul multiplies the scalars  a * b
                  if (rtConstP.u04188ShortenedRSDecoder_table1[254 -
                      rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
                      [j] - 1]] == 0) {
                    k = 0;
                  } else {
                    inIdx =
                      rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                      [254 -
                      rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
                      [j] - 1]] - 1] % 255;
                    if (inIdx == 0) {
                      inIdx = 255;
                    }

                    k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                  }

                  // end of gf_mul()
                  //  end of gf_div()
                  q = i;
                }

                if (k == 0) {
                  k = (q == 0);
                } else {
                  inIdx = rtConstP.u04188ShortenedRSDecoder_table2[k - 1] * q %
                    255;
                  if (inIdx == 0) {
                    inIdx = 255;
                  }

                  k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                }

                //  end of gf_pow()
                if (rtDW.u04188ShortenedRSDecoder_PsiZDe[i] > 0) {
                  //  start of gf_mul: gf_mul multiplies the scalars  a * b
                  if ((rtDW.u04188ShortenedRSDecoder_PsiZDe[i] == 0) || (k == 0))
                  {
                    k = 0;
                  } else {
                    inIdx =
                      (rtConstP.u04188ShortenedRSDecoder_table2[rtDW.u04188ShortenedRSDecoder_PsiZDe
                       [i] - 1] + rtConstP.u04188ShortenedRSDecoder_table2[k - 1])
                      % 255;
                    if (inIdx == 0) {
                      inIdx = 255;
                    }

                    k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
                  }

                  // end of gf_mul()
                  nCC = ((nCC + 1) ^ k) - 1;
                }
              }

              // Re-use space in Temp1
              //  start of gf_div():gf_div divides the scalars x/b
              //  start of gf_mul: gf_mul multiplies the scalars  a * b
              if ((rtConstP.u04188ShortenedRSDecoder_table1[254 -
                   rtConstP.u04188ShortenedRSDecoder_table2[nCC]] == 0) ||
                  (degGammaZ == 0)) {
                k = 0;
              } else {
                inIdx =
                  (rtConstP.u04188ShortenedRSDecoder_table2[rtConstP.u04188ShortenedRSDecoder_table1
                   [254 - rtConstP.u04188ShortenedRSDecoder_table2[nCC]] - 1] +
                   rtConstP.u04188ShortenedRSDecoder_table2[degGammaZ - 1]) %
                  255;
                if (inIdx == 0) {
                  inIdx = 255;
                }

                k = rtConstP.u04188ShortenedRSDecoder_table1[inIdx - 1];
              }

              // end of gf_mul()
              //  end of gf_div()
              // Find exponent representations of Errloc ==> get actual error locations 
              // Correct the current error
              rtDW.u04188ShortenedRSDecoder_CCode[254 -
                rtConstP.u04188ShortenedRSDecoder_table2[u04188ShortenedRSDecoder_Errloc
                [j] - 1]] ^= k;
            }

            //  end of correctErrors()
            // Assign outputs.  Reduce cnumerr by the number of punctures and erasures. 
            //  start of assignOutputs():Populate output vectors with proper data 
            // Corrected message.  If there is a decoding failure, return the input message. 
            for (i = 0; i < 188; i++) {
              rtb_u04188ShortenedRSDecoder[currWordIdx * 188 + i] = (uint8_T)
                rtDW.u04188ShortenedRSDecoder_CCode[i + 51];
            }

            // Optional output for # of errors corrected
            // Parity of corrected codeword. If it is punctured, remove the punctured symbols. 
            // If there is a decoding failure, return the input parity.
            //  end of assignOutputs()
          }
        }
      }
    }
  }

  // End of S-Function (scomberlekamp): '<S2>/(204,188) Shortened RS Decoder'

  // Outport: '<Root>/Out1' incorporates:
  //   S-Function (sfix_bitop): '<S2>/Bitwise Operator'

  //  end of COMM_DoBerlekamp()
  for (i = 0; i < 1504; i++) {
    rtY.Out1[i] = (uint8_T)(rtb_u04188ShortenedRSDecoder[i] ^
      rtConstB.DataTypeConversion[i]);
  }

  // End of Outport: '<Root>/Out1'

  // Update for Delay: '<Root>/Delay'
  memcpy(&rtDW.Delay_DSTATE[0], &rtb_GeneralMultiplexedDeinterle[612], 1020U *
         sizeof(uint8_T));
}

// Model initialize function
void myenergyModelClass::initialize()
{
  {
    int32_T i;

    // InitializeConditions for S-Function (scomgenmuxint): '<S1>/General Multiplexed Deinterleaver1' 
    rtDW.BuffBgn[0U] = 0;
    rtDW.BuffOff[0U] = 186;
    for (i = 0; i < 11; i++) {
      rtDW.BuffBgn[i + 1] = rtDW.BuffBgn[i] +
        rtConstP.GeneralMultiplexedDeinterleaver[i];
      rtDW.BuffOff[i + 1] = rtConstP.GeneralMultiplexedDeinterleaver[i + 1] - 1;
    }

    // End of InitializeConditions for S-Function (scomgenmuxint): '<S1>/General Multiplexed Deinterleaver1' 
  }
}

// Constructor
myenergyModelClass::myenergyModelClass()
{
}

// Destructor
myenergyModelClass::~myenergyModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL * myenergyModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
