#include "hal_types.h"

#ifndef BUZZER_H
#define BUZZER_H

#ifdef __cplusplus
extern "C"
{
#endif
  extern void BuzzerInit( void );

  extern void BuzzerOn(uint32 taskId, uint32 frequency, uint32 duration);

  extern void BuzzerOff( void );
#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H */