#include <L1Trigger/CSCTrackFinder/src/SPvpp_etau12.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>


void SPvpp_etau12::operator()
(
	Signal meA,
	Signal meB,
	Signal pass,
	Signal MinEta, 
	Signal MaxEta, 
	Signal EtaWindow
)
{
initio
	Input_(meA, BWMEIN-1, 0);
	Input_(meB, BWMEIN-1, 0);
	OutReg(pass);
	Input_(MinEta, BWETAIN-1,0);
	Input_(MaxEta, BWETAIN-1,0);
	Input_(EtaWindow, BWETAIN,0);

beginmodule
	Reg_(qA, BWQ-1, 0);
	Reg_(qB, BWQ-1,0);
	Reg_(etaA, BWETAIN-1,0);
	Reg_(etaB, BWETAIN-1,0);
	Reg(amA);
	Reg(amB);

	Reg_(Deta, BWETAIN,0);

	always (meA or meB or MinEta or MaxEta or EtaWindow)	
	begin

		(qA, etaA) = meA(BWMEIN-1, BWPHI);
		(qB, etaB) = meB(BWMEIN-1, BWPHI);

		amA = ifelse((qA < 3), 1, 0);
		amB = ifelse((qB < 3), 1, 0);

		Deta = ifelse (etaA > etaB, etaA - etaB, etaB - etaA);

		pass = 0;

		If 
		(
//			(!amA || !amB) &&
			(etaA <= MaxEta) && (etaA >= MinEta) && (etaB <= MaxEta) && (etaB >= MinEta) &&
			(Deta <= EtaWindow)
		)
		begin
			pass = 1;
		end
	end
endmodule
}
