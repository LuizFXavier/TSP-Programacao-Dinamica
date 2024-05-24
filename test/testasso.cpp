#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

int main(){

    unordered_map<string, int> maam;

    maam["6"] = 2;

    cout << maam["6"] << endl;
    cout << maam["7"] << endl;

    return EXIT_SUCCESS;
}