# dijkstra-shortestpath

Autor: Kalil Saldanha Kaliffe

Link para rodar o codigo: https://replit.com/@kalilkaliffe/PagPath#main.cpp

Esse programa calcula o menor custo e menor caminho entre dois pontos de uma matrix 7x7.

Primeiro o programa aplica o algoritmo de dijkstra para achar o menor custo, esse algoritmo utiliza
um mapa de custos para viajar por cada coordenada usando os movimentos possiveis
assim o custo para chegar de um ponto a outro é a soma do custo dos caminhos
logo para saber se uma soma é realmente a menor soma possivel devem ser verificadas todos os caminhos entre eles
esse não realiza recalculos desnecessarios já que depois que os 4 movimentos a partir de um node são testados já temos os valores finais de suas fronteiras
assim o algoritmo expande o seu conheicmento das fronteiras até chegar na coordenada alvo
e para verificar se uma soma é realmente a menor soma para chegar em uma posição e usado uma fila com prioridade(priority queue)
a fila com prioridade faz um sort dos custos(ela foi invertida para organizar do menor para o maior ao inveis da comparação padrão maior no topo)
na pratica essa fila organiza nodes que contém as coordenas, custo e node anterior.

Agora é possivel saber o menor custo a partir do ordenamento da fila e então o menor caminho a partir dos nodes
que antecedem o node final ou seja o caminho das menores somas usadas para chegar até esse ponto.
