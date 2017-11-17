

#ifndef CAGAOS_CLOCK_H
#define CAGAOS_CLOCK_H

#include "types.h"

#define TICKS_PER_SECONDS 18
#define TICKS_TO_MILLISECONDS 55
#define CHANEL_0_CONFIG 0x36
#define PIT_COMMAND_PORT    0x43
#define PIT_CHANEL_0_DATA_PORT 0x40

typedef struct {
    uint32_t ticks;
    uint32_t seconds;
    uint32_t total_ticks;
} system_time_dt;

void init_clock();

void timer_wait(uint32_t milliseconds);

void handler_timer_interruption();

system_time_dt get_system_time();

#endif
