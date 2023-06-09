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
////////////////////////////	matrix 12 x 12	////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int A[12][12];
int B[12][12];
int C[12][12];
	//################# SW matrix addition #########################
//Start
/*
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 165;
A[0][1] = 109;
A[0][2] = 19;
A[0][3] = 193;
A[0][4] = 13;
A[0][5] = 42;
A[0][6] = 229;
A[0][7] = 106;
A[0][8] = 25;
A[0][9] = 132;
A[0][10] = 181;
A[0][11] = 0;
A[1][0] = 51;
A[1][1] = 243;
A[1][2] = 75;
A[1][3] = 165;
A[1][4] = 71;
A[1][5] = 115;
A[1][6] = 176;
A[1][7] = 75;
A[1][8] = 110;
A[1][9] = 34;
A[1][10] = 223;
A[1][11] = 66;
A[2][0] = 122;
A[2][1] = 202;
A[2][2] = 25;
A[2][3] = 37;
A[2][4] = 75;
A[2][5] = 132;
A[2][6] = 105;
A[2][7] = 40;
A[2][8] = 87;
A[2][9] = 212;
A[2][10] = 125;
A[2][11] = 174;
A[3][0] = 186;
A[3][1] = 229;
A[3][2] = 242;
A[3][3] = 20;
A[3][4] = 170;
A[3][5] = 20;
A[3][6] = 158;
A[3][7] = 110;
A[3][8] = 144;
A[3][9] = 210;
A[3][10] = 120;
A[3][11] = 182;
A[4][0] = 242;
A[4][1] = 70;
A[4][2] = 129;
A[4][3] = 10;
A[4][4] = 33;
A[4][5] = 122;
A[4][6] = 96;
A[4][7] = 94;
A[4][8] = 34;
A[4][9] = 186;
A[4][10] = 14;
A[4][11] = 225;
A[5][0] = 190;
A[5][1] = 77;
A[5][2] = 81;
A[5][3] = 214;
A[5][4] = 252;
A[5][5] = 54;
A[5][6] = 135;
A[5][7] = 153;
A[5][8] = 12;
A[5][9] = 44;
A[5][10] = 173;
A[5][11] = 22;
A[6][0] = 165;
A[6][1] = 24;
A[6][2] = 32;
A[6][3] = 194;
A[6][4] = 205;
A[6][5] = 57;
A[6][6] = 30;
A[6][7] = 109;
A[6][8] = 115;
A[6][9] = 187;
A[6][10] = 166;
A[6][11] = 130;
A[7][0] = 202;
A[7][1] = 173;
A[7][2] = 2;
A[7][3] = 237;
A[7][4] = 131;
A[7][5] = 211;
A[7][6] = 26;
A[7][7] = 251;
A[7][8] = 174;
A[7][9] = 219;
A[7][10] = 53;
A[7][11] = 126;
A[8][0] = 112;
A[8][1] = 39;
A[8][2] = 226;
A[8][3] = 35;
A[8][4] = 73;
A[8][5] = 185;
A[8][6] = 60;
A[8][7] = 105;
A[8][8] = 232;
A[8][9] = 117;
A[8][10] = 177;
A[8][11] = 86;
A[9][0] = 136;
A[9][1] = 88;
A[9][2] = 105;
A[9][3] = 176;
A[9][4] = 75;
A[9][5] = 150;
A[9][6] = 184;
A[9][7] = 223;
A[9][8] = 51;
A[9][9] = 8;
A[9][10] = 247;
A[9][11] = 121;
A[10][0] = 122;
A[10][1] = 182;
A[10][2] = 16;
A[10][3] = 38;
A[10][4] = 22;
A[10][5] = 156;
A[10][6] = 59;
A[10][7] = 130;
A[10][8] = 81;
A[10][9] = 207;
A[10][10] = 162;
A[10][11] = 157;
A[11][0] = 167;
A[11][1] = 82;
A[11][2] = 106;
A[11][3] = 154;
A[11][4] = 5;
A[11][5] = 133;
A[11][6] = 171;
A[11][7] = 36;
A[11][8] = 207;
A[11][9] = 123;
A[11][10] = 112;
A[11][11] = 197;

B[0][0] = 218;
B[0][1] = 251;
B[0][2] = 139;
B[0][3] = 71;
B[0][4] = 215;
B[0][5] = 252;
B[0][6] = 248;
B[0][7] = 57;
B[0][8] = 172;
B[0][9] = 27;
B[0][10] = 196;
B[0][11] = 20;
B[1][0] = 63;
B[1][1] = 63;
B[1][2] = 39;
B[1][3] = 27;
B[1][4] = 154;
B[1][5] = 221;
B[1][6] = 120;
B[1][7] = 253;
B[1][8] = 119;
B[1][9] = 207;
B[1][10] = 12;
B[1][11] = 96;
B[2][0] = 198;
B[2][1] = 91;
B[2][2] = 244;
B[2][3] = 194;
B[2][4] = 114;
B[2][5] = 146;
B[2][6] = 193;
B[2][7] = 116;
B[2][8] = 36;
B[2][9] = 149;
B[2][10] = 80;
B[2][11] = 214;
B[3][0] = 9;
B[3][1] = 65;
B[3][2] = 38;
B[3][3] = 130;
B[3][4] = 20;
B[3][5] = 155;
B[3][6] = 42;
B[3][7] = 227;
B[3][8] = 197;
B[3][9] = 154;
B[3][10] = 23;
B[3][11] = 158;
B[4][0] = 186;
B[4][1] = 93;
B[4][2] = 217;
B[4][3] = 113;
B[4][4] = 52;
B[4][5] = 127;
B[4][6] = 68;
B[4][7] = 102;
B[4][8] = 146;
B[4][9] = 164;
B[4][10] = 16;
B[4][11] = 10;
B[5][0] = 245;
B[5][1] = 29;
B[5][2] = 233;
B[5][3] = 174;
B[5][4] = 26;
B[5][5] = 31;
B[5][6] = 145;
B[5][7] = 116;
B[5][8] = 128;
B[5][9] = 218;
B[5][10] = 86;
B[5][11] = 199;
B[6][0] = 117;
B[6][1] = 50;
B[6][2] = 106;
B[6][3] = 116;
B[6][4] = 72;
B[6][5] = 168;
B[6][6] = 174;
B[6][7] = 46;
B[6][8] = 90;
B[6][9] = 151;
B[6][10] = 62;
B[6][11] = 29;
B[7][0] = 244;
B[7][1] = 160;
B[7][2] = 198;
B[7][3] = 183;
B[7][4] = 237;
B[7][5] = 5;
B[7][6] = 228;
B[7][7] = 185;
B[7][8] = 10;
B[7][9] = 55;
B[7][10] = 32;
B[7][11] = 206;
B[8][0] = 55;
B[8][1] = 214;
B[8][2] = 251;
B[8][3] = 104;
B[8][4] = 108;
B[8][5] = 93;
B[8][6] = 215;
B[8][7] = 206;
B[8][8] = 160;
B[8][9] = 159;
B[8][10] = 178;
B[8][11] = 63;
B[9][0] = 142;
B[9][1] = 92;
B[9][2] = 20;
B[9][3] = 246;
B[9][4] = 67;
B[9][5] = 29;
B[9][6] = 139;
B[9][7] = 175;
B[9][8] = 46;
B[9][9] = 45;
B[9][10] = 232;
B[9][11] = 125;
B[10][0] = 90;
B[10][1] = 169;
B[10][2] = 31;
B[10][3] = 219;
B[10][4] = 192;
B[10][5] = 76;
B[10][6] = 227;
B[10][7] = 127;
B[10][8] = 96;
B[10][9] = 14;
B[10][10] = 64;
B[10][11] = 33;
B[11][0] = 254;
B[11][1] = 173;
B[11][2] = 44;
B[11][3] = 56;
B[11][4] = 189;
B[11][5] = 201;
B[11][6] = 135;
B[11][7] = 71;
B[11][8] = 125;
B[11][9] = 246;
B[11][10] = 123;
B[11][11] = 3;
reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Add matrices
    for (int i = 0; i < 12; i++) {
       
            C[i][0] = A[i][0] + B[i][0];
            C[i][1] = A[i][1] + B[i][1];
            C[i][2] = A[i][2] + B[i][2];
            C[i][3] = A[i][3] + B[i][3];
           
            C[i][4] = A[i][4] + B[i][4];
            C[i][5] = A[i][5] + B[i][5];
            C[i][6] = A[i][6] + B[i][6];
            C[i][7] = A[i][7] + B[i][7];
            
            C[i][8] = A[i][8] + B[i][8];
            C[i][9] = A[i][9] + B[i][9];
            C[i][10] = A[i][10] + B[i][10];
            C[i][11] = A[i][11] + B[i][11];
        
        reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
	reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    }
    */
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 	/*	//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 12; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------*/	
/*	//################# element-wise Logical AND operator #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 165;
A[0][1] = 109;
A[0][2] = 19;
A[0][3] = 193;
A[0][4] = 13;
A[0][5] = 42;
A[0][6] = 229;
A[0][7] = 106;
A[0][8] = 25;
A[0][9] = 132;
A[0][10] = 181;
A[0][11] = 0;
A[1][0] = 51;
A[1][1] = 243;
A[1][2] = 75;
A[1][3] = 165;
A[1][4] = 71;
A[1][5] = 115;
A[1][6] = 176;
A[1][7] = 75;
A[1][8] = 110;
A[1][9] = 34;
A[1][10] = 223;
A[1][11] = 66;
A[2][0] = 122;
A[2][1] = 202;
A[2][2] = 25;
A[2][3] = 37;
A[2][4] = 75;
A[2][5] = 132;
A[2][6] = 105;
A[2][7] = 40;
A[2][8] = 87;
A[2][9] = 212;
A[2][10] = 125;
A[2][11] = 174;
A[3][0] = 186;
A[3][1] = 229;
A[3][2] = 242;
A[3][3] = 20;
A[3][4] = 170;
A[3][5] = 20;
A[3][6] = 158;
A[3][7] = 110;
A[3][8] = 144;
A[3][9] = 210;
A[3][10] = 120;
A[3][11] = 182;
A[4][0] = 242;
A[4][1] = 70;
A[4][2] = 129;
A[4][3] = 10;
A[4][4] = 33;
A[4][5] = 122;
A[4][6] = 96;
A[4][7] = 94;
A[4][8] = 34;
A[4][9] = 186;
A[4][10] = 14;
A[4][11] = 225;
A[5][0] = 190;
A[5][1] = 77;
A[5][2] = 81;
A[5][3] = 214;
A[5][4] = 252;
A[5][5] = 54;
A[5][6] = 135;
A[5][7] = 153;
A[5][8] = 12;
A[5][9] = 44;
A[5][10] = 173;
A[5][11] = 22;
A[6][0] = 165;
A[6][1] = 24;
A[6][2] = 32;
A[6][3] = 194;
A[6][4] = 205;
A[6][5] = 57;
A[6][6] = 30;
A[6][7] = 109;
A[6][8] = 115;
A[6][9] = 187;
A[6][10] = 166;
A[6][11] = 130;
A[7][0] = 202;
A[7][1] = 173;
A[7][2] = 2;
A[7][3] = 237;
A[7][4] = 131;
A[7][5] = 211;
A[7][6] = 26;
A[7][7] = 251;
A[7][8] = 174;
A[7][9] = 219;
A[7][10] = 53;
A[7][11] = 126;
A[8][0] = 112;
A[8][1] = 39;
A[8][2] = 226;
A[8][3] = 35;
A[8][4] = 73;
A[8][5] = 185;
A[8][6] = 60;
A[8][7] = 105;
A[8][8] = 232;
A[8][9] = 117;
A[8][10] = 177;
A[8][11] = 86;
A[9][0] = 136;
A[9][1] = 88;
A[9][2] = 105;
A[9][3] = 176;
A[9][4] = 75;
A[9][5] = 150;
A[9][6] = 184;
A[9][7] = 223;
A[9][8] = 51;
A[9][9] = 8;
A[9][10] = 247;
A[9][11] = 121;
A[10][0] = 122;
A[10][1] = 182;
A[10][2] = 16;
A[10][3] = 38;
A[10][4] = 22;
A[10][5] = 156;
A[10][6] = 59;
A[10][7] = 130;
A[10][8] = 81;
A[10][9] = 207;
A[10][10] = 162;
A[10][11] = 157;
A[11][0] = 167;
A[11][1] = 82;
A[11][2] = 106;
A[11][3] = 154;
A[11][4] = 5;
A[11][5] = 133;
A[11][6] = 171;
A[11][7] = 36;
A[11][8] = 207;
A[11][9] = 123;
A[11][10] = 112;
A[11][11] = 197;

B[0][0] = 218;
B[0][1] = 251;
B[0][2] = 139;
B[0][3] = 71;
B[0][4] = 215;
B[0][5] = 252;
B[0][6] = 248;
B[0][7] = 57;
B[0][8] = 172;
B[0][9] = 27;
B[0][10] = 196;
B[0][11] = 20;
B[1][0] = 63;
B[1][1] = 63;
B[1][2] = 39;
B[1][3] = 27;
B[1][4] = 154;
B[1][5] = 221;
B[1][6] = 120;
B[1][7] = 253;
B[1][8] = 119;
B[1][9] = 207;
B[1][10] = 12;
B[1][11] = 96;
B[2][0] = 198;
B[2][1] = 91;
B[2][2] = 244;
B[2][3] = 194;
B[2][4] = 114;
B[2][5] = 146;
B[2][6] = 193;
B[2][7] = 116;
B[2][8] = 36;
B[2][9] = 149;
B[2][10] = 80;
B[2][11] = 214;
B[3][0] = 9;
B[3][1] = 65;
B[3][2] = 38;
B[3][3] = 130;
B[3][4] = 20;
B[3][5] = 155;
B[3][6] = 42;
B[3][7] = 227;
B[3][8] = 197;
B[3][9] = 154;
B[3][10] = 23;
B[3][11] = 158;
B[4][0] = 186;
B[4][1] = 93;
B[4][2] = 217;
B[4][3] = 113;
B[4][4] = 52;
B[4][5] = 127;
B[4][6] = 68;
B[4][7] = 102;
B[4][8] = 146;
B[4][9] = 164;
B[4][10] = 16;
B[4][11] = 10;
B[5][0] = 245;
B[5][1] = 29;
B[5][2] = 233;
B[5][3] = 174;
B[5][4] = 26;
B[5][5] = 31;
B[5][6] = 145;
B[5][7] = 116;
B[5][8] = 128;
B[5][9] = 218;
B[5][10] = 86;
B[5][11] = 199;
B[6][0] = 117;
B[6][1] = 50;
B[6][2] = 106;
B[6][3] = 116;
B[6][4] = 72;
B[6][5] = 168;
B[6][6] = 174;
B[6][7] = 46;
B[6][8] = 90;
B[6][9] = 151;
B[6][10] = 62;
B[6][11] = 29;
B[7][0] = 244;
B[7][1] = 160;
B[7][2] = 198;
B[7][3] = 183;
B[7][4] = 237;
B[7][5] = 5;
B[7][6] = 228;
B[7][7] = 185;
B[7][8] = 10;
B[7][9] = 55;
B[7][10] = 32;
B[7][11] = 206;
B[8][0] = 55;
B[8][1] = 214;
B[8][2] = 251;
B[8][3] = 104;
B[8][4] = 108;
B[8][5] = 93;
B[8][6] = 215;
B[8][7] = 206;
B[8][8] = 160;
B[8][9] = 159;
B[8][10] = 178;
B[8][11] = 63;
B[9][0] = 142;
B[9][1] = 92;
B[9][2] = 20;
B[9][3] = 246;
B[9][4] = 67;
B[9][5] = 29;
B[9][6] = 139;
B[9][7] = 175;
B[9][8] = 46;
B[9][9] = 45;
B[9][10] = 232;
B[9][11] = 125;
B[10][0] = 90;
B[10][1] = 169;
B[10][2] = 31;
B[10][3] = 219;
B[10][4] = 192;
B[10][5] = 76;
B[10][6] = 227;
B[10][7] = 127;
B[10][8] = 96;
B[10][9] = 14;
B[10][10] = 64;
B[10][11] = 33;
B[11][0] = 254;
B[11][1] = 173;
B[11][2] = 44;
B[11][3] = 56;
B[11][4] = 189;
B[11][5] = 201;
B[11][6] = 135;
B[11][7] = 71;
B[11][8] = 125;
B[11][9] = 246;
B[11][10] = 123;
B[11][11] = 3;

    // Add matrices
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
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
   for (int i = 0; i < 12; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 	*/	//------- Value verification -----------	
 	//################# element-wise Logical NOT operator #########################
