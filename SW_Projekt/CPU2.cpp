#include "pch.h"
#include <systemc.h>

using namespace std;

SC_MODULE(cpu2) {
	sc_fifo_in<int> fifo;
	sc_inout<sc_uint<8>> LED[8];
	sc_inout<sc_uint<8>> HEX[7];

	void task6() {
		while (true) {
			if (fifo.read() == 32 && LED[5].read() != 'D') {
				LED[5].write('D');
				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[7].write(' ');

				HEX[0].write(' ');
				HEX[1].write(' ');
				HEX[2].write(' ');
				HEX[3].write(' ');
				HEX[5].write(6);
			}
			wait(10, SC_MS);
		}
	}

	SC_CTOR(cpu2) {

		SC_THREAD(task6);
	}

};