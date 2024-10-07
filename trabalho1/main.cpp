#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    
    // Vetor de processos
    vector<tuple<int, int, int>> processos;

    // Adiciona os processos no vetor
    for (int i = 0; i < startTime.size(); i++) {
        processos.push_back({endTime[i], startTime[i], profit[i]});
    }

    // Ordena os processos pelo tempo de término
    sort(processos.begin(), processos.end());

    // Vetor de lucro
    vector<int> lucro(startTime.size());

    // Calcula o lucro máximo
    lucro[0] = get<2>(processos[0]);
    for (int i = 1; i < processos.size(); i++) {
        int profit = get<2>(processos[i]);
        int l = 0, r = i - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (get<0>(processos[m]) <= get<1>(processos[i])) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (r >= 0) {
            profit += lucro[r];
        }
        lucro[i] = max(profit, lucro[i - 1]);
    }
    return lucro.back();
}