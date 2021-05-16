#include "Projetil.h"

Projetil::Projetil(){
    // Tres pontos que definem a trajetoria do projetil
    Ponto P1, P2, P3;
}
// **********************************************************************
//  C1(t) = (1-t)2 * P0 + 2 * (1-t) * t * P1 + t2 * P2
// **********************************************************************
Ponto Projetil::calculaPosicaoNaCurvaDeBezier(Ponto P1, Ponto P2, Ponto P3, float t){
    Ponto NovoPonto = Ponto();
    NovoPonto.x = pow((1-t),2) * P1.x + 2 * (1 - t) * t * P2.x + pow(t,2) * P3.x;
    NovoPonto.y = pow((1-t),2) * P1.y + 2 * (1 - t) * t * P2.y + pow(t,2) * P3.y;
    return NovoPonto;
}