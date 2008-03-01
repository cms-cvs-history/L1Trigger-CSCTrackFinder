#include <L1Trigger/CSCTrackFinder/src/SPvpp_dtbx.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>



void SPvpp_dtbx::operator()
(
	Signal mb1a,

	Signal mb1ap,
	Signal mb1bp,

	Signal clk
)
{
initio
	Input_(mb1a, BWMBIN-1,0);

	OutReg_(mb1ap, BWMBIN-1,0);
	OutReg_(mb1bp, BWMBIN-1,0);

	Input (clk);

beginmodule

	Reg_(mb1ar, BWMBIN-1,0);

modulebody

	always (posedge (clk))
	begin

		mb1ap = mb1ar;

		If (mb1a(BWMBIN-1))
		begin
			mb1bp = mb1a;
			mb1ar = 0;
		end
		Else
		begin
			mb1bp = 0;
			mb1ar = mb1a;
		end
	end

endmodule
}
