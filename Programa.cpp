// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************
//
// Para compilar com linha de comando do Linux
// g++ ExibePoligonosCSG.cpp Poligono.cpp Ponto.cpp Temporizador.cpp -o CSG -lglut -lGLU -lGL -IGL
// Para executar: ./CSG


#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>


using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"

#include "Temporizador.h"
Temporizador T;
double AccumDeltaT=0;

// Limites l�gicos da �rea de desenho
Ponto Min, Max;

Poligono Predio;
Poligono Tanque;
int TanqueMovimentoX = 0;
int AnguloCanhao = 0;

// **********************************************************************
//
// **********************************************************************
void init()
{
    // Define a cor do fundo da tela (AZUL)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  
    Min = Ponto(0, 0);
    Max = Ponto(192, 108);
}

double nFrames=0;
double TempoTotal=0;
// **********************************************************************
//
// **********************************************************************
void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0/30) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: "  << TempoTotal << " segundos. \n" ;
        TempoTotal = 0;
        nFrames = 0;
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void desenhaCenario(){
    glBegin(GL_LINES);{
        glVertex2f(0, Max.y/16);
        glVertex2f(Max.x, Max.y/16);

    }
    glEnd();
}

void desenhaTanque(){
    //push matrix para salvar as configuracoes atuais do opengl
    glPushMatrix();{
        Poligono t = Poligono();
        //translate para compensar o movimento to tanque e a a altura do chao
        glTranslatef(TanqueMovimentoX, (Max.y/16), 0);
        t.quantidadeTranslatadaX = TanqueMovimentoX;
        t.quantidadeTranslatadaY = Max.y/16;
        t.insereVertice(Ponto(0, 0));
        t.insereVertice(Ponto(2, 10));
        t.insereVertice(Ponto(4, 10));
        t.insereVertice(Ponto(6, 0));
        t.desenhaPoligono();
        Tanque = t;
    }
    glPopMatrix();
    glPushMatrix();{
        Poligono canhao = Poligono();
        //translate para compensar o movimento do tanque, altura do chao e posicao do canhao no tanque
        glTranslatef(TanqueMovimentoX, (Max.y/16), 0);
        glTranslatef(3, 8, 0);
        glRotatef(AnguloCanhao, 0, 0, 1);
        canhao.insereVertice(Ponto(0, 0));
        canhao.insereVertice(Ponto(-0.5, 2));
        canhao.insereVertice(Ponto(-0.5, 6));
        canhao.insereVertice(Ponto(-0.5, 12));
        canhao.insereVertice(Ponto(0.5, 12));
        canhao.insereVertice(Ponto(0.5, 6));
        canhao.insereVertice(Ponto(0.5, 2));
        canhao.desenhaPoligono();
    }
    glPopMatrix();
}

void desenhaPredio(){
    glPushMatrix();{
        Poligono p = Poligono();
        p.quantidadeTranslatadaX = 100;
        p.quantidadeTranslatadaY = Max.y/16;
        glTranslatef(100, Max.y/16, 0);
        p.insereVertice(Ponto(0,0));
        p.insereVertice(Ponto(0,50));
        p.insereVertice(Ponto(30,50));
        p.insereVertice(Ponto(30,0));
        p.desenhaPoligono();
        Predio = p;
    }
    glPopMatrix();
}

void display( void )
{
	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glLineWidth(3);
    glColor3f(1,1,1);
    desenhaCenario(); 

    glLineWidth(2);
    glColor3f(1,0,0);
    desenhaTanque();   

    glLineWidth(4);
    glColor3f(1,1,0);
    desenhaPredio();

	glutSwapBuffers();
}

// **********************************************************************
//  
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
    // ver tabela ascii para o codigo das teclas
	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;
        case 122:        // tecla z
			AnguloCanhao -= 5;   
			break;
        case 120:        // tecla x
			AnguloCanhao += 5;   
			break;
	}
}

// **********************************************************************
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_LEFT:       // Se pressionar UP
            // Caso nao haja colisao atual, realiza o movimento
            if(!Poligono::calculaColisaoAABB(Tanque, Predio)){
                TanqueMovimentoX--;
            }
            // Atualiza a posicao e procura por colisao
            Tanque.quantidadeTranslatadaX--;
            Tanque.calculaAABB();
            // Caso haja colisao, volta dois movimentos
            if(Poligono::calculaColisaoAABB(Tanque, Predio)){
                TanqueMovimentoX += 2;
            }
            // Isso impede 2 problemas:
            // 1 - usuario avanca, entra em colisao com o objeto e por isso nao pode nem avancar nem retornar
            // 2 - a solucao inicial para o problema acima era que caso haja colisao, avancar retornaria 2x, e retornar avancaria 2x
            // porem essa solucao cria a possibilidade do usuario colidir, e ao retornar avancar, atravessando o objeto
			break;
	    case GLUT_KEY_RIGHT:     // Se pressionar DOWN
            if(!Poligono::calculaColisaoAABB(Tanque, Predio)){
                TanqueMovimentoX++;
            }
            Tanque.quantidadeTranslatadaX++;
            Tanque.calculaAABB();
            if(Poligono::calculaColisaoAABB(Tanque, Predio)){
                TanqueMovimentoX -= 2;
            }
			break;
		default:
			break;
	}
}

// **********************************************************************
//
// **********************************************************************
int  main ( int argc, char** argv )
{
    cout << "Programa OpenGL " << endl;

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 1000, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de titulo da janela.
    glutCreateWindow    ( "Programa OpenGL" );

    // executa algumas inicializa��es
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc ( display );

    // Define que o tratador de evento para
    // o invalida��o da tela. A funcao "display"
    // ser� chamada automaticamente sempre que a
    // m�quina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    // inicia o tratamento dos eventos
    glutMainLoop ( );
    return 0;
}
