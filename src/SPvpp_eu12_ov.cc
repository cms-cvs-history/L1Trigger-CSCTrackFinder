#include<L1Trigger/CSCTrackFinder/src/SPvpp_eu12_ov.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_eu12_ov::operator()
(
	Signal meA,
	Signal meB,
	Signal eq, 
	Signal passX,
	Signal passY, Signal meY,
	Signal passZ, Signal meZ,
	Signal control
)
{
initio
	meA.input(BWMEIN-1, 0, "meA");
	meB.input(BWMEIN-1, 0, "meB");
	eq.output("eq",makereg);
	passX.input("passX");
	passY.input("passY");
	meY.input(BWMEIN-1, 0, "meY");
	passZ.input("passZ");
	meZ.input(BWMEIN-1, 0, "meZ");
	Input_(control, 1, 0); // {"allow q = 4", "allow q = 3"}

beginmodule
	qA.reg(BWQ-1,0,"qA");
	qB.reg(BWQ-1,0,"qB");
	etaA.reg(BWETAIN-1,0,"etaA");
	etaB.reg(BWETAIN-1,0,"etaB");
	phiA.reg(BWPHI-3,0,"phiA");
	phiB.reg(BWPHI-3,0,"phiB");
	CSCidA.reg(BWCSCID-1, 0, "CSCidA");
	CSCidB.reg(BWCSCID-1, 0, "CSCidB");
	CSCidY.reg(BWCSCID-1, 0, "CSCidY");
	CSCidZ.reg(BWCSCID-1, 0, "CSCidZ");

	Dphi.reg(BWPHI-3,0,"Dphi");
	validA.reg ("validA");
	validB.reg ("validB");

modulebody

	always (meA or meB or passX or passY or meY or passZ or meZ or control)
	begin

		(validA, CSCidA, qA, /*amA,*/ etaA, phiA) = meA(BWMEIN-1, 2); // do not take 2 LSBs of phi
		(validB, CSCidB, qB, /*amB,*/ etaB, phiB) = meB(BWMEIN-1, 2);
		CSCidY = meY(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
		CSCidZ = meZ(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);

		If (phiA > phiB) Dphi = (phiA - phiB); Else Dphi = (phiB - phiA);

		eq = 0;
		If 
		(
			(
				    passX 
				|| (passY && CSCidA == CSCidY && CSCidA != 0) 
				|| (passZ && CSCidA == CSCidZ && CSCidA != 0)
			) &&

			(Dphi(9,7) == 0) &&
			(qA != 0) && (qA != 3 || control(0)) && (qA != 4 || control(1)) && 
			(qB != 0) && (qB != 3 || control(0)) && (qB != 4 || control(1)) &&
			validA && validB
		) 
		begin
			eq = 1;
		end
	end
endmodule
}
