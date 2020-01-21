#include "pch.h"
#include <systemc.h>
#include <conio.h>

using namespace std;

SC_MODULE(cpu1) {
	sc_inout<sc_uint<8>> SW;
	sc_inout<sc_uint<8>> HEX[7];
	sc_fifo_out<int> fifo;
	sc_out<sc_uint<8>> module;
	sc_inout<sc_uint<8>> LED[8];

	bool sw[6] = { false, false, false, false, false, false };

	void task1() {
		int odczyt = 0;

		while (true) {
			wait(500, SC_NS);

			if (_kbhit()) {
				wypisz();

				wait(25, SC_NS);
				cin >> odczyt;
				odczyt = zamine_bin_dec(odczyt);

				if (odczyt >= 0 && odczyt <= 32) {
					wait(500, SC_NS);
					sc_uint<8> sw_state = 0;
					sw_state = SW.read() ^ odczyt;
					SW.write(sw_state);

					wait(500, SC_NS);
				}
				else {
					odczyt = 0;
				}
			}
			wait(500, SC_NS);

			sc_uint<8> sw_state = SW.read();

			wait(500, SC_NS);
			SW.write(sw_state);

			wait(100, SC_MS);
			fifo.write(sw_state);

			module = sw_state;

			if (sw_state == 0) {

				for (int i = 0; i < 6; i++) {
					HEX[i].write(' ');
				}
				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write(' ');
			}

			wait(500, SC_NS);
			if (sw_state != 0 and sw_state != 1 and sw_state != 2 and sw_state != 4 and sw_state != 8 and sw_state != 16 and sw_state != 32){
				HEX[0].write('r');
				HEX[1].write('r');
				HEX[2].write('E');
				HEX[3].write(' ');
				HEX[5].write(' ');

				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write('D');
			}

			if (sw_state == 1 && LED[0].read() != 'D') {
				LED[0].write('D');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write(' ');
				HEX[0].write(1);
				HEX[1].write(' ');
				HEX[2].write(' ');
				HEX[3].write(' ');
				HEX[5].write(' ');
			}

			if (sw_state == 16 && LED[4].read() != 'D') {
				HEX[0].write(' ');
				HEX[1].write(' ');
				HEX[2].write(' ');
				HEX[3].write(' ');
				HEX[5].write(' ');
				HEX[6].write('E');

				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write(' ');
			}

		}
	}

	void task2() {
		while (true) {
			if (SW.read() == 2 && LED[1].read() != 'D') {
				LED[1].write('D');
				LED[0].write(' ');
				LED[2].write(' ');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write(' ');
				HEX[0].write(' ');
				HEX[1].write(2);
				HEX[2].write(' ');
				HEX[3].write(' ');
				HEX[5].write(' ');
			}
			wait(10, SC_MS);
		}
	}

	void task3() {
		while (true) {
			if (SW.read() == 4 && LED[2].read() != 'D') {
				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write('D');
				LED[3].write(' ');
				LED[5].write(' ');
				LED[7].write(' ');
				HEX[0].write(' ');
				HEX[1].write(' ');
				HEX[2].write(3);
				HEX[3].write(' ');
				HEX[5].write(' ');
			}
			wait(10, SC_MS);
		}
	}

	void task4() {
		while (true) {
			if (SW.read() == 8 && LED[3].read() != 'D') {
				LED[0].write(' ');
				LED[1].write(' ');
				LED[2].write(' ');
				LED[3].write('D');
				LED[5].write(' ');
				LED[7].write(' ');
				HEX[0].write(' ');
				HEX[1].write(' ');
				HEX[2].write(' ');
				HEX[3].write(4);
				HEX[5].write(' ');
			}
			wait(10, SC_MS);
		}
	}

	void wypisz() {

		system("CLS");

		cout << "HEX:|   | ";
		for (int i = 6; i >= 0; --i) {
			if (HEX[i].read() >= 0 && HEX[i].read() <= 6)
				cout << HEX[i].read() << " | ";
			else if (HEX[i].read() == (sc_uint<8>) 'E')
				cout << "E | ";
			else if (HEX[i].read() == (sc_uint<8>) 'r')
				cout << "r | ";
			else if (HEX[i].read() == (sc_uint<8>) ' ')
				cout << "  | ";
		}
		cout << endl;

		cout << "----+---+---+---+---+---+---+---+---+";
		cout << endl;

		cout << "LED:| ";
		for (int i = 7; i >= 0; --i) {
			if (LED[i].read() == 'D') {
				cout << "D" << " | ";
			}
			else {
				cout << " " << " | ";
			}
		}
		cout << endl;

		cout << "----+---+---+---+---+---+---+---+---+";
		cout << endl;

		sc_uint<8> switches_state = SW.read();
		sc_uint<8> old_bit = 0x80;
		cout << "SW: | ";

		for (int i = 7; i >= 0; --i) {
			if (switches_state & old_bit) {
				cout << "S" << " | ";
			}
			else {
				cout << " " << " | ";
			}
			old_bit = old_bit >> 1;
		}
		cout << endl;
		cout << "    | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 |" << endl;

	}

	int zamine_bin_dec(int value) {
		switch (value) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 4;
			break;
		case 4:
			return 8;
			break;
		case 5:
			return 16;
			break;
		case 6:
			return 32;
			break;
		default:
			return -1;
			break;
		}
	}

	SC_CTOR(cpu1) {
		SC_THREAD(task1);
		SC_THREAD(task2);
		SC_THREAD(task3);
		SC_THREAD(task4);
	}
};