#include <clock.h>
#include "io.h"
#include "console.h"
#include "string.h"

static system_time_dt time_dt;

void init_clock() {
    time_dt.seconds = 0;
    time_dt.ticks = 0;
    time_dt.total_ticks = 0;
    uint16_t divisor = 0;
    write_port(PIT_COMMAND_PORT, CHANEL_0_CONFIG);
    write_port(PIT_CHANEL_0_DATA_PORT, (unsigned char) (divisor & 0xFF));
    write_port(PIT_CHANEL_0_DATA_PORT, (unsigned char) divisor >> 8);
    write_text_to_char_console("clock init\n");
}

void timer_wait(uint32_t milliseconds) {
    uint32_t time_begin = time_dt.total_ticks;
    uint32_t current_time =  0;
    while (current_time < milliseconds) {
        current_time =  (time_dt.total_ticks - time_begin) * TICKS_TO_MILLISECONDS;
    }
}


system_time_dt get_system_time() {
    return time_dt;
}


void handler_timer_interruption() {
    time_dt.ticks += 1;
    time_dt.total_ticks += 1;
    if (time_dt.ticks >= TICKS_PER_SECONDS) {
        time_dt.seconds += 1;
        time_dt.ticks = 0;
    }
}