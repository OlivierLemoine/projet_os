#ifndef _LM75_H_
#define _LM75_H_

/* lm75_read_temp
 *   get current measured temperature
 */
int  lm75_read_temp(int *temp);

/* lm75_read_thyst
 *   get hysteresys value for overtemperature shutdown
 */
int  lm75_read_thyst(int *thyst);

/* lm75_read_tos
 *   get overtemperature shutdown
 */
int  lm75_read_tos(int *tos);

/* lm75_write_thyst
 *   set hysteresys value for overtemperature shutdown
 */
int  lm75_write_thyst(int thyst);

/* lm75_write_tos
 *   set overtemperature shutdown
 */
int  lm75_write_tos(int tos);

#endif
