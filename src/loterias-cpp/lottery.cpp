#include <iostream>
#include <vector>
#include <random>
#include <map>

using namespace std;

struct lottery
{
    void mostrarProgresso(int combinacoesGeradas)
    {
        if (combinacoesGeradas % 1000000 == 0)
        {
            std::cout << "\rCombinacoes geradas: " << combinacoesGeradas << std::flush;
        }
    }

    vector<int> gerarSorteio()
    {
        std::vector<int> numeros(6);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 60);

        for (int i = 0; i < 6; ++i)
        {
            int numero;
            do
            {
                numero = dis(gen);
            } while (std::find(numeros.begin(), numeros.end(), numero) != numeros.end());
            numeros[i] = numero;
        }

        return numeros;
    }

    void dolistLottery(){
        
        std::map<std::vector<int>, int> contagemSorteios;

        for (int i = 0; i < 53000000; ++i)
        {
            auto sorteio = gerarSorteio();
            contagemSorteios[sorteio]++;
            mostrarProgresso(i + 1);
        }

        std::vector<std::pair<std::vector<int>, int>> sorteiosOrdenados(
            contagemSorteios.begin(), contagemSorteios.end());
        std::sort(sorteiosOrdenados.begin(), sorteiosOrdenados.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a.second > b.second;
                  });

        int limite = std::min(10, static_cast<int>(sorteiosOrdenados.size()));
        for (int i = 0; i < limite; ++i)
        {
            const auto &sorteio = sorteiosOrdenados[i].first;
            const auto &frequencia = sorteiosOrdenados[i].second;

            std::cout << "Sorteio: ";
            for (int numero : sorteio)
            {
                std::cout << numero << " ";
            }
            std::cout << "| Frequência: " << frequencia << std::endl;
        }
    }
};



