//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Poligono.h"

Poligono::Poligono()
{
    
}

void Poligono::insereVertice(Ponto p)
{
    Vertices.push_back(p);
    obtemLimites(Min, Max);
    calculaAABB();
}

void Poligono::insereVertice(Ponto p, int pos)
{
    if ((pos < 0) || (pos>Vertices.size()))
    {
        cout << "Metodo " << __FUNCTION__ << ". Posicao Invalida. Vertice nao inserido." << endl;
        return;
    }
    Vertices.insert(Vertices.begin()+pos, p);
    obtemLimites(Min, Max);
    calculaAABB();
}

void Poligono::calculaAABB(){
    boundingBox.Centro = Ponto((Max.x + Min.x)/2, (Max.y + Min.y)/2, (Max.z + Min.z)/2);
    boundingBox.MeiaLarg = Ponto(Max.x - boundingBox.Centro.x, Max.y - boundingBox.Centro.y, Max.z - boundingBox.Centro.z);
    boundingBox.Centro.x += quantidadeTranslatadaX;
    boundingBox.Centro.y += quantidadeTranslatadaY;
}

bool Poligono::calculaColisaoAABB(Poligono P1, Poligono P2){
    AABB E1 = P1.boundingBox;
    AABB E2 = P2.boundingBox;
    if(abs(E1.Centro.x - E2.Centro.x) > (E1.MeiaLarg.x + E2.MeiaLarg.x)) {
        return false; // nao ha colisao
    }
    if(abs(E1.Centro.y - E2.Centro.y) > (E1.MeiaLarg.y + E2.MeiaLarg.y)) {
        return false; // nao ha colisao
    }
    if(abs(E1.Centro.z - E2.Centro.z) > (E1.MeiaLarg.z + E2.MeiaLarg.z)) {
        return false; // nao ha colisao
    }
    return true; // ha colisao
}

Ponto Poligono::getVertice(int i)
{
    return Vertices[i];
}
    
void Poligono::desenhaPoligono()
{
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::desenhaVertices()
{
    glBegin(GL_POINTS);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::imprime()
{
    for (int i=0; i<Vertices.size(); i++)
        Vertices[i].imprime();
}
unsigned long Poligono::getNVertices()
{
    return Vertices.size();
}

void Poligono::obtemLimites(Ponto &Min, Ponto &Max)
{
    Max = Min = Vertices[0];
    
    for (int i=0; i<Vertices.size(); i++)
    {
        Min = ObtemMinimo (Vertices[i], Min);
        Max = ObtemMaximo (Vertices[i], Max);
    }
}

