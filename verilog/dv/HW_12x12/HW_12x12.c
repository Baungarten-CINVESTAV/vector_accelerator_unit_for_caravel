/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

// This include is relative to $CARAVEL_PATH (see Makefile)
#include <defs.h>
#include <stub.c>
//#include <vector_instructions.h>
void Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
void Load_ALU_data_1_Operand(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a);

/*
	IO Test:
		- Configures MPRJ lower 8-IO pins as outputs
		- Observes counter value through the MPRJ lower 8 IO pins (in the testbench)
*/

void main()
{
	/* 
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |

	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |
	
	 
	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |

	*/

	/* Set up the housekeeping SPI to be connected internally so	*/
	/* that external pin changes don't affect it.			*/
/*
	 reg_spi_enable = 1;
	 reg_spimaster_cs = 0x10001;
	 reg_spimaster_control = 0x0801;

	 reg_spimaster_control = 0xa002;	// Enable, prescaler = 2,*/
                                        // connect to housekeeping SPI

	// Connect the housekeeping SPI to the SPI master
	// so that the CSB line is not left floating.  This allows
	// all of the GPIO pins to be used for user functions.

	// Configure lower 8-IOs as user output
	// Observe counter value in the testbench
	//|31|30|29|28|_|27|26|25|24|_|23|22|21|20|_|19|18|17|16|_|15|14|13|12|_|11|10|9|8|_|7|6|5|4|_|3|2|1|0|
	//1_0000_0000_0000
//###################### sw ###############################################
//--------------------  Operation  --------------------------------
	reg_mprj_io_12 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL;/// mem dir = 0x2600003c
	reg_mprj_io_13 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL;/// mem dir = 0x26000040
	reg_mprj_io_14 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL;/// mem dir = 0x26000044
	reg_mprj_io_15 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL;/// mem dir = 0x26000048
//--------------------  i_operand_sel A or B selector  --------------------------------	
	reg_mprj_io_16 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL; /// mem dir = 0x2600004c
//--------------------  clk  --------------------------------	
	//reg_mprj_io_17 = GPIO_MODE_USER_STD_OUTPUT;
//--------------------  i_rst  --------------------------------	
	reg_mprj_io_18 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL; ///mem dir = 0x26000054
//--------------------  i_CE  --------------------------------	
	reg_mprj_io_19 = GPIO_MODE_MGMT_STD_BIDIRECTIONAL; 
//###################### sw ###############################################
//###################### Hw ###############################################
//--------------------  Underflow  --------------------------------   
        reg_mprj_io_11 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_9  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_8  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//--------------------  Exception  --------------------------------
        reg_mprj_io_7  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_5  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_4  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_3  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//--------------------  Overflow  --------------------------------
        reg_mprj_io_2  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_1  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_0  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//###################### Hw ###############################################

	/* Apply configuration */
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);


	int c[12][12];
//////////////////////////////////////////////////////////////////////////////////
////////////////////////////	matrix 12 x 12	////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
	//################# HW matrix addition #########################	 
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO
	Load_ALU_data(0xB000,165,109,19,193,218,251,139,71);
c[0][0] = reg_la0_data;
c[0][1] = reg_la0_data;
c[0][2] = reg_la0_data;
c[0][3] = reg_la0_data;


Load_ALU_data(0xB000,13,42,229,106,215,252,248,57);
c[0][4] = reg_la0_data;
c[0][5] = reg_la0_data;
c[0][6] = reg_la0_data;
c[0][7] = reg_la0_data;


Load_ALU_data(0xB000,25,132,181,0,172,27,196,20);
c[0][8] = reg_la0_data;
c[0][9] = reg_la0_data;
c[0][10] = reg_la0_data;
c[0][11] = reg_la0_data;


Load_ALU_data(0xB000,51,243,75,165,63,63,39,27);
c[1][0] = reg_la0_data;
c[1][1] = reg_la0_data;
c[1][2] = reg_la0_data;
c[1][3] = reg_la0_data;


Load_ALU_data(0xB000,71,115,176,75,154,221,120,253);
c[1][4] = reg_la0_data;
c[1][5] = reg_la0_data;
c[1][6] = reg_la0_data;
c[1][7] = reg_la0_data;


Load_ALU_data(0xB000,110,34,223,66,119,207,12,96);
c[1][8] = reg_la0_data;
c[1][9] = reg_la0_data;
c[1][10] = reg_la0_data;
c[1][11] = reg_la0_data;


Load_ALU_data(0xB000,122,202,25,37,198,91,244,194);
c[2][0] = reg_la0_data;
c[2][1] = reg_la0_data;
c[2][2] = reg_la0_data;
c[2][3] = reg_la0_data;


