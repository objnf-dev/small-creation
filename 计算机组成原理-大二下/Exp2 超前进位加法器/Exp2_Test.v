`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   19:33:47 06/23/2020
// Design Name:   Exp2
// Module Name:   D:/CSAPP-Exp/Exp2/Exp2_Test.v
// Project Name:  Exp2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Exp2
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Exp2_Test;

	// Inputs
	reg [3:0] A;
	reg [3:0] B;
	reg C0;

	// Outputs
	wire [3:0] F;
	wire C4;

	// Instantiate the Unit Under Test (UUT)
	Exp2 uut (
		.F(F), 
		.A(A), 
		.B(B), 
		.C0(C0), 
		.C4(C4)
	);

	initial begin
		// Initialize Inputs
		A = 0;
		B = 0;
		C0 = 0;

		// Wait 100 ns for global reset to finish
		#100;
		A = 4'b0001;
		B = 4'b0111;
		
		#100;
		A = 4'b0011;
		B = 4'b1100;
		
		#100;
		A  = 4'b0111;
		C0 = 1'b1;
		
		#100;
		A = 4'b0101;
		B = 4'b0011;
		C0 = 1'b1;

	end
      
endmodule

