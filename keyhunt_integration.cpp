#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring> // Para a função isxdigit()

using namespace std;

// Função para gerar uma string hexadecimal aleatória
string generateRandomHexString(size_t length) {
    const string chars = "0123456789abcdef";  // Caracteres hexadecimais
    string result;
    result.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        result += chars[rand() % chars.size()];
    }
    
    return result;
}

// Função auxiliar para verificar se uma string é um hex válido
bool isValidHex(const string &str) {
    for (char const &c : str) {
        if (!isxdigit(c)) {
            return false;
        }
    }
    return true;
}

// Função para simular a lógica de range dentro do keyhunt
void processRange(const string &range_start, const string &range_end) {
    // Verifica se os intervalos são hexadecimais válidos
    if (isValidHex(range_start) && isValidHex(range_end)) {
        // Gerar uma string hexadecimal aleatória de 12 caracteres
        string randomHex = generateRandomHexString(12);
        cout << "Generated Hex: " << randomHex << endl;

        // Verifica se a string gerada está dentro do intervalo
        if (randomHex >= range_start && randomHex <= range_end) {
            cout << "Generated string " << randomHex << " is within the range." << endl;
        } else {
            cout << "Generated string " << randomHex << " is outside the range." << endl;
        }
    } else {
        cerr << "[E] Invalid hexstring for range: " << range_start << " or " << range_end << endl;
    }
}

int main(int argc, char *argv[]) {
    // Inicializando o gerador de números aleatórios
    srand(time(0));

    // Definir intervalo de exemplo, por exemplo, de 64 caracteres hexadecimais
    string range_start = "0000000000000000000000000000000000000000000000000000000000000000"; // Exemplo de range start
    string range_end = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"; // Exemplo de range end

    // A lógica aqui segue a estrutura de `keyhunt`, verificando as entradas e chamando a função `processRange`
    // Exemplo para simular a passagem do intervalo 'r'
    if (argc > 1 && strcmp(argv[1], "-r") == 0) {
        if (argc == 4) {
            range_start = argv[2];  // range_start fornecido como argumento
            range_end = argv[3];    // range_end fornecido como argumento
        }
        processRange(range_start, range_end);  // Chama a função para processar o intervalo
    }

    // Espera de 4 segundos antes de gerar outra string e verificar novamente
    while (true) {
        processRange(range_start, range_end);  // Processa a verificação a cada 4 segundos
        this_thread::sleep_for(chrono::seconds(4));  // Pausa de 4 segundos antes de gerar outra
    }

    return 0;
}
