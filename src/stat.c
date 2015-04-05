#include "stat.h"

void proba_elo(double elo, double draw_elo, double *pwin, double *ploss)
{
	*pwin  = 1 / (1 + pow(10.0, (-elo + draw_elo) / 400.0));
	*ploss = 1 / (1 + pow(10.0, (elo + draw_elo) / 400.0));
}

double scale(double draw_elo)
{
	const double x = pow(10.0, -draw_elo / 400.0);
	return 4.0 * x / ((1.0 + x) * (1.0 + x));
}

uint64_t rotate(uint64_t x, uint64_t k)
{ return (x << k) | (x >> (64 - k)); }

// RKISS 64-bit PRNG by Bob Jenkins
uint64_t rand64()
{
	static uint64_t
		a = 0x46dd577ff603b540,
		b = 0xc4077bddfacf987b,
		c = 0xbbf4d93b7200e858,
		d = 0xd3e075cfd449bb1e;

	const uint64_t e = a - rotate(b,  7);
	a = b ^ rotate(c, 13);
	b = c + rotate(d, 37);
	c = d + e;

	return d = e + a;
}

double uniform()
{ return (double)rand64() / 0xffffffffffffffffULL; }

int game_result(double pwin, double ploss)
{
	double x = uniform();
	return x < pwin ? WIN : (x < pwin+ploss ? LOSS : DRAW);
}
