#include <iostream>
#include <cassert>
using namespace std;

typedef struct {
    int numeracao;
    float pesoEntrada;
    float pesoAtual;
    int idade;
} gado;

bool checarInt(string input) {
    if(input == "draven") {
        while(true) {
            cout << "draven ";
        }
    } else if(input.length() == 0) {
        return false;
    }
    for(int i = 0; input[i] != '\0'; i++) {
        if(!(isdigit(input[i]))) {
            return false;
        }
    }
    return true;
}

bool checarFloat(string input) {
    int qtdPontos = 0;
    if(input == "draven") {
        while(true) {
            cout << "draven ";
        }
    } else if(input.length() == 0) {
        return false;
    }
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] == '.') {
            qtdPontos++;
        }
        if((!(isdigit(input[i])) && input[i] != '.') || qtdPontos > 1) {
            return false;
        }
    }
    return true;
}

gado *gerarLote(int *tamLote) {
    string input;
    gado *rebanho;
    cout << "Bem vindo ao sistema KGado de gerenciamento de gado de corte!" << endl;
    cout << "Quantas cabeças de gado tem o lote?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 1) {
            cout << "Insira uma quantidade valida" << endl;
        }
    } while((!(checarInt(input)) || stoi(input) < 1));
    *tamLote = stoi(input);
    assert(*tamLote > 0);

    if(!(rebanho = new(nothrow) gado[*tamLote])) {
        cout << "Falha na alocacao de memoria" << endl;
        return 0;
    }
    assert(rebanho);
    cout << "Tamanho do lote: " << *tamLote << endl;
    return rebanho;
}

bool checarNumeracao(gado *rebanho, int num, int qtdRegistros) {
    for(int i = 0; i < qtdRegistros; i++) {
        if(rebanho[i].numeracao == num) {
            return false;
        }
    }
    return true;
}

void ordenarGado(gado *rebanho, int tamLote) {
    int chave;
    for(int i = 0; i < tamLote; i++) {
        chave = i;
        for(int j = i+1; j < tamLote; j++) {
            if((rebanho+j)->numeracao < (rebanho+chave)->numeracao) {
                chave = j;
            }
        }
        swap(*(rebanho+i), *(rebanho+chave));
    }
}

int encontrarNumeracao(gado *rebanho, int alvo, int inicio, int fim) {
    if(inicio > fim) {
        return -1;
    } else {
        int meio = (inicio+fim)/2;
        if((rebanho+meio)->numeracao == alvo) {
            return meio;
        } else if((rebanho+meio)->numeracao > alvo) {
            return encontrarNumeracao(rebanho, alvo, inicio, meio-1);
        } else {
            return encontrarNumeracao(rebanho, alvo, meio+1, fim);
        }
    }
}

void funcContinuar() {
    string input;
    cout << "Insira 1 para continuar" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) != 1) {
            cout << "Entrada invalida, insira 1 para continuar" << endl;
        }
    } while((!(checarInt(input)) || stoi(input) != 1));
    system("clear||cls");
}

void preencherLote(gado *rebanho, int tamLote) {
    string input;
    for(int i = 0; i < tamLote; i++) {
        cout << "Insira a numeracao para o " << i+1 << " animal do lote." << endl;
        do {
            getline(cin, input);
            if(!(checarInt(input)) || stoi(input) < 0) {
                cout << "Entrada invalida, digite uma numeracao valida" << endl;
            } else if(!(checarNumeracao(rebanho, stoi(input), i))) {
                cout << "Essa numeracao ja foi cadastrada, insira outra numeracao" << endl;
            }
        } while(!(checarInt(input)) || !(checarNumeracao(rebanho, stoi(input), i)) || stoi(input) < 0);
        (rebanho+i)->numeracao = stoi(input);
        
        cout << "Insira o peso de entrada em arrobas para o " << i+1 << " animal do lote." << endl;
        do {
            getline(cin, input);
            if(!(checarFloat(input)) || stof(input) <= 0) {
                cout << "Entrada invalida, digite um peso valido" << endl;
            }
        } while(!(checarFloat(input)) || stof(input) <= 0);
        (rebanho+i)->pesoAtual = stof(input);
        (rebanho+i)->pesoEntrada = stof(input);

        cout << "Insira a idade em dentes para o " << i+1 << " animal do lote." << endl;
        do {
            getline(cin, input);
            if(!(checarInt(input)) || stoi(input) < 0 || stoi(input) % 2 != 0 || stoi(input) > 8) {
                cout << "Entrada invalida, digite uma idade valida" << endl;
            }
        } while(!(checarInt(input)) || stoi(input) < 0 || stoi(input) % 2 != 0 || stoi(input) > 8);
        (rebanho+i)->idade = stoi(input);
    }
    ordenarGado(rebanho, tamLote);

    funcContinuar();
}

