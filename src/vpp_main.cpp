#include <time.h>
#include <iostream>
#include "vpp_generated.h"
using namespace std;
vpp_generated sp;
#define ES 23
unsigned valid[ES], q[ES], phi[ES], eta[ES], phib[ES], cscid[ES];

int main()
{
	clock_t clk_before, clk_after, clk_spent = 0;
	int i;
	unsigned ptHp, signHp,  modeMemHp,  etaPTHp,  FRHp, phiHp;
	unsigned ptMp, signMp,  modeMemMp,  etaPTMp,  FRMp, phiMp;
	unsigned ptLp, signLp,  modeMemLp,  etaPTLp,  FRLp, phiLp;
	unsigned date;

	unsigned me1idH,  me2idH,  me3idH,  me4idH,  mb1idH,  mb2idH;
	unsigned me1idM,  me2idM,  me3idM,  me4idM,  mb1idM,  mb2idM;
	unsigned me1idL,  me2idL,  me3idL,  me4idL,  mb1idL,  mb2idL;
	int ev_num = 1;


#define MAX_EVS 1000

//	srand(123);

	for (int j = 0; j < MAX_EVS+10; j++)
	{

		// generate random numbers for each input param	

		// generate random numbers for each input param	

		if (j > 10)
			for (i = 0; i < ES; i++)
			{
				valid[i] = rand();
				q[i] = rand();
				eta[i] = rand();
				phi[i] = rand();
				cscid[i] = rand();
			}	
		else
			for (i = 0; i < ES; i++) // run zeroes first 10 events to zero out all the garbage that may have been left in logic
			{
				valid[i] = 0;
				q[i] = 0;
				eta[i] = 0;
		   		phi[i] = 0;
				cscid[i] = 0;
	   		}	


		clk_before = clock();

		sp.wrap
		(
			valid[0] , q[0], eta[0], phi[0], cscid[0],
			valid[1] , q[1], eta[1], phi[1], cscid[1],
			valid[2] , q[2], eta[2], phi[2], cscid[2],
			valid[3] , q[3], eta[3], phi[3], cscid[3],
			valid[4] , q[4], eta[4], phi[4], cscid[4],
			valid[5] , q[5], eta[5], phi[5], cscid[5],

			valid[6] , q[6], eta[6], phi[6],
			valid[7] , q[7], eta[7], phi[7],
			valid[8] , q[8], eta[8], phi[8],

			valid[9] , q[9],  eta[9],  phi[9],
			valid[10], q[10], eta[10], phi[10],
			valid[11], q[11], eta[11], phi[11],

			valid[12], q[12], eta[12], phi[12],
			valid[13], q[13], eta[13], phi[13],
			valid[14], q[14], eta[14], phi[14],

			valid[15], q[15], phi[15],
			valid[16], q[16], phi[16],
			valid[17], q[17], phi[17],
			valid[18], q[18], phi[18],

			ptHp,  signHp, modeMemHp, etaPTHp, FRHp, phiHp,
			ptMp,  signMp, modeMemMp, etaPTMp, FRMp, phiMp,
			ptLp,  signLp, modeMemLp, etaPTLp, FRLp, phiLp,

			me1idH,  me2idH,  me3idH,  me4idH,  mb1idH,  mb2idH, 
			me1idM,  me2idM,  me3idM,  me4idM,  mb1idM,  mb2idM, 
			me1idL,  me2idL,  me3idL,  me4idL,  mb1idL,  mb2idL, 

			// parameters below are such that any eta will pass
			0,  0,  0,  0,  0,  0,  0,  0,     // etamin	  
			127,127,127,127,127,127,127,127,	// etamax	  
			100,100,100,100,100,100,	// etawindow

			2, // mindphi, equal to 2*64=128 phi counts
			4, 16, 70, // mindeta_acc, maxdeta_acc, maxdphi_acc
			0x144
		);

		clk_after = clock();
		clk_spent += clk_after - clk_before;

		cout << dec << "Event Number " << ev_num++ << endl;

		cout << dec << ptHp  << "\t" << signHp << "\t" << modeMemHp << "\t" << etaPTHp << "\t" << FRHp << "\t" << phiHp << endl;
		cout << dec << ptMp  << "\t" << signMp << "\t" << modeMemMp << "\t" << etaPTMp << "\t" << FRMp << "\t" << phiMp << endl;
		cout << dec << ptLp  << "\t" << signLp << "\t" << modeMemLp << "\t" << etaPTLp << "\t" << FRLp << "\t" << phiLp << endl;

		cout << "\nIDs: \n";

		cout << oct << me1idH  << "\t" << me2idH  << "\t" << me3idH  << "\t" << me4idH  << "\t" << mb1idH  << "\t" << mb2idH  << endl;
		cout << oct << me1idM  << "\t" << me2idM  << "\t" << me3idM  << "\t" << me4idM  << "\t" << mb1idM  << "\t" << mb2idM  << endl;
		cout << oct << me1idL  << "\t" << me2idL  << "\t" << me3idL  << "\t" << me4idL  << "\t" << mb1idL  << "\t" << mb2idL  << endl;
		cout << endl;
	}
	cout << "Elapsed time: " << dec << clk_spent/(CLOCKS_PER_SEC/1000) << " ms" << endl;
}
