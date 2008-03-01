#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu2b1.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_eu2b1::operator()
(
	Signal meA,
	Signal mbB,
	Signal eq,
	Signal MinEta, 
	Signal MaxEta
)
{
initio
	meA.input(BWMEIN-1, 0, "meA");
	mbB.input(BWMBIN-1, 0, "mbB");
	eq.output(1,0,"eq",makereg);
	MinEta.input(BWETAIN-1,0,"MinEta");
	MaxEta.input(BWETAIN-1,0,"MaxEta");

beginmodule
	qA.reg(BWQ-1,0,"qA");
	qB.reg(BWQB-1,0,"qB");
	eta.reg(BWETAIN-1,0,"eta");
	phiA.reg(BWPHI-3,0,"phiA");
	phiB.reg(BWPHI-3,0,"phiB");

	Dphi.reg(BWPHI-3,0,"Dphi");
	
	CSCidA.reg(BWCSCID-1, 0, "CSCidA");
	validA.reg ("validA");
	validB.reg ("validB");

	HighP2b1.init(6,0,"_HighP2b1");
	MedP2b1.init(6,0,"_MedP2b1");
	LowP2b1.init(6,0,"_LowP2b1");

modulebody

	always (meA or mbB or MinEta or MaxEta)	
	begin

		(validA, CSCidA, qA, eta, phiA) = meA(BWMEIN-1, 2); // do not take 2 LSBs of phi
		(validB, qB, phiB) = mbB(BWMBIN-1, 2);

		If(phiA > phiB) Dphi = (phiA - phiB); Else Dphi = (phiB - phiA);

		eq = 0;

		If 
		(
			(eta <= MaxEta) && (eta >= MinEta) &&
			(Dphi(9,7) == 0) &&
			(qA != 0) && (qA != 3) && (qA != 4) && 
			(qB != 0) &&
			validA //&& validB
		) 
		begin
			If (Dphi(6,0) <= HighP2b1(eta)) eq = 3; Else
			If (Dphi(6,0) <= MedP2b1 (eta)) eq = 2; Else
			If (Dphi(6,0) <= LowP2b1 (eta)) eq = 1;
		end
	end

endmodule
}


Signal SPvpp_HighPt2b1::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction	
	begin
		begincase (eta(BWETAIN-1,1))
			case1(Signal(6, 00)) result =  0; case1(Signal(6, 01)) result =  0; case1(Signal(6, 02)) result =  0; case1(Signal(6, 03)) result = 12; case1(Signal(6, 04)) result = 11; case1(Signal(6, 05)) result = 11; case1(Signal(6, 06)) result = 10; case1(Signal(6, 07)) result =  9;
			case1(Signal(6,  8)) result =  8; case1(Signal(6,  9)) result =  8; case1(Signal(6, 10)) result =  7; case1(Signal(6, 11)) result =  7; case1(Signal(6, 12)) result =  7; case1(Signal(6, 13)) result =  6; case1(Signal(6, 14)) result =  0; case1(Signal(6, 15)) result =  0; 
			case1(Signal(6, 16)) result =  0; case1(Signal(6, 17)) result =  0; case1(Signal(6, 18)) result =  0; case1(Signal(6, 19)) result =  0; case1(Signal(6, 20)) result =  0; case1(Signal(6, 21)) result =  0; case1(Signal(6, 22)) result =  0; case1(Signal(6, 23)) result =  0; 
			case1(Signal(6, 24)) result =  0; case1(Signal(6, 25)) result =  0; case1(Signal(6, 26)) result =  0; case1(Signal(6, 27)) result =  0; case1(Signal(6, 28)) result =  0; case1(Signal(6, 29)) result =  0; case1(Signal(6, 30)) result =  0; case1(Signal(6, 31)) result =  0; 
			case1(Signal(6, 32)) result =  0; case1(Signal(6, 33)) result =  0; case1(Signal(6, 34)) result =  0; case1(Signal(6, 35)) result =  0; case1(Signal(6, 36)) result =  0; case1(Signal(6, 37)) result =  0; case1(Signal(6, 38)) result =  0; case1(Signal(6, 39)) result =  0; 
			case1(Signal(6, 40)) result =  0; case1(Signal(6, 41)) result =  0; case1(Signal(6, 42)) result =  0; case1(Signal(6, 43)) result =  0; case1(Signal(6, 44)) result =  0; case1(Signal(6, 45)) result =  0; case1(Signal(6, 46)) result =  0; case1(Signal(6, 47)) result =  0; 
			case1(Signal(6, 48)) result =  0; case1(Signal(6, 49)) result =  0; case1(Signal(6, 50)) result =  0; case1(Signal(6, 51)) result =  0; case1(Signal(6, 52)) result =  0; case1(Signal(6, 53)) result =  0; case1(Signal(6, 54)) result =  0; case1(Signal(6, 55)) result =  0; 
			case1(Signal(6, 56)) result =  0; case1(Signal(6, 57)) result =  0; case1(Signal(6, 58)) result =  0; case1(Signal(6, 59)) result =  0; case1(Signal(6, 60)) result =  0; case1(Signal(6, 61)) result =  0; case1(Signal(6, 62)) result =  0; case1(Signal(6, 63)) result =  0; 
		endcase
	end
endfunction
}