void alterarNumeracao(gado *rebanho, int tamLote) {
    string input;
    int posicaoNum;
    cout << "Qual a numeracao atual do animal que voce deseja alterar?" << endl;
    do {   
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1) {
            cout << "Essa numeracao nao foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1 || stoi(input) < 0);
    posicaoNum = encontrarNumeracao(rebanho, stoi(input), 0, tamLote);

    cout << "Qual a nova numeracao do animal?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) != -1) {
            cout << "Essa numeracao ja foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) != -1 || stoi(input) < 0);
    (rebanho+posicaoNum)->numeracao = stoi(input);
    ordenarGado(rebanho, tamLote);
    cout << "Numeracao alterada com sucesso!" << endl;

    funcContinuar();
}

void alterarPesoEntrada(gado *rebanho, int tamLote) {
    string input;
    int posicaoNum;
    cout << "Qual a numeracao do animal que voce deseja alterar o peso de entrada?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1) {
            cout << "Essa numeracao nao foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1 || stoi(input) < 0);
    posicaoNum = encontrarNumeracao(rebanho, stoi(input), 0, tamLote);
    
    cout << "Qual o novo peso de entrada em arrobas do animal?" << endl;
    do {
        getline(cin, input);
        if(!(checarFloat(input)) || stof(input) <= 0) {
            cout << "Entrada invalida, digite um peso valido" << endl;
        }
    } while(!(checarFloat(input)) || stof(input) <= 0);
    (rebanho+posicaoNum)->pesoEntrada = stof(input);
    cout << "Peso de entrada alterado com sucesso!" << endl;

    funcContinuar();
}

void alterarPesoAtual(gado *rebanho, int tamLote) {
    string input;
    int posicaoNum;
    cout << "Qual a numeracao do animal que voce deseja alterar o peso atual?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1) {
            cout << "Essa numeracao nao foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1 || stoi(input) < 0);
    posicaoNum = encontrarNumeracao(rebanho, stoi(input), 0, tamLote);
    
    cout << "Qual o novo peso atual em arrobas do animal?" << endl;
    do {
        getline(cin, input);
        if(!(checarFloat(input)) || stof(input) <= 0) {
            cout << "Entrada invalida, digite um peso valido" << endl;
        }
    } while(!(checarFloat(input)) || stof(input) <= 0);
    (rebanho+posicaoNum)->pesoAtual = stof(input);
    cout << "Peso atual alterado com sucesso!" << endl;

    funcContinuar();
}

void alterarIdade(gado *rebanho, int tamLote) {
    string input;
    int posicaoNum;
    cout << "Qual a numeracao do animal que voce deseja alterar a idade?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1) {
            cout << "Essa numeracao nao foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1 || stoi(input) < 0);
    posicaoNum = encontrarNumeracao(rebanho, stoi(input), 0, tamLote);
    
    cout << "Qual a nova idade em dentes do animal?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0 || stoi(input) % 2 != 0 || stoi(input) > 8) {
            cout << "Entrada invalida, digite uma idade valida" << endl;
        }
    } while(!(checarInt(input)) || stoi(input) < 0 || stoi(input) % 2 != 0 || stoi(input) > 8);
    (rebanho+posicaoNum)->idade = stoi(input);
    cout << "Idade alterada com sucesso!" << endl;

    funcContinuar();
}

