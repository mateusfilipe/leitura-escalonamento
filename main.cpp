#include <iostream>
#include <locale.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

/*
int 'n' : linhas

int 'p' : 0 <= p <= 10
int 'i' : 0 <= i <= 2^(n-1)
int 's' : 1 <= s <= 2^(n-2)
*/
int n;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSortChegada(int arr[], int arr1[], int arr2[])
{
    for (int i = 0; i < n-1; i++){
      for (int j = 0; j < n-i-1; j++){
        if (arr[j] > arr[j+1]){
          swap(&arr[j], &arr[j+1]);
          swap(&arr1[j], &arr1[j+1]);
          swap(&arr2[j], &arr2[j+1]);
        }
      }
    }
}
void calcFifo(int vectChegada[], int vectDuracao[], int vectPrioridade[]);
void calcPrio(int vectChegada[], int vectDuracao[], int vectPrioridade[]);
void calcSRT_(int vectChegada[], int vectDuracao[], int vectPrioridade[]);
void calcRRQ5(int vectChegada[], int vectDuracao[], int vectPrioridade[]);

int main()
{

    int p; //Prioridade do Processo
    int i; //Instante de chegada do processo
    int s; //Tempo de serviço do processo

    //Variáveis para leitura de arquivo:
    ifstream ler;
    ler.open("teste1.txt");
    vector<int> vect; //Vector a salvar

    // REGISTRANDO AS LINHAS E REMOVENDO O ESPAÇO//
    string linhas; //Linhas do arquivo
    int index;
    int auxiliar;
    while(!ler.eof())
    {
        getline(ler, linhas); // lendo linha por linha
        stringstream ss(linhas); // stringstream ss recebe a linha lida
        while (ss >> index)
        {
          vect.push_back(index); // salvando o primeiro valor num vector
          if (ss.peek() == ' ')
            ss.ignore();        //ignorando os espaços do arquivo
        }
    }
    //Impressão de Teste dos valores lidos no arquivo
    for (index=0; index< vect.size(); index++){
        auxiliar = vect[index];
        cout << auxiliar << endl;
    }
    n = vect[0];
    cout<<"Processos: "<<n<<endl;
    //Vetores para cada coluno do arquivo
    int *vectPrioridade = new int[n]; //Vetor de prioridades
    int *vectChegada = new int[n]; //Vetor do tempo de chegada
    int *vectDuracao = new int[n]; //Vetor do tempo de duração de cada um
    for(int x = 0, y = 2; x < n ; x++, y+=3){
      vectPrioridade[x] = vect[y-1];
      vectChegada[x] = vect[y];
      vectDuracao[x] = vect[y+1];
    }
    //Ordenando os vetores pelo tempo de chegada e acompanhados de sua duração e prioridade
    bubbleSortChegada(vectChegada, vectDuracao, vectPrioridade);

    //===========================================//
    //Função de cálculo do escalonamento FIFO
    calcFifo(vectChegada, vectDuracao, vectPrioridade);
    //===========================================//

    //===========================================//
    //Chamada da função de cálculo do escalonamento PRIORIDADE
    calcPrio(vectChegada, vectDuracao, vectPrioridade);
    //===========================================//

    //===========================================//
    //Chamada da função de cálculo do escalonamento SRT_
    calcSRT_(vectChegada, vectDuracao, vectPrioridade);
    //===========================================//

    //===========================================//
    //Chamada da função de cálculo do escalonamento RRQ5
    calcRRQ5(vectChegada, vectDuracao, vectPrioridade);
    //===========================================//

    ler.close();
}
//=========================================================================//
//Função de cálculo do escalonamento FIFO
//=========================================================================//
void calcFifo(int vectChegada[], int vectDuracao[], int vectPrioridade[]){
    ofstream saida;
    saida.open("saida.txt",fstream::app);
    float fifoME = 0;  //Tempo médio de espera do FIFO
    float fifoMR = 0; //Tempo médio de resposta do FIFO
    float tempoEspera; //Tempo de espera total
    float tempoDuracao; //Tempo de duração total
    //Calculando o Tempo médio de Espera do escalonamento FIFO
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            tempoEspera = 0;
            tempoDuracao = vectChegada[i] + vectDuracao[i];
        }
        else
        {
            tempoEspera += tempoDuracao - vectChegada[i];
            tempoDuracao += vectDuracao[i];
        }
    }
    fifoME = tempoEspera/n;
    fifoMR = fifoME;
    saida << fixed << setprecision(2);
    saida <<"FIFO "<<fifoME<<" "<<fifoMR<<endl;
}
//=========================================================================//
//Função de cálculo do escalonamento PRIORIDADE
//=========================================================================//
void calcPrio(int vectChegada[], int vectDuracao[], int vectPrioridade[]){
    ofstream saida;
    saida.open("saida.txt",fstream::app);
    float prioME = 0;  //Tempo médio de espera do FIFO
    float prioMR = 0; //Tempo médio de resposta do FIFO


    saida << fixed << setprecision(2);
    saida <<"PRIO "<<prioME<<" "<<prioMR<<endl;
}
//=========================================================================//
//Função de cálculo do escalonamento SRT_
//=========================================================================//
void calcSRT_(int vectChegada[], int vectDuracao[], int vectPrioridade[]){
    ofstream saida;
    saida.open("saida.txt",fstream::app);
    float srt_ME = 0;  //Tempo médio de espera do FIFO
    float srt_MR = 0; //Tempo médio de resposta do FIFO


    saida << fixed << setprecision(2);
    saida <<"SRT_ "<<srt_ME<<" "<<srt_MR<<endl;
}
//=========================================================================//
//Função de cálculo do escalonamento RRQ5
//=========================================================================//
void calcRRQ5(int vectChegada[], int vectDuracao[], int vectPrioridade[]){
    ofstream saida;
    saida.open("saida.txt",fstream::app);
    float rrq5ME = 0;  //Tempo médio de espera do FIFO
    float rrq5MR = 0; //Tempo médio de resposta do FIFO


    saida << fixed << setprecision(2);
    saida <<"RRQ5 "<<rrq5ME<<" "<<rrq5MR<<endl;
}
//=========================================================================//
