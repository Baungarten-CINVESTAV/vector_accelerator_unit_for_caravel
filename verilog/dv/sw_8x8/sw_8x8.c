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

typedef struct {
    int32_t real;
    int32_t imag;
} complex_t;

// Implement * operand using adds
int32_t multiply_with_adds(int32_t a, int32_t b) {
    int32_t result = 0;
    int32_t num1,num2;
    if(a>b){
    	num1 = a;
    	num2 = b;
    }
    else{
   	 num1 = b;
   	 num2 = a;
    }
    for (int i = 0; i == num2; i++) {
            result += num1;
    }
    return result;
}

// Multiply two complex numbers using custom multiplication function that uses adds
void complex_multiply_with_adds(complex_t *a, complex_t *b, complex_t *c) {
   	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
    	reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    c->real = multiply_with_adds(a->real, b->real) - multiply_with_adds(a->imag, b->imag);
    c->imag = multiply_with_adds(a->real, b->imag) + multiply_with_adds(a->imag, b->real);
}

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

	// reg_spi_enable = 1;
	// reg_spimaster_cs = 0x10001;
	// reg_spimaster_control = 0x0801;

	// reg_spimaster_control = 0xa002;	// Enable, prescaler = 2,
                                        // connect to housekeeping SPI

	// Connect the housekeeping SPI to the SPI master
	// so that the CSB line is not left floating.  This allows
	// all of the GPIO pins to be used for user functions.

	// Configure lower 8-IOs as user output
	// Observe counter value in the testbench
	reg_mprj_io_0 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_1 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_2 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_3 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_4 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_5 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_6 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_7 =  GPIO_MODE_USER_STD_OUTPUT;
	
	//------------Test SW instructions-----------------//
	//io_in[20] GPIO as control flag
	reg_mprj_io_20 =  GPIO_MODE_MGMT_STD_OUTPUT;
	/* Apply configuration */
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);
	
	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
	

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////	matrix 8 x 8	////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int A[8][8];
int B[8][8];
int C[8][8];
	//################# SW matrix addition #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 25;
A[0][1] = 140;
A[0][2] = 120;
A[0][3] = 141;
A[0][4] = 182;
A[0][5] = 13;
A[0][6] = 239;
A[0][7] = 123;
A[1][0] = 130;
A[1][1] = 137;
A[1][2] = 93;
A[1][3] = 124;
A[1][4] = 137;
A[1][5] = 244;
A[1][6] = 186;
A[1][7] = 127;
A[2][0] = 133;
A[2][1] = 105;
A[2][2] = 100;
A[2][3] = 34;
A[2][4] = 116;
A[2][5] = 122;
A[2][6] = 41;
A[2][7] = 127;
A[3][0] = 175;
A[3][1] = 154;
A[3][2] = 164;
A[3][3] = 202;
A[3][4] = 253;
A[3][5] = 13;
A[3][6] = 112;
A[3][7] = 108;
A[4][0] = 128;
A[4][1] = 229;
A[4][2] = 64;
A[4][3] = 51;
A[4][4] = 164;
A[4][5] = 140;
A[4][6] = 97;
A[4][7] = 18;
A[5][0] = 102;
A[5][1] = 242;
A[5][2] = 176;
A[5][3] = 212;
A[5][4] = 194;
A[5][5] = 216;
A[5][6] = 72;
A[5][7] = 136;
A[6][0] = 144;
A[6][1] = 206;
A[6][2] = 18;
A[6][3] = 114;
A[6][4] = 111;
A[6][5] = 254;
A[6][6] = 2;
A[6][7] = 29;
A[7][0] = 238;
A[7][1] = 230;
A[7][2] = 10;
A[7][3] = 130;
A[7][4] = 199;
A[7][5] = 38;
A[7][6] = 162;
A[7][7] = 237;

