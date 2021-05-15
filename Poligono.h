//
//  Poligono.hpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Poligono_hpp
#define Poligono_hpp

#include <iostream>
using namespace std;


#ifdef WIN32
#include <windows.h>
#include <glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include <vector>

class Poligono
{
    typedef struct AABB{
        Ponto Centro;
        Ponto MeiaLarg;
    }AABB;
    AABB boundingBox;
    vector <Ponto> Vertices;
    Ponto Min, Max;
public:
    // **********************************************************************
    //  quando desenhamos um poligono em OpenGL, ele e posicionado em relacao ao estado atual do mapa
    //  portanto, precisamos adicionar as translacoes que tanto o mapa quando o objeto tiver sofrido ao centro dele
    //  para o calculo das bounding boxes
    // **********************************************************************
    int quantidadeTranslatadaX, quantidadeTranslatadaY;

    Poligono();
    Ponto getVertice(int);
    unsigned long getNVertices();
    void insereVertice(Ponto);
    void insereVertice(Ponto p, int pos);
    void desenhaPoligono();
    void desenhaVertices();
    void imprime();
    void atualizaLimites();
    void obtemLimites(Ponto &Min, Ponto &Max);
    void calculaAABB();
    static bool calculaColisaoAABB(Poligono P1, Poligono P2);
};

#endif 
