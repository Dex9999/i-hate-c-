#include <iostream>
#include <iomanip>

int main()
{
    const double TAX = 8.5 / 100.f;
    double price = 0;
    std::string live = "";

        std::cout << "How much was your purchase? $";
        std::cin >> price;

        if(std::cin.fail()) {
            std::cout << "You can't enter a string, that breaks everything\n";
            std::cout << "⢻⢭⡓⣆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << "⠀⠀⠀⠀⠸⣏⢖⡲⣅⠀⠀\n" << "⣣⢾⡛⣜⢫⣦⠀⠀⢀⣤⠴⡦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣸⢏⡝⣆⢀\n" << "⢿⣧⢹⣬⡷⣚⣒⣶⡾⣍⡞⡱⣞⡇⠀⠀⠀⠀⢀⣠⢤⠖⣦⡤⠤⡶⠦⠤⣤⢶⠲⠤⣄⠀⠀⠀⠀⠀⢀⡤⠶⢶⢤⡀⢸⣛⣮⢞⡜⡚\n" << "⠈⡷⣻⢏⠶⣙⢶⣼⠟⡼⣜⡵⠋⠀⠀⠀⣠⠞⡩⢴⣿⣿⣾⣹⠐⢢⢁⡾⡵⠚⢻⣷⣤⡙⠲⢄⠀⠀⢾⣍⡻⣌⢧⣷⡾⡞⣥⢫⡝⣃\n" << "⠀⢻⣿⢊⣟⣾⢫⢇⡻⣱⢺⠁⠀⠀⠀⡼⣡⣿⣄⣀⡿⣿⣿⡏⡇⢢⢸⡿⣷⣤⣼⠿⢿⣿⣷⣎⣷⠀⠈⠳⣵⡩⢖⡻⣱⢻⣌⡳⢎⡵\n" << "⠀⠀⢻⡧⢞⡧⣋⣮⣕⡣⢿⠀⠀⢀⡼⢃⣻⢿⣿⣿⣧⠾⠟⡙⣧⣂⣌⢣⡛⡿⠿⠷⠾⠿⠿⠣⣌⠳⡀⢰⢯⡱⣫⡶⢥⣛⢮⡓⣏⢶\n" << "⠀⠀⠈⢯⡧⣓⢧⡚⣽⣞⡾⠀⢀⡞⠠⣿⠀⡰⢂⣖⣤⣯⣾⣿⣿⣿⣿⣿⣿⣇⠄⣎⣱⣉⢎⡱⣘⡇⠹⡞⣮⢵⢯⣱⠳⡬⢧⡙⣦⠋\n" << "⠀⠀⠀⠈⠳⣭⢲⡹⢲⡞⠁⠀⣼⢐⠡⡙⠳⠗⡛⣩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡁⡉⠛⣶⣵⠋⡐⢿⠈⠻⣆⢧⡛⢜⣣⠟⠁⠀\n" << "⠀⠀⠀⠀⠀⠈⠉⠉⠁⠀⠀⢰⡇⢊⠔⡡⢊⠔⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡈⠡⣿⢹⡄⢡⢚⣇⠀⠈⠉⠉⠉⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⢊⠤⢑⠢⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⢹⠃⢢⢻⡄⢊⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠌⢢⠁⢎⣿⣿⣿⣿⣿⣿⣿⠿⠟⠿⢿⣿⣿⣿⣿⣿⣿⣏⡄⢣⢺⡇⢼⡋⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡊⠤⠉⢼⣿⣿⣿⣿⠿⠋⡄⠒⡌⢢⠐⡌⠻⣿⣿⣿⣿⣯⠛⢓⠛⣠⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⡘⡏⣿⣿⣿⡿⠋⡄⠣⠌⡱⢈⠄⢣⠐⡡⠘⢿⣿⣿⣿⡐⣌⢒⣰⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡅⠸⠿⢛⡡⠘⡄⠣⡘⠄⠣⡘⠄⢣⠐⣉⠂⠻⢿⠿⠁⢼⡲⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⣁⠦⠟⡁⢣⠐⡡⠂⡍⠰⢁⠎⡄⠣⢄⡉⠲⢦⣂⣉⢴⠗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⢲⢥⣂⠅⣂⠑⡈⢅⠊⡐⠌⢡⢂⣌⣡⠶⣛⣙⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";

            std::cin.clear();
            return 0;
        } else {
        std::cout << "Do you live in state? (y/n) ";
        std::cin >> live;
        if(static_cast<char>(tolower(live[0])) == 'y'){
        std::cout << "Your price with tax is $" << price + (price * TAX);
        } else if (static_cast<char>(tolower(live[0])) == 'n'){
        std::cout << "You don't owe any tax! The price is still $" << price;
        } else {
        std::cout << "It's a simple question\n";
std::cout << "                                                  \n" << "                .:~!7??JJJJ?77~^:.                \n" << "            :!?YPGGGGGGGGGGGGGGGGPY?~.            \n" << "         :7YPGGGGGGGGGGGGGGGGGGGGGGGGPJ!.         \n" << "       ^JPGGGGGGGBBBBBBBBBBBBBBBGGGGGGGG57.       \n" << "     .?PGGGGGGBBBBBBBBBBBBBBBBBBBBBBGGGGGG5!      \n" << "    ^5GGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBGGGGGGGJ.    \n" << "   :5GGGGGGB#P7777JB#BBBBBBBB##J777?PBGGGGGGGJ    \n" << "   YGGGGGG#&@P::::~&@#BBBBB#&@&~::::5@&BGGGGGP!   \n" << "  ~PGGGGG#@@@@B5YP#@@@#BBBB&@@@&PY5B@@@&BGGGGG5.  \n" << "  ?GGGGGG#@@@@@@@@@@@@&BBB#&@@@@@@@@@@@@BGGGGGP~  \n" << "  YGGGGGBB#@@@@@@@@@@&BBBBBB&@@@@@@@@@@BBBGGGGP!  \n" << "  JGGGGGBBBB#&@@@@@&BBBBBBBBB#&@@@@@&#BBBBGGGGP~  \n" << "  7GGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGGG5^  \n" << "  :PGGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGGPJ   \n" << "   7GGGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGGP5^   \n" << "    JGGGGGGBBBBBBBBBGGGGGGGGGGBBBBBBBBBGGGGP5~    \n" << "     7PGGGGGGBBBBBB7^^^^^^^^^^7BBBBBBGGGGGPY^     \n" << "      ^YGGGGGGGBBBBPYYYYYYYYYYPBBBGGGGGGP57.      \n" << "        ~JPGGGGGGGGBBBBBBBBBBBBGGGGGGGPY7:        \n" << "          :!J5GGGGGGGGGGGGGGGGGGGGG5Y7^.          \n" << "             .:~7JY5PPPGGGPPP55Y?!~:              \n" << "                   ..::^^^:::..                   \n" << "                                                  \n";

}}}
