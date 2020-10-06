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
  Bruno Victor Vasconcelos
			&&
  Mateus Filipe de Lima Souza
		BSI-2018
*/

int n;
ofstream saida;

//Função de troca de valor dos vetores para ordenação
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

//Função de ordenação, ordena-se pelo primeiro vetor passado, os outros o acompanham
void bubbleSort(int arr[], int arr1[], int arr2[])
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				swap(&arr1[j], &arr1[j + 1]);
				swap(&arr2[j], &arr2[j + 1]);
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
	//Variáveis para leitura de arquivo:
	ifstream ler;
	ler.open("teste1.txt");
	saida.open("saida.txt", fstream::app);
	vector<int> vect; //Vector a salvar

	//REGISTRANDO AS LINHAS E REMOVENDO O ESPAÇO//
	string linhas; //Linhas do arquivo
	int index;
	while (!ler.eof())
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
	
	n = vect[0];

	//Vetores para cada coluno do arquivo
	int* vectPrioridade = new int[n]; //Vetor de prioridades
	int* vectChegada = new int[n]; //Vetor do tempo de chegada
	int* vectDuracao = new int[n]; //Vetor do tempo de duração de cada um
	for (int x = 0, y = 2; x < n; x++, y += 3)
	{
		vectPrioridade[x] = vect[y - 1];
		vectChegada[x] = vect[y];
		vectDuracao[x] = vect[y + 1];
	}

	//Função de cálculo do escalonamento FIFO
	calcFifo(vectChegada, vectDuracao, vectPrioridade);

	//Chamada da função de cálculo do escalonamento PRIORIDADE
	calcPrio(vectChegada, vectDuracao, vectPrioridade);

	//Chamada da função de cálculo do escalonamento SRT_
	calcSRT_(vectChegada, vectDuracao, vectPrioridade);

	//Chamada da função de cálculo do escalonamento RRQ5
	calcRRQ5(vectChegada, vectDuracao, vectPrioridade);

	saida.close();
	ler.close();
}

//Função de cálculo do escalonamento FIFO
void calcFifo(int vectChegada[], int vectDuracao[], int vectPrioridade[]) {
	float fifoME = 0; //Tempo médio de espera do FIFO
	float fifoMR = 0; //Tempo médio de resposta do FIFO
	float tempoEspera = 0; //Tempo de espera total
	float tempoDuracao = 0; //Tempo de duração total
	//Ordenando os vetores pelo tempo de chegada e acompanhados de sua duração e prioridade
	bubbleSort(vectChegada, vectDuracao, vectPrioridade);
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
	fifoME = tempoEspera / n;
	fifoMR = fifoME;
	saida << fixed << setprecision(2);
	saida << "FIFO " << fifoME << " " << fifoMR << endl;
}

//Função de cálculo do escalonamento PRIORIDADE
void calcPrio(int vectChegada[], int vectDuracao[], int vectPrioridade[]) {
	float prioME = 0; //Tempo médio de espera do PRIO
	float prioMR = 0; //Tempo médio de resposta do PRIO
	float tempoEspera = 0;
	float auxDuracao = 0;
	float difChegada = 0;
	//Ordenando os vetores pelo tempo de chegada e acompanhados de sua duração e prioridade
	bubbleSort(vectPrioridade, vectChegada, vectDuracao);
	//Calculando o Tempo médio de Espera do escalonamento Prioridade
	for (int i = 0; i < n; i++)
	{
		auxDuracao += vectDuracao[i]; //Auxiliar do somatório de todas as Durações
	}
	for (int i = (n - 1), j = (n - 2); i >= 0; i--, j--)
	{
		auxDuracao -= vectDuracao[i]; // Subtraindo a duração após "rodar" um dos processos
		if ((vectChegada[j] - vectChegada[i]) < 0 and j != -1)
		{
			difChegada += vectChegada[i] - vectChegada[j]; // Somando a diferença para subtrair da espera total
		}
		tempoEspera += auxDuracao; // Somando a espera total
	}
	tempoEspera -= difChegada; // Tirando a diferença da espera

	float duracao = 0;
	float somaPrioridade = 0;
	float somaResposta = 0;
	//Calculando o Tempo médio de Resposta do escalonamento Prioridade
	for (int i = 0, j = 1; i < n; i++, j++)
	{
		if (vectPrioridade[j] > vectPrioridade[i] && vectChegada[j] != vectChegada[i])
		{
			somaPrioridade += 0;
		}
		if (vectPrioridade[j] >= vectPrioridade[i] && vectChegada[j] == vectChegada[i])
		{
			somaPrioridade += vectDuracao[i];
			somaResposta += somaPrioridade;
		}
		if (vectPrioridade[j] == vectPrioridade[i] && vectChegada[j] > vectChegada[i])
		{
			somaPrioridade += (vectDuracao[j] + vectChegada[j]) - vectChegada[i];
			somaResposta += somaPrioridade;
		}
	}

	prioME = tempoEspera / n;
	prioMR = somaResposta / n;
	saida << fixed << setprecision(2);
	saida << "PRIO " << prioME << " " << prioMR << endl;
}

