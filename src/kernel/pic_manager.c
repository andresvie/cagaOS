#include "pic_manager.h"
#include "io.h"

void remap_pic_irqs()
{
  write_port(PIC_1_COMMAND_PORT, PIC_RESTART_AND_ENABLE_CASCADE_MODE_COMMAND);
  write_port(PIC_2_COMMAND_PORT, PIC_RESTART_AND_ENABLE_CASCADE_MODE_COMMAND);
  write_port(PIC_1_DATA_PORT, PIC_1_FREE_PORT_RANGE_IRQ);
  write_port(PIC_2_DATA_PORT, PIC_2_FREE_PORT_RANGE_IRQ);
  write_port(PIC_1_DATA_PORT, PIC_1_SET_IRQ_2_TO_COMUNICATE_WITH_SLAVE_PIC_COMMAND);
  write_port(PIC_2_DATA_PORT, PIC_2_SET_IRQ_2_TO_COMUNICATE_WITH_MASTER_PIC_COMMAND);
  write_port(PIC_1_DATA_PORT, ENABLE_8086_MODE_COMMAND);
  write_port(PIC_2_DATA_PORT, ENABLE_8086_MODE_COMMAND);
  write_port(PIC_1_DATA_PORT, 0x0);
  write_port(PIC_2_DATA_PORT, 0x0);
}

void ack_pic_interruption(uint8_t irq)
{
  if(irq < PIC_1_FREE_PORT_RANGE_IRQ || irq > PIC_2_FREE_PORT_RANGE_IRQ)
  {
    return;
  }
  if(irq<PIC_2_FREE_PORT_RANGE_IRQ)
  {
    write_port(PIC_1_COMMAND_PORT, PIC_ACK_COMMAND);
  }
  else{
    write_port(PIC_2_COMMAND_PORT, PIC_ACK_COMMAND);
  }

}
