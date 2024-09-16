#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Uma tarefa tem tempo de início, tempo de término e lucro.
struct Tarefa {
    int inicio, fim, lucro;
};

// Função de utilidade usada para ordenar as tarefas de acordo com o tempo de término
bool compararTarefas(Tarefa t1, Tarefa t2) {
    return (t1.fim < t2.fim);
}

// Encontra a última tarefa (no array ordenado) que não entra em conflito com a tarefa[i].
// Se não houver tarefa compatível, retorna -1.
int ultimaTarefaNaoConflitante(vector<Tarefa>& tarefas, int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (tarefas[j].fim <= tarefas[i - 1].inicio)
            return j;
    }
    return -1;
}

// Função recursiva que retorna o lucro máximo possível do array dado de tarefas.
// O array de tarefas deve estar ordenado por tempo de término.
// Memoization usada para armazenar resultados já calculados.
int encontrarLucroMaximoRecursivo(vector<Tarefa>& tarefas, int n, vector<int>& memo) {
    // Caso base
    if (n == 1) return tarefas[n - 1].lucro;

    // Se já foi calculado, retorna o valor armazenado
    if (memo[n - 1] != -1)
        return memo[n - 1];

    // Encontra o lucro quando a tarefa atual é incluída
    int lucroIncluido = tarefas[n - 1].lucro;
    int i = ultimaTarefaNaoConflitante(tarefas, n);
    if (i != -1)
        lucroIncluido += encontrarLucroMaximoRecursivo(tarefas, i + 1, memo);

    // Encontra o lucro quando a tarefa atual é excluída
    int lucroExcluido = encontrarLucroMaximoRecursivo(tarefas, n - 1, memo);

    // Armazena o resultado e retorna
    memo[n - 1] = max(lucroIncluido, lucroExcluido);
    return memo[n - 1];
}

// Função principal que retorna o lucro máximo possível do array dado de tarefas
int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    // Montando as tarefas a partir das entradas
    vector<Tarefa> tarefas;
    for (int i = 0; i < startTime.size(); i++) {
        tarefas.push_back({startTime[i], endTime[i], profit[i]});
    }

    int n = tarefas.size();
    // Ordena as tarefas de acordo com o tempo de término
    sort(tarefas.begin(), tarefas.end(), compararTarefas);

    // Vetor de memoização inicializado com -1 (valor indicando não calculado)
    vector<int> memo(n, -1);

    return encontrarLucroMaximoRecursivo(tarefas, n, memo);
}

// Função principal
int main() {

    // Entrada: tempos de início, tempos de fim e lucros
    vector<int> startTime = {1, 2, 3, 3};
    vector<int> endTime = {3, 4, 5, 6};
    vector<int> profit = {50, 10, 40, 70};

    // Saída
    cout << jobScheduling(startTime, endTime, profit) << endl;

    startTime = {1,2,3,4,6};
    endTime = {3,5,10,6,9};
    profit = {20,20,100,70,60};

    cout << jobScheduling(startTime, endTime, profit) << endl;

    startTime = {1,1,1};
    endTime = {2,3,4};
    profit = {5,6,4};

    cout << jobScheduling(startTime, endTime, profit) << endl;

    return 0;
}