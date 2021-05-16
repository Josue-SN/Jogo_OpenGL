#ifndef Projetil_hpp
#define Projetil_hpp

#include "Ponto.h"
#include <math.h>
using namespace std;

class Projetil{

public:

Projetil();
static Ponto calculaPosicaoNaCurvaDeBezier(Ponto P1, Ponto P2, Ponto P3, float t);
};

#endif