void alterarAnimal(gado *rebanho, int tamLote) {
    string input;
    cout << "Qual informacao voce deseja alterar?" << endl;
    cout << "1: Alterar numeracao" << endl;
    cout << "2: Alterar peso de entrada" << endl;
    cout << "3: Alterar peso atual" << endl;
    cout << "4: Alterar idade" << endl;
    cout << "5: Voltar para o menu anterior" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 1 || stoi(input) > 5) {
            cout << "Entrada invalida, digite uma opcao valida" << endl;
        }
    } while(!(checarInt(input)) || stoi(input) < 1 || stoi(input) > 5);
    if(stoi(input) == 1) {
        system("clear||cls");
        alterarNumeracao(rebanho, tamLote);
    } else if(stoi(input) == 2) {
        system("clear||cls");
        alterarPesoEntrada(rebanho, tamLote);
    } else if(stoi(input) == 3) {
        system("clear||cls");
        alterarPesoAtual(rebanho, tamLote);
    } else if(stoi(input) == 4) {
        system("clear||cls");
        alterarIdade(rebanho, tamLote);
    } else if(stoi(input) == 5) {
        system("clear||cls");
        return;
    }
}

void atualizarPesoLote(gado *rebanho, int tamLote) {
    string input;
    for(int i = 0; i < tamLote; i++) {
        cout << "Qual o peso atual em arrobas atualizado do " << i+1 << " animal do lote, de numeracao " << (rebanho+i)->numeracao << "?" << endl;
        do {
            getline(cin, input);
            if(!(checarFloat(input)) || stof(input) <= 0) {
                cout << "Entrada invalida, digite um peso valido" << endl;
            }
        } while(!(checarFloat(input)) || stof(input) <= 0);
        (rebanho+i)->pesoAtual = stof(input);
    }
    cout << "Peso atual do lote atualizado com sucesso!" << endl;

    funcContinuar();
}

void informacoesBoi(gado *rebanho, int tamLote) {
    string input;
    int posicaoNum, tempoFazenda;
    cout << "Qual a numeracao do animal que voce deseja visualizar as informacoes?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Entrada invalida, digite uma numeracao valida" << endl;
        } else if(encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1) {
            cout << "Essa numeracao nao foi cadastrada, insira outra numeracao" << endl;
        }
    } while(!(checarInt(input)) || encontrarNumeracao(rebanho, stoi(input), 0, tamLote) == -1 || stoi(input) < 0);
    posicaoNum = encontrarNumeracao(rebanho, stoi(input), 0, tamLote);

    cout << "Quantos dias o animal já passou na fazenda?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Digite uma quantidade de dias valida" << endl;
        }
    } while(!(checarInt(input)) || stoi(input) < 0);
    tempoFazenda = stoi(input);

    cout << "Numeracao: " << (rebanho+posicaoNum)->numeracao << endl;
    cout << "Idade: " << (rebanho+posicaoNum)->idade << " dentes" << endl;
    cout << "Peso de entrada: " << (rebanho+posicaoNum)->pesoEntrada << " arrobas" << endl;
    cout << "Peso atual: " << (rebanho+posicaoNum)->pesoAtual << " arrobas" << endl;
    if(tempoFazenda == 0) {
        cout << "Não foi possível calcular o ganho medio diario (GMD)" << endl;
    } else {
        assert(tempoFazenda > 0);
        cout << "Ganho medio diario (GMD): " << (((rebanho+posicaoNum)->pesoAtual - (rebanho+posicaoNum)->pesoEntrada) / tempoFazenda) * 15 << " kgs" << endl;
    }

    funcContinuar();
}

void informacoesLote(gado *rebanho, int tamLote) {
    string input;
    int tempoFazenda;
    cout << "Quantos dias a boiada já passou na fazenda?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Digite uma quantidade de dias valida" << endl;
        }
    } while(!(checarInt(input)) || stoi(input) < 0);
    tempoFazenda = stoi(input);

    for(int i = 0; i < tamLote; i++) {
        cout << "Numeracao: " << (rebanho+i)->numeracao << endl;
        cout << "Idade: " << (rebanho+i)->idade << " dentes" << endl;
        cout << "Peso de entrada: " << (rebanho+i)->pesoEntrada << " arrobas" << endl;
        cout << "Peso atual: " << (rebanho+i)->pesoAtual << " arrobas" << endl;
        if(tempoFazenda == 0) {
            cout << "Não foi possível calcular o ganho medio diario (GMD)" << endl;
        } else {
            assert(tempoFazenda > 0);
            cout << "Ganho medio diario (GMD): " << (((rebanho+i)->pesoAtual - (rebanho+i)->pesoEntrada) / tempoFazenda) * 15 << " kgs" << endl;
        }
        cout << endl;
    }

    funcContinuar();
}

