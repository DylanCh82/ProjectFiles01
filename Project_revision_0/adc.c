/**
 * adc.c: Functions for displaying content on the 4x16 Character LCD Screen.
 * Updated on 8/22/19 for compatibility with Isaac Rex's timer fixes.  (date corrected by phjones)
 *
 *  @author Noah Bergman, Eric Middleton
 *  @date 02/29/2016
 *
 *
 */


#include "adc.h"


void adc_init (void) {
    SYSCTL_RCGCGPIO_R |= 0x02;  // 1) activate clock for Port E

    while ((SYSCTL_PRGPIO_R & 0x02) == 0 ) {};


     GPIO_PORTB_DIR_R &= ~0x04;      // 2) make PB4 input

     GPIO_PORTB_AFSEL_R |= 0x10;     // 3) enable alternate function on PE2

     GPIO_PORTB_DEN_R &= ~0x10;      // 4) disable digital I/O on PE2

     GPIO_PORTB_AMSEL_R |= 0x10;     // 5) enable analog function on PE2

     SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0

     while((SYSCTL_PRADC_R & 0x01) == 0) {};


     ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3

     ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger

     ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field

     ADC0_SSMUX3_R += 10;             //    set channel Ain10 (PE4)

     ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0

     ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
}






unsigned long adc_read (void) {

      unsigned long result;

      ADC0_PSSI_R = 0x0008;            // 1) initiate SS3

      while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done

      result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result

      ADC0_ISC_R = 0x0008;             // 4) acknowledge completion

      return result;
}


