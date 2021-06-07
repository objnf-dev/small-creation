`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: HDU 
// Engineer: 18271241 
// 
// Create Date:    20:11:31 05/17/2020 
// Design Name: 	 FullAdd 
// Module Name:    FAdd 
//////////////////////////////////////////////////////////////////////////////////

// Full Adder needs to consider C1, but Half Adder won't.
module FAdd(
			A, B, C1, C2, F
    );
	input A, B, C1;
	output C2, F;
	wire A, B, C1, C2, F;
	// Temporary vars
	wire Tmp1, Tmp2, Tmp3;
	
	// Logic
	xor AxorB (Tmp1, A, B);
	xor CurrentVal (F, Tmp1, C1);
	and AandB (Tmp2, A, B);
	and CalcC1 (Tmp3, Tmp1, C1);
	or CurrentC2 (C2, Tmp2, Tmp3);

endmodule
