# Leitura de Escalonamento🧗‍♂️
<img width="22%" src="https://upload.wikimedia.org/wikipedia/commons/3/33/Fila_processos.jpg">
<img width="22%" src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3c/Algoritmo_SRT.gif/220px-Algoritmo_SRT.gif">
<h6>Exemplo de Escalonamento: <a href="https://pt.wikipedia.org/wiki/Shortest_remaining_time">SRT</a></h6> 
<h2>Resumo</h2>
Este projeto retrata uma leitura de um arquivo ".txt" com dados do escalonamento para o calcúlo das médias que irão para o arquivo de saída.
<h2>Escalonamentos retratados</h2>
<ul>
  <li>FIFO (First in / First Out)</li>
  <li>Prioridade</li>
  <li>SRT (Shortest Time Remaining)</li>
  <li>Round Robin, com quantum = 5</li>
</ul>
<h2>Arquivos Do Projeto</h2>
<ul>
  
  <li>
  main.cpp
    <ul>
      <li>Arquivo principal com todo a execução código, leitura, entre outras funções a serem implementadas.</li>
    </ul>
  </li>
  <li>
  teste.cpp
    <ul>
      <li>Arquivo para testes de implementação, foi nele onde testei inicialmente a remoção dos " "(espaços) na leitura.</li>
    </ul>
  </li>
  <li>
  testeX.txt
    <ul>
      <li>Todos os arquivos de texto são as entradas do código principal, com os dados necessários.</li>
    </ul>
  </li>
</ul>
<h2>Arquivos</h2>

No arquivo de <b>entrada</b>, a primeira linha do arquivo representa seu número de linhas de comandos.
Nas linhas de comando temos 3 valores inteiros, o primeiro P definindo a prioridade, 
o segundo I definindo o instante de chegada do processo e o S que determina o tempo de serviso do processo.

No arquivo de <b>saída</b> será necessário escrever o nome do escalonamento e junto a ele o resultado do cálculo 
do tempo médio de espera e o tempo médio de resposta de cada um com 2 casas decimais em cada um deles.

<h3>Exemplo:</h3>

| Entrada |       Saída      |
|---------|------------------|
| 3       | FIFO 30.67 30.67 |
| 0 20 42 | PRIO 46.00 0.00  |
| 2 3 33  | SRT_ 26.67 26.67 |
| 1 14 54 | RRQ5 53.34 4.00  |


<h6>Atualmente estou tentando refazer este projeto em C# se quiser dar uma olhada: <a href="https://github.com/mateusfilipe/Learning/tree/master/learning-cSharp/leitura-escalonamento-CSharp">Acesse aqui</a></h6>
