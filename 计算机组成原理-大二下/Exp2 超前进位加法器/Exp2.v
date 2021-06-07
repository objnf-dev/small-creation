`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer: 18271241
// Create Date:    18:51:02 06/20/2020     
// Module Name:    Exp2 
//////////////////////////////////////////////////////////////////////////////////
module Exp2(
        F, A, B, C0, C4
    );
	 
	 input[3: 0] A, B;
	 input C0;
	 output[3: 0] F;
	 output C4;
	 
	 wire[3: 0] P, G;
	 wire[4: 0] C_inner;
	 
	 assign C_inner[0] = C0;
	 assign P[3: 0] = A ^ B;
	 assign G[3: 0] = A & B;
	 
	 assign C_inner[1] = G[0] | (P[0] & C_inner[0]);
	 assign C_inner[2] = G[1] | (P[1] & C_inner[1]);
	 assign C_inner[3] = G[2] | (P[2] & C_inner[2]);
	 assign C_inner[4] = G[3] | (P[3] & C_inner[3]);
	 
	 assign F[3: 0] = P ^ C_inner[3: 0];
	 assign C4 = C_inner[4];

endmodule