Signal SPvpp_MedPt2b1::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin
		begincase (eta(BWETAIN-1,1))
			case1(Signal(6, 00)) result = 127; case1(Signal(6, 01)) result = 127; case1(Signal(6, 02)) result = 127; case1(Signal(6, 03)) result = 127; case1(Signal(6, 04)) result =  39; case1(Signal(6, 05)) result =  39; case1(Signal(6, 06)) result =   39; case1(Signal(6, 07)) result =  36;
			case1(Signal(6,  8)) result =  33; case1(Signal(6,  9)) result =  30; case1(Signal(6, 10)) result =  29; case1(Signal(6, 11)) result =  25; case1(Signal(6, 12)) result =  25; case1(Signal(6, 13)) result =  23; case1(Signal(6, 14)) result =  127; case1(Signal(6, 15)) result = 127; 
			case1(Signal(6, 16)) result = 127; case1(Signal(6, 17)) result = 127; case1(Signal(6, 18)) result = 127; case1(Signal(6, 19)) result = 127; case1(Signal(6, 20)) result = 127; case1(Signal(6, 21)) result = 127; case1(Signal(6, 22)) result =  127; case1(Signal(6, 23)) result = 127; 
			case1(Signal(6, 24)) result = 127; case1(Signal(6, 25)) result = 127; case1(Signal(6, 26)) result = 127; case1(Signal(6, 27)) result = 127; case1(Signal(6, 28)) result = 127; case1(Signal(6, 29)) result = 127; case1(Signal(6, 30)) result =  127; case1(Signal(6, 31)) result = 127; 
			case1(Signal(6, 32)) result = 127; case1(Signal(6, 33)) result = 127; case1(Signal(6, 34)) result = 127; case1(Signal(6, 35)) result = 127; case1(Signal(6, 36)) result = 127; case1(Signal(6, 37)) result = 127; case1(Signal(6, 38)) result =  127; case1(Signal(6, 39)) result = 127; 
			case1(Signal(6, 40)) result = 127; case1(Signal(6, 41)) result = 127; case1(Signal(6, 42)) result = 127; case1(Signal(6, 43)) result = 127; case1(Signal(6, 44)) result = 127; case1(Signal(6, 45)) result = 127; case1(Signal(6, 46)) result =  127; case1(Signal(6, 47)) result = 127; 
			case1(Signal(6, 48)) result = 127; case1(Signal(6, 49)) result = 127; case1(Signal(6, 50)) result = 127; case1(Signal(6, 51)) result = 127; case1(Signal(6, 52)) result = 127; case1(Signal(6, 53)) result = 127; case1(Signal(6, 54)) result =  127; case1(Signal(6, 55)) result = 127; 
			case1(Signal(6, 56)) result = 127; case1(Signal(6, 57)) result = 127; case1(Signal(6, 58)) result = 127; case1(Signal(6, 59)) result = 127; case1(Signal(6, 60)) result = 127; case1(Signal(6, 61)) result = 127; case1(Signal(6, 62)) result =  127; case1(Signal(6, 63)) result = 127; 
		endcase
	end
endfunction
}

Signal SPvpp_LowPt2b1::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin
		begincase (eta(BWETAIN-1,1))
			case1(Signal(6, 00)) result = 127; case1(Signal(6, 01)) result = 127; case1(Signal(6, 02)) result = 127; case1(Signal(6, 03)) result = 127; case1(Signal(6, 04)) result =  90; case1(Signal(6, 05)) result =  78; case1(Signal(6, 06)) result =  76; case1(Signal(6, 07)) result =  76;
			case1(Signal(6,  8)) result =  66; case1(Signal(6,  9)) result =  65; case1(Signal(6, 10)) result =  59; case1(Signal(6, 11)) result =  50; case1(Signal(6, 12)) result =  50; case1(Signal(6, 13)) result =  49; case1(Signal(6, 14)) result =  37; case1(Signal(6, 15)) result = 127; 
			case1(Signal(6, 16)) result = 127; case1(Signal(6, 17)) result = 127; case1(Signal(6, 18)) result = 127; case1(Signal(6, 19)) result = 127; case1(Signal(6, 20)) result = 127; case1(Signal(6, 21)) result = 127; case1(Signal(6, 22)) result = 127; case1(Signal(6, 23)) result = 127; 
			case1(Signal(6, 24)) result = 127; case1(Signal(6, 25)) result = 127; case1(Signal(6, 26)) result = 127; case1(Signal(6, 27)) result = 127; case1(Signal(6, 28)) result = 127; case1(Signal(6, 29)) result = 127; case1(Signal(6, 30)) result = 127; case1(Signal(6, 31)) result = 127; 
			case1(Signal(6, 32)) result = 127; case1(Signal(6, 33)) result = 127; case1(Signal(6, 34)) result = 127; case1(Signal(6, 35)) result = 127; case1(Signal(6, 36)) result = 127; case1(Signal(6, 37)) result = 127; case1(Signal(6, 38)) result = 127; case1(Signal(6, 39)) result = 127; 
			case1(Signal(6, 40)) result = 127; case1(Signal(6, 41)) result = 127; case1(Signal(6, 42)) result = 127; case1(Signal(6, 43)) result = 127; case1(Signal(6, 44)) result = 127; case1(Signal(6, 45)) result = 127; case1(Signal(6, 46)) result = 127; case1(Signal(6, 47)) result = 127; 
			case1(Signal(6, 48)) result = 127; case1(Signal(6, 49)) result = 127; case1(Signal(6, 50)) result = 127; case1(Signal(6, 51)) result = 127; case1(Signal(6, 52)) result = 127; case1(Signal(6, 53)) result = 127; case1(Signal(6, 54)) result = 127; case1(Signal(6, 55)) result = 127; 
			case1(Signal(6, 56)) result = 127; case1(Signal(6, 57)) result = 127; case1(Signal(6, 58)) result = 127; case1(Signal(6, 59)) result = 127; case1(Signal(6, 60)) result = 127; case1(Signal(6, 61)) result = 127; case1(Signal(6, 62)) result = 127; case1(Signal(6, 63)) result = 127; 
		endcase
	end
endfunction
}
	

