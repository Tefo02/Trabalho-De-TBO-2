#include "include/Desafio5.hpp"


int main() {
    std::string dictionaryFilePath = "data/portuguese-brazil.dic"; 
    std::string text = "Este é um exemplo de texto utilizado para testar a funcionalidade do verificador ortográfico desenvolvido em C++. O sistema deve ser capaz de identificar palavras que não estão presentes no dicionário carregado previamente. A verificação deve ser rápida, eficiente e precisa, mesmo em textos relativamente longos. Neste texto, por exemplo, falaremos sobre a importância da acurácia em sistemas de correção automática, bem como sua utilidade em aplicações educacionais, profissionais e pessoais. [Ortográfia] incorreta pode prejudicar a credibilidade de um documento, afetando negativamente a percepção do leitor. Além disso, palavras como [funcionalidae] e [desenvolvimente] foram inseridas propositadamente com erros para avaliar se o sistema é capaz de encontrar elas. A experiência do usuário deve ser fluida, com feedback imediato sobre as palavras não reconhecidas. O sistema também deve lidar com pontuação e formatação de maneira adequada, garantindo que apenas palavras isoladas sejam verificadas. Por fim, esperamos que o sistema seja capaz de lidar com uma variedade de casos, incluindo palavras compostas e termos técnicos específicos.";
    
    Desafio5 desafio(dictionaryFilePath, text);
    
    try {
        desafio.run();
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1; 
    }


    return 0;
}