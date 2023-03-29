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

/*
	IO Test:
		- Configures MPRJ lower 8-IO pins as outputs
		- Observes counter value through the MPRJ lower 8 IO pins (in the testbench)
*/

void main()
{


 	int a;
 	int b;
 	int c,d,e,f;
 


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

	// reg_spi_enable = 1;
	// reg_spimaster_cs = 0x10001;
	// reg_spimaster_control = 0x0801;

	// reg_spimaster_control = 0xa002;	// Enable, prescaler = 2,
                                        // connect to housekeeping SPI


		//reg_uart_enable = 1;
					   
	/* Apply configuration */
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);
	
	    // Configure LA probes [31:0], [127:64] as inputs to the cpu 
	// Configure LA probes [63:32] as outputs from the cpu
	reg_la0_oenb = reg_la0_iena = 0x00000000;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0x00000000;    // [63:32]
	reg_la2_oenb = reg_la2_iena = 0x00000000;    // [95:64]
	reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]
	
		// Flag start of the test 
		
 	
	
		// Flag start of the test 
	reg_mprj_datal = reg_mprj_datal | 0x00F00000; //Set 1 in GPIO port 20	|
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20	|1089 clk
	//1095 cloc cycles
	reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
		a = 0x0000FFFF;//  |
	b = 0xFFFF0000;//   |- 33 clk   (38635-37513)-1089
	//---------------test OR operator-------------
//init 37513

	c = a | b; //      |
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 38635
	d = a | b; 
	e = a | b; 
	f = a | b; 
// 4 instruction took =4392 (42994-37513)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 42994

	//---------------test OR operator-------------
	//---------------test AND operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 44093
	a = 0x0000FFFF;
	b = 0xFFFF0000;
	c = a & b;

	a = 0x03034F4F;
	b = 0x35623ABC;  
	c = a & b; 
	
	a = 0x56423ABC;
	b = 0x0304524F;
	c = a & b; 
	
	a = 0xFFFF1237;
	b = 0x9874FFFF;
	c = a & b; 
// 4 instruction took =5449 (50631-44093)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 50631

	//---------------test AND operator-------------
	//---------------test XOR operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 51730
	a = 0x0000FFFF;
	b = 0xFFFF0000;
	c = a ^ b;

	a = 0x03034F4F;
	b = 0x35623ABC;  
	c = a ^ b; 
	
	a = 0x56423ABC;
	b = 0x0304524F;
	c = a ^ b; 
	
	a = 0xFFFF1237;
	b = 0x9874FFFF;
	c = a ^ b; 
// 4 instruction took =4391 (57210-51730)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 51730

	//---------------test XOR operator-------------
	//---------------test NOT operator-------------
//init 58319
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20

	a = 0x0000FFFF;
	c = ~a;

	a = 0x03034F4F;  
	c = ~a; 
	
	a = 0x56423ABC;
	c = ~a; 
	
	a = 0xFFFF1237;
	c = ~a; 
// 4 instruction took =3293 (62701-58319)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 62701
	//---------------test NOT operator-------------
	//---------------test << operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 63800
	a = 0x0000FFFF;
	b = 0x0000001F;
	c = a << b;

	a = 0x03034F4F;
	b = 0x00000001; 
	c = a << b; 
	
	a = 0x56423ABC;
	b = 0x00000007;
	c = a << b; 
	
	a = 0xFFFF1237;
	b = 0x0000000A;
	c = a << b; 
// 4 instruction took =4398 (69287-63800)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 69287

	//---------------test << operator-------------
	//---------------test >> operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 70396
	a = 0x0000FFFF;
	b = 0x00000020;
	c = a >> b;

	a = 0x03034F4F;
	b = 0x00000001; 
	c = a >> b; 
	
	a = 0x56423ABC;
	b = 0x00000007;
	c = a >> b; 
	
	a = 0xFFFF1237;
	b = 0x0000000A;
	c = a >> b; 
// 4 instruction took =5461 (76946-70396)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 76946
	//---------------test >> operator-------------
	//---------------test + operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 78308
	a = 0x0000FFFF;
	b = 0x0000000F;
	c = a + b;

	a = 0x03034F4F;
	b = 0x00000002; 
	c = a + b; 
	
	a = 0x56423ABC;
	b = 0x00000007;
	c = a + b; 
	
	a = 0xFFFF1237;
	b = 0x0000000A;
	c = a + b; 
// 4 instruction took =4110 (83507-78308)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 83507
	//---------------test + operator-------------
	//---------------test - operator-------------
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
//init 84602
	a = 0x0000FFFF;
	b = 0x0000000F;
	c = a - b;

	a = 0x03034F4F;
	b = 0x00000002; 
	c = a - b; 
	
	a = 0x56423ABC;
	b = 0x00000007;
	c = a - b; 
	
	a = 0xFFFF1237;
	b = 0x0000000A;
	c = a - b; 
// 4 instruction took =4380 (90071-84602)-1089
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
//end 90071
	//---------------test - operator-------------
	
}