//Start
/*
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 165;
A[0][1] = 109;
A[0][2] = 19;
A[0][3] = 193;
A[0][4] = 13;
A[0][5] = 42;
A[0][6] = 229;
A[0][7] = 106;
A[0][8] = 25;
A[0][9] = 132;
A[0][10] = 181;
A[0][11] = 0;
A[1][0] = 51;
A[1][1] = 243;
A[1][2] = 75;
A[1][3] = 165;
A[1][4] = 71;
A[1][5] = 115;
A[1][6] = 176;
A[1][7] = 75;
A[1][8] = 110;
A[1][9] = 34;
A[1][10] = 223;
A[1][11] = 66;
A[2][0] = 122;
A[2][1] = 202;
A[2][2] = 25;
A[2][3] = 37;
A[2][4] = 75;
A[2][5] = 132;
A[2][6] = 105;
A[2][7] = 40;
A[2][8] = 87;
A[2][9] = 212;
A[2][10] = 125;
A[2][11] = 174;
A[3][0] = 186;
A[3][1] = 229;
A[3][2] = 242;
A[3][3] = 20;
A[3][4] = 170;
A[3][5] = 20;
A[3][6] = 158;
A[3][7] = 110;
A[3][8] = 144;
A[3][9] = 210;
A[3][10] = 120;
A[3][11] = 182;
A[4][0] = 242;
A[4][1] = 70;
A[4][2] = 129;
A[4][3] = 10;
A[4][4] = 33;
A[4][5] = 122;
A[4][6] = 96;
A[4][7] = 94;
A[4][8] = 34;
A[4][9] = 186;
A[4][10] = 14;
A[4][11] = 225;
A[5][0] = 190;
A[5][1] = 77;
A[5][2] = 81;
A[5][3] = 214;
A[5][4] = 252;
A[5][5] = 54;
A[5][6] = 135;
A[5][7] = 153;
A[5][8] = 12;
A[5][9] = 44;
A[5][10] = 173;
A[5][11] = 22;
A[6][0] = 165;
A[6][1] = 24;
A[6][2] = 32;
A[6][3] = 194;
A[6][4] = 205;
A[6][5] = 57;
A[6][6] = 30;
A[6][7] = 109;
A[6][8] = 115;
A[6][9] = 187;
A[6][10] = 166;
A[6][11] = 130;
A[7][0] = 202;
A[7][1] = 173;
A[7][2] = 2;
A[7][3] = 237;
A[7][4] = 131;
A[7][5] = 211;
A[7][6] = 26;
A[7][7] = 251;
A[7][8] = 174;
A[7][9] = 219;
A[7][10] = 53;
A[7][11] = 126;
A[8][0] = 112;
A[8][1] = 39;
A[8][2] = 226;
A[8][3] = 35;
A[8][4] = 73;
A[8][5] = 185;
A[8][6] = 60;
A[8][7] = 105;
A[8][8] = 232;
A[8][9] = 117;
A[8][10] = 177;
A[8][11] = 86;
A[9][0] = 136;
A[9][1] = 88;
A[9][2] = 105;
A[9][3] = 176;
A[9][4] = 75;
A[9][5] = 150;
A[9][6] = 184;
A[9][7] = 223;
A[9][8] = 51;
A[9][9] = 8;
A[9][10] = 247;
A[9][11] = 121;
A[10][0] = 122;
A[10][1] = 182;
A[10][2] = 16;
A[10][3] = 38;
A[10][4] = 22;
A[10][5] = 156;
A[10][6] = 59;
A[10][7] = 130;
A[10][8] = 81;
A[10][9] = 207;
A[10][10] = 162;
A[10][11] = 157;
A[11][0] = 167;
A[11][1] = 82;
A[11][2] = 106;
A[11][3] = 154;
A[11][4] = 5;
A[11][5] = 133;
A[11][6] = 171;
A[11][7] = 36;
A[11][8] = 207;
A[11][9] = 123;
A[11][10] = 112;
A[11][11] = 197;
    // Add matrices
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
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
   for (int i = 0; i < 12; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------			
 */		
	//################# 	Scalar Product	   #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 165;
