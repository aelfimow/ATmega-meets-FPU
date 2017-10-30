#ifdef NPE_H
#error Already included
#else

extern void npe_reset(void);
extern void npe_reset_off(void);

extern void npe_select(void);
extern void npe_select_off(void);

extern void npe_rw_off(void);
extern void npe_read(void);
extern void npe_write(void);
extern void npe_write_pulse(void);

extern void npe_cmd_instr(void);
extern void npe_cmd_data(void);

extern void npe_data_write(uint8_t high, uint8_t low);
extern uint16_t npe_data_read(void);
extern void npe_data_high_Z(void);

extern void npe_write_instruction(uint8_t high, uint8_t low);

extern uint8_t npe_wait(void);
extern uint8_t npe_error(void);
extern uint8_t npe_request(void);

#endif

