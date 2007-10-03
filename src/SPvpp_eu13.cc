#include <L1Trigger/CSCTrackFinder/src/SPvpp_eu13.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_eu13::operator()
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

	HighP13.init(6,0,"_HighP13");
	MedP13.init(6,0,"_MedP13");
	LowP13.init(6,0,"_LowP13");

	
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
			If (Dphi(6,0) <= HighP13(eta)) eq = 3; Else
			If (Dphi(6,0) <= MedP13 (eta)) eq = 2; Else
			If (Dphi(6,0) <= LowP13 (eta)) eq = 1;
		end
	end
endmodule
}


Signal SPvpp_HighPt13::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin	
		begincase (eta(BWETAIN-1,1))
			case1("6'd00") result =  0; case1("6'd01") result =  0; case1("6'd02") result =  0; case1("6'd03") result =  0; case1("6'd04") result =  0; case1("6'd05") result =  0; case1("6'd06") result =  0; case1("6'd07") result =  0;
			case1("6'd08") result =  3; case1("6'd09") result =  0; case1("6'd10") result =  0; case1("6'd11") result =  0; case1("6'd12") result =  6; case1("6'd13") result =  5; case1("6'd14") result =  5; case1("6'd15") result =  5; 
			case1("6'd16") result =  5; case1("6'd17") result =  6; case1("6'd18") result =  6; case1("6'd19") result =  6; case1("6'd20") result =  6; case1("6'd21") result =  6; case1("6'd22") result =  6; case1("6'd23") result =  7; 
			case1("6'd24") result =  7; case1("6'd25") result =  7; case1("6'd26") result =  7; case1("6'd27") result =  8; case1("6'd28") result = 10; case1("6'd29") result = 13; case1("6'd30") result = 13; case1("6'd31") result = 13; 
			case1("6'd32") result = 13; case1("6'd33") result = 12; case1("6'd34") result = 13; case1("6'd35") result = 12; case1("6'd36") result = 12; case1("6'd37") result = 12; case1("6'd38") result = 11; case1("6'd39") result = 11; 
			case1("6'd40") result = 11; case1("6'd41") result = 10; case1("6'd42") result = 11; case1("6'd43") result = 10; case1("6'd44") result = 10; case1("6'd45") result =  9; case1("6'd46") result =  9; case1("6'd47") result =  8; 
			case1("6'd48") result =  8; case1("6'd49") result =  9; case1("6'd50") result =  9; case1("6'd51") result =  8; case1("6'd52") result =  8; case1("6'd53") result =  7; case1("6'd54") result =  7; case1("6'd55") result =  7; 
			case1("6'd56") result =  7; case1("6'd57") result =  6; case1("6'd58") result =  7; case1("6'd59") result =  6; case1("6'd60") result =  7; case1("6'd61") result =  8; case1("6'd62") result =  0; case1("6'd63") result =  0; 
		endcase
	end
endfunction
}

Signal SPvpp_MedPt13::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin	
		begincase (eta(BWETAIN-1,1))
			case1("6'd00") result = 127; case1("6'd01") result = 127; case1("6'd02") result = 127; case1("6'd03") result = 127; case1("6'd04") result = 127; case1("6'd05") result = 127; case1("6'd06") result =  127; case1("6'd07") result =  37;
			case1("6'd08") result =  37; case1("6'd09") result =  12; case1("6'd10") result = 127; case1("6'd11") result = 127; case1("6'd12") result =  22; case1("6'd13") result =  21; case1("6'd14") result =   21; case1("6'd15") result =  21; 
			case1("6'd16") result =  24; case1("6'd17") result =  24; case1("6'd18") result =  24; case1("6'd19") result =  24; case1("6'd20") result =  24; case1("6'd21") result =  24; case1("6'd22") result =   25; case1("6'd23") result =  25; 
			case1("6'd24") result =  28; case1("6'd25") result =  28; case1("6'd26") result =  27; case1("6'd27") result =  34; case1("6'd28") result =  39; case1("6'd29") result =  46; case1("6'd30") result =   49; case1("6'd31") result =  49; 
			case1("6'd32") result =  47; case1("6'd33") result =  44; case1("6'd34") result =  51; case1("6'd35") result =  47; case1("6'd36") result =  47; case1("6'd37") result =  47; case1("6'd38") result =   46; case1("6'd39") result =  47; 
			case1("6'd40") result =  51; case1("6'd41") result =  51; case1("6'd42") result =  48; case1("6'd43") result =  44; case1("6'd44") result =  42; case1("6'd45") result =  42; case1("6'd46") result =   41; case1("6'd47") result =  39; 
			case1("6'd48") result =  39; case1("6'd49") result =  41; case1("6'd50") result =  41; case1("6'd51") result =  39; case1("6'd52") result =  37; case1("6'd53") result =  38; case1("6'd54") result =   41; case1("6'd55") result =  35; 
			case1("6'd56") result =  33; case1("6'd57") result =  36; case1("6'd58") result =  33; case1("6'd59") result =  33; case1("6'd60") result =  35; case1("6'd61") result =  35; case1("6'd62") result =  125; case1("6'd63") result = 125; 
		endcase
	end
endfunction
}

Signal SPvpp_LowPt13::operator()(Signal eta)
{
initio
	eta.input(BWETAIN-1,0,"eta");
beginfunction
	begin	
		begincase (eta(BWETAIN-1,1))
			case1("6'd00") result = 127; case1("6'd01") result = 127; case1("6'd02") result = 127; case1("6'd03") result = 127; case1("6'd04") result = 127; case1("6'd05") result = 127; case1("6'd06") result = 40; case1("6'd07") result =  80;
			case1("6'd08") result =  80; case1("6'd09") result =  64; case1("6'd10") result = 127; case1("6'd11") result = 127; case1("6'd12") result =  62; case1("6'd13") result =  41; case1("6'd14") result = 41; case1("6'd15") result =  45; 
			case1("6'd16") result =  47; case1("6'd17") result =  48; case1("6'd18") result =  47; case1("6'd19") result =  46; case1("6'd20") result =  47; case1("6'd21") result =  50; case1("6'd22") result = 52; case1("6'd23") result =  51; 
			case1("6'd24") result =  53; case1("6'd25") result =  54; case1("6'd26") result =  55; case1("6'd27") result =  73; case1("6'd28") result =  82; case1("6'd29") result =  91; case1("6'd30") result = 91; case1("6'd31") result =  94; 
			case1("6'd32") result = 100; case1("6'd33") result =  99; case1("6'd34") result =  95; case1("6'd35") result =  94; case1("6'd36") result =  95; case1("6'd37") result =  91; case1("6'd38") result = 96; case1("6'd39") result =  96; 
			case1("6'd40") result =  94; case1("6'd41") result =  94; case1("6'd42") result =  88; case1("6'd43") result =  88; case1("6'd44") result =  80; case1("6'd45") result =  80; case1("6'd46") result = 84; case1("6'd47") result =  84; 
			case1("6'd48") result =  79; case1("6'd49") result =  78; case1("6'd50") result =  80; case1("6'd51") result =  78; case1("6'd52") result =  75; case1("6'd53") result =  72; case1("6'd54") result = 70; case1("6'd55") result =  71; 
			case1("6'd56") result =  69; case1("6'd57") result =  71; case1("6'd58") result =  71; case1("6'd59") result =  66; case1("6'd60") result =  61; case1("6'd61") result =  60; case1("6'd62") result = 43; case1("6'd63") result = 127; 
		endcase
	end
endfunction
}
	
	

