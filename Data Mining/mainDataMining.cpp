#include <iostream>
#include <string>
#include <vector>

#include "FileReader.hpp"
#include "ValidateDate.hpp"
#include "ValidateEmail.hpp"
#include "ValidatePhone.hpp"

void printResults(const std::string &title,
                  const std::vector<std::string> &results) {
  std::cout << "\n--- " << title << " Encontrados ---" << std::endl;
  if (results.empty()) {
    std::cout << "Nenhum item encontrado." << std::endl;
  } else {
    for (const std::string &item : results) {
      std::cout << " - " << item << std::endl;
    }
  }
  std::cout << "------------------------" << std::endl;
}

void displayMenu() {
  std::cout << "\n========== MENU ==========" << std::endl;
  std::cout << "1. Procurar Emails" << std::endl;
  std::cout << "2. Procurar Telefones" << std::endl;
  std::cout << "3. Procurar Datas" << std::endl;
  std::cout << "4. Procurar Tudo" << std::endl;
  std::cout << "5. Sair" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << "Digite as opcoes desejadas (ex: 13 para Email e Data): ";
}

int main() {
  std::string filename = "data/texto.txt";
  std::string fileContent;

  if (!FileReader::readAllText(filename, fileContent)) {
    std::cerr << "Erro: Nao foi possivel abrir o arquivo '" << filename << "'."
              << std::endl;
    return 1;
  }

  std::cout << "Arquivo '" << filename << "' lido com sucesso." << std::endl;

  while (true) {
    displayMenu();

    std::string choice;
    std::cin >> choice;

    bool runEmail = false;
    bool runPhone = false;
    bool runDate = false;

    if (choice == "5") {
      std::cout << "Saindo do programa..." << std::endl;
      break;
    }

    if (choice == "4") {
      runEmail = true;
      runPhone = true;
      runDate = true;
    } else {

      if (choice.find('1') != std::string::npos)
        runEmail = true;
      if (choice.find('2') != std::string::npos)
        runPhone = true;
      if (choice.find('3') != std::string::npos)
        runDate = true;
    }

    if (!runEmail && !runPhone && !runDate) {
      std::cout << "Opcao invalida. Por favor, tente novamente." << std::endl;
      continue;
    }

    std::cout << "\n--- Iniciando Buscas ---";

    if (runEmail) {
      ValidateEmail emailValidator;
      emailValidator.search(fileContent);
      printResults("Emails", emailValidator.getEmails());
    }
    if (runPhone) {
      ValidatePhone phoneValidator;
      phoneValidator.search(fileContent);
      printResults("Telefones", phoneValidator.getPhoneNumbers());
    }
    if (runDate) {
      ValidateDate dateValidator;
      dateValidator.search(fileContent);
      printResults("Datas", dateValidator.getDates());
    }
  }

  return 0;
}