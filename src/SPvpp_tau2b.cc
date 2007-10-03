#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau2b.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_tau2b::operator()
(
	Signal mb21,
	Signal mb22,
	Signal me21,
	Signal idl, Signal idm, Signal idh,
	Signal rank
)
{
initio

	mb21.input(7, 0, "mb21");
	mb22.input(3, 0, "mb22");
	me21.input(5, 0, "me21");

	idl.output(2,0,"idl",makereg);
	idm.output(2,0,"idm",makereg);
	idh.output(2,0,"idh",makereg);
	rank.output(5,0,"rank", makereg);

beginmodule
	
	b21.reg(1, 0, 3, 0, "b21");
	b22.reg(3, 0, "b22");	
	e21.reg(5, 0, "e21");

	Maxb21p.init(4,0,"_Maxb21p");
	Max21bp.init(3,0,"_Max21bp");
	Maxb22p.init(3,0,"_Maxb22p");

	maxb21.reg(4,0,"maxb21");
	max21.reg(3,0,"max21");
	maxb22.reg(3,0,"maxb22");
	quality.reg(3,0,"quality");


	always (mb21 or mb22 or me21)
	begin
		(b21[3], b21[2], b21[1], b21[0]) = mb21;
		b22 = mb22;
		e21 = me21;

	    max21  = Max21bp(e21);
	    maxb21 = Maxb21p(b21[0], b21[1], b21[2], b21[3]);
	    maxb22 = Maxb22p(b22);

	    quality = (maxb21(1,0), maxb22(0), max21(0));
	    idl = maxb21(4,2);
	    idm = maxb22(3,1);
	    idh = max21 (3,1);

  		begincase (quality)
		    case1("4'b0001") rank = 6; //
		    case1("4'b0010") rank = 7;
		    case1("4'b0011") rank = 8;
		    case1("4'b0100") rank = 9;
		    case1("4'b1000") rank ="6'hc";
		    case1("4'b1100") rank ="6'hf";
		    case1("4'b0101") rank ="6'h13";
		    case1("4'b0110") rank ="6'h14";
		    case1("4'b1001") rank ="6'h18";
		    case1("4'b1010") rank ="6'h19";
		    case1("4'b1101") rank ="6'h1d";
		    case1("4'b1110") rank ="6'h1e";
		    case1("4'b0111") rank ="6'h20";
		    case1("4'b1011") rank ="6'h22";
		    case1("4'b1111") rank ="6'h24";
    		Default rank = 0;
	  	endcase
	end

endmodule
}


Signal SPvpp_Maxb21::operator()(Signal mb21a, Signal mb21b, Signal mb21c, Signal mb21d)
{
initio
	mb21a.input(1,0,"mb21a");
	mb21b.input(1,0,"mb21b");
	mb21c.input(1,0,"mb21c");
	mb21d.input(1,0,"mb21d");

beginfunction
	begin
		result(1) = mb21a(1) | mb21b(1) | mb21c(1) | mb21d(1);
		result(0) = (!result(1) & (mb21a(0) | mb21b(0) | mb21c(0) | mb21d(0))) |
         			(mb21a(1) & mb21a(0)) | (mb21b(1) & mb21b(0)) |
         			(mb21c(1) & mb21c(0)) | (mb21d(1) & mb21d(0));		
          			
       	result(4,2) = 
       		ifelse (result(1,0) == 0, 0,
       		ifelse (result(1,0) == mb21a, 1,
       		ifelse (result(1,0) == mb21b, 2,
       		ifelse (result(1,0) == mb21c, 3,
       		ifelse (result(1,0) == mb21d, 4, 0)))));
	end
endfunction
}

	
Signal SPvpp_Max21b::operator()(Signal me21)
{
initio
	me21.input(5,0,"me21");
beginfunction
	begin
	
		result(0) = me21(0) | me21(1) | me21(2) | me21(3) | me21(4) | me21(5);
		result(3,1) = 
			ifelse (me21(0) == 1, 1,
			ifelse (me21(1) == 1, 2,
			ifelse (me21(2) == 1, 3,
			ifelse (me21(3) == 1, 4,
			ifelse (me21(4) == 1, 5,
			ifelse (me21(5) == 1, 6, 0))))));
	end			
endfunction
}


Signal SPvpp_Maxb22::operator()(Signal mb)
{
initio
	mb.input(3,0,"mb");
beginfunction
	begin
	
		result(0) = mb(0) | mb(1) | mb(2) | mb(3);
		result(3,1) = 
			ifelse (mb(0) == 1, 1,
			ifelse (mb(1) == 1, 2,
			ifelse (mb(2) == 1, 3, 
			ifelse (mb(3) == 1, 4, 0))));
	end
endfunction
}

