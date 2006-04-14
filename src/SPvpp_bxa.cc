#include <L1Trigger/CSCTrackFinder/src/SPvpp_bxa.h>
#include <L1Trigger/CSCCommonTrigger/interface/vmac.h>



void SPvpp_bxa::operator ()
(                                                                
	Signal me1a,  Signal me1b,  Signal me1c,  Signal me1d,  Signal me1e,  Signal me1f, 
	Signal me2a,  Signal me2b,  Signal me2c, 
	Signal me3a,  Signal me3b,  Signal me3c, 
	Signal me4a,  Signal me4b,  Signal me4c, 
	Signal mb1a,  Signal mb1b,  Signal mb1c,  Signal mb1d, 
	Signal mb2a,  Signal mb2b,  Signal mb2c,  Signal mb2d, 

	Signal me1ar, Signal me1br, Signal me1cr, Signal me1dr, Signal me1er, Signal me1fr,
	Signal me2ar, Signal me2br, Signal me2cr,
	Signal me3ar, Signal me3br, Signal me3cr,
	Signal me4ar, Signal me4br, Signal me4cr,
	Signal mb1ar, Signal mb1br, Signal mb1cr, Signal mb1dr,
	Signal mb2ar, Signal mb2br, Signal mb2cr, Signal mb2dr,

	Signal etaoff1, Signal etaoff2, Signal etaoff3, Signal etaoff4,
	Signal enable,

	Signal clkp

)
{
initio
	me1a.input(BWMEIN-1,0,"me1a"); // {CSCid[3:0], q[3:0], eta[5:0], phi[11:0]}
	me1b.input(BWMEIN-1,0,"me1b"); 
	me1c.input(BWMEIN-1,0,"me1c"); 
	me1d.input(BWMEIN-1,0,"me1d"); 
	me1e.input(BWMEIN-1,0,"me1e"); 
	me1f.input(BWMEIN-1,0,"me1f"); 
							   
	me2a.input(BWMEIN-1,0,"me2a"); 
	me2b.input(BWMEIN-1,0,"me2b"); 
	me2c.input(BWMEIN-1,0,"me2c"); 
							   
	me3a.input(BWMEIN-1,0,"me3a"); 
	me3b.input(BWMEIN-1,0,"me3b"); 
	me3c.input(BWMEIN-1,0,"me3c"); 
							   
	me4a.input(BWMEIN-1,0,"me4a"); 
	me4b.input(BWMEIN-1,0,"me4b"); 
	me4c.input(BWMEIN-1,0,"me4c"); 

	mb1a.input(BWMBIN-1,0,"mb1a"); // {FL, q[2:0], phi[11:0]}
	mb1b.input(BWMBIN-1,0,"mb1b"); 
	mb1c.input(BWMBIN-1,0,"mb1c"); 
	mb1d.input(BWMBIN-1,0,"mb1d"); 
							   
	mb2a.input(BWMBIN-1,0,"mb2a"); 
	mb2b.input(BWMBIN-1,0,"mb2b"); 
	mb2c.input(BWMBIN-1,0,"mb2c"); 
	mb2d.input(BWMBIN-1,0,"mb2d"); 

	me1ar.output(BWMEIN-1,0,"me1ar"); // {CSCid[3:0], q[3:0], eta[5:0], phi[11:0]}
	me1br.output(BWMEIN-1,0,"me1br"); 
	me1cr.output(BWMEIN-1,0,"me1cr"); 
	me1dr.output(BWMEIN-1,0,"me1dr"); 
	me1er.output(BWMEIN-1,0,"me1er"); 
	me1fr.output(BWMEIN-1,0,"me1fr"); 
							   
	me2ar.output(BWMEIN-1,0,"me2ar"); 
	me2br.output(BWMEIN-1,0,"me2br"); 
	me2cr.output(BWMEIN-1,0,"me2cr"); 
							   
	me3ar.output(BWMEIN-1,0,"me3ar"); 
	me3br.output(BWMEIN-1,0,"me3br"); 
	me3cr.output(BWMEIN-1,0,"me3cr"); 
							   
	me4ar.output(BWMEIN-1,0,"me4ar"); 
	me4br.output(BWMEIN-1,0,"me4br"); 
	me4cr.output(BWMEIN-1,0,"me4cr"); 

	mb1ar.output(BWMBIN-1,0,"mb1ar"); // {FL, q[2:0], phi[11:0]}
	mb1br.output(BWMBIN-1,0,"mb1br"); 
	mb1cr.output(BWMBIN-1,0,"mb1cr"); 
	mb1dr.output(BWMBIN-1,0,"mb1dr"); 
							   
	mb2ar.output(BWMBIN-1,0,"mb2ar"); 
	mb2br.output(BWMBIN-1,0,"mb2br"); 
	mb2cr.output(BWMBIN-1,0,"mb2cr"); 
	mb2dr.output(BWMBIN-1,0,"mb2dr"); 

	Input_(etaoff1, BWETAIN-1, 0); 
	Input_(etaoff2, BWETAIN-1, 0); 
	Input_(etaoff3, BWETAIN-1, 0); 
	Input_(etaoff4, BWETAIN-1, 0); 

	Input(enable);

	clkp.input("clkp");

beginmodule

	bxame1ac.init("bxame", "bxame1ac");
	bxame1df.init("bxame", "bxame1df"); 
	bxame2.init("bxame", "bxame2");
	bxame3.init("bxame", "bxame3");
	bxame4.init("bxame", "bxame4");

	bxamb1.init("bxamb", "bxamb1"); 
	bxamb2.init("bxamb", "bxamb2");                            

	me1acv.wire("me1acv");
	me1dfv.wire("me1dfv");
	me2v.wire  ("me2v");
	me3v.wire  ("me3v");
	me4v.wire  ("me4v");
	mb1v.wire  ("mb1v");
	mb2v.wire  ("mb2v");

	bxame1ac
	(
		me1a,  me1b,  me1c,
		me1ar, me1br, me1cr,
		(me2v | me3v | me4v | mb2v | mb1v) & enable,
		me1acv,
		etaoff1,
		clkp
	);


	bxame1df
	(
		me1d,  me1e,  me1f,
		me1dr, me1er, me1fr,
		(me2v | me3v | me4v | mb2v | mb1v) & enable,
		me1dfv,
		etaoff1,
		clkp
	);

	bxame2
	(
		me2a,  me2b,  me2c,
		me2ar, me2br, me2cr,
		(me1acv | me1dfv | me3v | me4v | mb1v | mb2v) & enable,
		me2v,
		etaoff2,
		clkp
	);
	
	bxame3
	(
		me3a,  me3b,  me3c,
		me3ar, me3br, me3cr,
		(me1acv | me1dfv | me2v | me4v) & enable,
		me3v,
		etaoff3,
		clkp
	);

	bxame4
	(
		me4a,  me4b,  me4c,
		me4ar, me4br, me4cr,
		(me1acv | me1dfv | me2v | me3v) & enable,
		me4v,
		etaoff4,
		clkp
	);

	bxamb1
	(
		mb1a,  mb1b,  mb1c,	 mb1d,
		mb1ar, mb1br, mb1cr, mb1dr,
		(me1acv | me1dfv | me2v) & enable,
		mb1v,
		clkp
	);

	bxamb2
	(
		mb2a,  mb2b,  mb2c,	 mb2d,
		mb2ar, mb2br, mb2cr, mb2dr,
		(me1acv | me1dfv | me2v) & enable,
		mb2v,
		clkp
	);


endmodule
}

