`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:14:30 06/23/2020
// Design Name:   Exp3
// Module Name:   D:/CSAPP-Exp/Exp3/Exp3_Test.v
// Project Name:  Exp3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Exp3
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Exp3_Test;

	// Inputs
	reg [2:0] ALU_OP;
	reg [2:0] AB_SW;
	reg [2:0] F_LED_SW;

	// Outputs
	wire [31:0] F;
	wire [7:0] LED;
	wire ZF;
	wire OF;

	// Instantiate the Unit Under Test (UUT)
	Exp3 uut (
		.ALU_OP(ALU_OP), 
		.AB_SW(AB_SW), 
		.F_LED_SW(F_LED_SW), 
		.F(F), 
		.LED(LED), 
		.ZF(ZF), 
		.OF(OF)
	);

	initial begin
		// Initialize Inputs
		ALU_OP = 0;
		AB_SW = 0;
		F_LED_SW = 0;

		// Wait 100 ns for global reset to finish
		#100;
        ALU_OP = 3'b000;
		AB_SW = 3'b000;
		F_LED_SW = 3'b000;
		
		#100;
        ALU_OP = 3'b001;
		AB_SW = 3'b001;
		F_LED_SW = 3'b001;
		
		#100;
        ALU_OP = 3'b010;
		AB_SW = 3'b010;
		F_LED_SW = 3'b010;

	end
      
endmodule

