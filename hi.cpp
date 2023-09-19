#include <iostream>
int main(){
  // the values on my computer are: 4 2 8 8 4 1 1 32 4 4 4 2 8 4 4 1
  std::cout << "The sizes of datatypes on this computer:\n int " << sizeof(int) << "\n short int " << sizeof(short int) << "\n long int " << sizeof(long int) << "\n double " << sizeof(double) << "\n float " << sizeof(float) << "\n char " << sizeof(char) << "\n bool " << sizeof(bool) << "\n string " << sizeof(std::string) << "\n wchar_t " << sizeof(wchar_t) << "\n signed int " << sizeof(signed int)  << "\n unsigned int " << sizeof(unsigned int) << "\n short " << sizeof(short) << "\n long " << sizeof(long) << "\n signed " << sizeof(signed) << "\n unsigned " << sizeof(unsigned) << "\n void " << sizeof(void);
  return 0;
  }

