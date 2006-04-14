/**
Verilog++ SP.
\author A. Madorsky
*/

#ifndef _SPBITS_H_
#define _SPBITS_H_

#define BWVALID 1 // "track stub valid" input
#define BWCSCID 4 // CSC id (front-rear is derived from it)
#define BWQ 4     // quality input endcap
#define BWQB 3     // quality input barrel
//#define BWAM 1    // accelerator muon input 
#define BWETAIN 7 // eta input 
#define BWPHI 12  // phi input
#define BWPHISCALE 7 // input of phi scaling LUT
#define BWPHIOUT 5 // scaled phi output
#define BWFL 1 // "delayed track stub" input (only for DT stubs)

#define BWFR 1    // front-rear bit output 
#define BWPT 13   // PT output
#define BWSIGN 1  // sign output
#define BWMODE 4  // mode output
#define BWETAOUT 5 // eta output

#define BWMEIN (BWVALID + BWCSCID + BWQ + /*BWAM +*/ BWETAIN + BWPHI) // combined me input
#define BWMBIN (BWFL + BWQB + BWPHI)  // combined mb input (only 3 bits quality)
#define BWPOUT (BWFR + BWPHIOUT + BWPT + BWSIGN + BWMODE + BWETAOUT) // combined output

#define BWEQ12 2   // extrapolation qualities bit widths
#define BWEQ13 2
#define BWEQ12OV 1
#define BWEQ234 1
#define BWEQ2B1 2
#define BWEQ2B2 1


#define NSEG1  6 // segments from 1st station
#define NSEG234  3 // segments from 2, 3, 4-th stations
#define NSEG12B  4 // segments from barrel stations 1 and 2

// extrapolation quality registers bit widths
#define BWPASS12  (NSEG1 * NSEG234)
#define BWEQ12R   (BWEQ12 * NSEG1 * NSEG234)
#define BWEQ12OVR (BWEQ12OV * NSEG1 * NSEG234)
#define BWEQ234R  (BWEQ234 * NSEG234 * NSEG234)
#define BWEQ2B1R  (BWEQ2B1 * NSEG234 * NSEG12B)
#define BWEQ2B2R  (BWEQ2B2 * NSEG234 * NSEG12B)

// extrapolation quality registers bit portions lengths
#define BWEQ12P   (BWEQ12 * NSEG1)
#define BWEQ234P  (BWEQ234 * NSEG234)
#define BWEQ2B1P  (BWEQ2B1 * NSEG12B)
#define BWEQ2B2P  (BWEQ2B2 * NSEG12B)
#define BWEQ12OVP (BWEQ12OV * NSEG1)

#define MUIDME1		3	//Lengths for parts of ID
#define	MUIDME234	2
#define MUIDMB12	3
#define MUIDSIZE	(MUIDME1 + 3 * MUIDME234 + 2 * MUIDMB12)	//Length of muon id bitpattern

#define NTAU  3 // number of taus for each station

#define BWPTETA BWETAOUT // pt assignment units use only PTETA MSbits of eta

#endif

