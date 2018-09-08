#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pdi.h"

#define ORIGINAL "./GT2.BMP"
#define JANELA_X 15
#define JANELA_Y 15

int main() {

    Imagem *imagem;

    //Abre a imagem a ser borrada
    printf("A carregar a imagem [ %s ]... ", ORIGINAL);
    imagem = abreImagem(ORIGINAL, 3);
    
    if(!imagem) {
        printf("ERRO: A imagem não pode ser aberta.\n");
        exit(1);
    }
    printf("OK\n");

    bloomGauss(imagem);

    bloomMedia(imagem);

    destroiImagem(imagem);

    return 0;
}

void bloomMedia(Imagem *imagem) {
    
    int i;
    Imagem *saida, *final, *saida2, *saida3, *temp;

    saida = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    saida2 = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    saida3 = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    final = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    temp = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);

    copiaConteudo(imagem, temp);

    for(i=0;i<1;i++){
        filtroMediana8bpp(temp, saida, 3, 3);
        copiaConteudo(saida, temp);
    }

    salvaImagem(saida, "media1");

    copiaConteudo(imagem, temp);

    for(i=0;i<2;i++){
        filtroMediana8bpp(temp, saida2, 3,3);
        copiaConteudo(saida2, temp);
    }
    
    salvaImagem(saida2, "media2");
    copiaConteudo(imagem, temp);

    for(i=0;i<3;i++){
        filtroMediana8bpp(temp, saida3, 3, 3);
        copiaConteudo(saida3, temp);
    }

    salvaImagem(saida3, "media3");

    soma(imagem, saida, 1.0f, 0.1f, final);
    salvaImagem(final, "teste_med1");

    soma(imagem, saida2, 1.0f, 0.2f, final);
    salvaImagem(final, "teste_med2");

    soma(imagem, saida3, 1.0f, 0.3f, final);
    salvaImagem(final, "teste_med3");

    destroiImagem(saida);
    destroiImagem(saida2);
    destroiImagem(saida3);
    destroiImagem(temp);
    destroiImagem(final);

}


void bloomGauss(Imagem *imagem){

    Imagem *saida, *buffer, *final, *saida2, *saida3;

    saida = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    saida2 = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    saida3 = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);

    buffer = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);
    final = criaImagem(imagem->largura, imagem->altura, imagem->n_canais);


    filtroGaussiano(imagem, saida, 0.4f, 0.4f, buffer);
    salvaImagem(saida, "gauss1");

    filtroGaussiano(imagem, saida2, 1.2f, 1.2f, buffer);
    salvaImagem(saida2, "gauss2");

    filtroGaussiano(imagem, saida3, 2.4f, 2.4f, buffer);
    salvaImagem(saida3, "gauss3");

    soma(imagem, saida, 1.0f, 0.1f, final);
    salvaImagem(final, "teste1");
    soma(final, saida2, 1.0f, 0.1f, final);
    salvaImagem(final, "teste2");
    soma(final, saida3, 1.0f, 0.1f, final);
    salvaImagem(final, "teste3");
    
    destroiImagem(saida);
    destroiImagem(saida2);
    destroiImagem(saida3);
    destroiImagem(buffer);
    destroiImagem(final);
}

