#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    
    // Vetor de tarefas (processos)
    vector<tuple<int, int, int>> tarefas;

    // Adiciona as tarefas no vetor (tempo de início, tempo de fim, lucro)
    for (int i = 0; i < startTime.size(); i++) {
        tarefas.push_back({startTime[i], endTime[i], profit[i]});
    }

    // Ordena as tarefas pelo tempo de início
    sort(tarefas.begin(), tarefas.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<0>(a) < get<0>(b); // Ordena com base no primeiro elemento (tempo de início)
    });

    // Vetor que guarda o lucro máximo até cada tarefa
    vector<int> lucroMaximo(startTime.size());

    // O primeiro lucro é o lucro da primeira tarefa
    lucroMaximo[0] = get<2>(tarefas[0]);

    // Calcula o lucro máximo para cada tarefa
    for (int i = 1; i < tarefas.size(); i++) {

        // Lucro da tarefa atual
        int lucroAtual = get<2>(tarefas[i]);

        // Inicializa as extremidades para busca binária
        int l = 0, r = i - 1;

        // Busca binária para encontrar a última tarefa que não se sobrepõe com a tarefa atual
        while (l <= r) {
            int meio = l + (r - l) / 2;
            // Verifica se a tarefa no meio termina antes da tarefa atual começa
            if (get<1>(tarefas[meio]) <= get<0>(tarefas[i])) {
                l = meio + 1; // Move para a direita
            } else {
                r = meio - 1; // Move para a esquerda
            }
        }

        // Se encontrou uma tarefa compatível, soma o lucro dessa tarefa ao lucro atual
        if (r >= 0) {
            lucroAtual += lucroMaximo[r]; // Adiciona o lucro da última tarefa compatível
        }

        // Atualiza o lucro máximo até a tarefa atual
        lucroMaximo[i] = max(lucroAtual, lucroMaximo[i - 1]);
    }

    // Retorna o lucro máximo que pode ser obtido
    return lucroMaximo.back();
}
