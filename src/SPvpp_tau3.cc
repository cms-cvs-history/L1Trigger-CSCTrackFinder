#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau3.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_tau3::operator()
(
	Signal me31,
	Signal me32, 
	Signal me34,
	Signal idl, Signal idm, Signal idh,
	Signal rank
)
{
initio	

	me31.input(11, 0, "me31");
	me32.input(2, 0, "me32");
	me34.input(2, 0, "me34");

	idl.output(2,0,"idl",makereg);
	idm.output(1,0,"idm",makereg);
	idh.output(1,0,"idh",makereg);

	rank.output(5,0,"rank", makereg);
	
beginmodule
	
	e31.reg(1, 0, 5, 0, "e31");
	e32.reg(2, 0, "e32");
	e34.reg(2, 0, "e34");

	Max31p.init(4,0,"_Max31p");
	Max3p.init(2,0,"_Max3p");
	
	max31.reg(4,0,"max31");
	max32.reg(2,0,"max32");
	max34.reg(2,0,"max34");
	quality.reg(3,0,"quality");

modulebody

	always (me31 or me32 or me34)
	begin
	    (e31[5], e31[4], e31[3], e31[2], e31[1], e31[0]) = me31;
		e32 = me32;
		e34 = me34;

	    max31 = Max31p(e31[0], e31[1], e31[2], e31[3], e31[4], e31[5]);
	    max32 = Max3p  (e32);
	    max34 = Max3p  (e34);
	    quality = (max31(1,0), max32(0), max34(0));
	    idl = max31(4,2);
	    idm = max32(2,1);
	    idh = max34(2,1);
  		begincase (quality)
		    case1(Signal(4, 1)) rank = 1;
		    case1(Signal(4, 2)) rank = 3; //  
		    case1(Signal(4, 3)) rank = 4; //
		    case1(Signal(4, 4)) rank = 5;
		    case1(Signal(4, 8)) rank = Signal(6, 0xa);
		    case1(Signal(4,12)) rank = Signal(6, 0xd);
		    case1(Signal(4, 5)) rank = Signal(6, 0x10);
		    case1(Signal(4, 6)) rank = Signal(6, 0x12); //
		    case1(Signal(4, 9)) rank = Signal(6, 0x15);
		    case1(Signal(4,10)) rank = Signal(6, 0x17); //
		    case1(Signal(4,13)) rank = Signal(6, 0x1a);
		    case1(Signal(4,14)) rank = Signal(6, 0x1c); //
		    case1(Signal(4, 7)) rank = Signal(6, 0x1f); //
		    case1(Signal(4,11)) rank = Signal(6, 0x21); //
		    case1(Signal(4,15)) rank = Signal(6, 0x23); //
		    Default rank = 0;
	  	endcase
	end

endmodule
}


Signal SPvpp_Max31::operator()(Signal me31a, Signal me31b, Signal me31c, Signal me31d, Signal me31e, Signal me31f)
{
initio
	me31a.input(1,0,"me31a");
	me31b.input(1,0,"me31b");
	me31c.input(1,0,"me31c");
	me31d.input(1,0,"me31d");
    me31e.input(1,0,"me31e");
	me31f.input(1,0,"me31f");
beginfunction
	begin
	    result(1) = me31a(1) | me31b(1) | me31c(1) |
		            me31d(1) | me31e(1) | me31f(1);
	    result(0) = (!result(1) & (me31a(0) | me31b(0) | me31c(0) |
		                          me31d(0) | me31e(0) | me31f(0))) |
			        (me31a(1) & me31a(0)) | (me31b(1) & me31b(0)) |
				    (me31c(1) & me31c(0)) | (me31d(1) & me31d(0)) |
					(me31e(1) & me31e(0)) | (me31f(1) & me31f(0));		
	    result(4,2) = 
		  	ifelse (result(1,0) == 0, 0,
       		ifelse (result(1,0) == me31a, 1,
	       	ifelse (result(1,0) == me31b, 2,
		   	ifelse (result(1,0) == me31c, 3,
       		ifelse (result(1,0) == me31d, 4,
	       	ifelse (result(1,0) == me31e, 5,
		   	ifelse (result(1,0) == me31f, 6, 0)))))));
	end
endfunction
}


Signal SPvpp_Max3::operator()(Signal me)
{
initio
	me.input(2,0,"me");

beginfunction
	begin
		result(0) = me(0) | me(1) | me(2);
		result(2,1) = 
			ifelse (me(0) == 1, 1,
			ifelse (me(1) == 1, 2,
			ifelse (me(2) == 1, 3, 0)));
	end				
endfunction
}

