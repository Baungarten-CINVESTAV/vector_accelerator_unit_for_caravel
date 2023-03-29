module Top_Module_4_ALU(
input [127:0] operand,
input [3:0]Operation,
output [127:0] ALU_Output,
output [3:0] Exception, Overflow,Underflow,
input clk,	//new signal
input i_rst, 	//new signal
input i_operand_sel, //new signal 1 = A, 0 = B
input iCE
);

reg [127:0] a_operand_D;
reg [127:0] a_operand_Q;

reg [127:0] b_operand_D;
reg [127:0] b_operand_Q;


always@(posedge clk or posedge i_rst)
begin
	if(i_rst)
	begin
	a_operand_Q <= 128'd0;
	b_operand_Q <= 128'd0;
	end
	else if(iCE)
	begin
	a_operand_Q <= a_operand_D;
	b_operand_Q <= b_operand_D;
	end
	else
	begin
	a_operand_Q <= a_operand_Q;
	b_operand_Q <= a_operand_Q;
	end
end

always@*
begin
a_operand_D = a_operand_Q;
b_operand_D = b_operand_Q;
	if(i_operand_sel)
	begin
	a_operand_D = operand;
	end
	else
	begin
	b_operand_D = operand;
	end
end
//LSB
ALU ALU_1(
	.a_operand(a_operand_Q[31:0]),
	.b_operand(b_operand_Q[31:0]),
	.Operation(Operation),	
	.ALU_Output(ALU_Output[31:0]),
	.Exception(Exception[0]),
	.Overflow(Overflow[0]),
	.Underflow(Underflow[0])
	);

ALU ALU_2(
	.a_operand(a_operand_Q[63:32]),
	.b_operand(b_operand_Q[63:32]),
	.Operation(Operation),	
	.ALU_Output(ALU_Output[63:32]),
	.Exception(Exception[1]),
	.Overflow(Overflow[1]),
	.Underflow(Underflow[1])
	);

ALU ALU_3(
	.a_operand(a_operand_Q[95:64]),
	.b_operand(b_operand_Q[95:64]),
	.Operation(Operation),	
	.ALU_Output(ALU_Output[95:64]),
	.Exception(Exception[2]),
	.Overflow(Overflow[2]),
	.Underflow(Underflow[2])
	);

	//MSB
ALU ALU_4(
	.a_operand(a_operand_Q[127:96]),
	.b_operand(b_operand_Q[127:96]),
	.Operation(Operation),	
	.ALU_Output(ALU_Output[127:96]),
	.Exception(Exception[3]),
	.Overflow(Overflow[3]),
	.Underflow(Underflow[3])
	);
	

endmodule 
