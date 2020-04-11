#include <iostream>
#include <vector>
#include <algorithm>

using namespace::std;

int main(){
    string word;
    vector<string> arr;
    while(cin>>word){
        transform(word.begin(),word.end(),word.begin(),::toupper);
        arr.push_back(word);
    }
    for(int i=0;i<arr.size();i++)
        cout<<arr[i]<<endl;
    return 0;
}

