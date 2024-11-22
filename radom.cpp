#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <thread> // Para usar std::this_thread::sleep_for
#include <chrono> // Para std::chrono::seconds

std::string generateRandomHex(int length) {
    const char hexChars[] = "0123456789abcdef";
    std::string randomHex;
    srand(time(0) + rand()); // Inicializa o gerador com uma semente variável
    for (int i = 0; i < length; ++i) {
        randomHex += hexChars[rand() % 16];
    }
    return randomHex;
}

void generateAndSaveRanges() {
    const std::string fixedPart = "17a1a736be4e";
    const std::string suffix = "000000";
    const std::string upperLimit = ":1fffffffffffffffff";
    const int randomLength = 12; // Número de caracteres hexadecimais aleatórios

    while (true) {
        // Gera a parte aleatória e monta o intervalo
        std::string randomPart = generateRandomHex(randomLength);
        std::string range = fixedPart + randomPart + suffix + upperLimit;

        // Exibe na saída padrão (console)
        std::cout << "Novo intervalo: " << range << std::endl;

        // Salva o intervalo em um arquivo
        std::ofstream outputFile("range.txt");
        if (outputFile.is_open()) {
            outputFile << range << std::endl;
            outputFile.close();
            std::cout << "Intervalo salvo em 'range.txt'!" << std::endl;
        } else {
            std::cerr << "Erro ao salvar o arquivo!" << std::endl;
        }

        // Aguarda 4 segundos antes de repetir
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
}

int main() {
    generateAndSaveRanges();
    return 0;
}
