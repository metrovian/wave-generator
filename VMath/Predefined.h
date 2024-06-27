#pragma once
#include <cmath>

const BYTE MIDI_KEY_DOWN = 154;
const BYTE MIDI_KEY_REL = 138;
const BYTE MIDI_SUSTAIN = 186;
const BYTE MIDI_PITCH = 234;

const double PI = 3.1415926;
const double Z0 = 0.0;

const double A4 = 440.0;
const double B4 = A4 * pow(2.0, 2.0 / 12.0);
const double C5 = A4 * pow(2.0, 3.0 / 12.0);
const double D5 = A4 * pow(2.0, 5.0 / 12.0);
const double E5 = A4 * pow(2.0, 7.0 / 12.0);
const double F5 = A4 * pow(2.0, 8.0 / 12.0);
const double G5 = A4 * pow(2.0, 10.0 / 12.0);

const double A0 = A4 / 16.0;
const double B0 = A0 * pow(2.0, 2.0 / 12.0);
const double C1 = A0 * pow(2.0, 3.0 / 12.0);
const double D1 = A0 * pow(2.0, 5.0 / 12.0);
const double E1 = A0 * pow(2.0, 7.0 / 12.0);
const double F1 = A0 * pow(2.0, 8.0 / 12.0);
const double G1 = A0 * pow(2.0, 10.0 / 12.0);

const double A1 = A4 / 8.0;
const double B1 = A1 * pow(2.0, 2.0 / 12.0);
const double C2 = A1 * pow(2.0, 3.0 / 12.0);
const double D2 = A1 * pow(2.0, 5.0 / 12.0);
const double E2 = A1 * pow(2.0, 7.0 / 12.0);
const double F2 = A1 * pow(2.0, 8.0 / 12.0);
const double G2 = A1 * pow(2.0, 10.0 / 12.0);

const double A2 = A4 / 4.0;
const double B2 = A2 * pow(2.0, 2.0 / 12.0);
const double C3 = A2 * pow(2.0, 3.0 / 12.0);
const double D3 = A2 * pow(2.0, 5.0 / 12.0);
const double E3 = A2 * pow(2.0, 7.0 / 12.0);
const double F3 = A2 * pow(2.0, 8.0 / 12.0);
const double G3 = A2 * pow(2.0, 10.0 / 12.0);

const double A3 = A4 / 2.0;
const double B3 = A3 * pow(2.0, 2.0 / 12.0);
const double C4 = A3 * pow(2.0, 3.0 / 12.0);
const double D4 = A3 * pow(2.0, 5.0 / 12.0);
const double E4 = A3 * pow(2.0, 7.0 / 12.0);
const double F4 = A3 * pow(2.0, 8.0 / 12.0);
const double G4 = A3 * pow(2.0, 10.0 / 12.0);

const double A5 = A4 * 2.0;
const double B5 = A5 * pow(2.0, 2.0 / 12.0);
const double C6 = A5 * pow(2.0, 3.0 / 12.0);
const double D6 = A5 * pow(2.0, 5.0 / 12.0);
const double E6 = A5 * pow(2.0, 7.0 / 12.0);
const double F6 = A5 * pow(2.0, 8.0 / 12.0);
const double G6 = A5 * pow(2.0, 10.0 / 12.0);