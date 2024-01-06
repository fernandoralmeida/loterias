#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <future>
#include <string>
#include <numeric>

using namespace std;

// Classe Lotteries
class Lotteries
{
public:
    // Enumeração TLotteries
    enum TLotteries
    {
        Quina = 5,
        MegaSena = 6
    };

    // Método estático DoListLottery
    static std::vector<std::pair<std::string, int>> DoListLottery(TLotteries types, int combinations)
    {
        int count = 0;
        int count_progress = 0;

        // Inicializando o gerador de números aleatórios
        std::random_device rd;
        std::mt19937 rng(rd());

        // Lista para armazenar os números sorteados
        std::vector<std::string> numbers;
        numbers.reserve(combinations);

        // Gerando x quantidade de combinações numéricas
        for (int i = 0; i < combinations; ++i)
        {
            ++count;
            ++count_progress;

            // Sorteando x números aleatórios
            auto selected = Lottery(LotteryDictionary[types], rng);

            // Exibindo o progresso a cada x números de jogos processados
            if (count_progress % 1000000 == 0)
            {
                count_progress = 0;
                std::cout << "  -> " << count << " gerados!";
                std::cout << "\r" << std::flush;
            }

            // Ordenando os números em ordem crescente
            std::sort(selected.begin(), selected.end());

            // Convertendo os números para string
            std::string number_to_string;
            for (int num : selected)
            {
                number_to_string += std::to_string(num) + " ";
            }

            // Adicionando o número à lista
            numbers.emplace_back(std::move(number_to_string));
        }

        // Ajustando o tipo do mapa para suportar a ordenação
        using MapType = std::map<std::string, int, std::greater<>>;

        // Agrupando as séries sorteadas repetidas e retornando as 10 séries mais sorteadas
        MapType countedNumbers;
        for (const auto &n : numbers)
        {
            ++countedNumbers[n];
        }

        std::vector<std::pair<std::string, int>> result(countedNumbers.begin(), countedNumbers.end());
        result.resize(std::min<size_t>(10, result.size())); // Ajustando para no máximo 10 elementos

        return result;
    }

    // Método estático Lottery
    static std::vector<int> Lottery(std::pair<int, int> lotterydictionary, std::mt19937 &random)
    {
        std::vector<int> result(lotterydictionary.first);
        std::iota(result.begin(), result.end(), 1);

        std::shuffle(result.begin(), result.end(), random);
        result.resize(lotterydictionary.second);

        return result;
    }

    // Dicionário de loterias
    static const std::map<TLotteries, std::pair<int, int>> LotteryDictionary;
};

// Inicializando o dicionário de loterias
const std::map<Lotteries::TLotteries, std::pair<int, int>> Lotteries::LotteryDictionary = {
    {Lotteries::TLotteries::MegaSena, {6, 60}},
    {Lotteries::TLotteries::Quina, {5, 80}}};