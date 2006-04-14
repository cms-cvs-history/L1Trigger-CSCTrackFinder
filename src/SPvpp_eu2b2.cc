#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu2b2.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_eu2b2::operator()
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
	eq.output("eq",makereg);
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

	always (meA or mbB or MinEta or MaxEta or eta)	
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
			eq = 1;
		end
	end

endmodule
}

