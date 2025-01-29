#include <iostream>
#include <thread>
#include <stdexcept>
#include <mutex>
#include <queue>
#include <cstdio>
#include "TernaryNumber.hpp"

using namespace std;

/// ������� FIFO ������� ������
queue<TernaryNumber> inFifo;
/// ������� FIFO �������� ������
queue<TernaryNumber> outFifo;
/// ������ ��� ������������� ������ � FIFO ������� ������ �� ������ �������
mutex inFifoMutex;
/// ������ ��� ������������� ������ � FIFO �������� ������ �� ������ �������
mutex outFifoMutex;
/// ����, ��������������� � ���������� ������ ������, ��������� ������� ������
bool isInputRun = true;
/// ����, ��������������� � ���������� ������ ������, ��������� ������
bool isSolutionRun = true;
/// ��� �������� �����
string inFilename;
/// ��� ��������� �����
string outFilename;

/// �����, �������� ������� ������
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
  cin>>t;   // ���������� ����� �� ������� ������ ������
  while(t--)
    {
    int n;
    string x;
    cin>>n;  // ����� ��������� �����
        cin>>x;  // �������� �����
        // �������� �������� ����� � ������� FIFO
        inFifoMutex.lock();
        inFifo.push(TernaryNumber(x));
        inFifoMutex.unlock();
  }
  isInputRun = false;
}

/// �����, ����������� ����� �������
void solutionProcess()
{
    TernaryNumber x;
    bool run = true;
    bool dataAvailable = false;
    while(run)
    {
        // �������� �� ������� ������� ����� �����
        inFifoMutex.lock();
        if(!inFifo.empty())
        {
            x = inFifo.front();
            inFifo.pop();
            dataAvailable = true;
        }
        inFifoMutex.unlock();

        // ������ ������
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

      // �������� ������� � �������� �������
      outFifoMutex.lock();
      outFifo.push(a);
      outFifo.push(b);
      outFifoMutex.unlock();
    }

        // ���������� ���� ������� ����� ������
        dataAvailable = false;

        // ���� ������� ������ ������ �� �����, �� ��������� ������ ������
        inFifoMutex.lock();
        if(!isInputRun && inFifo.empty())
        {
            run = false;
        }
        inFifoMutex.unlock();
    }
    isSolutionRun = false;
}

/// �����, ����������� ����� ����������� �������
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
