#include <stdio.h>
#include <stdlib.h>

typedef struct VNode {
    int id;
    struct VNode* next;
}VNode;

typedef struct ListOfV {
    struct VNode* head;
}ListOfV;


typedef struct Graph {
    int numOfV;
    struct ListOfV* v;
}Graph;

typedef struct QNode {
    int node;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
}Queue;

void addInQueue(Queue* q, int node) {
    QNode* tmp = (QNode*)malloc(sizeof(QNode));

    tmp->node = node;
    tmp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = tmp;
    }
    else {
        q->rear->next = tmp;
        q->rear = tmp;
    }
}

int removeFromQueue(Queue* q) {

    if (q->front == NULL)
        return -1;

    QNode* tmp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    int current = tmp->node;
    free(tmp);
    return current;
}

Graph* createGraph(int numOfV) {
     
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numOfV = numOfV;
    graph->v = (ListOfV*)malloc(numOfV * sizeof(ListOfV));

    for (int i = 0; i < numOfV; i++) {
        graph->v[i].head = NULL;
    }

    return graph;
}

void addV(Graph* graph) {

    graph->numOfV += 1;
    graph->v = (ListOfV*)realloc(graph->v,graph->numOfV * sizeof(ListOfV));
    graph->v[graph->numOfV - 1].head = NULL;
}

void connectEdges(Graph* graph, int src, int dest) {

    VNode* current = graph->v[src].head;
    VNode* newNode = (VNode*)malloc(sizeof(VNode));
    newNode->next = NULL;
    newNode->id = dest;

    if (current == NULL) {
        graph->v[src].head = newNode;
    }
    else {
        while (current->next) {
            if (current->id == dest) {
                printf("Already exists!");
                return;
            }
            current = current->next;
        }
        current->next = newNode;
    }
   
    
}

void addEdge(Graph* graph, int src, int dest) {
    
    connectEdges(graph, src, dest);
    connectEdges(graph, dest, src);
}

