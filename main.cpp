#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"

using namespace std;

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if(!graph->getWeightedEdge() && !graph->getWeightedNode()) {
        while(input_file >> idNodeSource >> idNodeTarget) {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    } else if(graph->getWeightedEdge() && !graph->getWeightedNode() ) {
        float edgeWeight;
        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }

    } else if(graph->getWeightedNode() && !graph->getWeightedEdge()) {
        float nodeSourceWeight, nodeTargetWeight;
        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    } else if(graph->getWeightedNode() && graph->getWeightedEdge()) {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;
        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    return graph;
}

Graph* leituraInstancia(ifstream& input_file, int directed, int weightedEdge, int weightedNode) {

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    while(input_file >> idNodeSource >> idNodeTarget) {
        graph->insertEdge(idNodeSource, idNodeTarget, 0);
    }
    return graph;
}

int menu() {

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Subgrafo induzido por conjunto de vértices" << endl;
    cout << "[2] Caminho Mínimo entre dois vértices - Dijkstra" << endl;
    cout << "[3] Caminho Mínimo entre dois vértices - Floyd" << endl;
    cout << "[4] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[5] Árvore Geradora Mínima de Prim" << endl;
    cout << "[6] Imprimir caminhamento em largura" << endl;
    cout << "[7] Imprimir ordenacao topológica" << endl;
    cout << "[8] Algoritmo Guloso" << endl;
    cout << "[9] Algoritmo Guloso Randomizado " << endl;
    cout << "[10] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Graph* graph, ofstream& output_file) {

    switch (selecao) {
        //Subgrafo induzido por um conjunto de vértices X;
        case 1:{
            int id;
            cout << "Qual será o vértice de origem?" << endl;
            cin >> id;
            Graph *graphAux = graph->getVertexInduced(id);
            cout << "**************************************************" << endl;
            cout << "Vértice-induzido pelo fecho transitivo direto: " << endl;
            graphAux->printGraph();
            graphAux = graph->getIndirectTransitive(id);
            cout << "**************************************************" << endl;
            cout << "Vértice-induzido pelo fecho transitivo indireto: " << endl;
            graphAux->printGraph();
            break;
        }
            //Caminho mínimo entre dois vértices usando Dijkstra;
        case 2:{
            int idStart, idEnd;
            cout << "Vértice de origem?" << endl;
            cin >> idStart;
            cout << "Vértice de destino?" << endl;
            cin >> idEnd;
            int distance = graph->dijkstra(idStart, idEnd);
            cout << "**************************************************" << endl;
            cout << "A distância entre " << idStart << " e " << idEnd << " é de " << distance << endl;
            break;
        }
            //Caminho mínimo entre dois vértices usando Floyd;
        case 3:{
            int idStart, idEnd;
            cout << "Vértice de origem?" << endl;
            cin >> idStart;
            cout << "Vértice de destino?" << endl;
            cin >> idEnd;
            int distance = graph->floydMarshall(idStart,idEnd);;
            cout << "**************************************************" << endl;
            cout << "A distância entre " << idStart << " e " << idEnd << " é de " << distance << endl;
            break;
        }
            //AGM - Kruscal;
        case 4:{
            cout << "Funcionabilidade ainda não desenvolvida" << endl;
            break;
        }
            //AGM Prim;
        case 5:{
            int max = graph->getOrder();
            cout << "Número máximo de vertices (até " << graph->getOrder() << "): " << endl;
            cin >> max;
            int *list = new int[max];
            cout << "Informe a lista de vertices: " << endl;
            for (int i = 0; i < max; i++) {
                cout << "Vértice " << i << ": " << endl;
                cin >> list[i];
                // list[i] = i;
            }
            // for (int i = 0; i < max; i++) {
            //     cout << list[i] << " ";
            // }
            Graph *graphAux = graph->auxAgmPrim(list, max);
            graphAux->printGraphDot(output_file);
            break;
        }
            //Busca em largura;
        case 6:{
            int id;
            cout << "Qual será o vértice de origem?" << endl;
            cin >> id;
            graph->breadthFirstSearch(id);
            break;
        }
            //Ordenação Topologica;
        case 7:{
            cout << "Funcionabilidade ainda não desenvolvida" << endl;
            break;
        }
        default:
        {
            cout << " Error!!! invalid option!!" << endl;
        }

    }
}

int mainMenu(ofstream& output_file, Graph* graph) {

    int selecao = 1;

    while(selecao != 0) {
        // system("clear");
        selecao = menu();

        if(output_file.is_open())
            selecionar(selecao, graph, output_file);
        else
            cout << "Unable to open the output_file" << endl;
        output_file << endl;
    }

    return 0;
}



int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size()) {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph* graph;

    if(input_file.is_open()) {
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    } else
        cout << "Unable to open " << argv[1];


    
    mainMenu(output_file, graph);
    // graph->printGraph();
    // graph->printGraphDot(output_file);
    // Graph *graph2 = graph->getIndirectTransitive(5);
    // graph2->printGraph();
    // graph->breadthFirstSearch(0);
    // cout << graph->dijkstra(1,4);
    //Fechando arquivo de entrada
    // Graph *aux = graph->agmPrim();
    // aux->printGraphDot(output_file);
    

    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}

