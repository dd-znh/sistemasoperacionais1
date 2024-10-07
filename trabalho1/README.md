# Trabalho de Sistemas Operacionais

Nomes: Eduardo Achar - 23102448

## Introdução:
Esse código implementa uma solução eficiente para o problema de agendamento de tarefas com lucro máximo, sem que haja sobreposição de tarefas (intervalos). A estratégia utilizada é combinar uma abordagem gulosa (ordenar os processos pelo tempo de término) com programação dinâmica e busca binária para otimizar a escolha das tarefas.

## Explicação detalhada do código:

### Entrada e armazenamento dos processos:

```
vector<tuple<int, int, int>> processos;
for (int i = 0; i < startTime.size(); i++) {
    processos.push_back({endTime[i], startTime[i], profit[i]});
}
```

Aqui, estamos construindo um vetor de tuplas, onde cada tupla representa um processo com três elementos:

Tempo de término (endTime[i]).
Tempo de início (startTime[i]).
Lucro (profit[i]).

A razão pela qual o tempo de término é armazenado primeiro é que queremos ordenar os processos por esse valor para facilitar o algoritmo.

### Ordenação dos processos:

```
sort(processos.begin(), processos.end());
```
O vetor de processos é ordenado com base no tempo de término (endTime), porque ao ordená-los dessa forma, podemos garantir que, ao processar cada tarefa, todas as tarefas anteriores terminam antes ou no mesmo instante, facilitando o cálculo das tarefas que podem ser selecionadas sem sobreposição.

### Vetor de lucro máximo:

```
vector<int> lucro(startTime.size());
```
Este vetor lucro[i] armazenará o lucro máximo que podemos obter até o i-ésimo processo. Inicialmente, ele é vazio, mas será preenchido conforme calculamos o lucro de cada tarefa.

### Lucro do primeiro processo:

```
lucro[0] = get<2>(processos[0]);
```
Para a primeira tarefa (o processo que termina mais cedo), o lucro máximo será o próprio lucro do processo. Isso é armazenado em lucro[0].

### Laço principal para calcular o lucro máximo:

```
for (int i = 1; i < processos.size(); i++) {
    int profit = get<2>(processos[i]);
```
A partir da segunda tarefa, o código tenta calcular o lucro máximo acumulado até essa tarefa. A cada iteração do loop:

profit captura o lucro atual do processo i.
### Busca binária para encontrar a tarefa mais recente não sobreposta:

```
int l = 0, r = i - 1;
while (l <= r) {
    int m = l + (r - l) / 2;
    if (get<0>(processos[m]) <= get<1>(processos[i])) {
        l = m + 1;
    } else {
        r = m - 1;
    }
}
```
A busca binária é usada para encontrar o processo mais recente (antes do processo i) que não tenha conflito com o início do processo atual i.

Objetivo: Encontrar o maior índice r tal que o tempo de término do processo r (isto é, get<0>(processos[r])) seja menor ou igual ao tempo de início do processo i (isto é, get<1>(processos[i])).

Se encontrarmos tal processo r, então podemos incluir o lucro desse processo no lucro do processo atual i.

### Atualizando o lucro máximo:

```
if (r >= 0) {
    profit += lucro[r];
}
lucro[i] = max(profit, lucro[i - 1]);
```
Se a busca binária encontrou um processo válido (r >= 0), então o lucro do processo i será o lucro do processo i mais o lucro do processo r (aquele que não tem sobreposição).

Finalmente, o código atualiza o valor de lucro[i] como o máximo entre:

Incluir o processo atual (o lucro do processo i mais o lucro do processo mais recente que não sobrepõe).
Não incluir o processo atual (o lucro máximo anterior, lucro[i - 1]).
### Retorno do lucro máximo final:
```
return lucro.back();
```
No final, o maior valor de lucro estará armazenado no último elemento de lucro (lucro.back()), que representa o lucro máximo acumulado considerando todos os processos.
