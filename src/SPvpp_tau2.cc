#include <L1Trigger/CSCTrackFinder/src/SPvpp_tau2.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>

void SPvpp_tau2::operator()
(
	Signal me21,
	Signal me23,
	Signal me24,
	Signal idl, Signal idm, Signal idh,
	Signal rank
)	
{
initio

	me21.input(11, 0, "me21");
	me23.input(2, 0, "me23");
	me24.input(2, 0, "me24");

	idl.output(2,0,"idl",makereg);
	idm.output(1,0,"idm",makereg); 
	idh.output(1,0,"idh",makereg); 
	rank.output(5,0,"rank",makereg);

beginmodule

	e21.reg(1, 0, 5, 0, "e21");
	e23.reg(2, 0, "e23");
	e24.reg(2, 0, "e24");
	Max21p.init(4,0,"_Max21p");
	Maxp.init(2,0,"_Maxp");

 	max21.reg(4,0,"max21");
	max23.reg(2,0,"max23"); 
	max24.reg(2,0,"max24"); 
	quality.reg(3,0,"quality");


	always (me21 or me23 or me24)
	begin
	    (e21[5], e21[4], e21[3], e21[2], e21[1], e21[0]) = me21;
		e23 = me23;
		e24 = me24;

	    max21 = Max21p(e21[0], e21[1], e21[2], e21[3], e21[4], e21[5]);
	    max23 = Maxp  (e23);
	    max24 = Maxp  (e24);
	    quality = (max21(1,0), max23(0), max24(0));
	    idl = max21(4,2);
	    idm = max23(2,1);
	    idh = max24(2,1);

  		begincase (quality)
		    case1("4'b0001") rank = 2;
		    case1("4'b0010") rank = 3;
		    case1("4'b0011") rank = 4;
		    case1("4'b0100") rank = 6;
		    case1("4'b1000") rank = "6'hb";
		    case1("4'b1100") rank = "6'he";
		    case1("4'b0101") rank = "6'h11";
		    case1("4'b0110") rank = "6'h12";
		    case1("4'b1001") rank = "6'h16";
		    case1("4'b1010") rank = "6'h17";
		    case1("4'b1101") rank = "6'h1b";
		    case1("4'b1110") rank = "6'h1c";
		    case1("4'b0111") rank = "6'h1f";
		    case1("4'b1011") rank = "6'h21";
		    case1("4'b1111") rank = "6'h23";
		    Default rank = 0;
	  	endcase
	end

endmodule
}

Signal SPvpp_Max21::operator()(Signal me21a, Signal me21b, Signal me21c, Signal me21d, Signal me21e, Signal me21f)
{
initio
	me21a.input(1,0,"me21a");
	me21b.input(1,0,"me21b");
	me21c.input(1,0,"me21c");
	me21d.input(1,0,"me21d");
	me21e.input(1,0,"me21e");
	me21f.input(1,0,"me21f");

beginfunction
	maxq.reg(1, 0, "maxq");
	// have to use temp variable here!
	begin
	
       	maxq(1) = me21a(1) | me21b(1) | me21c(1) |
                 me21d(1) | me21e(1) | me21f(1);
        maxq(0) = (!maxq(1) & (me21a(0) | me21b(0) | me21c(0) |
                              me21d(0) | me21e(0) | me21f(0))) |
                 (me21a(1) & me21a(0)) | (me21b(1) & me21b(0)) |
                 (me21c(1) & me21c(0)) | (me21d(1) & me21d(0)) |
                 (me21e(1) & me21e(0)) | (me21f(1) & me21f(0));		
        
        result(4,2) = 
        	ifelse (maxq(1,0) == 0,     0,
        	ifelse (maxq(1,0) == me21a, 1,
        	ifelse (maxq(1,0) == me21b, 2,
        	ifelse (maxq(1,0) == me21c, 3,
        	ifelse (maxq(1,0) == me21d, 4,
        	ifelse (maxq(1,0) == me21e, 5,
        	ifelse (maxq(1,0) == me21f, 6, 0)))))));
		result(1,0) = maxq;
	end	
endfunction
}
Signal SPvpp_Max::operator()(Signal me)
{
initio
	me.input(3,1,"me");

beginfunction
	begin
			result(0) = me(1) | me(2) | me(3);
			result(2,1) = 
				ifelse (me(1) == 1, 1,
				ifelse (me(2) == 1, 2,
				ifelse (me(3) == 1, 3, 0)));
	end		
endfunction
}
