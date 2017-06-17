/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s_gpio.h"
#include "motor.h"
#include "gpio.h"
#include "motor.h"

#define PWM_TABLE_VALUES ORIGINAL_FIRMWARE_SINEWAVE_SVM

#define ORIGINAL_FIRMWARE_SINEWAVE_SVM	 1 // THIS IS THE BEST!!
#define SINE				 2
#define SQUARE				 3
#define SVM_LARGE			 4


#if (PWM_TABLE_VALUES == ORIGINAL_FIRMWARE_SINEWAVE_SVM)
uint8_t ui8_pwm_table_values [PWM_TABLE_VALUES_LEN] =
{
    7	,
    16	,
    25	,
    35	,
    44	,
    53	,
    63	,
    72	,
    81	,
    90	,
    99	,
    108	,
    117	,
    126	,
    135	,
    144	,
    153	,
    161	,
    170	,
    178	,
    186	,
    192	,
    195	,
    197	,
    200	,
    202	,
    204	,
    206	,
    208	,
    210	,
    211	,
    213	,
    214	,
    216	,
    217	,
    218	,
    218	,
    219	,
    220	,
    220	,
    221	,
    221	,
    221	,
    221	,
    221	,
    220	,
    220	,
    219	,
    218	,
    218	,
    217	,
    215	,
    214	,
    213	,
    211	,
    210	,
    208	,
    206	,
    204	,
    202	,
    200	,
    197	,
    195	,
    192	,
    193	,
    196	,
    198	,
    201	,
    203	,
    205	,
    207	,
    209	,
    210	,
    212	,
    213	,
    215	,
    216	,
    217	,
    218	,
    219	,
    219	,
    220	,
    220	,
    221	,
    221	,
    221	,
    221	,
    220	,
    220	,
    220	,
    219	,
    218	,
    217	,
    216	,
    215	,
    214	,
    212	,
    211	,
    209	,
    207	,
    205	,
    203	,
    201	,
    199	,
    196	,
    194	,
    191	,
    183	,
    174	,
    166	,
    157	,
    149	,
    140	,
    131	,
    123	,
    114	,
    105	,
    96	,
    86	,
    77	,
    68	,
    59	,
    50	,
    40	,
    31	,
    21	,
    12	,
    3	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#elif (PWM_TABLE_VALUES == SINE)
uint8_t ui8_pwm_table_values [PWM_TABLE_VALUES_LEN] =
{
    4	,
    11	,
    17	,
    23	,
    29	,
    36	,
    42	,
    48	,
    54	,
    60	,
    66	,
    72	,
    78	,
    84	,
    90	,
    96	,
    102	,
    107	,
    113	,
    119	,
    124	,
    130	,
    135	,
    140	,
    145	,
    150	,
    155	,
    160	,
    165	,
    170	,
    175	,
    179	,
    183	,
    188	,
    192	,
    196	,
    200	,
    204	,
    207	,
    211	,
    214	,
    218	,
    221	,
    224	,
    227	,
    230	,
    232	,
    235	,
    237	,
    239	,
    242	,
    243	,
    245	,
    247	,
    248	,
    250	,
    251	,
    252	,
    253	,
    254	,
    254	,
    255	,
    255	,
    255	,
    255	,
    255	,
    254	,
    254	,
    253	,
    252	,
    252	,
    250	,
    249	,
    248	,
    246	,
    245	,
    243	,
    241	,
    239	,
    236	,
    234	,
    231	,
    229	,
    226	,
    223	,
    220	,
    216	,
    213	,
    210	,
    206	,
    202	,
    198	,
    194	,
    190	,
    186	,
    182	,
    177	,
    173	,
    168	,
    163	,
    158	,
    153	,
    148	,
    143	,
    138	,
    133	,
    127	,
    122	,
    116	,
    111	,
    105	,
    99	,
    93	,
    88	,
    82	,
    76	,
    70	,
    64	,
    58	,
    52	,
    45	,
    39	,
    33	,
    27	,
    21	,
    14	,
    8	,
    2	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#elif (PWM_TABLE_VALUES == SQUARE)
uint8_t ui8_pwm_table_values [PWM_TABLE_VALUES_LEN] =
{
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#elif (PWM_TABLE_VALUES == SVM_LARGE)
uint8_t ui8_pwm_table_values [PWM_TABLE_VALUES_LEN] =
{
    7	,
    13	,
    20	,
    27	,
    33	,
    40	,
    47	,
    53	,
    60	,
    66	,
    73	,
    80	,
    86	,
    93	,
    99	,
    105	,
    112	,
    118	,
    125	,
    131	,
    137	,
    143	,
    149	,
    156	,
    162	,
    168	,
    174	,
    180	,
    185	,
    191	,
    193	,
    195	,
    197	,
    198	,
    200	,
    202	,
    203	,
    205	,
    206	,
    208	,
    209	,
    210	,
    211	,
    212	,
    213	,
    214	,
    215	,
    216	,
    217	,
    217	,
    218	,
    219	,
    219	,
    220	,
    220	,
    220	,
    221	,
    221	,
    221	,
    221	,
    221	,
    221	,
    221	,
    220	,
    220	,
    220	,
    219	,
    219	,
    218	,
    217	,
    217	,
    216	,
    215	,
    214	,
    213	,
    212	,
    211	,
    210	,
    209	,
    208	,
    206	,
    205	,
    203	,
    202	,
    200	,
    198	,
    197	,
    195	,
    193	,
    191	,
    193	,
    195	,
    197	,
    198	,
    200	,
    202	,
    203	,
    205	,
    206	,
    208	,
    209	,
    210	,
    211	,
    212	,
    213	,
    214	,
    215	,
    216	,
    217	,
    217	,
    218	,
    219	,
    219	,
    220	,
    220	,
    220	,
    221	,
    221	,
    221	,
    221	,
    221	,
    221	,
    221	,
    220	,
    220	,
    220	,
    219	,
    219	,
    218	,
    217	,
    217	,
    216	,
    215	,
    214	,
    213	,
    212	,
    211	,
    210	,
    209	,
    208	,
    206	,
    205	,
    203	,
    202	,
    200	,
    198	,
    197	,
    195	,
    193	,
    191	,
    185	,
    180	,
    174	,
    168	,
    162	,
    156	,
    149	,
    143	,
    137	,
    131	,
    125	,
    118	,
    112	,
    105	,
    99	,
    93	,
    86	,
    80	,
    73	,
    66	,
    60	,
    53	,
    47	,
    40	,
    33	,
    27	,
    20	,
    13	,
    7	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#endif

