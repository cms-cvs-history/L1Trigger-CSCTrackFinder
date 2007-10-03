#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu12.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>



void SPvpp_eu12::operator()
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
	eq.output(1,0,"eq",makereg);
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
	eta.reg(BWETAIN-1,0,"eta");
	phiA.reg(BWPHI-3,0,"phiA");
	phiB.reg(BWPHI-3,0,"phiB");
	CSCidA.reg(BWCSCID-1, 0, "CSCidA");
	CSCidB.reg(BWCSCID-1, 0, "CSCidB");
	CSCidY.reg(BWCSCID-1, 0, "CSCidY");
	CSCidZ.reg(BWCSCID-1, 0, "CSCidZ");
	Dphi.reg(BWPHI-3,0,"Dphi");
	validA.reg("validA");
	validB.reg("validB");

	HighP12.init(6,0,"_HighP12");
	MedP12.init(6,0,"_MedP12");
	LowP12.init(6,0,"_LowP12");

	
	always (meA or meB or passX or passY or meY or passZ or meZ or control)	
	begin

		(validA, CSCidA, qA, /*amA,*/ etaA, phiA) = meA(BWMEIN-1, 2); // do not take 2 LSBs of phi
		(validB, CSCidB, qB, /*amB,*/ etaB, phiB) = meB(BWMEIN-1, 2);
		CSCidY = meY(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);
		CSCidZ = meZ(BWCSCID+BWQ+BWETAIN+BWPHI-1, BWQ+BWETAIN+BWPHI);

		eta = etaB;

		If(phiA > phiB) Dphi = (phiA - phiB); Else Dphi = (phiB - phiA);
	
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
			If (Dphi(6,0) <= HighP12(eta)) eq = 3; Else
			If (Dphi(6,0) <= MedP12 (eta)) eq = 2; Else
			If (Dphi(6,0) <= LowP12 (eta)) eq = 1;
		end
	end
endmodule
}




Signal SPvpp_HighPt12::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin
		begincase (eta(BWETAIN-1, 1))
			case1("6'd00") result =  0; case1("6'd01") result =  0; case1("6'd02") result =  0; case1("6'd03") result =  0; case1("6'd04") result =  0; case1("6'd05") result =  0; case1("6'd06") result =  0; case1("6'd07") result =  0;
			case1("6'd08") result =  0; case1("6'd09") result =  0; case1("6'd10") result =  0; case1("6'd11") result =  0; case1("6'd12") result =  5; case1("6'd13") result =  4; case1("6'd14") result =  4; case1("6'd15") result =  4; 
			case1("6'd16") result =  4; case1("6'd17") result =  4; case1("6'd18") result =  4; case1("6'd19") result =  5; case1("6'd20") result =  4; case1("6'd21") result =  5; case1("6'd22") result =  5; case1("6'd23") result =  5; 
			case1("6'd24") result =  5; case1("6'd25") result =  5; case1("6'd26") result =  4; case1("6'd27") result =  7; case1("6'd28") result =  9; case1("6'd29") result = 12; case1("6'd30") result = 12; case1("6'd31") result = 11; 
			case1("6'd32") result = 11; case1("6'd33") result = 11; case1("6'd34") result = 11; case1("6'd35") result = 10; case1("6'd36") result = 10; case1("6'd37") result = 10; case1("6'd38") result =  9; case1("6'd39") result =  9; 
			case1("6'd40") result =  9; case1("6'd41") result =  8; case1("6'd42") result =  9; case1("6'd43") result =  8; case1("6'd44") result =  8; case1("6'd45") result =  7; case1("6'd46") result =  7; case1("6'd47") result =  6; 
			case1("6'd48") result =  7; case1("6'd49") result =  7; case1("6'd50") result =  7; case1("6'd51") result =  7; case1("6'd52") result =  7; case1("6'd53") result =  6; case1("6'd54") result =  6; case1("6'd55") result =  6; 
			case1("6'd56") result =  5; case1("6'd57") result =  5; case1("6'd58") result =  5; case1("6'd59") result =  5; case1("6'd60") result =  5; case1("6'd61") result =  7; case1("6'd62") result =  0; case1("6'd63") result =  0; 
		endcase
	end
endfunction
}

