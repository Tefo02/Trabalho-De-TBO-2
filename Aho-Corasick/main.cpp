#include "AhoCorasick.hpp"

int main() {
    AhoCorasick ac;
    ac.addPattern("Teste");
    ac.addPattern("Aho");
    ac.addPattern("Corasick");
    ac.addPattern("encontrar padrões");

    ac.build();
    std::string text = "Este é um Teste de Aho-Corasick para encontrar padrões.";
    std::cout << "Texto: " << text << std::endl;

    ac.search(text);

    return 0;
}