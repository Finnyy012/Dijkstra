#include <iostream>
#include <random>
#include <unordered_set>
#include "Edge.h"
#include "Reis.h"
#include "AutoRit.h"
#include "TreinRit.h"
#include "Vlucht.h"

/**
 * maakt een graph van grootte x * y met random weights
 *
 * @param seed: seed voor rand() (int)
 * @param x: breedte van de graph (int)
 * @param y: hoogte van de graph (int)
 * @param afstandPrijs: prijs per km in een auto (float)
 * @param tijdPrijs: prijs per minuut in een trein (float)
 * @param bagageKosten: kosten van de bagage in het vliegtuig (float)
 * @return set met edges (unordered_set<Edge*>)
 */
static unordered_set<Edge*> generateGraph(int seed, int x, int y, float afstandPrijs, float tijdPrijs, float bagageKosten){
//    random_device dev;    //uncomment dit en `weight = dist(rng);` voor betere randomness
//    mt19937 rng(dev());
//    uniform_int_distribution<mt19937::result_type> dist(1,100);

    srand(seed);
    unordered_set<Edge*> res;
    float weight;

    // deze twee loops maken alle autoritten; de eerste van het begin en eindpunt naar de punten in respectievelijk de
    // eerste en laatste kolom, de tweede maakt alle punten daartussen. bijvoorbeeld een 2*2 graph ziet er zo uit:
    //   / 1 - 3 \
    //  0    X    5
    //   \ 2 - 4 /

    for(int i = 0; i < y; i++){
        //weight = dist(rng);
        weight = (rand() % 100) + 1;
        res.insert(new AutoRit(0, i + 1, weight, afstandPrijs));
        //weight = dist(rng);
        weight = (rand() % 100) + 1;
        res.insert(new AutoRit((x-1)*y + i + 1, 1 + (x*y), weight, afstandPrijs));
    }

    for(int i = 0; i < (x-1); i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < y; k++) {
                //weight = dist(rng);
                weight = rand() % 100;
                res.insert(new AutoRit(1 + j + i*y, 1 + (i+1)*y + k, weight, afstandPrijs));
            }
        }
    }

    // dit stuk maakt de treinritten; het neemt ceil((x*y)/2) aantal vertices en connect die met elkaar en met het
    // begin en eindpunt (als er duplicate vertices zijn worden deze overgeslagen). een trein netwerk in een 3*3 graph
    // kan er bijvoorbeeld zo uit zien:
    // 0 -- 2 --- 9
    //      |  X  |
    //      5 --- 1 -- 10
    vector<int> vertices;
    for(int i = 1; i < ceil((x*y)/2)+1; i++){
        int v = (rand() % (x*y))+1;
        for(int j : vertices) {
            if(j!=v) {
                weight = rand() % 100;
                res.insert(new TreinRit(v, j, weight, tijdPrijs));
            }
        }
        vertices.push_back(v);
    }
    res.insert(new TreinRit(0, vertices[0], rand() % 100, tijdPrijs));
    res.insert(new TreinRit(vertices[1], 1 + (x*y), rand() % 100, tijdPrijs));

    // dit maakt de vluchten; een edge gaat van het beginpunt naar een willekeurige vertice en de andere van deze
    // vertice naar het eindpunt
    int v = (rand() % (x*y))+1;
    res.insert(new Vlucht(0,v,(rand() % 500)+100,(float(rand() % 100)) /100,bagageKosten));
    res.insert(new Vlucht(v,1 + (x*y),(rand() % 500)+100,(float(rand() % 100))/100,bagageKosten));

    return res;
}

/**
 * functie om de priority_queue met reizen uit te printen
 *
 * @param pq: queue om uit te printen
 */
static void printQueue(priority_queue<Reis, vector<Reis>, greater<>> pq){
    stack<Reis> s;
    while(!pq.empty()){
        s.push(pq.top());
        pq.pop();
        cout << s.top() << endl;
    }
    while(!s.empty()){
        pq.push(s.top());
        s.pop();
    }
}

/**
 * print de edges uit met de extra informatie van de class eronder
 * (anders wordt er gewoon "vertex_1: x vertex_2: y prijs: z" uitgeprint)
 *
 * @param e: edge
 */
static void printEdge(Edge* e){
    try{
        auto& a = dynamic_cast<TreinRit&>(*e);
        cout << a << endl;
    } catch(const bad_cast& e) {}
    try{
        auto& a = dynamic_cast<Vlucht&>(*e);
        cout << a << endl;
    } catch(const bad_cast& e) {}
    try{
        auto& a = dynamic_cast<AutoRit&>(*e);
        cout << a << endl;
    } catch(const bad_cast& e) {}
}

/**
 * het Dijkstra algoritme: zoekt in de gegeven graph de beste (goedkoopste) route van type T
 * ik heb ervoor gekozen om afstand en tijd om te rekenen naar prijs zodat verschillende rijzen met elkaar vergeleken
 * kunnen worden.
 *
 * @tparam T: Type vervoersmiddel
 * @param start: begin vertex (int)
 * @param end: eind vertex (int)
 * @param graph: graph om te evalueren (unordered_set<Edge*>)
 * @return set van vertices (Reis)
 * @throws invalid_argument: wanneer er geen pad van start naar end gevonden kan worden.
 */
template<typename T>
static Reis dijkstra(int start, int end, unordered_set<Edge*> graph){
    priority_queue<Reis, vector<Reis>, greater<>> pq;
    unordered_set<int> visited = {start};
    Reis cReis;
    Reis tempReis;
    cReis.endPoint = start;

    for(Edge* e : graph){
        if(e->vertex_1==start || e->vertex_2==start){
            cReis = Reis();
            cReis.addEdge(e);
            pq.push(cReis);
            graph.erase(e);
        }
    }
    if(pq.empty()){throw invalid_argument("no path");}

//    cout<<endl;
//    printQueue(pq);

    while(pq.top().endPoint!=end) {
        cReis = pq.top();
        pq.pop();
        for (Edge* currentEdge: graph) {
            try{
                auto& a = dynamic_cast<T&>(*currentEdge);
                if (currentEdge->vertex_1 == cReis.endPoint || currentEdge->vertex_2 == cReis.endPoint) {
                    tempReis = cReis;
                    tempReis.addEdge(currentEdge);
                    pq.push(tempReis);
                    graph.erase(currentEdge);
                }
            } catch(const bad_cast& e) {}
        }
        if(pq.empty()){throw invalid_argument("no path");}
//        cout<<endl;
//        printQueue(pq);
    }

    if(pq.empty()){throw invalid_argument("no path");}
    return pq.top();
}


int main() {
    int x = 3;
    int y = 3;
    int seed = 1;
    //pas hier de grootte van de graph en de seed voor rand aan

    unordered_set<Edge*> graph = generateGraph(seed, x, y, 0.4, 0.25, 100);

    for(Edge* e : graph) {printEdge(e);}
    cout << endl;

    Reis autoRit = dijkstra<AutoRit>(0, x*y+1, graph);
    Reis treinRit = dijkstra<TreinRit>(0, x*y+1, graph);
    Reis vlucht = dijkstra<Vlucht>(0, x*y+1, graph);

    cout << "Autorit: " << autoRit << endl << endl;
    cout << "Treinrit: " << treinRit << endl << endl;
    cout << "Vlucht: " << vlucht << endl << endl;

    return 0;
}