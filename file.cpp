#include<iostream>
#include<fstream>

using namespace std;

void readFromFile(const string& fileName, int itemCount, int arr[]) {
    string token;
    ifstream inputFile(fileName);
    for (int i = 0; i < itemCount; i++) {
        getline(inputFile, token);
        arr[i] = stoi(token);
    }
    inputFile.close();
};

void writeToFile(const string& fileName, int itemCount, int arr[]) {
    ofstream outputFile(fileName);
    for (int i = 0; i < itemCount; i++){
        outputFile << arr[i] << endl;
    }
};


int main() {
    string infileName, outFileName;
    int itemCount;
    cout << "Input in filename" << endl;
    cin >> infileName;
    cout << "Input out filename" << endl;
    cin >> outFileName;
    cout << "Input count item in file" << endl;
    cin >> itemCount;
    int arr[itemCount];
    readFromFile(infileName, itemCount, arr);
    writeToFile(outFileName, itemCount, arr);
    return 0;
};