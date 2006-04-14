#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxamb.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>



void SPvpp_bxamb::operator()
(
	Signal inAp, Signal inBp, Signal inCp, Signal inDp,
	Signal outA, Signal outB, Signal outC, Signal outD,
	Signal validin,
	Signal validout,
	Signal clk
)
{
initio
	inAp.input(BWMBIN-1, 0, "inAp");
	inBp.input(BWMBIN-1, 0, "inBp");
	inCp.input(BWMBIN-1, 0, "inCp");
	inDp.input(BWMBIN-1, 0, "inDp");
	outA.output(BWMBIN-1, 0, "outA", makereg);
	outB.output(BWMBIN-1, 0, "outB", makereg);
	outC.output(BWMBIN-1, 0, "outC", makereg);
	outD.output(BWMBIN-1, 0, "outD", makereg);
	validin.input("validin"); // this input shows if there are valid delayed inputs in other BXAs
	validout.output("validout");
	clk.input("clk");

beginmodule

	inA.wire(BWMBIN-1, 0, "inA");
	inB.wire(BWMBIN-1, 0, "inB");
	inC.wire(BWMBIN-1, 0, "inC");
	inD.wire(BWMBIN-1, 0, "inD");
	inAr.reg(BWMBIN-1, 0, "inAr");
	inBr.reg(BWMBIN-1, 0, "inBr");
	inCr.reg(BWMBIN-1, 0, "inCr");
	inDr.reg(BWMBIN-1, 0, "inDr");
	validABCD.reg(3, 0, "validABCD"); // all four valid flags from all delayed stubs

	Reg(vA);
	Reg(vB);
	Reg(vC);
	Reg(vD);

	assign inA = inAp; // This assignment is historical. There was a register, which is now in the wrapper.
	assign inB = inBp;
	assign inC = inCp;
	assign inD = inDp;

	always (posedge (clk))
	begin

		vA = inAr(BWPHI+BWQB-1, BWPHI) != 0;
		vB = inBr(BWPHI+BWQB-1, BWPHI) != 0;
		vC = inCr(BWPHI+BWQB-1, BWPHI) != 0;
		vD = inDr(BWPHI+BWQB-1, BWPHI) != 0;

		validABCD = (vA, vB, vC, vD);	

		If (!validin) // no stubs in other BXAs - just copy delayed stubs to the output
		begin
			outA = inAr; 
			outB = inBr; 
			outC = inCr;
			outD = inDr;
		end
		Else
		begin // there are some stubs in other BXAs - so take appropriate stubs from the next clock to the output

			begincase (validABCD)
				case1("4'b1111")    begin outA = inAr; outB = inBr; outC = inCr; outD = inDr; end // all four stubs are valid
				case1("4'b1110")    begin outA = inAr; outB = inBr; outC = inCr; outD = inA;  end // ABC valid
				case1("4'b1100")    begin outA = inAr; outB = inBr; outC = inA;  outD = inB;  end // AB valid
				case1("4'b1000")    begin outA = inAr; outB = inA;  outC = inB;  outD = inC;  end // A valid
				case1("4'b0000")    begin outA = inA;  outB = inB;  outC = inC;  outD = inD;  end // no valid stubs
				Default             begin outA = inAr; outB = inBr; outC = inCr; outD = inDr; end // should never happen
			endcase
		end
	
		inAr = inA; // register all stubs for one-bx history
		inBr = inB;
		inCr = inC;
		inDr = inD;

	end

	assign validout = inAr(BWPHI+BWQB-1, BWPHI) != 0;
	// "valid" output shows if there were any valid stubs in the current (not delayed) inputs
	// it is necessary for other bxa units to understand if their current stubs are needed on the next clock

	
endmodule
}

