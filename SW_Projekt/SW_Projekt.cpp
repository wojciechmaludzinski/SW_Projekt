#include <iostream>
#include "systemc.h"

#include "CPU1.cpp"
#include "CPU2.cpp"
#include "modul.cpp"

SC_MODULE(fifo) {
	sc_fifo<int> fifoo;

	SC_CTOR(fifo) {
		sc_fifo<int> fifoo(6);
	}
};

int main(int argc, char* argv[]) {
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> LED[8];
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> SW;
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> HEX[7];
	sc_signal<sc_uint<8>, SC_MANY_WRITERS> cpu_1_out_module;
	fifo f("fifoo");

	cpu1 CPU1("cpu1");
	CPU1.fifo(f.fifoo);
	CPU1.module(cpu_1_out_module);
	CPU1.SW(SW);

	for (int i = 0; i < 7; i++) {
		CPU1.HEX[i](HEX[i]);
	}
	for (int i = 0; i < 8; i++) {
		CPU1.LED[i](LED[i]);
	}

	cpu2 CPU2("cpu2");
	CPU2.fifo(f.fifoo);

	for (int i = 0; i < 7; i++) {
		CPU2.HEX[i](HEX[i]);
	}
	for (int i = 0; i < 8; i++) {
		CPU2.LED[i](LED[i]);
	}

	modul mod("modul");
	mod.LED[0](LED[4]);
	mod.LED[1](LED[6]);
	mod.HEX[1](HEX[6]);
	mod.HEX[0](HEX[4]);
	mod.input(cpu_1_out_module);

	sc_start();

	return(0);
}