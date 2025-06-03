# Atividade 03 - Compilação de código dentro de docker fedora

#### Aluno: Pedro Lucas Xavier da Fonseca

#### Data 02/06/2025

## 1. Objetivo

O exercício foi dividido em duas partes. A primeira parte teve como objetivo principal introduzir conceitos a cerca do **Dockerfile** e de como é possível, a partir desse arquivo, criar imagens personalizadas com configurações específicas para a execução de uma aplicação, projeto, etc. Após a criação da imagem personalizada, na segunda parte do exercício executamos um container a partir dessa imagem para compilar códigos em C, por meio dos quais pudemos compreender melhor a dinâmica envolvida na **implementação de tarefas**.

## 2. Passos Executados

### 2.1 Criando Dockerfile

O primeiro passo foi criar um diretório chamado `docker-c-pratice`. Nesse diretório criei o arquivo `Dockerfile` e colei o código disponibilizado no tutorial da primeira parte do exercício, adicionando na linha 8 o comando `dnf -y install gcc && \` para instalar previamente o compilador da gcc da linguagem C.

![Dockerfile](imgs/Captura%20de%20tela%20de%202025-06-01%2023-59-13.png)

### 2.2 Construindo a imagem personalizada a partir do Dockerfile

Na sequência naveguei até o diretório recém criado e executei o comando `docker build -t minha-imagem-fedora .` para criar uma nova imagem chamada `minha-imagem-fedora` a partir das instruções definidas no arquivo **`Dockerfile`**.

![Nova imagem](imgs/Captura%20de%20tela%20de%202025-06-02%2000-06-21.png)

### 2.3 Criando arquivos fork.c e thread.c

Novamente no diretório `docker-c-pratice` criei dois arquivos: `fork.c` e `thread.c`. Os códigos foram retirados do cápitulo 5 do livro texto da disciplina, que aborda o assunto **Implementação de tarefas**. O código a seguir demonstra uma das formas de se implementar tarefas no sistema operacional que é por meio de **processos**.

![fork.c](imgs/Captura%20de%20tela%20de%202025-06-02%2016-55-11.png)

O próximo código, semelhantemente, demonstra outra forma de se implementar tarefas que é por meio de **threads**.

> Várias **threads** podem ser executadas em um mesmo **processo**.

![thread.c](imgs/Captura%20de%20tela%20de%202025-06-02%2016-55-30.png)

### 2.4 Executando o Container com Mapeamento de Volume

Com a imagem e os arquivos necessários criados executei o comando `docker run -it --rm -v "$(PWD)":/app minha-imagem-fedora` para executar um container mapeando o diretório atual (pwd) para dentro do container, no diretório `/app`. O container foi inicializado executando o terminal `fish`. Executei o comando `ls` para verificar se os arquivos haviam sido mapeados corretamente.

![Executando container](imgs/Captura%20de%20tela%20de%202025-06-02%2017-07-30.png)

Abri um terminal externo e executei o comando `docker ps` para verificar a lista de containeres ativos e consegui ver o container que acabara de criar.

![Verificando containers ativos](imgs/Captura%20de%20tela%20de%202025-06-02%2017-08-10.png)

### 2.5 Compilando e executando códigos no container

Após executar o container e com o compilador C já instalado segui com a compilação e execução do primeiro código, `fork.c`. Esse código utiliza chamadas de sistema do Unix para criar um **processo filho** e executar um programa externo, o /bin/date. Na saída temos a data e hora do momento da execução (derivado do processo filho) e, após o processo filho encerrar, é exibida a mensagem "Tchau !".

![Compilando e executando fork.c](imgs/Captura%20de%20tela%20de%202025-06-02%2017-14-18.png)

Repeti o processo para o segundo arquivo `threads.c`. Esse código exemplifica o funcionamento de threads, uma das formas de se implementar tarefas no SO. O programa inicia apenas com a thread "main" e segue criando um array de novas threads. Cada thread vai executar a mesma função, exibindo na tela a mensagem "Hello World!", aguardando 5 segundos e depois exibem a mensagem "Bye bye World!" e encerram.

> Detalhe: uma thread não precisa aguardar a outra encerrar para executar sua ação. Diferente do que ocorre entre processos.

![Compilando e executando thread.c](imgs/Captura%20de%20tela%20de%202025-06-02%2017-17-18.png)

### 2.6 Encerrando o container

Por fim, executei o comando `exit` para encerrar o container e verifiquei se havia containeres ativos com o comando `docker ps` e não havia pois o container foi configurado para ser removido após a execução.

![Compilando e executando fork.c](imgs/Captura%20de%20tela%20de%202025-06-02%2017-18-18.png)

## 3. Conclusão

Nesse exercício pude aprofundar conhecimentos de Docker, em especial o uso do arquivo `Dockerfile` para a criação de imagens personalizadas bem como aprender a mapear volumes da máquina host para a máquina virtual (container). Pude também ver a dinâmica de funcionamento de **processos** e **threads** no SO, facilitando a assimilação do conteúdo teórico que havia lido no livro. 