A[0][1] = 109;
A[0][2] = 19;
A[0][3] = 193;
A[0][4] = 13;
A[0][5] = 42;
A[0][6] = 229;
A[0][7] = 106;
A[0][8] = 25;
A[0][9] = 132;
A[0][10] = 181;
A[0][11] = 0;
A[1][0] = 51;
A[1][1] = 243;
A[1][2] = 75;
A[1][3] = 165;
A[1][4] = 71;
A[1][5] = 115;
A[1][6] = 176;
A[1][7] = 75;
A[1][8] = 110;
A[1][9] = 34;
A[1][10] = 223;
A[1][11] = 66;
A[2][0] = 122;
A[2][1] = 202;
A[2][2] = 25;
A[2][3] = 37;
A[2][4] = 75;
A[2][5] = 132;
A[2][6] = 105;
A[2][7] = 40;
A[2][8] = 87;
A[2][9] = 212;
A[2][10] = 125;
A[2][11] = 174;
A[3][0] = 186;
A[3][1] = 229;
A[3][2] = 242;
A[3][3] = 20;
A[3][4] = 170;
A[3][5] = 20;
A[3][6] = 158;
A[3][7] = 110;
A[3][8] = 144;
A[3][9] = 210;
A[3][10] = 120;
A[3][11] = 182;
A[4][0] = 242;
A[4][1] = 70;
A[4][2] = 129;
A[4][3] = 10;
A[4][4] = 33;
A[4][5] = 122;
A[4][6] = 96;
A[4][7] = 94;
A[4][8] = 34;
A[4][9] = 186;
A[4][10] = 14;
A[4][11] = 225;
A[5][0] = 190;
A[5][1] = 77;
A[5][2] = 81;
A[5][3] = 214;
A[5][4] = 252;
A[5][5] = 54;
A[5][6] = 135;
A[5][7] = 153;
A[5][8] = 12;
A[5][9] = 44;
A[5][10] = 173;
A[5][11] = 22;
A[6][0] = 165;
A[6][1] = 24;
A[6][2] = 32;
A[6][3] = 194;
A[6][4] = 205;
A[6][5] = 57;
A[6][6] = 30;
A[6][7] = 109;
A[6][8] = 115;
A[6][9] = 187;
A[6][10] = 166;
A[6][11] = 130;
A[7][0] = 202;
A[7][1] = 173;
A[7][2] = 2;
A[7][3] = 237;
A[7][4] = 131;
A[7][5] = 211;
A[7][6] = 26;
A[7][7] = 251;
A[7][8] = 174;
A[7][9] = 219;
A[7][10] = 53;
A[7][11] = 126;
A[8][0] = 112;
A[8][1] = 39;
A[8][2] = 226;
A[8][3] = 35;
A[8][4] = 73;
A[8][5] = 185;
A[8][6] = 60;
A[8][7] = 105;
A[8][8] = 232;
A[8][9] = 117;
A[8][10] = 177;
A[8][11] = 86;
A[9][0] = 136;
A[9][1] = 88;
A[9][2] = 105;
A[9][3] = 176;
A[9][4] = 75;
A[9][5] = 150;
A[9][6] = 184;
A[9][7] = 223;
A[9][8] = 51;
A[9][9] = 8;
A[9][10] = 247;
A[9][11] = 121;
A[10][0] = 122;
A[10][1] = 182;
A[10][2] = 16;
A[10][3] = 38;
A[10][4] = 22;
A[10][5] = 156;
A[10][6] = 59;
A[10][7] = 130;
A[10][8] = 81;
A[10][9] = 207;
A[10][10] = 162;
A[10][11] = 157;
A[11][0] = 167;
A[11][1] = 82;
A[11][2] = 106;
A[11][3] = 154;
A[11][4] = 5;
A[11][5] = 133;
A[11][6] = 171;
A[11][7] = 36;
A[11][8] = 207;
A[11][9] = 123;
A[11][10] = 112;
A[11][11] = 197;


    // Add matrices
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            C[i][j] = multiply_with_adds(A[i][j], 10);
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 	/*	//------- Value verification -----------
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 12; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------	 		

	*/
}

