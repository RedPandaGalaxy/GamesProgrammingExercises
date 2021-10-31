#include <iostream>
#include <string>
#include <vector>

int main() {
    // Examples:
    // input -> output
    // ifmanwasmeanttostayonthegroundgodwouldhavegivenusroots -> imtgdvs  fearwer  mayoogo  anouuio  ntnnlvt  wttddes  aohghn   sseoau
    // haveaniceday -> hae and via ecy
    // feedthedog -> fto ehg ee dd
    // chillout -> cluhltio 

    using namespace std;
    vector<vector<int>> vect
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

   // the vector output is always in a rectangular shape

    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            cout << vect[i][j] << " ";
        }
        cout << endl;
    }
    

    // todo output secret message

    int x; // waits for user input. Workaround for not closing window on Windows
    std::cin >> x;

    return 0;
}