void venderLote(gado *rebanho, int tamLote) {
    string input;
    float porcentagemPesoVivo, pesoAtualTotal = 0, pesoAtualMedio, pesoEntradaTotal = 0, pesoEntradaMedio, ganhoMedioDiario, valorArroba, valorLote;
    int tempoFazenda;
    cout << "Qual a porcentagem do peso vivo que o frigorifico pagou? (normalmente 50-55%)" << endl;
    do {
        getline(cin, input);
        if(!(checarFloat(input)) || stof(input) < 0 || stof(input) > 100) {
            cout << "Entrada invalida, digite uma porcentagem valida" << endl;
        }
    } while(!(checarFloat(input)) || stof(input) < 0 || stof(input) > 100);
    porcentagemPesoVivo = stof(input) / 100;

    cout << "Quantos reais o frigorifico pagou por arroba?" << endl;
    do {
        getline(cin, input);
        if(!(checarFloat(input)) || stof(input) < 0) {
            cout << "Entrada invalida, digite um valor valido" << endl;
        }
    } while(!(checarFloat(input)) || stof(input) < 0);
    valorArroba = stof(input);

    cout << "Quantos dias a boiada passou na fazenda?" << endl;
    do {
        getline(cin, input);
        if(!(checarInt(input)) || stoi(input) < 0) {
            cout << "Digite uma quantidade de dias valida" << endl;
        }
    } while(!(checarInt(input)) || stoi(input) < 0);
    tempoFazenda = stoi(input);

    for(int i = 0; i < tamLote; i++) {
        pesoAtualTotal += (rebanho+i)->pesoAtual;
        pesoEntradaTotal += (rebanho+i)->pesoEntrada;
    }
    pesoAtualMedio = pesoAtualTotal / tamLote;
    pesoEntradaMedio = pesoEntradaTotal / tamLote;
    ganhoMedioDiario = ((pesoAtualMedio - pesoEntradaMedio) / tempoFazenda) * 15;
    valorLote = (pesoAtualTotal * porcentagemPesoVivo) * valorArroba;
    
    if(tempoFazenda == 0) {
        cout << "Não houve ganho medio diario (GMD)" << endl;
    } else {
        assert(tempoFazenda > 0);
        cout << "O ganho medio diario (GMD) da boiada foi de: " << ganhoMedioDiario << " kgs" << endl;
    }
    cout << "O valor pago pelo lote foi de: " << valorLote << " reais" << endl;

    funcContinuar();
}

void limparMemoria(gado *rebanho) {
    delete[] rebanho;
    rebanho = nullptr;
}

void sistema(gado *rebanho, int tamLote) {
    bool rodarSistema = true;
    while(rodarSistema) {
        string input;
        cout << "Sistema KGado de gerenciamento de gado de corte" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Selecione uma opcao: " << endl;
        cout << "1: Fazer uma alteracao em um animal" << endl;
        cout << "2: Atualizar peso do lote" << endl;
        cout << "3: Visualizar informacoes de um animal do lote" << endl;
        cout << "4: Visualizar informacoes de todo o lote" << endl;
        cout << "5: Vender lote" << endl;
        cout << "6: Encerrar o sistema" << endl;
        do {
            getline(cin, input);
            if(!(checarInt(input)) || stoi(input) < 1 || stoi(input) > 6) {
                cout << "Entrada invalida, digite uma opcao valida" << endl;
            }
        } while(!(checarInt(input)) || stoi(input) < 1 || stoi(input) > 6);
        if(stoi(input) == 1) {
            system("clear||cls");
            alterarAnimal(rebanho, tamLote);
        } else if(stoi(input) == 2) {
            system("clear||cls");
            atualizarPesoLote(rebanho, tamLote);
        } else if(stoi(input) == 3) {
            system("clear||cls");
            informacoesBoi(rebanho, tamLote);
        } else if(stoi(input) == 4) {
            system("clear||cls");
            informacoesLote(rebanho, tamLote);
        } else if(stoi(input) == 5) {
            system("clear||cls");
            venderLote(rebanho, tamLote);
            rodarSistema = false;
        } else if(stoi(input) == 6) {
            system("clear||cls");
            rodarSistema = false;
        }
    }
}

int main() {
    int tamLote;
    gado *rebanho;
    rebanho = gerarLote(&tamLote);
    preencherLote(rebanho, tamLote);
    sistema(rebanho, tamLote);
    limparMemoria(rebanho);
    cout << "Obrigado por usar o sistema KGado de gerenciamento de gado de corte!" << endl;
}