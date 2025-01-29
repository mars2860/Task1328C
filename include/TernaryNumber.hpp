#pragma once

#include <string>
#include <stdexcept>

/** ����� ���������� ��������, ���� ��� �������� ������ ����� 0,1 � 2.
  * ��������, ��������� ����� �������� ���������: 1022,11,21,2002
  */
class TernaryNumber
{
private:
  /// ���������� ���� � �������� �����
  int length;
  /// ����� ��������� ����� � ������� ASCII
  char *digit;
  /// ������ �����
  int pos;
private:
  /// ������ ������ �������� ����� �������� �����
  void init(int len)
  {
    length = len;
    pos = 0;
    if(len > 0)
    {
      digit = new char[len];
      for(int i = 0; i < len; i++)
      {
        digit[i] = '0';
      }
    }
    else
    {
      digit = NULL;
    }
  }
public:
  TernaryNumber()
  {
    init(0);
  }

  TernaryNumber(int len)
  {
    init(len);
  }

  TernaryNumber(std::string const& num)
  {
    init(num.length());

    for(int i = 0; i < length; i++)
    {
      pushDigit(num[i]);
    }
  }

  TernaryNumber(TernaryNumber const &num)
  {
    init(num.length);
    for(int i = 0; i < this->length; i++)
    {
      this->digit[i] = num.digit[i];
    }
  }

  ~TernaryNumber()
  {
    if(digit)
    {
      delete[] digit;
    }
  }

  /// ���������� ����� �����
  int getLength()
  {
    return this->length;
  }

  /// ���������� ����� �� �������� �������
  char getDigit(int i)
  {
    if(i < 0 || i >= this->length)
    {
      throw std::runtime_error("Invalid digit index");
    }

    return this->digit[i];
  }

  /// ����������� ����� � ������
  std::string toString()
  {
    std::string res;
    if(this->length > 0)
    {
      for(int i = 0; i < this->length; i++)
      {
        res += digit[i];
      }
    }
    return res;
  }

  /** ��������� ����� ����� � �������� �����. ����� ������ ���� � ������� ASCII
   * @note ���������� runtime_error ���� ����� �� ������������� �������� '0','1','2'
   */
  void pushDigit(char c)
  {
    if(pos >= length)
    {
      return;
    }

    if(c < '0' || c > '2')
    {
      throw std::runtime_error("Invalid digit for ternary number");
    }

    digit[pos++] = c;
  }

  /** �������� �������� XOR ��� ����� ��������� ������� a � b
    * (��� ����� ����� n) �������� ��� ����� c=a^b ����� n, ��� ci=(ai+bi)%3
    * (��� % � �������� ������ �� ������).
    * ������� �������, ������ ��������������� ����� � ������� �������
    * �� ���� ��� ������� �� 3. ��������, 10222 ^ 11021=21210
    */
  TernaryNumber operator^(TernaryNumber const& obj)
  {
    if(this->length != obj.length)
    {
      throw std::runtime_error("Can't execute XOR: the length of two ternary number is not the same");
    }
    TernaryNumber res(obj.length);
    for(int i = 0; i < obj.length; i++)
    {
      res.digit[i] = (((this->digit[i] - '0') + (obj.digit[i] - '0')) % 3) + '0';
    }
    return res;
  }

  bool operator==(TernaryNumber const& obj)
  {
    if(this->length != obj.length)
    {
      return false;
    }

    for(int i = 0; i < this->length; i++)
    {
      if(this->digit[i] != obj.digit[i])
      {
        return false;
      }
    }

    return true;
  }

  TernaryNumber& operator=(TernaryNumber const& num)
  {
    init(num.length);

    for(int i = 0; i < length; i++)
    {
      pushDigit(num.digit[i]);
    }

    return *this;
  }
};