//Função de cálculo do escalonamento SRT_
void calcSRT_(int vectChegada[], int vectDuracao[], int vectPrioridade[]) {
	float srt_ME = 0;  //Tempo médio de espera do SRT
	float srt_MR = 0; //Tempo médio de resposta do SRT
	bubbleSort(vectChegada, vectPrioridade, vectDuracao);

	//Calculando o Tempo médio de Espera do escalonamento SRT_
	int* auxDuracao = new int[n]; //Vetor auxiliar para tempo de Espera;
	float tempoFinal;
	int menorIndex;
	float restante = 0, time, esperaTotal = 0;
	float respDiferente = 0, aux = 0, respIgual = 0;
	
	bool bo = true;

	for (int i = 0; i < n; i++)
	{
		auxDuracao[i] = vectDuracao[i];
	}
	auxDuracao[9] = 9999;
	for (time = 0; restante != n; time++)
	{
		menorIndex = 9;
		for (int i = 0; i < n; i++)
		{
			if (vectChegada[i] <= time && auxDuracao[i] < auxDuracao[menorIndex] && auxDuracao[i] > 0)
			{
				menorIndex = i;
			}
		}
		auxDuracao[menorIndex]--;
		if (auxDuracao[menorIndex] == 0)
		{
			restante++;
			tempoFinal = time + 1;
			esperaTotal += tempoFinal - vectDuracao[menorIndex] - vectChegada[menorIndex];
			if (bo) {
				respDiferente += esperaTotal - aux; // Diferentes
				respIgual = esperaTotal - aux; // Iguais
				bo = false;
			}
			if (respDiferente == esperaTotal) {
				bo = true;
				aux = esperaTotal;
			}
		}
	}
	
	float totalTempo = vectChegada[0];
	for (int i = 0; i < n; i++) {
		totalTempo += vectDuracao[i];
	}

	//Calculando o Tempo médio de Resposta do escalonamento SRT_
	bool complete = false;
	int cont = 0;
	int aux2 = 0;
	for (int i = 0, j = 1; i < n; i++, j++)
	{
		while (complete == false)
		{
			aux2 += 1;
			if (aux2 == vectChegada[j]) {
				if (vectDuracao[i] - aux2 > vectDuracao[j])
				{
					cont++;
				}
			}
			if (aux2 == totalTempo)
				complete = true;
		}
	}
	if (cont > 0) {
		srt_MR = respIgual / n;
	}
	else {
		srt_MR = respDiferente / n;
	}

	srt_ME = esperaTotal / n;
	saida << fixed << setprecision(2);
	saida << "SRT_ " << srt_ME << " " << srt_MR << endl;
}

//Função de cálculo do escalonamento RRQ5
void calcRRQ5(int vectChegada[], int vectDuracao[], int vectPrioridade[]) {
	float rrq5ME = 0;  //Tempo médio de espera do RRQ5
	float rrq5MR = 0; //Tempo médio de resposta do RRQ5
	bubbleSort(vectChegada, vectPrioridade, vectDuracao);
	//Cálculo do tempo médio de Espera
	int i;
	float total = 0, x, counter = 0;
	float wait_time = 0;
	int* copyDuracao = new int[n];
	int b = 0;
	x = n;
	for (i = 0; i < n; i++)
	{
		copyDuracao[i] = vectDuracao[i];
	}

	for (total = 0, i = 0; x != 0;)
	{
		if (copyDuracao[i] <= 5 && copyDuracao[i] > 0)
		{
			total = total + copyDuracao[i];
			copyDuracao[i] = 0;
			counter = 1;
		}
		else if (copyDuracao[i] > 0)
		{
			copyDuracao[i] = copyDuracao[i] - 5;
			total = total + 5;
		}
		if (copyDuracao[i] == 0 && counter == 1)
		{
			x--;
			wait_time += total - vectChegada[i] - vectDuracao[i];
			counter = 0;
		}
		if (i == n - 1)
		{
			i = 0;
		}
		else if (vectChegada[i + 1] <= total)
		{
			i++;
		}
		else
		{
			i = 0;
		}
	}
	rrq5ME = wait_time / n;

	//Cálculo do tempo médio de Resposta
	float diferencaResposta = 0;
	float somaResposta = 0;
	float primeiraChegada = vectChegada[0];
	for (int i = 0, j = 1; i < n; i++, j++)
	{
		if (j != n)
		{
			while (vectChegada[j] >= primeiraChegada)
			{
				primeiraChegada += 5;
			}
			if (i > 0)
			{
				diferencaResposta = (primeiraChegada + 5) - vectChegada[j];
			}
			else
			{
				diferencaResposta = primeiraChegada - vectChegada[j];
			}
			somaResposta += diferencaResposta;
		}
	}

	rrq5MR = somaResposta / n;
	saida << fixed << setprecision(2);
	saida << "RRQ5 " << rrq5ME << " " << rrq5MR << endl;
}