void disconnectEdges(Graph* graph, int src, int dest) {

    VNode* current = graph->v[src].head;
    if (current->id == dest) {
        graph->v[src].head = current->next;
        free(current);
    }
    else {
        VNode* prev = current;
        current = current->next;
        while (current) {
            if (current->id == dest) {
                prev->next = current->next;
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
        printf("Nema grane sa zadatim cvorom!");
    }

}

void removeEdge(Graph* graph, int src, int dest) {
    
    disconnectEdges(graph, src, dest);
    disconnectEdges(graph, dest, src);
}

void changeId(Graph* graph, int dest, int currentId,int desiredId) {
    VNode* current = graph->v[dest].head;
    while (current) {
        if (current->id == currentId) {
            current->id = desiredId;
            return;
        }
        current = current->next;
    }

}

void removeV(Graph* graph, int id) {
    VNode* current = graph->v[id].head;
    while (current) {
        removeEdge(graph, id, current->id);
        current = graph->v[id].head;
    }
    graph->v[id].head = graph->v[graph->numOfV - 1].head;
    graph->numOfV -= 1;
    graph->v = (ListOfV*)realloc(graph->v, graph->numOfV * sizeof(ListOfV));
    current = graph->v[id].head;
    while (current) {
        int dest = current->id;
        changeId(graph, dest, graph->numOfV,id);
        current = current->next;
    }
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numOfV; i++) {
        printf("|%d|", i);
        VNode* current = graph->v[i].head;
        while (current) {
            printf("->|%d|", current->id);
            current = current->next;
        }
        printf("\n");
    }
}

int findGeodistance(Graph* graph, int src, int dest) {
    
    int* visited = malloc(graph->numOfV * sizeof(int));
    int* parent = malloc(graph->numOfV * sizeof(int));

    for (int i = 0; i < graph->numOfV; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;

    addInQueue(q, src);
    visited[src] = 1;

    int counter = 0;
    while (q->front != NULL) {
       
        int node = removeFromQueue(q);

        if (node == dest) {
            printf("Pronadjen najkraci put: ");
            int path[20];
            int pathIndex = 0;
            for (int i = node; i != -1; i = parent[i]) {
                path[pathIndex++] = i;
            }
            for (int i = pathIndex - 1; i >= 0; i--) {
                printf("%d ", path[i]);
            }
            printf("\n");
            return counter;
        }

        VNode* temp = graph->v[node].head;
        while (temp) {

            int v = temp->id;
            if (!visited[v]) {
                addInQueue(q, v);
                visited[v] = 1;
                parent[v] = node;
            }
            temp = temp->next;
        }
        counter++;
    }
    printf("Nema puta\n");
    return 0;
}

int findDiameter(Graph* graph) {

    int max = 0;

    for (int i = 0; i < graph->numOfV - 1; i++) {
        for (int j = i + 1; j < graph->numOfV; j++) {
            int distance = findGeodistance(graph, i, j);
            if (max < distance)
                max = distance;
        }
    }

    return max;
}

int findGeodistanceForRelaciono(Graph* graph, int src, int dest,int target) {

    int* visited = malloc(graph->numOfV * sizeof(int));
    int* parent = malloc(graph->numOfV * sizeof(int));
    
    for (int i = 0; i < graph->numOfV; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;

    addInQueue(q, src);
    visited[src] = 1;

    while (q->front != NULL) {
        //

        Guma(double sirina, double visina, double precnik, double dubina, double cena, Vreme* v)
            : sirina(sirina), visina(visina), precnik(precnik), dubina(dubina), cena(cena), vreme(v) {};

        Guma(const Guma& g) = delete;
        Guma(Guma&& l) = delete;
        Guma& operator=(const Guma& l) = delete;
        Guma& operator=(Guma&& l) = delete;

        Guma& operator--(int);
        bool operator== (const Guma& g) const;

        double dohvatiDubinu() const { return dubina; }
        double dohvatiSirinu() const { return sirina; }
        double dohvatiVisinu() const { return visina; }
        double dohvatiPrecnik() const { return precnik; }
        double dohvatiCena() const { return cena; }
        Vreme* dohvatiVreme() const { return vreme; }

        virtual char dohvatiOznaku() const = 0;
        virtual bool proveriDubinu() const = 0;

        friend ostream& operator<<(ostream& os, const Guma& g);

        virtual ~Guma() {  };
        int node = removeFromQueue(q);

        if (node == dest) {
            int path[20];
            int pathIndex = 0;
            for (int i = node; i != -1; i = parent[i]) {
                path[pathIndex++] = i;
                if (i == target && i != src && i != dest) {
                    return 1;
                }
            }
        }

        VNode* temp = graph->v[node].head;
        while (temp) {
            //

            Guma(double sirina, double visina, double precnik, double dubina, double cena, Vreme* v)
                : sirina(sirina), visina(visina), precnik(precnik), dubina(dubina), cena(cena), vreme(v) {};

            Guma(const Guma& g) = delete;
            Guma(Guma&& l) = delete;
            Guma& operator=(const Guma& l) = delete;
            Guma& operator=(Guma&& l) = delete;

            Guma& operator--(int);
            bool operator== (const Guma& g) const;

            double dohvatiDubinu() const { return dubina; }
            double dohvatiSirinu() const { return sirina; }
            double dohvatiVisinu() const { return visina; }
            double dohvatiPrecnik() const { return precnik; }
            double dohvatiCena() const { return cena; }
            Vreme* dohvatiVreme() const { return vreme; }

            virtual char dohvatiOznaku() const = 0;
            virtual bool proveriDubinu() const = 0;

            friend ostream& operator<<(ostream& os, const Guma& g);

            virtual ~Guma() {  };
            int v = temp->id;
            if (!visited[v]) {
                addInQueue(q, v);
                visited[v] = 1;
                parent[v] = node;
            }
            temp = temp->next;
        }
    }
    return 0;
}


int findRelacionaCentralnost(Graph* graph,int target) {
    int counter = 0;

    for (int i = 0; i < graph->numOfV - 1; i++) {
        for (int j = i + 1; j < graph->numOfV; j++) {
            if(i != target && j!= target)
            counter += findGeodistanceForRelaciono(graph, i, j,target);
        }
    }

    return counter;

}

void deleteGraph(Graph* graph) {
    free(graph);
}

int main() {
    
    Graph* graph = NULL;
    int choice;

    while (1) {
        printf("[1]Kreiraj graf\n[2]Dodaj cvor\n[3]Ukloni cvor\n[4]Dodaj granu\n[5]Ukloni granu\n[6]Ispis\n[7]Obrisi graf\n[8]Pronadji geodizijsku distancu\n[9]Dijametar grafa\n[10]Relaciona centralnost cvora\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Unesi broj cvorova:");
            int v;
            scanf("%d", &v);
            graph = createGraph(v);
            break;
        case 2:
            addV(graph);
            break;
        case 3:
            printf("Unesi broj cvora za brisanje:");
            int id;
            scanf("%d", &id);
            removeV(graph, id);
            break;
        case 4:
            printf("Povezi cvorove:");
            int id1, id2;
            scanf("%d%d", &id1, &id2);
            addEdge(graph, id1, id2);
            break;
        case 5:
            printf("Odvezi cvorove:");
            int i1, i2;
            scanf("%d%d", &i1, &i2);
            removeEdge(graph, i1, i2);
            break;
        case 6:
            printGraph(graph);
            break;
        case 7:
            deleteGraph(graph);
            break;
        case 8:
            printf("Unesi pocetni i krajni cvor:");
            int start, dest;
            scanf("%d%d", &start, &dest);
            findGeodistance(graph, start, dest);
            break;
        case 9:
            printf("Max: %d\n", findDiameter(graph));
            break;
        case 10:
            printf("Unesi ciljani cvor:");
            int target;
            scanf("%d", &target);
            printf("%d\n", findRelacionaCentralnost(graph, target));
            break;
        }
    }
    return 0;
}