B[0][0] = 241;
B[0][1] = 84;
B[0][2] = 60;
B[0][3] = 190;
B[0][4] = 166;
B[0][5] = 197;
B[0][6] = 173;
B[0][7] = 44;
B[1][0] = 26;
B[1][1] = 207;
B[1][2] = 28;
B[1][3] = 165;
B[1][4] = 251;
B[1][5] = 167;
B[1][6] = 24;
B[1][7] = 74;
B[2][0] = 101;
B[2][1] = 32;
B[2][2] = 197;
B[2][3] = 55;
B[2][4] = 241;
B[2][5] = 220;
B[2][6] = 160;
B[2][7] = 44;
B[3][0] = 163;
B[3][1] = 129;
B[3][2] = 98;
B[3][3] = 97;
B[3][4] = 116;
B[3][5] = 149;
B[3][6] = 80;
B[3][7] = 148;
B[4][0] = 185;
B[4][1] = 187;
B[4][2] = 73;
B[4][3] = 198;
B[4][4] = 198;
B[4][5] = 80;
B[4][6] = 3;
B[4][7] = 64;
B[5][0] = 51;
B[5][1] = 86;
B[5][2] = 134;
B[5][3] = 74;
B[5][4] = 159;
B[5][5] = 153;
B[5][6] = 62;
B[5][7] = 119;
B[6][0] = 194;
B[6][1] = 247;
B[6][2] = 22;
B[6][3] = 239;
B[6][4] = 28;
B[6][5] = 53;
B[6][6] = 221;
B[6][7] = 122;
B[7][0] = 71;
B[7][1] = 89;
B[7][2] = 198;
B[7][3] = 197;
B[7][4] = 112;
B[7][5] = 41;
B[7][6] = 197;
B[7][7] = 148;

    // Add matrices
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 		//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 8; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------	
	//################# element-wise Logical AND operator #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 25;
A[0][1] = 140;
A[0][2] = 120;
A[0][3] = 141;
A[0][4] = 182;
A[0][5] = 13;
A[0][6] = 239;
A[0][7] = 123;
A[1][0] = 130;
A[1][1] = 137;
A[1][2] = 93;
A[1][3] = 124;
A[1][4] = 137;
A[1][5] = 244;
A[1][6] = 186;
A[1][7] = 127;
A[2][0] = 133;
A[2][1] = 105;
A[2][2] = 100;
A[2][3] = 34;
A[2][4] = 116;
A[2][5] = 122;
A[2][6] = 41;
A[2][7] = 127;
A[3][0] = 175;
A[3][1] = 154;
A[3][2] = 164;
A[3][3] = 202;
A[3][4] = 253;
A[3][5] = 13;
A[3][6] = 112;
A[3][7] = 108;
A[4][0] = 128;
A[4][1] = 229;
A[4][2] = 64;
A[4][3] = 51;
A[4][4] = 164;
A[4][5] = 140;
A[4][6] = 97;
A[4][7] = 18;
A[5][0] = 102;
A[5][1] = 242;
A[5][2] = 176;
A[5][3] = 212;
A[5][4] = 194;
A[5][5] = 216;
A[5][6] = 72;
A[5][7] = 136;
A[6][0] = 144;
A[6][1] = 206;
A[6][2] = 18;
A[6][3] = 114;
A[6][4] = 111;
A[6][5] = 254;
A[6][6] = 2;
A[6][7] = 29;
A[7][0] = 238;
A[7][1] = 230;
A[7][2] = 10;
A[7][3] = 130;
A[7][4] = 199;
A[7][5] = 38;
A[7][6] = 162;
A[7][7] = 237;

B[0][0] = 241;
B[0][1] = 84;
B[0][2] = 60;
B[0][3] = 190;
B[0][4] = 166;
B[0][5] = 197;
B[0][6] = 173;
B[0][7] = 44;
B[1][0] = 26;
B[1][1] = 207;
B[1][2] = 28;
B[1][3] = 165;
B[1][4] = 251;
B[1][5] = 167;
B[1][6] = 24;
B[1][7] = 74;
B[2][0] = 101;
B[2][1] = 32;
B[2][2] = 197;
B[2][3] = 55;
B[2][4] = 241;
B[2][5] = 220;
B[2][6] = 160;
B[2][7] = 44;
B[3][0] = 163;
B[3][1] = 129;
B[3][2] = 98;
B[3][3] = 97;
B[3][4] = 116;
B[3][5] = 149;
B[3][6] = 80;
B[3][7] = 148;
B[4][0] = 185;
B[4][1] = 187;
B[4][2] = 73;
B[4][3] = 198;
B[4][4] = 198;
B[4][5] = 80;
B[4][6] = 3;
B[4][7] = 64;
B[5][0] = 51;
B[5][1] = 86;
B[5][2] = 134;
B[5][3] = 74;
B[5][4] = 159;
B[5][5] = 153;
B[5][6] = 62;
B[5][7] = 119;
B[6][0] = 194;
B[6][1] = 247;
B[6][2] = 22;
B[6][3] = 239;
B[6][4] = 28;
B[6][5] = 53;
B[6][6] = 221;
B[6][7] = 122;
B[7][0] = 71;
B[7][1] = 89;
B[7][2] = 198;
B[7][3] = 197;
B[7][4] = 112;
B[7][5] = 41;
B[7][6] = 197;
B[7][7] = 148;

    // Add matrices
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C[i][j] = A[i][j] & B[i][j];
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 		//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 8; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------	
 	//################# element-wise Logical NOT operator #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 25;