Load_ALU_data(0xB000,75,132,105,40,114,146,193,116);
c[2][4] = reg_la0_data;
c[2][5] = reg_la0_data;
c[2][6] = reg_la0_data;
c[2][7] = reg_la0_data;


Load_ALU_data(0xB000,87,212,125,174,36,149,80,214);
c[2][8] = reg_la0_data;
c[2][9] = reg_la0_data;
c[2][10] = reg_la0_data;
c[2][11] = reg_la0_data;


Load_ALU_data(0xB000,186,229,242,20,9,65,38,130);
c[3][0] = reg_la0_data;
c[3][1] = reg_la0_data;
c[3][2] = reg_la0_data;
c[3][3] = reg_la0_data;


Load_ALU_data(0xB000,170,20,158,110,20,155,42,227);
c[3][4] = reg_la0_data;
c[3][5] = reg_la0_data;
c[3][6] = reg_la0_data;
c[3][7] = reg_la0_data;


Load_ALU_data(0xB000,144,210,120,182,197,154,23,158);
c[3][8] = reg_la0_data;
c[3][9] = reg_la0_data;
c[3][10] = reg_la0_data;
c[3][11] = reg_la0_data;


Load_ALU_data(0xB000,242,70,129,10,186,93,217,113);
c[4][0] = reg_la0_data;
c[4][1] = reg_la0_data;
c[4][2] = reg_la0_data;
c[4][3] = reg_la0_data;


Load_ALU_data(0xB000,33,122,96,94,52,127,68,102);
c[4][4] = reg_la0_data;
c[4][5] = reg_la0_data;
c[4][6] = reg_la0_data;
c[4][7] = reg_la0_data;


Load_ALU_data(0xB000,34,186,14,225,146,164,16,10);
c[4][8] = reg_la0_data;
c[4][9] = reg_la0_data;
c[4][10] = reg_la0_data;
c[4][11] = reg_la0_data;


Load_ALU_data(0xB000,190,77,81,214,245,29,233,174);
c[5][0] = reg_la0_data;
c[5][1] = reg_la0_data;
c[5][2] = reg_la0_data;
c[5][3] = reg_la0_data;


Load_ALU_data(0xB000,252,54,135,153,26,31,145,116);
c[5][4] = reg_la0_data;
c[5][5] = reg_la0_data;
c[5][6] = reg_la0_data;
c[5][7] = reg_la0_data;


Load_ALU_data(0xB000,12,44,173,22,128,218,86,199);
c[5][8] = reg_la0_data;
c[5][9] = reg_la0_data;
c[5][10] = reg_la0_data;
c[5][11] = reg_la0_data;


Load_ALU_data(0xB000,165,24,32,194,117,50,106,116);
c[6][0] = reg_la0_data;
c[6][1] = reg_la0_data;
c[6][2] = reg_la0_data;
c[6][3] = reg_la0_data;


Load_ALU_data(0xB000,205,57,30,109,72,168,174,46);
c[6][4] = reg_la0_data;
c[6][5] = reg_la0_data;
c[6][6] = reg_la0_data;
c[6][7] = reg_la0_data;


Load_ALU_data(0xB000,115,187,166,130,90,151,62,29);
c[6][8] = reg_la0_data;
c[6][9] = reg_la0_data;
c[6][10] = reg_la0_data;
c[6][11] = reg_la0_data;


Load_ALU_data(0xB000,202,173,2,237,244,160,198,183);
c[7][0] = reg_la0_data;
c[7][1] = reg_la0_data;
c[7][2] = reg_la0_data;
c[7][3] = reg_la0_data;


Load_ALU_data(0xB000,131,211,26,251,237,5,228,185);
c[7][4] = reg_la0_data;
c[7][5] = reg_la0_data;
c[7][6] = reg_la0_data;
c[7][7] = reg_la0_data;


Load_ALU_data(0xB000,174,219,53,126,10,55,32,206);
c[7][8] = reg_la0_data;
c[7][9] = reg_la0_data;
c[7][10] = reg_la0_data;
c[7][11] = reg_la0_data;


Load_ALU_data(0xB000,112,39,226,35,55,214,251,104);
c[8][0] = reg_la0_data;
c[8][1] = reg_la0_data;
c[8][2] = reg_la0_data;
c[8][3] = reg_la0_data;


Load_ALU_data(0xB000,73,185,60,105,108,93,215,206);
c[8][4] = reg_la0_data;
c[8][5] = reg_la0_data;
c[8][6] = reg_la0_data;
c[8][7] = reg_la0_data;


