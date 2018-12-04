============================================================
Geração de código
============================================================

O objectivo desta aula é implementar um gerador de código intermédio para expressões aritméticas.
O input é uma estrutura Expr do primeiro trabalho prático, adaptado de forma a lidar só com expressões aritméticas ( a variável root será de tipo Expr)

============================================================
1. Baseado no primeiro trabalho crie um novo projeto para construir a árvore abstracta de expressões aritméticas sem variáveis.



============================================================
2.

a) Defina ficheiros stack.h e stack.c para implementar uma estrutura (struct Instr) e respectivos construtores de uma máquina de stack com as seguintes instruções: LDC Num, ADI, MPI e SBI (para push de um inteiro, adição, multiplicação e subtração).

b) Defina uma estrutura para listas de instruções (lista de apontadores para structs Instr), respectivos construtores e funções de acesso head e tail e uma função append para concatenação de listas.

c) Defina uma função printInstr para imprimir uma instrução.

d) Defina uma função printListIntrs para imprimir uma lista de instruções.



============================================================
3. Defina em C um compilador da árvore abstracta para expressões (struct Expr) para uma lista de instruções (lista de struct Instr).

============================================================
4. Defina em C uma função printMIPS que imprime num ficheiro o código MIPS correspondente à lista de instruções gerada pelo compilador.

LDC n ->estrutura

de ldc n para o q esta em baixo é print para um ficheiro depois executamos o ficheiro em mars
li t0 n
subu $sp,$sp,4
sw $t0,($sp)


============================================================

5. Repita as perguntas 2. e 3. mas para um código intermédio de três endereços (a estrutura neste caso tem quatro campos relativos à instrução e aos três endereços do género t1 = a1 op a2).
