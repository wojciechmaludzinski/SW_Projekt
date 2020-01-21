#include "pch.h"
#include <systemc.h>

SC_MODULE(modul) {
	sc_in<sc_uint<8>> input;
	sc_out<sc_uint<8>> HEX[2];
	sc_out<sc_uint<8>> LED[2];

	void modul_run() {

		while (true) {

			if (input.read() == 16) {
				wait(50, SC_MS);
				HEX[0].write(5);
				HEX[1].write(' ');
				LED[0].write('D');
				LED[1].write(' ');
			}
			else if((input.read() & 16) == 16){
				LED[0].write(' ');
				LED[1].write('D');
				HEX[0].write(' ');
				HEX[1].write('E');
			}
			else{
				LED[0].write(' ');
				LED[1].write(' ');
				HEX[1].write(' ');
				HEX[0].write(' ');
			}
			wait(50, SC_MS);
		}
	}

	SC_CTOR(modul) {
		SC_THREAD(modul_run);
	}
};