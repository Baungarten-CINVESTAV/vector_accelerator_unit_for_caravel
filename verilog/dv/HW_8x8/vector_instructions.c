#include <vector_instructions.h>

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
	
	res_0 = reg_la0_data;
	res_1 = reg_la1_data;
	res_2 = reg_la2_data;
	res_3 = reg_la3_data;
};


