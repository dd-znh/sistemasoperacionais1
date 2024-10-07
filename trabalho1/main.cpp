#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    
    // Vetor de tarefas (processos)
    vector<tuple<int, int, int>> tarefas;

    // Adiciona as tarefas no vetor (tempo de fim, tempo de início, lucro)
    for (int i = 0; i < startTime.size(); i++) {
        tarefas.push_back({endTime[i], startTime[i], profit[i]});
    }

    // Ordena as tarefas pelo tempo de término
    sort(tarefas.begin(), tarefas.end());

    // Vetor que guarda o lucro máximo até cada tarefa
    vector<int> lucroMaximo(startTime.size());

    // O primeiro lucro é o lucro da primeira tarefa
    lucroMaximo[0] = get<2>(tarefas[0]);

    // Calcula o lucro máximo para cada tarefa
    for (int i = 1; i < tarefas.size(); i++) {
        // Lucro da tarefa atual
        int lucroAtual = get<2>(tarefas[i]);

        // Busca a última tarefa que não sobrepõe com a atual
        int l = 0, r = i - 1;

        // Busca binária para encontrar a última tarefa que termina antes da atual
        while (l <= r) {
            int meio = l + (r - l) / 2;
            if (get<0>(tarefas[meio]) <= get<1>(tarefas[i])) {
                l = meio + 1;
            } else {
                r = meio - 1;
            }
        }

        // Se encontrou uma tarefa compatível, soma o lucro dessa tarefa ao lucro atual
        if (r >= 0) {
            lucroAtual += lucroMaximo[r];
        }

        // Atualiza o lucro máximo até a tarefa atual
        lucroMaximo[i] = max(lucroAtual, lucroMaximo[i - 1]);
    }

    // Retorna o lucro máximo que pode ser obtido
    return lucroMaximo.back();
}