Load_ALU_data(0xB000,232,117,177,86,160,159,178,63);
c[8][8] = reg_la0_data;
c[8][9] = reg_la0_data;
c[8][10] = reg_la0_data;
c[8][11] = reg_la0_data;


Load_ALU_data(0xB000,136,88,105,176,142,92,20,246);
c[9][0] = reg_la0_data;
c[9][1] = reg_la0_data;
c[9][2] = reg_la0_data;
c[9][3] = reg_la0_data;


Load_ALU_data(0xB000,75,150,184,223,67,29,139,175);
c[9][4] = reg_la0_data;
c[9][5] = reg_la0_data;
c[9][6] = reg_la0_data;
c[9][7] = reg_la0_data;


Load_ALU_data(0xB000,51,8,247,121,46,45,232,125);
c[9][8] = reg_la0_data;
c[9][9] = reg_la0_data;
c[9][10] = reg_la0_data;
c[9][11] = reg_la0_data;


Load_ALU_data(0xB000,122,182,16,38,90,169,31,219);
c[10][0] = reg_la0_data;
c[10][1] = reg_la0_data;
c[10][2] = reg_la0_data;
c[10][3] = reg_la0_data;


Load_ALU_data(0xB000,22,156,59,130,192,76,227,127);
c[10][4] = reg_la0_data;
c[10][5] = reg_la0_data;
c[10][6] = reg_la0_data;
c[10][7] = reg_la0_data;


Load_ALU_data(0xB000,81,207,162,157,96,14,64,33);
c[10][8] = reg_la0_data;
c[10][9] = reg_la0_data;
c[10][10] = reg_la0_data;
c[10][11] = reg_la0_data;


Load_ALU_data(0xB000,167,82,106,154,254,173,44,56);
c[11][0] = reg_la0_data;
c[11][1] = reg_la0_data;
c[11][2] = reg_la0_data;
c[11][3] = reg_la0_data;


Load_ALU_data(0xB000,5,133,171,36,189,201,135,71);
c[11][4] = reg_la0_data;
c[11][5] = reg_la0_data;
c[11][6] = reg_la0_data;
c[11][7] = reg_la0_data;


Load_ALU_data(0xB000,207,123,112,197,125,246,123,3);
c[11][8] = reg_la0_data;
c[11][9] = reg_la0_data;
c[11][10] = reg_la0_data;
c[11][11] = reg_la0_data;



	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)

	//################# HW element-wise Logical AND operator #########################		 
		reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO
		
	Load_ALU_data(0x5000,165,109,19,193,218,251,139,71);
c[0][0] = reg_la0_data;
c[0][1] = reg_la0_data;
c[0][2] = reg_la0_data;
c[0][3] = reg_la0_data;


Load_ALU_data(0x5000,13,42,229,106,215,252,248,57);
c[0][4] = reg_la0_data;
c[0][5] = reg_la0_data;
c[0][6] = reg_la0_data;
c[0][7] = reg_la0_data;


Load_ALU_data(0x5000,25,132,181,0,172,27,196,20);
c[0][8] = reg_la0_data;
c[0][9] = reg_la0_data;
c[0][10] = reg_la0_data;
c[0][11] = reg_la0_data;


Load_ALU_data(0x5000,51,243,75,165,63,63,39,27);
c[1][0] = reg_la0_data;
c[1][1] = reg_la0_data;
c[1][2] = reg_la0_data;
c[1][3] = reg_la0_data;


Load_ALU_data(0x5000,71,115,176,75,154,221,120,253);
c[1][4] = reg_la0_data;
c[1][5] = reg_la0_data;
c[1][6] = reg_la0_data;
c[1][7] = reg_la0_data;


Load_ALU_data(0x5000,110,34,223,66,119,207,12,96);
c[1][8] = reg_la0_data;
c[1][9] = reg_la0_data;
c[1][10] = reg_la0_data;
c[1][11] = reg_la0_data;


Load_ALU_data(0x5000,122,202,25,37,198,91,244,194);
c[2][0] = reg_la0_data;
c[2][1] = reg_la0_data;
c[2][2] = reg_la0_data;
c[2][3] = reg_la0_data;


Load_ALU_data(0x5000,75,132,105,40,114,146,193,116);
c[2][4] = reg_la0_data;
c[2][5] = reg_la0_data;
c[2][6] = reg_la0_data;
c[2][7] = reg_la0_data;


Load_ALU_data(0x5000,87,212,125,174,36,149,80,214);
c[2][8] = reg_la0_data;
c[2][9] = reg_la0_data;
c[2][10] = reg_la0_data;
c[2][11] = reg_la0_data;


