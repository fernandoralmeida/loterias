#include <thread>
#include <istream>
#include <string>

// includes struct & class & custon head
#include "lottery.cpp"

using namespace std;

int main()
{
    lottery _lottery;
    try
    {
        /* code */
        while (true)
        {
            /* code */
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "\nLeterias V1.0\n";
            std::cout << "Escolha o Jogo!\n";
            std::cout << "------------------------\n";
            std::cout << "1 Mega Sena\n";
            std::cout << "------------------------\n";
            std::cout << "0 Close\n";

            std::cout << "\nOption: ";
            std::string input;
            std::getline(std::cin, input);
            int choice = std::stoi(input);

            std::chrono::steady_clock::time_point timerStart;
            std::chrono::steady_clock::time_point timerEnd;
            
            switch (choice)
            {
            case 1:
                timerStart = std::chrono::steady_clock::now();

                std::cout << "Loterias\n";
                std::cout << "------------------------\n";
                
                _lottery.dolistLottery();
                
                timerEnd = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsedTime = timerEnd - timerStart;

                std::cout << "------------------------\n";
                std::cout << "Processado em " << elapsedTime.count() << " segundos\n";
                std::cout << "------------------------\n";
                break;

            case 0:
                std::cout << "Closing App...\n";
                return 0;

            default:
                std::cout << "Invalid option. Try again!\n";
                break;
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    return 0;
}