#include "interruption_handler.h"
#include "pic_manager.h"
#include "string.h"
#include "keyboard.h"
interruption_register idt_r;
interruption_entry idt[NUMBER_OF_INTERRUPTIONS];
static void set_idt(uint8_t num, uint32_t function_address);
void interrupt_handler(cpu_state cpu, interruption_state irq_state)
{
  if(cpu.ds == 0)
  {
    return;
  }
  if(irq_state.inturruption_number == 0x21){

    handler_keyboard_interruption();
  }
  ack_pic_interruption(irq_state.inturruption_number);
}

void setup_interruption()
{
  idt_r.limit_in_bytes = NUMBER_OF_INTERRUPTIONS * sizeof(struct interruption_entry_struct);
  idt_r.interruption_table_address=(uint32_t)&idt;
  for(uint8_t i=0;i<NUMBER_OF_INTERRUPTIONS;i++)
  {
    set_idt(i, (uint32_t) interruption_handler_default);
  }
  set_idt(32, CLOCK_INTERRUPTION);
  set_idt(33, KEYBOARD_INTERRUPTION);
  remap_pic_irqs();
  load_idt(&idt_r);
  write_text_to_char_console("*** Setting Interruptions ***\n");
}

static void set_idt(uint8_t num, uint32_t function_address)
{
   idt[num].offset_low = function_address & 0xFFFF;
   idt[num].code_descriptor = CODE_DESCRIPTOR;
   idt[num].zero  = 0x0;
   idt[num].attr = INTERRUPTION_HANDLER_ATTR;
   idt[num].offset_high = (function_address >> 16) & 0xFFFF;
}
