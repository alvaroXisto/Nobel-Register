/*Trabalho de Introdução aos Algoritmos - 2024/1 
Tema: Ganhadores do Prêmio Nobel.
Integrantes: Adrielly Ferreira da Silva (202410420)
Álvaro de Souza Xisto (202410858)
Marina Barbosa Valim (202410197)*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cstring>
using namespace std;

struct nobel
{
    short id;
    char nome[50];
    char categoria[20];
    short anoPremiacao;
    char paisOrigem[30];
    char formacao[50];
};

// Função de particionamento do id para ordenação.
int particionaID(nobel *vet, int inicio, int fim)
{

    int pivo = vet[inicio].id;
    int i = inicio + 1;
    int j = fim;

    while (i <= j)
    {
        while (i <= j and vet[i].id <= pivo)
            i++;
        while (i <= j and vet[j].id >= pivo)
            j--;
        if (i < j)
        {
            swap(vet[i], vet[j]);
        }
    }
    swap(vet[inicio], vet[j]);
    return j;
}

//Função para ordenar o vetor por ID.
void quicksortID(nobel *vet, int inicio, int fim)
{
    while (vet[fim].id == -1)
    {
        fim--;
    }
    if (inicio < fim)
    {
        int pos_pivo = particionaID(vet, inicio, fim);
        quicksortID(vet, inicio, pos_pivo - 1);
        quicksortID(vet, pos_pivo + 1, fim);
    }
}

// Função de particionamento do nome para ordenação
int particionaNome(nobel *vetor, int inicio, int fim)
{
    nobel pivo = vetor[fim];
    int j = inicio;
    for (int i = inicio; i < fim; i++)
    {
        if (strcmp(vetor[i].nome, pivo.nome) <= 0)
        {
            swap(vetor[j], vetor[i]);
            j++;
        }
    }
    swap(vetor[j], vetor[fim]);
    return j;
}

//Função para ordenar o vetor por nome.
void quicksortNome(nobel *vet, int inicio, int fim)
{
    if (inicio < fim)
    {
        int pos_pivo = particionaNome(vet, inicio, fim);
        quicksortNome(vet, inicio, pos_pivo - 1);
        quicksortNome(vet, pos_pivo + 1, fim);
    }
}

//Função para redmensionar o vetor.
nobel *redimensionaVetor(nobel *vet, int &capacidade, int incremento)
{
    capacidade += incremento;
    nobel *novo = new nobel[capacidade];

    copy(vet, vet + (capacidade - incremento), novo);

    delete[] vet;
    return novo;
}

//Função para ler o arquivo binário
nobel *leituraTipado(int &tamanho)
{
    int capacidade = 40;
    nobel *vet = new nobel[capacidade];
    int i = 0;

    ifstream arqE("entrada1.bin", ios::binary);

    while (arqE.read(reinterpret_cast<char *>(&vet[i]), sizeof(nobel)))
    {
        i++;

        if (i == capacidade)
        {
            vet = redimensionaVetor(vet, capacidade, 10); 
        }
    }

    while (i < capacidade)
    {
        vet[i].id = -1;
        i++;
    }

    tamanho = i;
    return vet;
}

//Função para ler o arquivo CSV.
nobel *leituraArquivoCSV(ifstream &entrada, int &tamanho)
{
    int capacidade = 40;
    nobel *vet = new nobel[capacidade];
    char lixo;

    int i = 0;

    while (entrada >> vet[i].id)
    {
        entrada >> lixo;
        entrada.getline(vet[i].nome, 50, ';');
        entrada.getline(vet[i].categoria, 20, ';');
        entrada >> vet[i].anoPremiacao;
        entrada >> lixo;
        entrada.getline(vet[i].paisOrigem, 30, ';');
        entrada.getline(vet[i].formacao, 50, ';');
        entrada.ignore();
        i++;

        if (i == capacidade)
        {
            vet = redimensionaVetor(vet, capacidade, 10); 
        }
    }
    while (i < capacidade)
    {
        vet[i].id = -1;
        i++;
    }

    tamanho = i; 
    return vet;
}

//Função para fazer a busca binária recursiva do nome.
int buscaBinNome(nobel vet[], char busca[50], int inicio, int fim)
{
    system("cls||clear");
    if (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        int resultadoComparacao = strcmp(vet[meio].nome, busca);

        if (resultadoComparacao == 0)
        {
            return meio; 
        }
        else if (resultadoComparacao > 0)
        {
            return buscaBinNome(vet, busca, inicio, meio - 1);
        }
        else
        {
            return buscaBinNome(vet, busca, meio + 1, fim);
        }
    }
    else
    {
        return -1; 
    }
}

//Função para fazer a busca binária recursiva do ID.
int buscaBinID(nobel vet[], short busca, int inicio, int fim)
{
    if (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        if (vet[meio].id == busca)
        {
            return meio;
        }
        else if (vet[meio].id > busca)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
        return buscaBinID(vet, busca, inicio, fim);
    }
    else
    {
        return -1;
    }
}

//Função para imprimir apenas um trecho do vetor.
void mostrarTrecho(nobel *vet, int tamanho)
{

    system("cls||clear");

    int posInicio, posFim;
    cout << "Digite a posicao inical do trecho no qual deseja imprimir: ";
    cin >> posInicio;

    cout << endl;

    cout << "Digite a posicao final do trecho no qual deseja imprimir: ";
    cin >> posFim;
    cout << endl;

    system("cls||clear");
    if ((posInicio < tamanho and posInicio > 0) and (posFim < tamanho and posFim > 0))
    {
        for (int i = posInicio; i <= posFim; i++)
        {
            if (vet[i].id != -1)
            {
                cout << "-------------------------------------------------------" << endl
                     << "ID:" << vet[i].id << endl
                     << "Nome: " << vet[i].nome << endl
                     << "Categoria: " << vet[i].categoria << endl
                     << "Ano Premiacao: " << vet[i].anoPremiacao << endl
                     << "Pais de Origem: " << vet[i].paisOrigem << endl
                     << "Formacao: " << vet[i].formacao << endl
                     << "-------------------------------------------------------" << endl;
            }
        }
    }
    else
    {

        cout << "Trecho invalido." << endl;
    }
}

//Função para chamar a busca binária do nome.
void buscarNome(nobel vet[], int tamanho)
{
    system("cls||clear");
    char nomeProcurado[50];
    quicksortNome(vet, 0, tamanho - 1);

    cout << "Digite o nome a ser procurado: " << endl;
    cin.ignore();
    cin.getline(nomeProcurado, 50);

    int nomeEncontrado = buscaBinNome(vet, nomeProcurado, 0, tamanho - 1);
    // cout<<"Resultado busca: "<<nomeEncontrado<<endl;
    if (nomeEncontrado != -1 and vet[nomeEncontrado].id != -1)
    {
        system("cls||clear");
        cout << "Ganhador encontrado:" << endl
             << endl
             << "ID:" << vet[nomeEncontrado].id << endl
             << "Nome: " << vet[nomeEncontrado].nome << endl
             << "Categoria: " << vet[nomeEncontrado].categoria << endl
             << "Ano Premiacao: " << vet[nomeEncontrado].anoPremiacao << endl
             << "Pais de Origem: " << vet[nomeEncontrado].paisOrigem << endl
             << "Formacao: " << vet[nomeEncontrado].formacao << endl;
    }
    else
    {
        system("cls||clear");
        cout << endl
             << "Nome nao encontrado!" << endl;
    }
}

//Função para chamar a busca binária do ID.
void buscarID(nobel vet[], int tamanho)
{
    system("cls||clear");
    short idProcurado;

    quicksortID(vet, 0, tamanho - 1);

    cout << "Digite o ID a ser procurado: " << endl;
    cin >> idProcurado;
    cin.ignore();

    int idEncontrado = buscaBinID(vet, idProcurado, 0, tamanho - 1);
    if (idEncontrado != -1)
    {
        system("cls||clear");
        cout << "Ganhador encontrado: " << endl
             << endl
             << "ID:" << vet[idEncontrado].id << endl
             << "Nome: " << vet[idEncontrado].nome << endl
             << "Categoria: " << vet[idEncontrado].categoria << endl
             << "Ano Premiacao: " << vet[idEncontrado].anoPremiacao << endl
             << "Pais de Origem: " << vet[idEncontrado].paisOrigem << endl
             << "Formacao: " << vet[idEncontrado].formacao << endl;
    }
    else
    {

        cout << endl
             << "ID nao encontrado!" << endl;
    }
}

//Função para imprimir o vetor inteiro.
void imprimeVetor(nobel *vet, int tamanho)
{
    system("cls||clear");

    int i = 0;

    while (i < tamanho)
    {
        if (vet[i].id != -1)
        {
            cout << "ID:" << vet[i].id << endl
                 << "Nome: " << vet[i].nome << endl
                 << "Categoria: " << vet[i].categoria << endl
                 << "Ano Premiacao: " << vet[i].anoPremiacao << endl
                 << "Pais de Origem: " << vet[i].paisOrigem << endl
                 << "Formacao: " << vet[i].formacao << endl
                 << "-------------------------------------------------------" << endl;
        }
        i++;
    }
}

//Função para adicionar item no vetor.
void adicionaItem(nobel *vet, int &tamanho)
{
    system("cls||clear");
    string resposta;

    cout << "Deseja adicionar um novo ganhador? Responda Sim ou Nao" << endl;
    cin >> resposta;
    cin.ignore();

    bool inseriu = false;

    if (resposta == "Sim")
    {
        nobel ganhadorNovo;

        while (!inseriu)
        {
            system("cls||clear");
            
            cout << "Insira um novo ID:" << endl;
            cin >> ganhadorNovo.id;
            cin.ignore();
            cout << endl;
            
            int j = 0;
            while (j < tamanho)
            {
                if (vet[j].id == ganhadorNovo.id)
                {
                    system("cls||clear");
                    cout << endl
                         << "ID ja cadastrado." << endl;
                    return;
                }
                j++;
            }

            cout << "Insira um novo Nome:" << endl;
            cin.getline(ganhadorNovo.nome, 50);
            cout << endl;

            j = 0;
            while (j < tamanho )
            {
                if (strcmp(vet[j].nome, ganhadorNovo.nome) == 0)
                {
                    system("cls||clear");
                    cout << endl
                         << "Nome ja cadastrado." << endl;
                    
                    return;
                }
                j++;
            }

            cout << "Insira uma nova Categoria:" << endl;
            cin.getline(ganhadorNovo.categoria, 20);
            cout << endl;

            cout << "Insira um novo Ano de Premiacao:" << endl;
            cin >> ganhadorNovo.anoPremiacao;
            cin.ignore();
            cout << endl;

            cout << "Insira um novo Pais de Origem:" << endl;
            cin.getline(ganhadorNovo.paisOrigem, 30);
            cout << endl;

            cout << "Insira uma nova Formacao: " << endl;
            cin.getline(ganhadorNovo.formacao, 50);

            system("cls||clear");
            cout << endl
                 << "Ganhador inserido com sucesso!" << endl;

            inseriu = true;
        }

        int i = tamanho - 10;
        bool posicaoEncontrada = false;

        while (i < tamanho && !posicaoEncontrada)
        {
            if (vet[i].id == -1)
            {
                vet[i] = ganhadorNovo;
                posicaoEncontrada = true;
            }
            i++;
        }

        if (!posicaoEncontrada)
        {
            redimensionaVetor(vet, tamanho, 10);
            vet[tamanho - 10] = ganhadorNovo;
        }
    }
}

//Função para editar um dado já cadastrado.
void editar(nobel vetor[], int tamanho)
{
    system("cls||clear");
    short id;

    cout << "Digite o id do ganhador que deseja editar:" << endl;
    cin >> id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    quicksortID(vetor, 0, tamanho - 1);

    int busca = buscaBinID(vetor, id, 0, tamanho - 1);

    if (busca != -1)
    {
        system("cls||clear");
        cout << "O identificador foi encontrado. Confira os dados:" << endl;

        cout << endl;

        cout << "ID:" << vetor[busca].id << endl
             << "Nome: " << vetor[busca].nome << endl
             << "Categoria: " << vetor[busca].categoria << endl
             << "Ano Premiacao: " << vetor[busca].anoPremiacao << endl
             << "Pais de Origem: " << vetor[busca].paisOrigem << endl
             << "Formacao: " << vetor[busca].formacao << endl;

        cout << endl
             << "Realmente deseja remover este ganhador? Digite S para SIM e N para NAO." << endl;
        char resposta;
        cin >> resposta;

        if (resposta == 'S' or resposta == 's')
        {

            system("cls||clear");
            cout << "Por favor, insira os novos dados:" << endl;
            cout << endl;
            cout << "Digite o novo nome: ";
            cin.getline(vetor[busca].nome, 50);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cout << endl;

            cout << "Digite a nova categoria: ";
            cin.getline(vetor[busca].categoria, 20);
            
            cout << endl;

            cout << "Digite o novo ano de premiacao: ";
            cin >> vetor[busca].anoPremiacao;
            
            cout << endl;

            cout << "Digite o novo pais de origem: ";
            cin.getline(vetor[busca].paisOrigem, 30);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Digite a nova formacao: ";
            cin.getline(vetor[busca].formacao, 50);
            
        }

        cout << "Dados atualizados com sucesso!" << endl;
    }
    else
    {
        cout << "Id nao encontrado!" << endl;
    }
}

//Função para remover um elemento do vetor.
void remover(nobel *vetor, int &tamanho)
{

    system("cls||clear");

    short id;

    cout << "Digite o ID do ganhador que deseja remover:";
    cin >> id;

    quicksortID(vetor, 0, tamanho - 1);

    short procuraID = buscaBinID(vetor, id, 0, tamanho - 1);

    system("cls||clear");
    if (procuraID != -1)
    {
        cout << "Id encontrado. Dados do ganhador:" << endl
             << endl
             << "ID:" << vetor[procuraID].id << endl
             << "Nome: " << vetor[procuraID].nome << endl
             << "Categoria: " << vetor[procuraID].categoria << endl
             << "Ano Premiacao: " << vetor[procuraID].anoPremiacao << endl
             << "Pais de Origem: " << vetor[procuraID].paisOrigem << endl
             << "Formacao: " << vetor[procuraID].formacao << endl
             << endl
             << "Realmente deseja remover este ganhador? Digite S para SIM e N para NAO." << endl;

        char certeza;
        cin >> certeza;

        if (certeza == 'S' or certeza == 's')
        {
            cout << endl;
            cout << "O ganhador " << vetor[procuraID].nome << " foi removido com sucesso." << endl;
            for (int j = procuraID; j < tamanho - 1; j++)
            {
                vetor[j] = vetor[j + 1];
            }

            // decrementa o tamanho do vetor
            tamanho--;
        }
    }

    else
    {
        cout << "ID nao encontrado!" << endl;
    }
}

//Função para gravar informações no arquivo binário.
void gravarTipado(nobel *vetor, int tamanho, string arqE)
{

    ofstream saida(arqE, ios::binary);

    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i].id != -1)
        {
            saida.write(reinterpret_cast<char *>(&vetor[i]), sizeof(nobel));
        }
    }
}

//Função para gravar as informações no arquivo CSV.
void gravarCSV(nobel *vetor, int tamanho, string arqE)
{

    ofstream saida(arqE);

    if (!saida)
    {

        cout << " Nao foi possivel criar o arquivo." << endl;
        return;
    }
    else
    {
        saida << "id;nome;categoria;anoPremiacao;paisOrigem;formacao;" << endl;

        for (int i = 0; i < tamanho; i++)
        {
            if (vetor[i].id != -1)
            {
                saida << vetor[i].id << ';'
                      << vetor[i].nome << ';'
                      << vetor[i].categoria << ';'
                      << vetor[i].anoPremiacao << ';'
                      << vetor[i].paisOrigem << ';'
                      << vetor[i].formacao << ';' << "\n";
            }
        }
        system("cls||clear");
        cout << "Dados gravados com sucesso!" << endl;
        saida.close();
    }
}

//Função para imprimir o menu.
void menu()
{

    cout << "ESCOLHA UMA OPCAO:" << endl;
    cout << "----------------------------------" << endl;
    cout << "|  1 - Exibir a tabela           |" << endl
         << "|  2 - Buscar ganhador por ID    |" << endl
         << "|  3 - Buscar Ganhador por Nome  |" << endl
         << "|  4 - Imprimir trecho           |" << endl
         << "|  5 - Inserir ganhador          |" << endl
         << "|  6 - Remover ganhador          |" << endl
         << "|  7 - Alterar ganhador          |" << endl
         << "|  8 - Salvar dados no arquivo   |" << endl
         << "|  0 - Encerrar programa         |" << endl
         << "----------------------------------" << endl;
}

//Função para decidir em qual tipo de arquivo gravar os dados.
void gravarTipo(nobel *vetor, int tamanho)
{
    string extensao;
    cout << "Deseja salvar o arquivo em formato CSV ou binario? Digite csv ou bin." << endl;
    cin >> extensao;

    if (extensao == "csv")
    {
        gravarCSV(vetor, tamanho, "entrada1.csv");
        cout << "Salvo em csv!" << endl;
    }
    else if (extensao == "bin")
    {
        gravarTipado(vetor, tamanho, "entrada1.bin");
        cout << "Salvo em binario!" << endl;
    }
    else
    {
        cout << "Opcao Invalida" << endl;
    }
}

//Função principal
int main()
{
    int tamanho = 0;
    nobel *ganhadores;
    int operacao;

    string tipo;

    cout << "Como deseja ler o arquivo? Digite csv ou bin." << endl;

    cin >> tipo;

    if (tipo == "csv" or tipo == "bin")
    {

        if (tipo == "csv")
        {
            system("cls||clear");
            ifstream entrada("entrada1.csv");
            if (!entrada)
            {
                cout << "Erro ao abrir o arquivo!" << endl;
            }
            else
            {
                string linha = "";
                getline(entrada, linha);
                ganhadores = leituraArquivoCSV(entrada, tamanho);
            }
        }
        else if (tipo == "bin")
        {
            system("cls||clear");
            ganhadores = leituraTipado(tamanho);
        }

        do
        {
            
            cout << endl;
            menu();
            cin >> operacao;

            switch (operacao)
            {
            case 1:
                imprimeVetor(ganhadores, tamanho);

                break;
            case 2:
                quicksortID(ganhadores, 0, tamanho - 1);
                buscarID(ganhadores, tamanho);
                break;
            case 3:
                quicksortID(ganhadores, 0, tamanho - 1);
                buscarNome(ganhadores, tamanho);
                break;
            case 4:
                mostrarTrecho(ganhadores, tamanho);
                break;
            case 5:
                adicionaItem(ganhadores, tamanho);
                break;
            case 6:
                remover(ganhadores, tamanho);
                break;
            case 7:
                editar(ganhadores, tamanho);
                break;
            case 8:
                gravarTipo(ganhadores, tamanho);
                break;
            case 0:
                break;
            default:
                system("cls||clear");
                cout << "Opcao invalida, tente novamente.";
                cout << endl;
            }
        } while (operacao != 0);
        cout << endl
             << "PROGRAMA ENCERRADO";
    }
    else
    {
        cout << endl;
        cout << "Opcao invalida. Reinicie o programa." << endl;
    }

    delete[] ganhadores;

    return 0;
}
