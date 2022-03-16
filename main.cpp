#include <iostream>
#include "NeuroNet.h"
#include <vector>
#include <fstream>
#include <string>
#include "Math.h"
using namespace std;

void file_read(vector<vector<double>>& x, vector<vector<double>>& y) {
    ifstream input("iris.data", ios_base::in);
    string temp;
    input >> temp;
    while (input >> temp) {
        string str1 = temp.substr(0, temp.find(','));
        temp = temp.erase(0, temp.find(',') + 1);
        string str2 = temp.substr(0, temp.find(','));
        temp = temp.erase(0, temp.find(',') + 1);
        string str3 = temp.substr(0, temp.find(','));
        temp = temp.erase(0, temp.find(',') + 1);
        string str4 = temp.substr(0, temp.find(','));
        temp = temp.erase(0, temp.find(',') + 1);
        string str5 = temp.substr(0, temp.find(','));
        if (str5 == "Iris-setosa") y.push_back(vector<double>{1, 0, 0});
        if (str5 == "Iris-versicolor") y.push_back(vector<double>{0, 1, 0});
        if (str5 == "Iris-virginica") y.push_back(vector<double>{0, 0, 1});


        x.push_back(vector<double>{stod(str1), stod(str2), stod(str3), stod(str4)});
    }
}

int main()
{
    srand(time(NULL));
    vector<vector<double>> x;
    vector<vector<double>> y;
    file_read(x, y);
    
    NeuroNet net(normalize(x), vector<int>{4, 4,4, 3});
    
    cout << x[0][0];
    /*
    net.testing();
    net.feedforward(vector<double>{2, 3}, vector<double>{1});
    net.testing();
    */
    

    
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < x.size(); j++)
        {
            net.feedforward(x[j], y[j])[0];
        } 
    }

    vector<vector<double>> x_test;
    x_test.push_back(vector<double>{5, 3.5, 1.4, 0.3});
    x_test.push_back(vector<double>{5.6, 2.3, 3.7, 1.0});
    x_test.push_back(vector<double>{6.1, 3.1, 4.9, 1.8});

    for (vector<double> x_t : x_test) {
        auto predict = net.predict(x_t);
        for (int i = 0; i < predict.size(); i++) {
            cout << predict[i] << " ";
        }
        cout << endl;
    }

    return 0;
}