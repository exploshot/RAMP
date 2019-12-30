#include <stdint.h>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdlib.h>

#include <version.h>

std::string cliHeader()
{
    std::stringstream header;

    header << "######     #    #     # ###### " << std::endl
           << "#     #   # #   ##   ## #     #" << std::endl
           << "#     #  #   #  # # # # #     #" << std::endl
           << "######  #     # #  #  # ###### " << std::endl
           << "#   #   ####### #     # #  " << std::endl
           << "#    #  #     # #     # #" << std::endl
           << "#     # #     # #     # #" << std::endl

           << "Random Massive Passwords v" << PROJECT_VERSION_LONG << std::endl;

    return header.str();
}

uint16_t getPasswordLength()
{
    std::string passwordLength;
    std::cout << "How many chars should the password have? 1 - " << 0xffffui16 << " are possible..." << std::endl;

    std::getline(std::cin, passwordLength);

    passwordLength.erase(std::find(passwordLength.begin(), passwordLength.end(), ','));

    if (passwordLength == "") {
        return 0;
    }

    try {
        std::cout << "You've entered a password length of: " << passwordLength << std::endl;
    }
    catch (const std::invalid_argument &) {
        std::cout
            << "Failed to parse height - input is not a number!"
            << std::endl
            << std::endl;
    }

    return std::stoi(passwordLength);
}

bool confirm(std::string msg)
{
    /*!
     * In unix programs, the upper case letter indicates the default, for
     * example when you hit enter
     */
    std::string prompt = " (Y/n): ";

    while (true) {
        std::cout
            << msg + prompt;

        std::string answer;
        std::getline(std::cin, answer);

        char c = std::tolower(answer[0]);

        switch (std::tolower(answer[0])) {
            /*!
             * Lets people spam enter / choose default value
             */
            case 'y':
                return true;
            case 'n':
                return false;
        }

        std::cout
            << "Bad input: "
            << answer
            << " - please enter either Y or N."
            << std::endl;
    }
}

bool advancedSymbolsF(std::string symbols)
{
    std::stringstream msg;
    msg << "Do you want to use additional Symbols like: " << symbols << "?" << std::endl;

    return confirm(msg.str());
}

std::string convertToString(char *a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int main(int argc, char *argv[])
{
    std::string password;
    uint16_t passwordLength;
    std::string symbols = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    std::string heavySymbols = "@#$%&*/-+.,<>?\\|";

    bool advancedSymbols;

    std::cout << cliHeader();

    passwordLength = getPasswordLength();
    advancedSymbols = advancedSymbolsF(heavySymbols);

    int count = 0;
    while (count < passwordLength) {
        std::string tempChar = "";
        if (advancedSymbols) {
            tempChar = symbols + heavySymbols;
        }
        else {
            tempChar = symbols;
        }
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, tempChar.size() - 1);

        password += tempChar[distribution(generator)];

        count++;
    }

    std::cout << "Your password is: "
              << std::endl << std::endl
              << password
              << std::endl << std::endl;

    return 0;

}
