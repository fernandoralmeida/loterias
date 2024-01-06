
using System.Text;

namespace LoteriasCS;
public static class Lotteries
{
    public enum TLotteries { Quina = 5, MegaSena = 6 }

    public static async Task<IEnumerable<KeyValuePair<string, int>>> DoListLottery(TLotteries types, int combinations)
    {        
        var _count = 0;
        var _count_progress = 0;

        return await Task.Run(() =>
        {
            //gera números aleatórios
            Random _random = new();

            //lista para armazenar os números sorteados
            List<string> _numbers = new();

            //gera x quantidade de combinações numéricas
            for (int i = 0; i < combinations; i++)
            {
                _count++;
                _count_progress++;

                //sorteia x números aleatórios
                var _selected = Lottery(LotteryDictionary[types], _random);

                //exibe o progresso a cada x numneros de jogos processados
                if (_count_progress % 1000000 == 0)
                {
                    _count_progress = 0;
                    Console.Write($"  -> {_count} gerados!");
                    Console.Write("\r");
                }

                //Ordenando os números  em ordem crescente
                _selected.Sort();

                //Convertendo os números para string
                StringBuilder _number_to_string = new();
                _number_to_string.AppendJoin(" ", _selected);

                //Adicionando o número à lista
                _numbers.Add(_number_to_string.ToString());
            }

            //agrupa as series sorteadas repetidas e retorna as 10 series mais sorteadas
            return from n in _numbers
                                .GroupBy(g => g)
                                .OrderByDescending(o => o.Count())
                                .Take(10)
                   select (new KeyValuePair<string, int>(n.Key, n.Count()));
        });
    }

    public static List<int> Lottery(KeyValuePair<int, int> lotterydictionary, Random random)
    {
        return Enumerable
                .Range(1, lotterydictionary.Value)
                .OrderBy(_ => random.Next())
                .Take(lotterydictionary.Key)
                .ToList();
    }

    public static readonly Dictionary<TLotteries, KeyValuePair<int, int>> LotteryDictionary = new()
    {
        {TLotteries.MegaSena, new KeyValuePair<int, int>(6,60)},
        {TLotteries.Quina, new KeyValuePair<int, int>(5,80)}
    };
}