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

	Signal me1abi, Signal me1bbi, Signal me1cbi, Signal me1dbi, Signal me1ebi, Signal me1fbi,
	Signal me2abi, Signal me2bbi, Signal me2cbi,
	Signal me3abi, Signal me3bbi, Signal me3cbi,
	Signal me4abi, Signal me4bbi, Signal me4cbi,
	Signal mb1abi, Signal mb1bbi, Signal mb1cbi, Signal mb1dbi,
	Signal mb2abi, Signal mb2bbi, Signal mb2cbi, Signal mb2dbi,

	Signal depth,

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

	Output_(me1abi, BWBXID-1, 0); // {bx[2:0], orig_id[2:0]}
	Output_(me1bbi, BWBXID-1, 0);
	Output_(me1cbi, BWBXID-1, 0);
	Output_(me1dbi, BWBXID-1, 0);
	Output_(me1ebi, BWBXID-1, 0);
	Output_(me1fbi, BWBXID-1, 0);
				 
	Output_(me2abi, BWBXID-1, 0);
	Output_(me2bbi, BWBXID-1, 0);
	Output_(me2cbi, BWBXID-1, 0);
				 
	Output_(me3abi, BWBXID-1, 0);
	Output_(me3bbi, BWBXID-1, 0);
	Output_(me3cbi, BWBXID-1, 0);
				 
	Output_(me4abi, BWBXID-1, 0);
	Output_(me4bbi, BWBXID-1, 0);
	Output_(me4cbi, BWBXID-1, 0);
					 
	Output_(mb1abi, BWBXID-1, 0);
	Output_(mb1bbi, BWBXID-1, 0);
	Output_(mb1cbi, BWBXID-1, 0);
	Output_(mb1dbi, BWBXID-1, 0);
				 
	Output_(mb2abi, BWBXID-1, 0);
	Output_(mb2bbi, BWBXID-1, 0);
	Output_(mb2cbi, BWBXID-1, 0);
	Output_(mb2dbi, BWBXID-1, 0); 

	Input_(depth, 1, 0);

	clkp.input("clkp");

beginmodule

	bxame1ac.init("bxame", "bxame1ac");
	bxame1df.init("bxameo", "bxame1df"); 
	bxame2.init("bxame", "bxame2");
	bxame3.init("bxame", "bxame3");
	bxame4.init("bxame", "bxame4");
	bxamb1.init("bxamb", "bxamb1"); 
	bxamb2.init("bxamb", "bxamb2");                            

	bxame1ac.idoff = 0;
	bxame1df.idoff = 1; // stub IDs shifted for me1d-f 
	bxame2.idoff = 0;
	bxame3.idoff = 0;
	bxame4.idoff = 0;
	bxamb1.idoff = 0;
	bxamb2.idoff = 0;

	bxame1ac.mb = 0;
	bxame1df.mb = 0;
	bxame2.mb = 0;
	bxame3.mb = 0;
	bxame4.mb = 0;
	bxamb1.mb = 1; // these two are for overlap region
	bxamb2.mb = 1;

	// dummy wires for unused outputs
	Wire__(med,  BWMEIN-1, 0, 4, 0);
	Wire__(medb, BWBXID-1, 0, 4, 0);

	bxame1ac
	(
		me1a,  me1b,  me1c,  cns(BWMEIN, 0),
		me1ar,  me1br,  me1cr,  med[1], 
		me1abi, me1bbi, me1cbi, medb[1],
		depth,
		clkp
	);


	bxame1df
	(
		me1d,  me1e,  me1f,  cns(BWMEIN, 0),
		me1dr,  me1er,  me1fr,  med[2], 
		me1dbi, me1ebi, me1fbi, medb[2],
		depth,
		clkp
	);

	bxame2
	(
		me2a,  me2b,  me2c,  cns(BWMEIN, 0),
		me2ar,  me2br,  me2cr,  med[3], 
		me2abi, me2bbi, me2cbi, medb[3],
		depth,
		clkp
	);
	
	bxame3
	(
		me3a,  me3b,  me3c,  cns(BWMEIN, 0),
		me3ar,  me3br,  me3cr,  med[4], 
		me3abi, me3bbi, me3cbi, medb[4],
		depth,
		clkp
	);

	bxame4
	(
		me4a,  me4b,  me4c,  cns(BWMEIN, 0),
		me4ar,  me4br,  me4cr,  med[0], 
		me4abi, me4bbi, me4cbi, medb[0],
		depth,
		clkp
	);

	bxamb1
	(
		mb1a,  mb1b,  mb1c,	 mb1d,
		mb1ar, mb1br, mb1cr, mb1dr,
		mb1abi, mb1bbi, mb1cbi, mb1dbi,
		depth,
		clkp
	);

/*	bxamb2
	(
		mb2a,  mb2b,  mb2c,	 mb2d,
		mb2ar, mb2br, mb2cr, mb2dr,
		(me1acv | me1dfv | me2v) & enable,
		mb2v,
		clkp
	);
*/

endmodule
}

