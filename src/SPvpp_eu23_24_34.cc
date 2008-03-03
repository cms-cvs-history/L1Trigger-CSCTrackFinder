#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu23_24_34.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>
void SPvpp_eu23_24_34::operator()
(
	Signal meA,
	Signal meB,
	Signal eq,
	Signal MinEta, 
	Signal MaxEta, 
	Signal EtaWindow,
	Signal control
)
{
initio
		
	meA.input(BWMEIN-1, 0, "meA");
	meB.input(BWMEIN-1, 0, "meB");
	eq.output("eq",makereg);
	MinEta.input(BWETAIN-1,0,"MinEta");
	MaxEta.input(BWETAIN-1,0,"MaxEta");
	EtaWindow.input(BWETAIN,0,"EtaWindow");
	Input_(control, 1, 0); // {"allow q = 2", "allow q = 1"}

beginmodule
	qA.reg(BWQ-1,0,"qA");
	qB.reg(BWQ-1,0,"qB");
	etaA.reg(BWETAIN-1,0,"etaA");
	etaB.reg(BWETAIN-1,0,"etaB");
	phiA.reg(BWPHI-3,0,"phiA");
	phiB.reg(BWPHI-3,0,"phiB");
	amA.reg("amA");
	amB.reg("amB");

	Deta.reg(BWETAIN,0,"Deta");
	Dphi.reg(BWPHI-3,0,"Dphi");
	
	CSCidA.reg(BWCSCID-1, 0, "CSCidA");
	CSCidB.reg(BWCSCID-1, 0, "CSCidB");
	validA.reg ("validA");
	validB.reg ("validB");

modulebody

	always (meA or meB or MinEta or MaxEta or EtaWindow or control)	
	begin

		(validA, CSCidA, qA, /*amA,*/ etaA, phiA) = meA(BWMEIN-1, 2); // do not take 2 LSBs of phi
		(validB, CSCidB, qB, /*amB,*/ etaB, phiB) = meB(BWMEIN-1, 2);

		amA = ifelse((qA < 3), 1, 0);
		amB = ifelse((qB < 3), 1, 0);

		If(etaA > etaB) Deta = (etaA - etaB); Else Deta = (etaB - etaA);
		If(phiA > phiB) Dphi = (phiA - phiB); Else Dphi = (phiB - phiA);
		eq = 0;

		If 
		(
//			(!amA || !amB) &&
			(etaA <= MaxEta) && (etaA >= MinEta) && (etaB <= MaxEta) && (etaB >= MinEta) &&
			(Deta <= EtaWindow) &&
			(Dphi(9,7) == 0) &&
			(qA != 0) && (qA != 1 || control(0)) && (qA != 2 || control(1)) && 
			(qB != 0) && (qB != 1 || control(0)) && (qB != 2 || control(1)) &&
			validA && validB 
		) 
		begin
			eq = 1;
		end
	end

endmodule
}