Load_ALU_data(0x5000,186,229,242,20,9,65,38,130);
c[3][0] = reg_la0_data;
c[3][1] = reg_la0_data;
c[3][2] = reg_la0_data;
c[3][3] = reg_la0_data;


Load_ALU_data(0x5000,170,20,158,110,20,155,42,227);
c[3][4] = reg_la0_data;
c[3][5] = reg_la0_data;
c[3][6] = reg_la0_data;
c[3][7] = reg_la0_data;


Load_ALU_data(0x5000,144,210,120,182,197,154,23,158);
c[3][8] = reg_la0_data;
c[3][9] = reg_la0_data;
c[3][10] = reg_la0_data;
c[3][11] = reg_la0_data;


Load_ALU_data(0x5000,242,70,129,10,186,93,217,113);
c[4][0] = reg_la0_data;
c[4][1] = reg_la0_data;
c[4][2] = reg_la0_data;
c[4][3] = reg_la0_data;


Load_ALU_data(0x5000,33,122,96,94,52,127,68,102);
c[4][4] = reg_la0_data;
c[4][5] = reg_la0_data;
c[4][6] = reg_la0_data;
c[4][7] = reg_la0_data;


Load_ALU_data(0x5000,34,186,14,225,146,164,16,10);
c[4][8] = reg_la0_data;
c[4][9] = reg_la0_data;
c[4][10] = reg_la0_data;
c[4][11] = reg_la0_data;


Load_ALU_data(0x5000,190,77,81,214,245,29,233,174);
c[5][0] = reg_la0_data;
c[5][1] = reg_la0_data;
c[5][2] = reg_la0_data;
c[5][3] = reg_la0_data;


Load_ALU_data(0x5000,252,54,135,153,26,31,145,116);
c[5][4] = reg_la0_data;
c[5][5] = reg_la0_data;
c[5][6] = reg_la0_data;
c[5][7] = reg_la0_data;


Load_ALU_data(0x5000,12,44,173,22,128,218,86,199);
c[5][8] = reg_la0_data;
c[5][9] = reg_la0_data;
c[5][10] = reg_la0_data;
c[5][11] = reg_la0_data;


Load_ALU_data(0x5000,165,24,32,194,117,50,106,116);
c[6][0] = reg_la0_data;
c[6][1] = reg_la0_data;
c[6][2] = reg_la0_data;
c[6][3] = reg_la0_data;


Load_ALU_data(0x5000,205,57,30,109,72,168,174,46);
c[6][4] = reg_la0_data;
c[6][5] = reg_la0_data;
c[6][6] = reg_la0_data;
c[6][7] = reg_la0_data;


Load_ALU_data(0x5000,115,187,166,130,90,151,62,29);
c[6][8] = reg_la0_data;
c[6][9] = reg_la0_data;
c[6][10] = reg_la0_data;
c[6][11] = reg_la0_data;


Load_ALU_data(0x5000,202,173,2,237,244,160,198,183);
c[7][0] = reg_la0_data;
c[7][1] = reg_la0_data;
c[7][2] = reg_la0_data;
c[7][3] = reg_la0_data;


Load_ALU_data(0x5000,131,211,26,251,237,5,228,185);
c[7][4] = reg_la0_data;
c[7][5] = reg_la0_data;
c[7][6] = reg_la0_data;
c[7][7] = reg_la0_data;


Load_ALU_data(0x5000,174,219,53,126,10,55,32,206);
c[7][8] = reg_la0_data;
c[7][9] = reg_la0_data;
c[7][10] = reg_la0_data;
c[7][11] = reg_la0_data;


Load_ALU_data(0x5000,112,39,226,35,55,214,251,104);
c[8][0] = reg_la0_data;
c[8][1] = reg_la0_data;
c[8][2] = reg_la0_data;
c[8][3] = reg_la0_data;


Load_ALU_data(0x5000,73,185,60,105,108,93,215,206);
c[8][4] = reg_la0_data;
c[8][5] = reg_la0_data;
c[8][6] = reg_la0_data;
c[8][7] = reg_la0_data;


Load_ALU_data(0x5000,232,117,177,86,160,159,178,63);
c[8][8] = reg_la0_data;
c[8][9] = reg_la0_data;
c[8][10] = reg_la0_data;
c[8][11] = reg_la0_data;


Load_ALU_data(0x5000,136,88,105,176,142,92,20,246);
c[9][0] = reg_la0_data;
c[9][1] = reg_la0_data;
c[9][2] = reg_la0_data;
c[9][3] = reg_la0_data;


