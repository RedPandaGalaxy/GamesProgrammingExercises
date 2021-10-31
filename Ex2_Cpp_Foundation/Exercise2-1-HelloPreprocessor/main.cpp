#include <iostream>
#include <ctime>

using namespace std;

int main() {

    //Current Time
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char* dt = ctime(&now);

    cout << "The local date and time is: " << now << endl;


    //Compile Time
    clock_t runTime = clock();
    cout << runTime << endl;
    int x; // waits for user input. Workaround for not closing window on Windows
    std::cin >> x;
    return 0;
}