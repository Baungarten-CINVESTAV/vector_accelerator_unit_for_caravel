////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//File Name: ALU.v
//Created By: Sheetal Swaroop Burada
//Date: 30-04-2019
//Project Name: Design of 32 Bit Floating Point ALU Based on Standard IEEE-754 in Verilog and its implementation on FPGA.
//University: Dayalbagh Educational Institute
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*						Operations
Opcode
0000: Floating point Addition 
0001: Floating point Multiplication	
0010: Floating point division
0011: Floating point subtraction  
0100: OR operator
0101: AND operator
0110: XOR operator
0111:	Left shif
1000: Right shift
1001: Floating Point to Integer
1010: Not operator
1011: Integer Addition
1100: Integer subtraction
1101: Integer Multiplication_32_MSB
1110: Integer Multiplication_32_LSB
1111: Zero
*/

`include "./Addition_Subtraction.v"
`include "./Multiplication.v"
//`include "./Division.v"
`include "./Converter.v"

module ALU(
	input [31:0] a_operand,
	input [31:0] b_operand,
	input [3:0] Operation,	
	output reg [31:0] ALU_Output,
	output reg Exception,Overflow,Underflow
	);


wire [31:0] Add_Sub_A,Add_Sub_B,Mul_A,Mul_B,Div_A,Div_B,OR_Output,AND_Output,XOR_Output,L_S_Output,R_S_Output,Floating_Point;

wire Add_Sub_Exception,Mul_Exception,Mul_Overflow,Mul_Underflow,Div_Exception;

wire [31:0] Add_Sub_Output,Mul_Output,Integer_Value;

wire AddBar_Sub;

wire [31:0] Complement_output;

wire [32:0] int_add;
wire [31:0] int_sub;
wire [63:0] int_mult;
wire [31:0] int_div;

assign {Add_Sub_A,Add_Sub_B,AddBar_Sub} = (Operation == 4'd0) ? {a_operand,b_operand,1'b0} : {a_operand,b_operand,1'b1};

assign {Mul_A,Mul_B} = (Operation == 4'd1) ? {a_operand,b_operand} : 64'd0;
//assign {Div_A,Div_B} = (Operation == 4'd2) ? {a_operand,b_operand}	: 64'd0;

assign OR_Output = (Operation == 4'd4) ? a_operand | b_operand	: 32'd0;

assign AND_Output = (Operation == 4'd5) ? a_operand & b_operand	: 32'd0;

assign XOR_Output = (Operation == 4'd6) ? a_operand ^ b_operand: 32'd0;

assign L_S_Output = (Operation == 4'd7) ? a_operand << 1'b1 : 32'd0;

assign R_S_Output = (Operation == 4'd8) ? a_operand >> 1'b1	: 32'd0;

assign Floating_Point = (Operation == 4'd9) ? a_operand	: 32'd0;

assign Complement_output = (Operation == 4'd10) ? ~a_operand : 32'd0;
////////////////////////////Extra instructions//////////////////////////////////////////////////////////////////////////////
assign int_add = (Operation == 4'd11) ? a_operand + b_operand: 33'd0;
assign int_sub = (Operation == 4'd12) ? ((a_operand>b_operand)?(a_operand-b_operand):(b_operand-a_operand)): 32'd0;
assign int_mult = (Operation == 4'd13|Operation == 4'd14) ? a_operand * b_operand: 64'd0;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Addition_Subtraction AuI(Add_Sub_A,Add_Sub_B,AddBar_Sub,Add_Sub_Exception,Add_Sub_Output);

Multiplication MuI(Mul_A,Mul_B,Mul_Exception,Mul_Overflow,Mul_Underflow,Mul_Output);

//Division DuI(Div_A,Div_B,Div_Exception,Div_Output);

Floating_Point_to_Integer FuI(Floating_Point,Integer_Value);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

always@*
begin
	case(Operation)
	4'd0:  {Exception,Overflow,Underflow,ALU_Output} = {Add_Sub_Exception,1'b0,1'b0,Add_Sub_Output};
	4'd1:  {Exception,Overflow,Underflow,ALU_Output} = {Mul_Exception,Mul_Overflow,Mul_Underflow,Mul_Output};
	//4'd2:  {Exception,Overflow,Underflow,ALU_Output} = {Div_Exception,1'b0,1'b0,Div_Output};
	4'd3:	{Exception,Overflow,Underflow,ALU_Output} = {Add_Sub_Exception,1'b0,1'b0,Add_Sub_Output};
	4'd4:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,OR_Output};
	4'd5:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,AND_Output};
	4'd6:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,XOR_Output};
	4'd7:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,L_S_Output};
	4'd8:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,R_S_Output};
	4'd9:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,Integer_Value};
	4'd10:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,Complement_output};
	4'd11:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,int_add[32],1'b0,int_add[31:0]} ;
	4'd12:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,int_sub[31:0]};
	4'd13:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,int_mult[63:32]};
	4'd14:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,int_mult[31:0]};
	default:	{Exception,Overflow,Underflow,ALU_Output} = {1'b0,1'b0,1'b0,32'd0};
	
	endcase
end


/*
assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd0) ? {Add_Sub_Exception,1'b0,1'b0,Add_Sub_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd1) ? {Mul_Exception,Mul_Overflow,Mul_Underflow,Mul_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd2) ? {Div_Exception,1'b0,1'b0,Div_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd3) ? {Add_Sub_Exception,1'b0,1'b0,Add_Sub_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd4) ? {1'b0,1'b0,1'b0,OR_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd5) ? {1'b0,1'b0,1'b0,AND_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd6) ? {1'b0,1'b0,1'b0,XOR_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd7) ? {1'b0,1'b0,1'b0,L_S_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd8) ? {1'b0,1'b0,1'b0,R_S_Output}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd9) ? {1'b0,1'b0,1'b0,Integer_Value}	: 35'dz;

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd10) ? {1'b0,1'b0,1'b0,Complement_output} : 35'dz;

////////////////////////////Extra instructions//////////////////////////////////////////////////////////////////////////////
assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd11) ? {1'b0,int_add[32],1'b0,int_add[31:0]} : 35'dz; //Overflow output = Carry output

assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd12) ? {1'b0,1'b0,1'b0,int_sub[31:0]} : 35'dz;
assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd13) ? {1'b0,1'b0,1'b0,int_mult[63:32]} : 35'dz;
assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd14) ? {1'b0,1'b0,1'b0,int_mult[31:0]} : 35'dz;
assign {Exception,Overflow,Underflow,ALU_Output} = (Operation == 4'd15) ? {1'b0,1'b0,1'b0,32'd0} : 35'dz;
*/

endmodule 
