#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxame.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>



void SPvpp_bxame::operator()
(
	Signal inAp, Signal inBp, Signal inCp,
	Signal outA, Signal outB, Signal outC,
	Signal validin,
	Signal validout,
	Signal etaoff,
	Signal clk
)
{
initio
	inAp.input(BWMEIN-1, 0, "inAp");
	inBp.input(BWMEIN-1, 0, "inBp");
	inCp.input(BWMEIN-1, 0, "inCp");
	outA.output(BWMEIN-1, 0, "outA", makereg);
	outB.output(BWMEIN-1, 0, "outB", makereg);
	outC.output(BWMEIN-1, 0, "outC", makereg);
	validin.input("validin"); // this input shows if there are valid delayed inputs in other BXAs
	validout.output("validout");
	Input_(etaoff, BWETAIN-1, 0); // eta offset input
	clk.input("clk");

beginmodule

	inA.wire(BWMEIN-1, 0, "inA");
	inB.wire(BWMEIN-1, 0, "inB");
	inC.wire(BWMEIN-1, 0, "inC");
	inAr.reg(BWMEIN-1, 0, "inAr");
	inBr.reg(BWMEIN-1, 0, "inBr");
	inCr.reg(BWMEIN-1, 0, "inCr");
	validABC.reg(2, 0, "validABC"); // all three valid flags from all delayed stubs
	
	Wire_(etaA, BWETAIN-1, 0);
	Wire_(etaB, BWETAIN-1, 0);
	Wire_(etaC, BWETAIN-1, 0);

	// add offset to eta
	assign etaA = inAp(BWPHI+BWETAIN-1, BWPHI) + etaoff;
	assign etaB = inBp(BWPHI+BWETAIN-1, BWPHI) + etaoff;
	assign etaC = inCp(BWPHI+BWETAIN-1, BWPHI) + etaoff;

	assign inA = (inAp(BWMEIN-1, BWPHI+BWETAIN), etaA, inAp(BWPHI-1, 0)); 
	assign inB = (inBp(BWMEIN-1, BWPHI+BWETAIN), etaB, inBp(BWPHI-1, 0));
	assign inC = (inCp(BWMEIN-1, BWPHI+BWETAIN), etaC, inCp(BWPHI-1, 0));

	always (posedge (clk))
	begin

		validABC = (inAr(BWMEIN-1), inBr(BWMEIN-1), inCr(BWMEIN-1));	

		If (!validin) // no stubs in other BXAs - just copy delayed stubs to the output
		begin
			outA = inAr; 
			outB = inBr; 
			outC = inCr;
		end
		Else
		begin // there are some stubs in other BXAs - so take appropriate stubs from the next clock to the output

			begincase (validABC)
				case1("3'b111")    begin outA = inAr; outB = inBr; outC = inCr; end // all three stubs are valid
				case1("3'b110")    begin outA = inAr; outB = inBr; outC = inA;  end // A and B valid
				case1("3'b100")    begin outA = inAr; outB = inA;  outC = inB;  end // A valid
				case1("3'b000")    begin outA = inA;  outB = inB;  outC = inC;  end // no valid stubs
				Default            begin outA = inAr; outB = inBr; outC = inCr; end // should never happen
			endcase
		end
	
		inAr = inA; // register all stubs for one-bx history
		inBr = inB;
		inCr = inC;

	end

	assign validout = inAr(BWMEIN-1); 
	// "valid" output shows if there were any valid stubs in the current (not delayed) inputs
	// it is necessary for other bxa units to understand if their current stubs are needed on the next clock
		
endmodule
}

