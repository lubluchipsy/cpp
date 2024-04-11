#include <iostream>
#include <ctime>
#include <chrono>
#include <locale>
#include <iomanip>

void EURtoRUB()
{
  std::locale rus("ru_RU.utf8");
  std::locale ger("de_DE.utf8");
  long double money_eur;

  std::locale::global(ger);
  std::cin.imbue(ger);
  std::cout << "Input money in euros: ";
  std::cin >> std::get_money(money_eur);

  long double money_rub = money_eur * 100;
  std::locale::global(rus);
  std::cout.imbue(rus);
  std::cout << '\n' << "The money in rubles: " << std::put_money(money_rub, true) << std::endl;
}
int main()
{
  EURtoRUB();
  return 0;
}