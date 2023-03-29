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
////////////////////////////	matrix 4 x 4	////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int A[4][4];
int B[4][4];
int C[4][4];
	//################# SW matrix addition #########################
//Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
    // Define matrices
A[0][0] = 68;
A[0][1] = 20;
A[0][2] = 63;
A[0][3] = 81;
A[1][0] = 75;
A[1][1] = 50;
A[1][2] = 54;
A[1][3] = 166;
A[2][0] = 119;
A[2][1] = 92;
A[2][2] = 161;
A[2][3] = 125;
A[3][0] = 160;
A[3][1] = 152;
A[3][2] = 200;
A[3][3] = 53;

B[0][0] = 66;
B[0][1] = 77;
B[0][2] = 3;
B[0][3] = 18;
B[1][0] = 120;
B[1][1] = 87;
B[1][2] = 137;
B[1][3] = 198;
B[2][0] = 134;
B[2][1] = 24;
B[2][2] = 26;
B[2][3] = 152;
B[3][0] = 173;
B[3][1] = 79;
B[3][2] = 194;
B[3][3] = 11;

    // Add matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
   for (int i = 0; i < 4; i++) {
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
A[0][0] = 68;
A[0][1] = 20;
A[0][2] = 63;
A[0][3] = 81;
A[1][0] = 75;
A[1][1] = 50;
A[1][2] = 54;
A[1][3] = 166;
A[2][0] = 119;
A[2][1] = 92;
A[2][2] = 161;
A[2][3] = 125;
A[3][0] = 160;
A[3][1] = 152;
A[3][2] = 200;
A[3][3] = 53;

B[0][0] = 66;
B[0][1] = 77;
B[0][2] = 3;
B[0][3] = 18;
B[1][0] = 120;
B[1][1] = 87;
B[1][2] = 137;
B[1][3] = 198;
B[2][0] = 134;
B[2][1] = 24;
B[2][2] = 26;
B[2][3] = 152;
B[3][0] = 173;
B[3][1] = 79;
B[3][2] = 194;
B[3][3] = 11;

    // Add matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
   for (int i = 0; i < 4; i++) {
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
A[0][0] = 68;
A[0][1] = 20;
A[0][2] = 63;
A[0][3] = 81;
A[1][0] = 75;
A[1][1] = 50;
A[1][2] = 54;
A[1][3] = 166;
A[2][0] = 119;
A[2][1] = 92;
A[2][2] = 161;
A[2][3] = 125;
A[3][0] = 160;
A[3][1] = 152;
A[3][2] = 200;
A[3][3] = 53;

    // Add matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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
   for (int i = 0; i < 4; i++) {
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
A[0][0] = 68;
A[0][1] = 20;
A[0][2] = 63;
A[0][3] = 81;
A[1][0] = 75;
A[1][1] = 50;
A[1][2] = 54;
A[1][3] = 166;
A[2][0] = 119;
A[2][1] = 92;
A[2][2] = 161;
A[2][3] = 125;
A[3][0] = 160;
A[3][1] = 152;
A[3][2] = 200;
A[3][3] = 53;


    // Add matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] += multiply_with_adds(A[i][j], 100);
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
   for (int i = 0; i < 4; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }
 		//------- Value verification -----------	 		
 		
 		
 		
 		
 	/*	


  //###################### SW Multiplication ######################################
  //Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
A[0][0] = 1;
A[0][1] = 2;
A[0][2] = 3;
A[0][3] = 4;
A[1][0] = 5;
A[1][1] = 6;
A[1][2] = 7;
A[1][3] = 8;
A[2][0] = 9;
A[2][1] = 10;
A[2][2] = 11;
A[2][3] = 12;
A[3][0] = 13;
A[3][1] = 14;
A[3][2] = 15;
A[3][3] = 16;

B[0][0] = 16;
B[0][1] = 15;
B[0][2] = 14;
B[0][3] = 13;
B[1][0] = 12;
B[1][1] = 11;
B[1][2] = 10;
B[1][3] = 9;
B[2][0] = 8;
B[2][1] = 7;
B[2][2] = 6;
B[2][3] = 5;
B[3][0] = 4;
B[3][1] = 3;
B[3][2] = 2;
B[3][3] = 1;

C[0][0] = 0;
C[0][1] = 0;
C[0][2] = 0;
C[0][3] = 0;
C[1][0] = 0;
C[1][1] = 0;
C[1][2] = 0;
C[1][3] = 0;
C[2][0] = 0;
C[2][1] = 0;
C[2][2] = 0;
C[2][3] = 0;
C[3][0] = 0;
C[3][1] = 0;
C[3][2] = 0;
C[3][3] = 0;

    // Multiply matrices
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] += multiply_with_adds(A[i][k], B[k][j]);
            }
        }
    }
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
 
 // Configure All LA probes as outputs to the cpu 
	reg_la0_oenb = 0xFFFFFFFF;    // [31:0]
	reg_la1_oenb = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = 0xFFFFFFFF;    // [95:64]
	reg_la3_oenb  = 0xFFFFFFFF;    // [127:96]
   for (int i = 0; i < 4; i++) {
            reg_la0_data = C[i][0];
            reg_la1_data = C[i][1];
            reg_la2_data = C[i][2];
            reg_la3_data = C[i][3];

    }

//###################### SW Complex Multiplication #################################
  //Start
reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
	reg_mprj_datal = reg_mprj_datal | 0x00100000; //Set 1 in GPIO port 20
	   // Define two complex numbers
    	complex_t a = {38, 19};
    	complex_t b = {94, 45};
   	 // Multiply the two complex numbers using the custom multiplication function
   	 complex_t c;

   	 complex_multiply_with_adds(&a, &b, &c);
   	
   	reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20
    //End
 reg_mprj_datal = reg_mprj_datal & 0x00000000; //Set 0 in GPIO port 20   
//###################### SW Complex Multiplication ######################################
	
	
	*/
	
	
}

