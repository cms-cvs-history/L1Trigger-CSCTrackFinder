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

modulebody

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
		    case1(Signal(4, 1)) rank = 6; //
		    case1(Signal(4, 2)) rank = 7;
		    case1(Signal(4, 3)) rank = 8;
		    case1(Signal(4, 4)) rank = 9;
		    case1(Signal(4, 8)) rank =Signal(6, 0xc);
		    case1(Signal(4,12)) rank =Signal(6, 0xf);
		    case1(Signal(4, 5)) rank =Signal(6, 0x13);
		    case1(Signal(4, 6)) rank =Signal(6, 0x14);
		    case1(Signal(4, 9)) rank =Signal(6, 0x18);
		    case1(Signal(4,10)) rank =Signal(6, 0x19);
		    case1(Signal(4,13)) rank =Signal(6, 0x1d);
		    case1(Signal(4,14)) rank =Signal(6, 0x1e);
		    case1(Signal(4, 7)) rank =Signal(6, 0x20);
		    case1(Signal(4,11)) rank =Signal(6, 0x22);
		    case1(Signal(4,15)) rank =Signal(6, 0x24);
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

