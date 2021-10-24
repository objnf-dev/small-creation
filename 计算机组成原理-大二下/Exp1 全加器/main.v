`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: HDU 
// Engineer: ObjectNF 
// Create Date:   20:38:53 05/17/2020
// Design Name:   FAdd
// Module Name:   D:/CSAPP-Exp/FullAdd/Main.v
// Project Name:  FullAdd
////////////////////////////////////////////////////////////////////////////////

module Main;

	// Inputs
	reg A;
	reg B;
	reg C1;

	// Outputs
	wire C2;
	wire F;

	// Instantiate the Unit Under Test (UUT)
	FAdd uut (
		.A(A), 
		.B(B), 
		.C1(C1), 
		.C2(C2), 
		.F(F)
	);

	initial begin
		// Initialize Inputs
		A = 0;
		B = 0;
		C1 = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Simulations
		A = 0;
		B = 0;
		C1 = 0;
		#100;
		
		A = 0;
		B = 0;
		C1 = 1;
		#100;
		
		A = 0;
		B = 1;
		C1 = 0;
		#100;
		
		A = 0;
		B = 1;
		C1 = 1;
		#100;
		
		A = 1;
		B = 0;
		C1 = 0;
		#100;
		
		A = 1;
		B = 0;
		C1 = 1;
		#100;
		
		A = 1;
		B = 1;
		C1 = 0;
		#100;
		
		A = 1;
		B = 1;
		C1 = 1;
		#100;

	end
      
endmodule