Load_ALU_data(0x5000,75,150,184,223,67,29,139,175);
c[9][4] = reg_la0_data;
c[9][5] = reg_la0_data;
c[9][6] = reg_la0_data;
c[9][7] = reg_la0_data;


Load_ALU_data(0x5000,51,8,247,121,46,45,232,125);
c[9][8] = reg_la0_data;
c[9][9] = reg_la0_data;
c[9][10] = reg_la0_data;
c[9][11] = reg_la0_data;


Load_ALU_data(0x5000,122,182,16,38,90,169,31,219);
c[10][0] = reg_la0_data;
c[10][1] = reg_la0_data;
c[10][2] = reg_la0_data;
c[10][3] = reg_la0_data;


Load_ALU_data(0x5000,22,156,59,130,192,76,227,127);
c[10][4] = reg_la0_data;
c[10][5] = reg_la0_data;
c[10][6] = reg_la0_data;
c[10][7] = reg_la0_data;


Load_ALU_data(0x5000,81,207,162,157,96,14,64,33);
c[10][8] = reg_la0_data;
c[10][9] = reg_la0_data;
c[10][10] = reg_la0_data;
c[10][11] = reg_la0_data;


Load_ALU_data(0x5000,167,82,106,154,254,173,44,56);
c[11][0] = reg_la0_data;
c[11][1] = reg_la0_data;
c[11][2] = reg_la0_data;
c[11][3] = reg_la0_data;


Load_ALU_data(0x5000,5,133,171,36,189,201,135,71);
c[11][4] = reg_la0_data;
c[11][5] = reg_la0_data;
c[11][6] = reg_la0_data;
c[11][7] = reg_la0_data;


Load_ALU_data(0x5000,207,123,112,197,125,246,123,3);
c[11][8] = reg_la0_data;
c[11][9] = reg_la0_data;
c[11][10] = reg_la0_data;
c[11][11] = reg_la0_data;



	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)

	//################# element-wise Logical NOT operator #########################	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO
			
	Load_ALU_data_1_Operand(0xA000,165,109,19,193);
