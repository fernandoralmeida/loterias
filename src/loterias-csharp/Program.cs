using System.Diagnostics;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace LoteriasCS;
class Program
{
    static async Task Main(string[] args)
    {
        // Configurar o serviço de logging
        var serviceProvider = new ServiceCollection()
            .AddLogging(builder =>
            {
                builder.AddConsole(); // Adicionar um provedor de console
            })
            .BuildServiceProvider();

        // Criar um logger
        var _logger = serviceProvider.GetRequiredService<ILogger<Program>>();

        try
        {
            while (true)
            {
                Thread.Sleep(1000);
                Console.WriteLine("\nLeterias V1.0");
                Console.WriteLine("Escolha o Jogo!");
                Console.WriteLine("------------------------");
                Console.WriteLine("1 Mega Sena");
                Console.WriteLine("------------------------");
                Console.WriteLine("0 Close");

                Console.Write("\nOption: ");
                string input = Console.ReadLine()!;
                int choice = int.Parse(input);

                var _timer = new Stopwatch();

                switch (choice)
                {
                    case 1:
                        _timer.Start();
                        var _count = 0;
                        Console.WriteLine("Loterias");
                        Console.WriteLine("------------------------");
                        foreach (var item in await Lotteries.DoListLottery(Lotteries.TLotteries.MegaSena, 10000000))
                        {
                            _count++;
                            if (_count == 1)
                            {
                                Console.WriteLine("10 maiores combinações!");
                                Console.WriteLine("------------------------");
                            }
                            Console.WriteLine($"{_count}º\t{item.Key}\t{item.Value} ocorrências");
                        }
                        _timer.Stop();
                        Console.WriteLine("------------------------");
                        Console.WriteLine($"Processado em {_timer.Elapsed:hh\\:mm\\:ss\\.fff}");
                        _timer.Reset();
                        Console.WriteLine("------------------------");
                        break;

                    case 0:
                        _logger.Log(LogLevel.Information, "Closing App...");
                        return;

                    default:
                        _logger.Log(LogLevel.Information, "Invalid option. Try again!");
                        break;
                }
            }
        }
        catch (Exception ex)
        {
            _logger.Log(LogLevel.Error, ex!.Message);
        }
    }
}
