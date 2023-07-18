#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<string>> groups;
vector<vector<string>> nums;

struct hashes{
    double hash;
    int size;
};

vector<vector<hashes>> groups_h;
vector<vector<hashes>> nums_h;


hashes calHash(string num){
    hashes h;
    h.hash = 0;
    h.size = num.size();
    for(int k = 0;k < num.size();k++){
            h.hash += (num[k] - 96) * pow(k+1,10);
        }

        //cout  << h.hash << " " << h.size << endl;;
    return h;
}

void input() {
    ifstream infile("p1_input.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> group;
        vector<string> num;
        vector<hashes> group_h;
        vector<hashes> num_h;
        if (line.find('{') != string::npos) {
            // Extract group items
            int start = line.find('{') + 1;
            int end = line.find('}');
            string items = line.substr(start, end - start);
            stringstream ss(items);
            string item;
            while (getline(ss, item,'\'')) {
                if( getline(ss, item,','))
                item.erase(item.size()-1);
                group.push_back(item);
                group_h.push_back(calHash(item));
            }
            groups.push_back(group);
            groups_h.push_back(group_h);
        }
        else if(line.find('[') != string::npos){
            // Extract num items
                int start = line.find('[') + 1;
                int end = line.find(']');
                string items = line.substr(start, end - start);
                stringstream ss(items);
                string item;
                while (getline(ss, item,'\'')) {
                    if( getline(ss, item,','))
                    item.erase(item.size()-1);
                    num.push_back(item);
                    num_h.push_back(calHash(item));
                }
                nums.push_back(num);
                nums_h.push_back(num_h);
            }
        }
    return;
}

void canDisheshBeMade(int r){
    int count = 0;
        hashes hash_groups;
        hashes hash_nums;
        bool match = false;       
        for(int c = 0;c < groups_h.size();c++){
            hash_groups.size = 0;
            hash_groups.hash = 0;
            for(int k = 0;k < groups_h[c].size();k++){
                hash_groups.hash += groups_h[c][k].hash;
                hash_groups.size += groups_h[c][k].size;
            }
            //cout << c << ") " << hash_groups.hash << " " << hash_groups.size << endl;
            match = false;
            for(int k = 0;k <= nums_h[r].size() - groups_h[c].size();k++){
                hash_nums.size = 0;
                hash_nums.hash = 0;
                for(int i = 0;i < groups_h[c].size();i++){
                    hash_nums.hash += nums_h[r][k+i].hash;
                    hash_nums.size += nums_h[r][k+i].size;
                }
                //cout << k << ") " << hash_nums.hash << " " << hash_nums.size << endl;
                if(hash_groups.hash == hash_nums.hash){
                    if(hash_groups.size == hash_nums.size){
                        match = true;
                        //cout << "yay" << endl;
                        for(int i = 0;i < groups_h[c].size();i++){
                            nums_h[r][k+i].hash = -1;
                            nums_h[r][k+i].size;
                        }
                        count++;
                        break;
                    }
                }
                else{
                    match = false;
                }
            }
            
        }
        cout << "Test case " << r+1 << ": ";
        if(match && count == groups.size())
            cout << "Pass";
        else
            cout << "Fail";
        cout << endl;
}

int main(){
    input();
    //loop for each testcase
    for(int r = 0;r < nums.size();r++){
        canDisheshBeMade(r);
    }
}   