c[0][0] = reg_la0_data;
c[0][1] = reg_la0_data;
c[0][2] = reg_la0_data;
c[0][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,13,42,229,106);
c[0][4] = reg_la0_data;
c[0][5] = reg_la0_data;
c[0][6] = reg_la0_data;
c[0][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,25,132,181,0);
c[0][8] = reg_la0_data;
c[0][9] = reg_la0_data;
c[0][10] = reg_la0_data;
c[0][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,51,243,75,165);
c[1][0] = reg_la0_data;
c[1][1] = reg_la0_data;
c[1][2] = reg_la0_data;
c[1][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,71,115,176,75);
c[1][4] = reg_la0_data;
c[1][5] = reg_la0_data;
c[1][6] = reg_la0_data;
c[1][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,110,34,223,66);
c[1][8] = reg_la0_data;
c[1][9] = reg_la0_data;
c[1][10] = reg_la0_data;
c[1][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,122,202,25,37);
c[2][0] = reg_la0_data;
c[2][1] = reg_la0_data;
c[2][2] = reg_la0_data;
c[2][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,75,132,105,40);
c[2][4] = reg_la0_data;
c[2][5] = reg_la0_data;
c[2][6] = reg_la0_data;
c[2][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,87,212,125,174);
c[2][8] = reg_la0_data;
c[2][9] = reg_la0_data;
c[2][10] = reg_la0_data;
c[2][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,186,229,242,20);
c[3][0] = reg_la0_data;
c[3][1] = reg_la0_data;
c[3][2] = reg_la0_data;
c[3][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,170,20,158,110);
c[3][4] = reg_la0_data;
c[3][5] = reg_la0_data;
c[3][6] = reg_la0_data;
c[3][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,144,210,120,182);
c[3][8] = reg_la0_data;
c[3][9] = reg_la0_data;
c[3][10] = reg_la0_data;
c[3][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,242,70,129,10);
c[4][0] = reg_la0_data;
c[4][1] = reg_la0_data;
c[4][2] = reg_la0_data;
c[4][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,33,122,96,94);
c[4][4] = reg_la0_data;
c[4][5] = reg_la0_data;
c[4][6] = reg_la0_data;
c[4][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,34,186,14,225);
c[4][8] = reg_la0_data;
c[4][9] = reg_la0_data;
c[4][10] = reg_la0_data;
c[4][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,190,77,81,214);
c[5][0] = reg_la0_data;
c[5][1] = reg_la0_data;
c[5][2] = reg_la0_data;
c[5][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,252,54,135,153);
c[5][4] = reg_la0_data;
c[5][5] = reg_la0_data;
c[5][6] = reg_la0_data;
c[5][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,12,44,173,22);
c[5][8] = reg_la0_data;
c[5][9] = reg_la0_data;
c[5][10] = reg_la0_data;
c[5][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,165,24,32,194);
c[6][0] = reg_la0_data;
c[6][1] = reg_la0_data;
c[6][2] = reg_la0_data;
c[6][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,205,57,30,109);
c[6][4] = reg_la0_data;
c[6][5] = reg_la0_data;
c[6][6] = reg_la0_data;
c[6][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,115,187,166,130);
c[6][8] = reg_la0_data;
c[6][9] = reg_la0_data;
c[6][10] = reg_la0_data;
c[6][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,202,173,2,237);
c[7][0] = reg_la0_data;
c[7][1] = reg_la0_data;
c[7][2] = reg_la0_data;
c[7][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,131,211,26,251);
c[7][4] = reg_la0_data;
c[7][5] = reg_la0_data;
c[7][6] = reg_la0_data;
c[7][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,174,219,53,126);
c[7][8] = reg_la0_data;
c[7][9] = reg_la0_data;
c[7][10] = reg_la0_data;
c[7][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,112,39,226,35);
c[8][0] = reg_la0_data;
c[8][1] = reg_la0_data;
c[8][2] = reg_la0_data;
c[8][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,73,185,60,105);
c[8][4] = reg_la0_data;
c[8][5] = reg_la0_data;
c[8][6] = reg_la0_data;
c[8][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,232 , 117 , 177 , 86);
c[8][8] = reg_la0_data;
c[8][9] = reg_la0_data;
c[8][10] = reg_la0_data;
c[8][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,136 , 88 , 105 , 176 );
c[9][0] = reg_la0_data;
c[9][1] = reg_la0_data;
c[9][2] = reg_la0_data;
c[9][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,75 , 150 , 184 , 223);
c[9][4] = reg_la0_data;
c[9][5] = reg_la0_data;
c[9][6] = reg_la0_data;
c[9][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,51,8,247,121);
c[9][8] = reg_la0_data;
c[9][9] = reg_la0_data;
c[9][10] = reg_la0_data;
c[9][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,122,182,16,38);
c[10][0] = reg_la0_data;
c[10][1] = reg_la0_data;
c[10][2] = reg_la0_data;
c[10][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,22,156,59,130);
c[10][4] = reg_la0_data;
c[10][5] = reg_la0_data;
c[10][6] = reg_la0_data;
c[10][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,81,207,162,157);
c[10][8] = reg_la0_data;
c[10][9] = reg_la0_data;
c[10][10] = reg_la0_data;
c[10][11] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,167,82,106,154);
c[11][0] = reg_la0_data;
c[11][1] = reg_la0_data;
c[11][2] = reg_la0_data;
c[11][3] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,5,133,171,36);
c[11][4] = reg_la0_data;
c[11][5] = reg_la0_data;
c[11][6] = reg_la0_data;
c[11][7] = reg_la0_data;


Load_ALU_data_1_Operand(0xA000,207,123,112,197);
c[11][8] = reg_la0_data;
c[11][9] = reg_la0_data;
c[11][10] = reg_la0_data;
c[11][11] = reg_la0_data;



	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)	
	
		//#################  Scalar Product	#########################	 
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO

			Load_ALU_data(0xE000,165,109,19,193,100,100,100,100);
c[0][0] = reg_la0_data;
c[0][1] = reg_la0_data;
c[0][2] = reg_la0_data;
c[0][3] = reg_la0_data;


Load_ALU_data(0xE000,13,42,229,106,100,100,100,100);
c[0][4] = reg_la0_data;
c[0][5] = reg_la0_data;
c[0][6] = reg_la0_data;
c[0][7] = reg_la0_data;


Load_ALU_data(0xE000,25,132,181,0,100,100,100,100);
c[0][8] = reg_la0_data;
c[0][9] = reg_la0_data;
c[0][10] = reg_la0_data;
c[0][11] = reg_la0_data;


Load_ALU_data(0xE000,51,243,75,165,100,100,100,100);
c[1][0] = reg_la0_data;
c[1][1] = reg_la0_data;
c[1][2] = reg_la0_data;
c[1][3] = reg_la0_data;


Load_ALU_data(0xE000,71,115,176,75,100,100,100,100);
c[1][4] = reg_la0_data;
c[1][5] = reg_la0_data;
c[1][6] = reg_la0_data;
c[1][7] = reg_la0_data;


