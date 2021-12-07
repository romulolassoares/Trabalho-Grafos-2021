# Trabalho de Grafos

![GitHub repo size](https://img.shields.io/github/repo-size/romulolassoares/Trabalho-Grafos?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/romulolassoares/Trabalho-Grafos?style=for-the-badge)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)


## 💻 Sobre o projeto

Tem o foco em representar grafos simples, orientados e não orientados, podenrados nos vértices e arestas e implemtar uma serie de funcionalidades detalhadas em sala de aula.  ([Funcionalidades](#funcionalidades)) 

Todas as atividades de implementação cobradas ao longo do curso da disciplina DCC059 - Teoria dos Grafos no semestre letivo 2021-3.

### Funcionalidades

- [x] Subgrafo vértice-induzido pelo fecho transitivo direto.
- [x] Subgrafo vértice-induzido pelo fecho transitivo indireto.
- [ ] Caminho mínimo entre dois vertices - Djkstra
- [ ] Caminho mínimo entre dois vertices - Floyd
- [ ] Árvore geradora mínima - Prim
- [ ] Árvore Geradora Mínima - Kruskal
- [x] Caminhamento em largura

## ☕ Executando o código

Para executar, siga estas etapas:

```console
g++ *.c* -o execGrupoX

./execGrupoX <arquivo-de-entrada> <arquivo-de-saida> <op-direc> <op-peso-aresta> <op-peso-no>
```

* arquivo-de-entrada: arquivo que possuira as informações para a montagem do grafo.
* arquivo-de-saida: arquivo onde será gravado o grafo armazenado na memória ao término da execução.
* op-direc: 0 não é direcionado - 1 é direcionado
* op-peso-aresta: 0 não é ponderando nas arestas - 1 é ponderando nas arestas
* op-peso-no: 0 não é ponderado nos vértices - 1 é ponderado nos vértices

### Exemplo de um arquivo de entrada
```
5
1 2
2 5
5 3
4 5
1 5
```
## 🤝 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="#">
        <img src="https://github.com/romulolassoares.png" width="100px;" alt="Foto do Rômulo Soares no GitHub"/><br>
        <sub>
          <b>Rômulo Soares</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

[⬆ Voltar ao topo](#trabalho-de-grafos)<br>
