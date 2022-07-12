// Autor: <Kalil Saldanha Kaliffe>
// Link para rodar o codigo: https://replit.com/@kalilkaliffe/PagPath#main.cpp
// Esse programa calcula o menor custo e menor caminho entre dois pontos de uma matrix 7x7
// Primeiro o programa aplica o algoritmo de dijkstra para achar o menor custo, esse algoritmo utiliza
//um mapa de custos para viajar por cada coordenada usando os movimentos possiveis
//assim o custo para chegar de um ponto a outro é a soma do custo dos caminhos
//logo para saber se uma soma é realmente a menor soma possivel devem ser verificadas todos os caminhos entre eles
//esse não realiza recalculos desnecessarios já que depois que os 4 movimentos a partir de um node são testados já temos os valores finais de suas fronteiras
//assim o algoritmo expande o seu conheicmento das fronteiras até chegar na coordenada alvo
//e para verificar se uma soma é realmente a menor soma para chegar em uma posição e usado uma fila com prioridade(priority queue)
//a fila com prioridade faz um sort dos custos(ela foi invertida para organizar do menor para o maior ao inveis da comparação padrão maior no topo)
//na pratica essa fila organiza nodes que contém as coordenas, custo e node anterior.
//Agora é possivel saber o menor custo a partir do ordenamento da fila e então o menor caminho a partir dos nodes
//que antecedem o node final ou seja o caminho das menores somas usadas para chegar até esse ponto.
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;


//O os recalculos são minimos já que só são feitos recalculados enquanto a posição esta na fila(ela sai da fila quando todas as suas conexões foram calculadas)
//Esse calculo é salvo na matrix custos
int mat[7][7] = {{ 4, 7, 5, 0, 3, 8,13},
                 { 3, 5, 2, 1, 6, 1, 4},
                 { 1, 3, 9,11, 9, 2, 3},
                 {17, 3, 8, 4, 1, 8,14},
                 { 2, 0, 9, 5,11, 0, 4},
                 { 6, 4, 0, 2, 1,10, 3},
                 {7, 13, 2, 0, 7, 1, 2}};

//Possui os movimentos possiveis direita, esquerda, cima e baixo
int moves[4][2] = {{+1, 0},
                   {0, +1},
                   {-1, 0},
                   {0, -1}};


int custos[7][7];


int min(int x, int y);

bool valid(int visitado[7][7], int nextRow, int nextFile);

int cam_min_custo(int mat[7][7], int currRow, int currFile, int Row, int File);

//Node que possui um custo para ser viajado e coordenadas, também armazena as coordenadas do node anterior
struct Node{
    int cost;
    int x;
    int y;
    int prevX;
    int prevY;
};

//Caminho minimo final
vector<Node> caminho_min;


//Comparador para ser usado no terceiro parametro da fila com prioridade

class comparador_novo{
public:
    bool operator() (const Node &lhs, const Node &rhs)
    {
        return (lhs.cost > rhs.cost);
    }
};



int min(int x, int y){
    if(x > y){
        return y;
    }
    return x;

}

//Testa se o movimento esta dentro do espaço da matrix e se a posição já foi visitada
bool valid(int visitado[7][7], int nextRow, int nextFile){
    if(nextRow <7 && nextFile <7 && nextRow >= 0 && nextFile >= 0 && visitado[nextRow][nextFile] == 0){
        return true;
    }
    return false;

}

