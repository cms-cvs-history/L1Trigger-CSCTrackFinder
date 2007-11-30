#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu23a.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>


// extrapolation unit for accelerator tracks
void SPvpp_eu23a::operator()
(
	Signal meA,
	Signal meB,
	Signal eq,
	Signal MinDeta, 
	Signal MaxDeta, 
	Signal MaxDphi,
//	Signal control,
	Signal clk
)
{
initio
		
	meA.input(BWMEIN-1, 0, "meA"); // first stub, from station with lower number
	meB.input(BWMEIN-1, 0, "meB"); // second stub, from station with higher number
	OutReg(eq);
	Input_(MinDeta, BWETAIN-1,0); // min eta difference
	Input_(MaxDeta, BWETAIN-1,0); // max eta difference
	Input_(MaxDphi, BWPHI-3,0);   // max phi difference
//	Input_(control, 1, 0); // {"allow q = 4", "allow q = 3"}
	Input (clk);

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

	Reg(eqold);
	Reg(eqnew);

	always (posedge(clk))	
	begin

		(validA, CSCidA, qA, etaA, phiA) = meA(BWMEIN-1, 2); // do not take 2 LSBs of phi
		(validB, CSCidB, qB, etaB, phiB) = meB(BWMEIN-1, 2);

		amA = ifelse((qA < 3), 1, 0);
		amB = ifelse((qB < 3), 1, 0);

		Deta = ifelse(etaA > etaB, cns(BWETAIN, 0), etaB - etaA); // etaB must be larger than etaA always
		Dphi = ifelse(phiA > phiB, phiA - phiB, phiB - phiA);

		eqold = eqnew;
		eqnew = 0;

		If 
		(
//			(amA && amB) &&
			(Deta <= MaxDeta) && (Deta >= MinDeta) &&
			(Dphi <= MaxDphi) &&
			(qA != 0) && (qA != 3 /*|| control(0)*/) && (qA != 4 /*|| control(1)*/) && 
			(qB != 0) && (qB != 3 /*|| control(0)*/) && (qB != 4 /*|| control(1)*/) &&
			validA && validB 
		) 
		begin
			eqnew = 1;
		end

		eq = (!eqold) && eqnew; // output is true only at transition 0->1, to prevent multiple triggers due to BXA
	
	end

endmodule
}
