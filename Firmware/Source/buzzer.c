#include "OnBoard.h"
#include "buzzer.h"

#define T3CFG_A2 BV(5)

#define PRI2P1 BV(5)
#define PRI3P1 BV(6)

void BuzzerInit( void ) {
  P1DIR |= BV(7);
  P1_7 = 0;
  P2SEL |= PRI2P1 | PRI3P1;
  PERCFG |= T3CFG_A2;
  T3CTL = BV(0) | BV(1) | BV(2);
  T3CCTL1 = BV(2) | BV(4);
}

void BuzzerOn(uint32 taskId, uint32 frequency, uint32 duration) {

  T3CTL |= BV(2);
  P1SEL |= BV(7);

  // Get current Timer tick divisor setting
  uint8 tickSpdDiv = (CLKCONSTA & 0x38) >> 3;
  // Check if frequency too low
  if (frequency < (244 >> tickSpdDiv)){   // 244 Hz = 32MHz / 256 (8bit counter) / 4 (up/down counter and toggle on compare) / 128 (max timer prescaler)
    BuzzerOff();                       // A lower tick speed will lower this number accordingly.
    return;
  }
  // Calculate nr of ticks required to achieve target frequency
  uint32 ticks = (8000000/frequency) >> tickSpdDiv;
  // Fit this into an 8bit counter using the timer prescaler
  uint8 prescaler = 0;
  while ((ticks & 0xFFFFFF00) != 0)
  {
    ticks >>= 1;
    prescaler += 32;
  }

  // Update registers
  T3CTL &= ~0xE0;
  T3CTL |= prescaler;
  T3CC0 = (uint8)ticks;

  T3CTL |= BV(4);
  //osal_start_timerEx(taskId, BUZZER_TIMER_EVT, duration);
}

void BuzzerOff( void ) {
  T3CTL &= ~BV(4);
  T3CTL |= BV(2);

  P1SEL &= ~BV(7);
  P1_7 = 0;
}