int cam_min_custo(int mat[7][7], int currRow, int currFile, int Row, int File)
{
    //Contabiliza as posições já vizitadas
    int visitado[7][7] = {{ 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0},
                          { 0, 0, 0, 0, 0, 0, 0}};


    int currCost = 0;
    int pRow = currRow;
    int pFile = currFile;



    //O custo de ir para a posição atual deve ser 0.
    if(currRow == Row && currFile == File){
        return 0;
    }

    //Define um tempo padrão muito alto, porque as posições não contabilizadas tem o tempo desconhecido(infinito na teoria)
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            custos[i][j] = 9999999;
        }
    }

    //Em uma fila com prioriadade, a prioriadade original era do maior para o menor mas como
    //queremos do menor caminho para o maior, é usado o comparador_novo que inverte o valor da comparação
    //O comparador_novo faz a menor distancia aparencer no .top()
    priority_queue<Node, vector<Node>, comparador_novo> fila;

    //Vector que vai servir para organizar o camiho minimo
    vector<Node> caminho;

    //Bota o primeiro custo na fila e matrix
    custos[currRow][currFile] = mat[currRow][currFile];
    fila.push({mat[currRow][currFile], currRow, currFile}); // 0, 0?

    //Insere o primeiro node no vector do caminho
    caminho.insert(caminho.end(), fila.top());

    //quando a fila estiver vazia é porque todas as distancias já foram contabilizadas
    while(!fila.empty()){


        //Extrai a posição a ser testada e a de menor distancia(topo da queue)
        Node node = fila.top();

        //Insere a posição do topo na queue no final do vector caminho
        caminho.insert(caminho.end(), node);

        //Retira o topo da fila
        fila.pop();

        currRow = node.x;
        currFile = node.y;


        //Marca a posição atual como visitada
        visitado[currRow][currFile] += 1;


        //Testa os quatro movimentos possiveis
        for(int i = 0; i < 4; i++){

            int nextRow = currRow + moves[i][0];
            int nextFile = currFile + moves[i][1];

            //Coloca o movimento na fila se ele for valido
            if(valid(visitado, nextRow, nextFile)){
                //Atualiza os custo da proxima posição se ela for menor que a atual
                custos[nextRow][nextFile] = min(custos[nextRow][nextFile], custos[currRow][currFile] + mat[nextRow][nextFile]);

                fila.push({custos[nextRow][nextFile], nextRow, nextFile, currRow, currFile});
            }
        }
    }
    //Imprime o mapa de custos
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            cout<< custos[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;


    bool ultimo = false;
    int tempPrev[2];
    Node tempNode;
    //Imprime o menor caminho a partir do vector caminho
    for(int i = caminho.size(); i >= 0 ; i--){

        //Faz o backtracking do historico de coordenadas a partir do ponto de chegado(o ultimo)
        if(caminho[i].x == Row && caminho[i].y == File && !ultimo){
            ultimo = true;
            tempNode = caminho[i];
            //Verifica as coordenadas do anterior
            tempPrev[0] = tempNode.prevX;
            tempPrev[1] = tempNode.prevY;
            printf("Caminho: x:%d y:%d custo:%d Anterior: x:%d y:%d \n", tempNode.x, tempNode.y, tempNode.cost, tempNode.prevX, tempNode.prevY);
            caminho_min.insert(caminho_min.begin(), tempNode);
            cout << endl;
        }
        if(ultimo){

            for (int j =0; j <= caminho.size(); j++) {
                //Verifica as coordenadas do anterior e então verifica o anterior desse anterior...
                if(tempNode.x == tempPrev[0] && tempNode.y == tempPrev[1]){
                    printf("Caminho: x:%d y:%d custo:%d Anterior: x:%d y:%d \n", tempNode.x, tempNode.y, tempNode.cost, tempNode.prevX, tempNode.prevY);
                    caminho_min.insert(caminho_min.begin(), tempNode);
                    tempPrev[0] = tempNode.prevX;
                    tempPrev[1] = tempNode.prevY;

                    if(tempNode.prevX == pRow && tempNode.prevY == pFile){
                        tempNode.x = pRow;
                        tempNode.y = pFile;
                        caminho_min.insert(caminho_min.begin(), tempNode);
                        ultimo = false;
                    }

                    cout << endl;
                }
                tempNode = caminho[j];

            }
        }
    }

    //Imprime só as coordenadas do caminho minimo
    cout << "Caminho:\n";
    for(int i =0; i <= caminho_min.size() -1; i++){
        caminho_min[i];
        printf("x:%d y:%d\n", caminho_min[i].x, caminho_min[i].y);
    }

    //Retorna o custo da ulitma posição
    return custos[Row][File];
}

int main(){
    int menor_cam;

    menor_cam = cam_min_custo(mat,0,0,6,6);
    //menor_cam = cam_min_custo(mat,3,1,4,5);

    cout<< "Menor caminho: "<<menor_cam << endl;

}