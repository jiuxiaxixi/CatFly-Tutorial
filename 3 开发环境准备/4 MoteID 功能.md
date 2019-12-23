# MoteID 功能

```c
void moteid_init(void)
{
   uint32_t id;
   stm32f10xx_flash_read(MOTE_ID_FLASH_ADDR,&id,4);
   moteid = id >> 16;
}

uint16_t get_moteid(void)
{
  return moteid;
}
```

 [moteID test.bin](..\..\..\Desktop\moteID test.bin) 

```c
PROCESS(led_process, "Blink1");
PROCESS_THREAD(led_process, ev, data)
{
  PROCESS_BEGIN();
  
  while(1)
  {
    static struct etimer et;
    etimer_set(&et, CLOCK_SECOND/1);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    PRINTF("The moteid is %d \r\n",get_moteid());
  }
  PROCESS_END();
}
```