Load_ALU_data(0xE000,110,34,223,66,100,100,100,100);
c[1][8] = reg_la0_data;
c[1][9] = reg_la0_data;
c[1][10] = reg_la0_data;
c[1][11] = reg_la0_data;


Load_ALU_data(0xE000,122,202,25,37,100,100,100,100);
c[2][0] = reg_la0_data;
c[2][1] = reg_la0_data;
c[2][2] = reg_la0_data;
c[2][3] = reg_la0_data;


Load_ALU_data(0xE000,75,132,105,40,100,100,100,100);
c[2][4] = reg_la0_data;
c[2][5] = reg_la0_data;
c[2][6] = reg_la0_data;
c[2][7] = reg_la0_data;


Load_ALU_data(0xE000,87,212,125,174,100,100,100,100);
c[2][8] = reg_la0_data;
c[2][9] = reg_la0_data;
c[2][10] = reg_la0_data;
c[2][11] = reg_la0_data;


Load_ALU_data(0xE000,186,229,242,20,100,100,100,100);
c[3][0] = reg_la0_data;
c[3][1] = reg_la0_data;
c[3][2] = reg_la0_data;
c[3][3] = reg_la0_data;


Load_ALU_data(0xE000,170,20,158,110,100,100,100,100);
c[3][4] = reg_la0_data;
c[3][5] = reg_la0_data;
c[3][6] = reg_la0_data;
c[3][7] = reg_la0_data;


Load_ALU_data(0xE000,144,210,120,182,100,100,100,100);
c[3][8] = reg_la0_data;
c[3][9] = reg_la0_data;
c[3][10] = reg_la0_data;
c[3][11] = reg_la0_data;


Load_ALU_data(0xE000,242,70,129,10,100,100,100,100);
c[4][0] = reg_la0_data;
c[4][1] = reg_la0_data;
c[4][2] = reg_la0_data;
c[4][3] = reg_la0_data;


Load_ALU_data(0xE000,33,122,96,94,100,100,100,100);
c[4][4] = reg_la0_data;
c[4][5] = reg_la0_data;
c[4][6] = reg_la0_data;
c[4][7] = reg_la0_data;


Load_ALU_data(0xE000,34,186,14,225,100,100,100,100);
c[4][8] = reg_la0_data;
c[4][9] = reg_la0_data;
c[4][10] = reg_la0_data;
c[4][11] = reg_la0_data;


Load_ALU_data(0xE000,190,77,81,214,100,100,100,100);
c[5][0] = reg_la0_data;
c[5][1] = reg_la0_data;
c[5][2] = reg_la0_data;
c[5][3] = reg_la0_data;


Load_ALU_data(0xE000,252,54,135,153,100,100,100,100);
c[5][4] = reg_la0_data;
c[5][5] = reg_la0_data;
c[5][6] = reg_la0_data;
c[5][7] = reg_la0_data;


Load_ALU_data(0xE000,12,44,173,22,100,100,100,100);
c[5][8] = reg_la0_data;
c[5][9] = reg_la0_data;
c[5][10] = reg_la0_data;
c[5][11] = reg_la0_data;


Load_ALU_data(0xE000,165,24,32,194,100,100,100,100);
c[6][0] = reg_la0_data;
c[6][1] = reg_la0_data;
c[6][2] = reg_la0_data;
c[6][3] = reg_la0_data;


Load_ALU_data(0xE000,205,57,30,109,100,100,100,100);
c[6][4] = reg_la0_data;
c[6][5] = reg_la0_data;
c[6][6] = reg_la0_data;
c[6][7] = reg_la0_data;


Load_ALU_data(0xE000,115,187,166,130,100,100,100,100);
c[6][8] = reg_la0_data;
c[6][9] = reg_la0_data;
c[6][10] = reg_la0_data;
c[6][11] = reg_la0_data;


Load_ALU_data(0xE000,202,173,2,237,100,100,100,100);
c[7][0] = reg_la0_data;
c[7][1] = reg_la0_data;
c[7][2] = reg_la0_data;
c[7][3] = reg_la0_data;


Load_ALU_data(0xE000,131,211,26,251,100,100,100,100);
c[7][4] = reg_la0_data;
c[7][5] = reg_la0_data;
c[7][6] = reg_la0_data;
c[7][7] = reg_la0_data;


Load_ALU_data(0xE000,174,219,53,126,100,100,100,100);
c[7][8] = reg_la0_data;
c[7][9] = reg_la0_data;
c[7][10] = reg_la0_data;
c[7][11] = reg_la0_data;


