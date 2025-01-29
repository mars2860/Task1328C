#include <iostream>
#include <thread>
#include <stdexcept>
#include <mutex>
#include <queue>
#include <cstdio>
#include "TernaryNumber.hpp"

using namespace std;

/// Очередь FIFO входных данных
queue<TernaryNumber> inFifo;
/// Очередь FIFO выходных данных
queue<TernaryNumber> outFifo;
/// Мютекс для синхронизации работы с FIFO входных данных из разных потоков
mutex inFifoMutex;
/// Мютекс для синхронизации работы с FIFO выходных данных из разных потоков
mutex outFifoMutex;
/// Флаг, сигнализирующий о завершении работы потока, читающего входные данные
bool isInputRun = true;
/// Флаг, сигнализирующий о завершении работы потока, решающего задачу
bool isSolutionRun = true;
/// Имя входного файла
string inFilename;
/// Имя выходного файла
string outFilename;

/// Поток, читающий входные данные
void inputProcess()
{
  if(inFilename.length() > 0)
  {
    freopen(inFilename.c_str(), "r", stdin);
  }
  
  if(outFilename.length() > 0)
  {
    freopen(outFilename.c_str(), "w", stdout);
  }

  int t;
  cin>>t;   // Количество чисел во входном потоке данных
  while(t--)
    {
    int n;
    string x;
    cin>>n;  // Длина заданного числа
        cin>>x;  // Заданное число
        // Помещаем заданное число в очередь FIFO
        inFifoMutex.lock();
        inFifo.push(TernaryNumber(x));
        inFifoMutex.unlock();
  }
  isInputRun = false;
}

/// Поток, выполняющий поиск решения
void solutionProcess()
{
    TernaryNumber x;
    bool run = true;
    bool dataAvailable = false;
    while(run)
    {
        // Забираем из входной очереди новое число
        inFifoMutex.lock();
        if(!inFifo.empty())
        {
            x = inFifo.front();
            inFifo.pop();
            dataAvailable = true;
        }
        inFifoMutex.unlock();

        // Решаем задачу
        if(dataAvailable)
        {
            TernaryNumber a(x.getLength()), b(x.getLength());

            for(int i = 0; i < x.getLength(); ++i)
            {
                if(x.getDigit(i) == '1')
                {
                    a.pushDigit('1');
                    b.pushDigit('0');
                    for(int j = i + 1; j < x.getLength(); ++j)
                    {
                        b.pushDigit(x.getDigit(j));
                    }
                    break;
        }
        else
                {
                    char digit = '0' + ((x.getDigit(i) - '0') / 2);
                    a.pushDigit(digit);
                    b.pushDigit(digit);
                }
      }

      // Помещаем решение в выходную очередь
      outFifoMutex.lock();
      outFifo.push(a);
      outFifo.push(b);
      outFifoMutex.unlock();
    }

        // Сбрасываем флаг наличия новых данных
        dataAvailable = false;

        // Если входных данных больше не будет, то завершаем работу потока
        inFifoMutex.lock();
        if(!isInputRun && inFifo.empty())
        {
            run = false;
        }
        inFifoMutex.unlock();
    }
    isSolutionRun = false;
}

/// Поток, выполняющий вывод результатов решения
void outputProcess()
{
    bool run = true;
    while(run)
    {
        outFifoMutex.lock();
        while(!outFifo.empty())
        {
            TernaryNumber x = outFifo.front();
            outFifo.pop();
            cout<<x.toString()<<endl;
        }
        if(!isSolutionRun)
        {
            run = false;
        }
    outFifoMutex.unlock();
    }
}

int main(int argc, char** argv)
{
  if(argc > 1)
  {
    inFilename.append(argv[1]);
  }
  
  if(argc > 2)
  {
    outFilename.append(argv[2]);
  }
  
    thread thInput(inputProcess);
    thread thSolution(solutionProcess);
    thread thOutput(outputProcess);

    thInput.join();
    thSolution.join();
    thOutput.join();

    return 0;
}
