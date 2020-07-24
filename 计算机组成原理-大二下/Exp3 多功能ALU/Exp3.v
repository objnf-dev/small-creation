`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Engineer:	   18271241
// Create Date:    19:50:20 06/23/2020
// Module Name:    Exp3
//////////////////////////////////////////////////////////////////////////////////
module Exp3(
		input wire [2: 0] ALU_OP,
		input wire [2: 0] AB_SW,
		input wire [2: 0] F_LED_SW,

		output reg [31: 0] F,
		output reg [7: 0] LED,
		output ZF,
		output OF
	);

		reg [31: 0] A, B;
		parameter Zero_32 = 32'h00000000, One_32 = 32'h00000001;
		reg C32;

		always @(*)
		begin
			case (AB_SW)
				3'b000:
					begin
						A = 32'h00000000;
						B = 32'hFFFFFFFF;
					end
				
				3'b001:
					begin
						A = 32'h00000003;
						B = 32'h00000607;
					end
				
				3'b010:
					begin
						A = 32'h80000000;
						B = 32'h80000000;
					end
				
				3'b011:
					begin
						A = 32'h7FFFFFFF;
						B = 32'h7FFFFFFF;
					end
				
				3'b100:
					begin
						A = 32'hFFFFFFFF;
						B = 32'hFFFFFFFF;
					end
				
				3'b101:
					begin
						A = 32'h80000000;
						B = 32'hFFFFFFFF;
					end
				
				3'b110:
					begin
						A = 32'hFFFFFFFF;
						B = 32'h80000000;
					end
				
				3'b111:
					begin
						A = 32'h12345678;
						B = 32'h33332222;
					end
				
				default:
					begin
						A = 32'h9ABCDEF0;
						B = 32'h11112222;
					end
			endcase
		end
		
		always @(*)
		begin
			C32 = 1'b0;
			case (ALU_OP)
				3'b000:
					F = A & B;
				3'b001:
					F = A | B;
				3'b010:
					F = A ^ B;
				3'b011:
					F = ~(A | B);
				3'b100:
					{C32, F} = A + B;
				3'b101:
					{C32, F} = A - B;
				3'b110:
					F = (A < B) ? One_32 : Zero_32;
				3'b111:
					F = A >> B;
				default:
					F = Zero_32;
			endcase
		end

		assign ZF = (F == Zero_32) ? 1'b1 : 1'b0;
		assign OF = ((ALU_OP == 3'b100) || (ALU_OP == 3'b101)) && (A[31] ^ B[31] ^ F[31] ^ C32);
		
		always @(*)
		begin
			case (F_LED_SW)
				3'b000:
					LED = F[7: 0];
				3'b001:
					LED = F[15: 8];
				3'b010:
					LED = F[23: 16];
				3'b011:
					LED = F[31: 24];
				default:
					begin
						LED[0] = OF;
						LED[7] = ZF;
						LED[6: 1] = 6'b000000;
					end
			endcase
		end

endmodule
