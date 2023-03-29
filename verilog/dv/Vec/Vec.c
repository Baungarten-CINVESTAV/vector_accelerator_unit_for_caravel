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


	int c[4][4];
//////////////////////////////////////////////////////////////////////////////////
////////////////////////////	matrix 4 x 4	////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
	//################# HW matrix addition #########################	 
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xB000, 68 , 20 , 63 , 81 , 66 , 77 , 3 , 18);
	
	c[0][0] = reg_la0_data;
	c[0][1] = reg_la1_data;
	c[0][2] = reg_la2_data;
	c[0][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xB000, 75 , 50 , 54 , 166 , 120 , 87 , 137 , 198);
	
	c[1][0] = reg_la0_data;
	c[1][1] = reg_la1_data;
	c[1][2] = reg_la2_data;
	c[1][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xB000, 119 , 92 , 161 , 125 , 134 , 24 , 26 , 152);
	
	c[2][0] = reg_la0_data;
	c[2][1] = reg_la1_data;
	c[2][2] = reg_la2_data;
	c[2][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	

//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xB000, 160 , 152 , 200 , 53 , 173 , 79 , 194 , 11);
	
	c[3][0] = reg_la0_data;
	c[3][1] = reg_la1_data;
	c[3][2] = reg_la2_data;
	c[3][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	
	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)

	//################# element-wise Logical AND operator #########################	
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO 
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0x5000, 68 , 20 , 63 , 81 , 66 , 77 , 3 , 18);
	
	c[0][0] = reg_la0_data;
	c[0][1] = reg_la1_data;
	c[0][2] = reg_la2_data;
	c[0][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0x5000, 75 , 50 , 54 , 166 , 120 , 87 , 137 , 198);
	
	c[1][0] = reg_la0_data;
	c[1][1] = reg_la1_data;
	c[1][2] = reg_la2_data;
	c[1][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0x5000, 119 , 92 , 161 , 125 , 134 , 24 , 26 , 152);
	
	c[2][0] = reg_la0_data;
	c[2][1] = reg_la1_data;
	c[2][2] = reg_la2_data;
	c[2][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	

//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0x5000, 160 , 152 , 200 , 53 , 173 , 79 , 194 , 11);
	
	c[3][0] = reg_la0_data;
	c[3][1] = reg_la1_data;
	c[3][2] = reg_la2_data;
	c[3][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	
	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)	

	//################# element-wise Logical NOT operator #########################	
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO 
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data_1_Operand(0xA000, 68 , 20 , 63 , 81);
	
	c[0][0] = reg_la0_data;
	c[0][1] = reg_la1_data;
	c[0][2] = reg_la2_data;
	c[0][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data_1_Operand(0xA000, 75 , 50 , 54 , 166);
	
	c[1][0] = reg_la0_data;
	c[1][1] = reg_la1_data;
	c[1][2] = reg_la2_data;
	c[1][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data_1_Operand(0xA000, 119 , 92 , 161 , 125);
	
	c[2][0] = reg_la0_data;
	c[2][1] = reg_la1_data;
	c[2][2] = reg_la2_data;
	c[2][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	

//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data_1_Operand(0xA000, 160 , 152 , 200 , 53);
	
	c[3][0] = reg_la0_data;
	c[3][1] = reg_la1_data;
	c[3][2] = reg_la2_data;
	c[3][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	
	
	reg_mprj_datal = reg_mprj_datal | 0xD0000; //Set 1 in GPIO port 18 (RST), 19 (CE) & GPIO port 16 (Selec input data A)	
	
		//#################  Scalar Product	#########################	
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 all GPIO 
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xE000, 68 , 20 , 63 , 81 , 100 , 100 , 100 , 100);
	
	c[0][0] = reg_la0_data;
	c[0][1] = reg_la1_data;
	c[0][2] = reg_la2_data;
	c[0][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xE000, 75 , 50 , 54 , 166 , 100 , 100 , 100 , 100);
	
	c[1][0] = reg_la0_data;
	c[1][1] = reg_la1_data;
	c[1][2] = reg_la2_data;
	c[1][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)
//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xE000, 119 , 92 , 161 , 125 , 100 , 100 , 100 , 100);
	
	c[2][0] = reg_la0_data;
	c[2][1] = reg_la1_data;
	c[2][2] = reg_la2_data;
	c[2][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	

//Load_ALU_data(int inst, int num_1_a, int num_2_a, int num_3_a, int num_4_a, int num_1_b, int num_2_b, int num_3_b, int num_4_b);
	Load_ALU_data(0xE000, 160 , 152 , 200 , 53 , 100 , 100 , 100 , 100);
	
	c[3][0] = reg_la0_data;
	c[3][1] = reg_la1_data;
	c[3][2] = reg_la2_data;
	c[3][3] = reg_la3_data;
	reg_mprj_datal = reg_mprj_datal | 0x90000; //Set 1 in GPIO port 16 (Selec input data A) & GPIO port 19 (CE)	
	
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

