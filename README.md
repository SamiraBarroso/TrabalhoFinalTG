### Universidade Federal de Juiz de Fora
### Departamento de Ciência da Computação
### Disciplina DCC059 – Teoria dos Grafos - 2021-1
Alunas:</br>
 Andressa Augusta Ferrugini de Oliveira </br>
 Samira Barroso dos Santos

### Árvore Geradora Mínima Generalizada
Para executar esse repositório, abra seu terminal na pasta raíz do projeto e execute o comando para compilar o código:

```
g++ *.cpp -o NOME_DO_EXECUTAVEL
```
Em seguida, após a compilção, use o comando para execução do programa:
```
./NOME_DO_EXECUTAVEL <arquivo_entrada> <arquivo_saida> 0 1 0
```

Onde:
* Nome do arquivo executável do programa
* O caminho do arquivo contendo a instância do problema
* O caminho do arquivo onde será impresso o resultado das funções
* Se o grafo é direcionado
  * 0 para não direcionado
  * 1 para grafo direcionado
* Se o grafo é ponderado nas arestas
  * 0 para não ponderado
  * 1 para ponderado
* Se o grafo é ponderado nos vértices
  - 0 para não ponderado
  - 1 para ponderado

Na pasta raiz do projeto existe uma pasta chamada _instancias_ que possui as instancias utilizadas neste trabalho.

Ao ser executado, o programa lerá os dados do arquivo de entrada e criará o grafo. Aparecerá um menu para selecionar a opção desejada: 

>  MENU
> ------
>
> [1] Fecho Transitivo Direto </br>
> [2] Fecho Transitivo Indireto</br>
> [3] Caminho Minimo entre dois vertices - Dijkstra</br>
> [4] Caminho Minimo entre dois vertices - Floyd</br>
> [5] AGM sobre subgrafo vertice induzido por X usando algoritmo de Prim</br>
> [6] AGM sobre subgrafo vertice induzido por X usando algoritmo de Kruskal</br>
> [7] Caminhamento Profundidade destacando as Arestas de retorno</br>
> [8] Ordenacao topologica </br>
> [9] Subgrafo induzido por um conjunto de vertices X</br>
> [10] Imprime Grafo</br>
> ### [11] Algoritmo Guloso</br>
> ### [12] Algoritmo Guloso Randomizado</br>
> ### [13] Algoritmo Guloso Randomizado Reativo</br>
> [0] Sair</br>

Ao escolher entre as opções e após a execução, aperte [0] para sair do programa e os resultados serem salvos no arquivo de saída passado como parâmetro. 

Os alfas para os algortimos são os mesmos: {0.05, 0.1, 0.15, 0.30, 0.5}.

Para o Algoritmo Guloso Randomizado, o programa perguntará qual alfa desejará usar e quantas iterações desejará fazer.

Já para o Algoritmo Guloso Randomizado Reativo, o programa perguntará quantas iterações e o tamanho do bloco para atualizar a probabilidade dos alfas a cada k iterações.