Signal SPvpp_MedPt12::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin
		begincase (eta(BWETAIN-1, 1))
			case1("6'd00") result = 127; case1("6'd01") result = 127; case1("6'd02") result = 127; case1("6'd03") result = 127; case1("6'd04") result =  8; case1("6'd05") result =  8; case1("6'd06") result = 11; case1("6'd07") result =  13;
			case1("6'd08") result =  13; case1("6'd09") result =  11; case1("6'd10") result = 127; case1("6'd11") result = 127; case1("6'd12") result = 16; case1("6'd13") result = 15; case1("6'd14") result = 15; case1("6'd15") result =  15; 
			case1("6'd16") result =  16; case1("6'd17") result =  17; case1("6'd18") result =  17; case1("6'd19") result =  17; case1("6'd20") result = 18; case1("6'd21") result = 18; case1("6'd22") result = 17; case1("6'd23") result =  18; 
			case1("6'd24") result =  19; case1("6'd25") result =  19; case1("6'd26") result =  19; case1("6'd27") result =  29; case1("6'd28") result = 35; case1("6'd29") result = 40; case1("6'd30") result = 44; case1("6'd31") result =  43; 
			case1("6'd32") result =  42; case1("6'd33") result =  42; case1("6'd34") result =  42; case1("6'd35") result =  43; case1("6'd36") result = 44; case1("6'd37") result = 41; case1("6'd38") result = 38; case1("6'd39") result =  38; 
			case1("6'd40") result =  38; case1("6'd41") result =  40; case1("6'd42") result =  40; case1("6'd43") result =  36; case1("6'd44") result = 35; case1("6'd45") result = 35; case1("6'd46") result = 36; case1("6'd47") result =  35; 
			case1("6'd48") result =  33; case1("6'd49") result =  32; case1("6'd50") result =  31; case1("6'd51") result =  30; case1("6'd52") result = 30; case1("6'd53") result = 33; case1("6'd54") result = 34; case1("6'd55") result =  29; 
			case1("6'd56") result =  27; case1("6'd57") result =  28; case1("6'd58") result =  27; case1("6'd59") result =  30; case1("6'd60") result = 28; case1("6'd61") result = 26; case1("6'd62") result = 15; case1("6'd63") result = 127; 
		endcase
	end
endfunction
}

Signal SPvpp_LowPt12::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin
		begincase (eta(BWETAIN-1, 1))
			case1("6'd00") result = 127; case1("6'd01") result = 127; case1("6'd02") result = 127; case1("6'd03") result = 125; case1("6'd04") result =  57; case1("6'd05") result =  45; case1("6'd06") result = 41; case1("6'd07") result =  42;
			case1("6'd08") result =  42; case1("6'd09") result =  31; case1("6'd10") result = 127; case1("6'd11") result = 127; case1("6'd12") result =  29; case1("6'd13") result =  28; case1("6'd14") result = 29; case1("6'd15") result =  30; 
			case1("6'd16") result =  35; case1("6'd17") result =  37; case1("6'd18") result =  34; case1("6'd19") result =  34; case1("6'd20") result =  36; case1("6'd21") result =  37; case1("6'd22") result = 37; case1("6'd23") result =  37; 
			case1("6'd24") result =  39; case1("6'd25") result =  40; case1("6'd26") result =  52; case1("6'd27") result = 126; case1("6'd28") result = 104; case1("6'd29") result = 104; case1("6'd30") result = 87; case1("6'd31") result =  90; 
			case1("6'd32") result =  93; case1("6'd33") result =  87; case1("6'd34") result =  85; case1("6'd35") result =  82; case1("6'd36") result =  80; case1("6'd37") result =  79; case1("6'd38") result = 82; case1("6'd39") result =  79; 
			case1("6'd40") result =  79; case1("6'd41") result =  77; case1("6'd42") result =  75; case1("6'd43") result =  75; case1("6'd44") result =  67; case1("6'd45") result =  67; case1("6'd46") result = 69; case1("6'd47") result =  68; 
			case1("6'd48") result =  67; case1("6'd49") result =  65; case1("6'd50") result =  65; case1("6'd51") result =  64; case1("6'd52") result =  60; case1("6'd53") result =  58; case1("6'd54") result = 57; case1("6'd55") result =  57; 
			case1("6'd56") result =  57; case1("6'd57") result =  55; case1("6'd58") result =  53; case1("6'd59") result =  51; case1("6'd60") result =  49; case1("6'd61") result =  46; case1("6'd62") result = 36; case1("6'd63") result = 127; 
		endcase
	end
endfunction
}
