#include "include/Desafio5.hpp"


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    
    std::string dictionaryFilePath = "data/portuguese-brazil.dic"; 
    std::string text = "Este eh um texo de exempllo para testar o progeto. O computador eh rapido mas o algorimo esta lento. Qual a linguagem de programacão correta?";
    
    Desafio5 desafio(dictionaryFilePath, text);
    
    try {
        desafio.run();
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1; 
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> totalDuration = end - start;
    std::cout << "Tempo total de execução: " << totalDuration.count() << " ms\n";

    std::cout << '\n';
    std::cout << "Sugestões: ";
    const std::vector<std::string> incorrectWords = {
        "exempllo", "progeto", "rapido", "algorimo", "programacão"
    };

    for (const auto& word : incorrectWords) {
        std::string suggestion = desafio.getWordSuggestion(word);
        if (!suggestion.empty()) {
            for (const auto& sug : desafio.getSuggestions(word, 1)) {
                std::cout << sug << " ";
            }
            std::cout << "(Sugestão para '" << word << "': " << suggestion << ")\n";
        } else {
            std::cout << "Nenhuma sugestão encontrada para: " << word << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return 0;
}