A[0][1] = 140;
A[0][2] = 120;
A[0][3] = 141;
A[0][4] = 182;
A[0][5] = 13;
A[0][6] = 239;
A[0][7] = 123;
A[1][0] = 130;
A[1][1] = 137;
A[1][2] = 93;
A[1][3] = 124;
A[1][4] = 137;
A[1][5] = 244;
A[1][6] = 186;
A[1][7] = 127;
A[2][0] = 133;
A[2][1] = 105;
A[2][2] = 100;
A[2][3] = 34;
A[2][4] = 116;
A[2][5] = 122;
A[2][6] = 41;
A[2][7] = 127;
A[3][0] = 175;
A[3][1] = 154;
A[3][2] = 164;
A[3][3] = 202;
A[3][4] = 253;
A[3][5] = 13;
A[3][6] = 112;
A[3][7] = 108;
A[4][0] = 128;
A[4][1] = 229;
A[4][2] = 64;
A[4][3] = 51;
A[4][4] = 164;
A[4][5] = 140;
A[4][6] = 97;
A[4][7] = 18;
A[5][0] = 102;
A[5][1] = 242;
A[5][2] = 176;
A[5][3] = 212;
A[5][4] = 194;
A[5][5] = 216;
A[5][6] = 72;
A[5][7] = 136;
A[6][0] = 144;
A[6][1] = 206;
A[6][2] = 18;
A[6][3] = 114;
A[6][4] = 111;
A[6][5] = 254;
A[6][6] = 2;
A[6][7] = 29;
A[7][0] = 238;
A[7][1] = 230;
A[7][2] = 10;
A[7][3] = 130;
A[7][4] = 199;
A[7][5] = 38;
A[7][6] = 162;
A[7][7] = 237;

    // Add matrices
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C[i][j] = ~A[i][j];
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 		//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 8; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------			
 		
	//################# 	Scalar Product	   #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 25;
A[0][1] = 140;
A[0][2] = 120;
A[0][3] = 141;
A[0][4] = 182;
A[0][5] = 13;
A[0][6] = 239;
A[0][7] = 123;
A[1][0] = 130;
A[1][1] = 137;
A[1][2] = 93;
A[1][3] = 124;
A[1][4] = 137;
A[1][5] = 244;
A[1][6] = 186;
A[1][7] = 127;
A[2][0] = 133;
A[2][1] = 105;
A[2][2] = 100;
A[2][3] = 34;
A[2][4] = 116;
A[2][5] = 122;
A[2][6] = 41;
A[2][7] = 127;
A[3][0] = 175;
A[3][1] = 154;
A[3][2] = 164;
A[3][3] = 202;
A[3][4] = 253;
A[3][5] = 13;
A[3][6] = 112;
A[3][7] = 108;
A[4][0] = 128;
A[4][1] = 229;
A[4][2] = 64;
A[4][3] = 51;
A[4][4] = 164;
A[4][5] = 140;
A[4][6] = 97;
A[4][7] = 18;
A[5][0] = 102;
A[5][1] = 242;
A[5][2] = 176;
A[5][3] = 212;
A[5][4] = 194;
A[5][5] = 216;
A[5][6] = 72;
A[5][7] = 136;
A[6][0] = 144;
A[6][1] = 206;
A[6][2] = 18;
A[6][3] = 114;
A[6][4] = 111;
A[6][5] = 254;
A[6][6] = 2;
A[6][7] = 29;
A[7][0] = 238;
A[7][1] = 230;
A[7][2] = 10;
A[7][3] = 130;
A[7][4] = 199;
A[7][5] = 38;
A[7][6] = 162;
A[7][7] = 237;


    // Add matrices
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C[i][j] = multiply_with_adds(A[i][j], 100);
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 		//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 8; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------	 		

	
}

