#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
    string str = "3 2 20 42 2 3 33 1 14 54";
    vector<int> vect;

    stringstream ss(str);

    int i;
    int t;
    while (ss >> i)
    {
        vect.push_back(i);

        if (ss.peek() == ' ')
            ss.ignore();
    }

    for (i=0; i< vect.size(); i++){
        t = vect[i];
        cout << t<<endl;
    }
}