Load_ALU_data(0xE000,112,39,226,35,100,100,100,100);
c[8][0] = reg_la0_data;
c[8][1] = reg_la0_data;
c[8][2] = reg_la0_data;
c[8][3] = reg_la0_data;


Load_ALU_data(0xE000,73,185,60,105,100,100,100,100);
c[8][4] = reg_la0_data;
c[8][5] = reg_la0_data;
c[8][6] = reg_la0_data;
c[8][7] = reg_la0_data;


Load_ALU_data(0xE000,232 , 117 , 177 , 86,100,100,100,100);
c[8][8] = reg_la0_data;
c[8][9] = reg_la0_data;
c[8][10] = reg_la0_data;
c[8][11] = reg_la0_data;


Load_ALU_data(0xE000,136 , 88 , 105 , 176,100,100,100,100);
c[9][0] = reg_la0_data;
c[9][1] = reg_la0_data;
c[9][2] = reg_la0_data;
c[9][3] = reg_la0_data;


Load_ALU_data(0xE000,75 , 150 , 184 , 223,100,100,100,100);
c[9][4] = reg_la0_data;
c[9][5] = reg_la0_data;
c[9][6] = reg_la0_data;
c[9][7] = reg_la0_data;


Load_ALU_data(0xE000,51,8,247,121,100,100,100,100);
c[9][8] = reg_la0_data;
c[9][9] = reg_la0_data;
c[9][10] = reg_la0_data;
c[9][11] = reg_la0_data;


Load_ALU_data(0xE000,122,182,16,38,100,100,100,100);
c[10][0] = reg_la0_data;
c[10][1] = reg_la0_data;
c[10][2] = reg_la0_data;
c[10][3] = reg_la0_data;


Load_ALU_data(0xE000,22,156,59,130,100,100,100,100);
c[10][4] = reg_la0_data;
c[10][5] = reg_la0_data;
c[10][6] = reg_la0_data;
c[10][7] = reg_la0_data;


Load_ALU_data(0xE000,81,207,162,157,100,100,100,100);
c[10][8] = reg_la0_data;
c[10][9] = reg_la0_data;
c[10][10] = reg_la0_data;
c[10][11] = reg_la0_data;


Load_ALU_data(0xE000,167,82,106,154,100,100,100,100);
c[11][0] = reg_la0_data;
c[11][1] = reg_la0_data;
c[11][2] = reg_la0_data;
c[11][3] = reg_la0_data;


Load_ALU_data(0xE000,5,133,171,36,100,100,100,100);
c[11][4] = reg_la0_data;
c[11][5] = reg_la0_data;
c[11][6] = reg_la0_data;
c[11][7] = reg_la0_data;


Load_ALU_data(0xE000,207,123,112,197,100,100,100,100);
c[11][8] = reg_la0_data;
c[11][9] = reg_la0_data;
c[11][10] = reg_la0_data;
c[11][11] = reg_la0_data;



	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)	
	


}


void Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b){
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
	
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE) 
	
	reg_la0_data = num_1_a;
	reg_la1_data = num_2_a;
	reg_la2_data = num_3_a;
	reg_la3_data = num_4_a;
	
	reg_mprj_datal = reg_mprj_datal & 0xEFFFF; //Set 0 in GPIO port 16 (Selec input data B)
	
 	reg_la0_data = num_1_b;
	reg_la1_data = num_2_b;
	reg_la2_data = num_3_b;
	reg_la3_data = num_4_b;
	
	reg_mprj_datal = reg_mprj_datal | inst; //Set the operator 
	reg_mprj_datal = reg_mprj_datal & 0x7FFFF; //Set 0 GPIO port 19 (CE)
	reg_la0_oenb = 0x00000000;    // [31:0]
	reg_la1_oenb = 0x00000000;    // [63:32]
	reg_la2_oenb = 0x00000000;    // [95:64]
	reg_la3_oenb  = 0x00000000;    // [127:96]
};

void Load_ALU_data_1_Operand(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a){
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
	
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE) 
	
	reg_la0_data = num_1_a;
	reg_la1_data = num_2_a;
	reg_la2_data = num_3_a;
	reg_la3_data = num_4_a;
	
	reg_mprj_datal = reg_mprj_datal | inst; //Set the operator 
	reg_mprj_datal = reg_mprj_datal & 0x7FFFF; //Set 0 GPIO port 19 (CE)
	reg_la0_oenb = 0x00000000;    // [31:0]
	reg_la1_oenb = 0x00000000;    // [63:32]
	reg_la2_oenb = 0x00000000;    // [95:64]
	reg_la3_oenb  = 0x00000000;    // [127:96]
};

