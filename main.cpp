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

int main()
{

    int p; //Prioridade do Processo
    int i; //Instante de chegada do processo
    int s; //Tempo de serviço do processo

    //Variáveis para leitura de arquivo:
    ifstream ler;
    ofstream saida;
    saida.open("saida.txt",fstream::app);
    ler.open("teste1.txt");

    // REGISTRANDO AS LINHAS E REMOVENDO O ESPAÇO//
    string linhas; //Linhas do arquivo
    vector<int> vect; //Vector a salvar
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
    //===========================================//
    //Impressão de Teste dos valores lidos no arquivo
    for (index=0; index< vect.size(); index++){
        auxiliar = vect[index];
        //cout << auxiliar << endl;
    }
    n = vect[0];
    cout<<"Processos: "<<n<<endl;
    //==================================================//
    //Calculando o Tempo médio de Espera do escalonamento FIFO
    float fifoSoma = 0; //Soma de tempo do FIFO
    float fifoME = 0;  //Tempo médio de espera do FIFO
    float fifoMR = 0; //Tempo médio de resposta do FIFO
    for(int x = 0, y = 3 ; x < n ; x++, y+=3){
      fifoSoma += vect[y]-vect[y-1];
    }
    fifoME = fifoSoma/n;
    fifoMR = fifoME;
    cout << fixed << setprecision(2);
    cout<<"FIFO "<<fifoME<<" "<<fifoMR<<endl;
    //==========================================================//

    ler.close();
}
