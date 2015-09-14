/*
Copyright 2014 Kai Ryu <kai1103@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KIMERA_H
#define KIMERA_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "matrix.h"

/*
             U1 (Pro Micro)
           ,----------------.
      TX --| TX0(PD3)   RAW |--
      RX --| RX1(PD2)   GND |--
         --| GND      RESET |-- RST
         --| GND        VCC |--
     SDA --| 2(PD1) (PF4)A3 |--
     SCL --| 3(PD0) (PF5)A2 |--
   (INT) --| 4(PD4) (PF6)A1 |--
         --| 5(PC6) (PF7)A0 |--
         --| 6(PD7) (PB1)15 |-- SCK
    LED2 --| 7(PE6) (PB3)14 |-- MISO
    LED1 --| 8(PB4) (PB2)16 |-- MOSI
    LED3 --| 9(PB5) (PB6)10 |-- LED4
          `----------------'
*/

#define LED1_PORT   PORTB
#define LED1_PIN    PINB
#define LED1_DDR    DDRB
#define LED1_BIT    PB4

#define LED2_PORT   PORTE
#define LED2_PIN    PINE
#define LED2_DDR    DDRE
#define LED2_BIT    PE6

#define LED3_PORT   PORTB
#define LED3_PIN    PINB
#define LED3_DDR    DDRB
#define LED3_BIT    PB5

#define LED4_PORT   PORTB
#define LED4_PIN    PINB
#define LED4_DDR    DDRB
#define LED4_BIT    PB6
#define LED4_OCR    OCR1B

/*
         IC1 (PCA9555)                  IC2 (PCA9555)
         ,----------.                   ,----------.
   SDA --| SDA  P00 |-- P1        SDA --| SDA  P00 |-- P9
   SCL --| SCL  P01 |-- P2        SCL --| SCL  P01 |-- P10
   INT --| INT  P02 |-- P3        INT --| INT  P02 |-- P11
         |      P03 |-- P4              |      P03 |-- P12
   GND --| A0   P04 |-- P5        VCC --| A0   P04 |-- P13
   SJ1 --| A1   P05 |-- P6        SJ1 --| A1   P05 |-- P14
   SJ2 --| A2   P06 |-- P7        SJ2 --| A2   P06 |-- P15
         |      P07 |-- P8              |      P07 |-- P16
         |          |                   |          |
         |      P10 |-- P25             |      P10 |-- P17
         |      P11 |-- P26             |      P11 |-- P18
         |      P12 |-- P27             |      P12 |-- P19
         |      P13 |-- P28             |      P13 |-- P20
         |      P14 |-- P29             |      P14 |-- P21
         |      P15 |-- P30             |      P15 |-- P22
         |      P16 |-- P31             |      P16 |-- P23
         |      P17 |-- P32             |      P17 |-- P24
         `----------'                   `----------'
*/

#define EXP_COUNT           2
#define EXP_ADDR(n)         ((0x20+(n))<<1)
#define EXP_OUTPUT          0
#define EXP_INPUT           1
#define EXP_PORT_COUNT      2
#define EXP_PIN_PER_PORT    8
enum {
    EXP_COMM_INPUT_0 = 0,
    EXP_COMM_INPUT_1,
    EXP_COMM_OUTPUT_0,
    EXP_COMM_OUTPUT_1,
    EXP_COMM_INVERSION_0,
    EXP_COMM_INVERSION_1,
    EXP_COMM_CONFIG_0,
    EXP_COMM_CONFIG_1
};
#define PX_TO_EXP(x)        (((x)>>5<<1)+((((x)>>3)&1)^(((x)>>4)&1)))
#define PX_TO_PORT(x)       (((x)>>4)&1)
#define PX_TO_PIN(x)        ((x)&7)
#define PX_COUNT            (EXP_PIN_PER_PORT * EXP_PORT_COUNT * EXP_COUNT)

#ifdef KIMERA_C
const uint16_t PROGMEM dummy[] = {
};
#endif

/* Matrix Mapping in EEPROM */

#define EECONFIG_ROW_COUNT          (uint8_t *)7
#define EECONFIG_COL_COUNT          (uint8_t *)8
#define EECONFIG_ROW_COL_MAPPING    (uint8_t *)9
#define UNCONFIGURED                0xFF

/* Functions */

void kimera_init(void);
void wdt_init(void);
uint8_t read_matrix_mapping(void);
void write_matrix_mapping(void);
void kimera_scan(void);
matrix_row_t read_cols(void);
void unselect_rows(void);
void select_row(uint8_t row);
void expander_init(uint8_t exp);
uint8_t expander_write(uint8_t exp, uint8_t command, uint8_t *data);
uint8_t expander_read(uint8_t exp, uint8_t command, uint8_t *data);
uint8_t expander_write_output(uint8_t exp, uint8_t *data);
uint8_t expander_write_inversion(uint8_t exp, uint8_t *data);
uint8_t expander_write_config(uint8_t exp, uint8_t *data);
uint8_t expander_read_input(uint8_t exp, uint8_t *data);
void init_data(uint8_t value);

#endif
