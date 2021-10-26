#include <bits/stdc++.h>
using namespace std;
#define all(x)          (x).begin(),(x).end()
#define MOD             1000000007
#define case(tc)        cout << "Case " << tc << ": ";
#define close           << "\n";
typedef int64_t ll;
typedef uint64_t ull;
typedef long double lld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

// Settings
int variables = 4; // QM Method for 4 variable

struct row1{
    int group_no;
    int minterm;
    string bin_rep = "";
    bool has_pair = false;
    bool operator <(row1 other){
        if(group_no == other.group_no){
            if(minterm == other.minterm){
                return bin_rep < other.bin_rep;
            }return minterm < other.minterm;
        }else return group_no < other.group_no;
    }
};

struct row2{
    int group_no;
    pii matches;
    string bin_rep = "";
    bool has_pair = false;
    bool operator <(row2 other){
        if(group_no == other.group_no){
            if(matches == other.matches){
                return bin_rep < other.bin_rep;
            }return matches < other.matches;
        }else return group_no < other.group_no;
    }
};

struct row3{
    int group_no;
    tuple<int,int,int,int> matches;
    string bin_rep = "";
    bool has_pair = false;
    bool operator <(row3 other){
        if(group_no == other.group_no){
            if(matches == other.matches){
                return bin_rep < other.bin_rep;
            }return matches < other.matches;
        }else return group_no < other.group_no;
    }
};

string dec_to_bin(int dec, int bits){
    string res = bitset<64>(dec).to_string();
    reverse(all(res));
    res = res.substr(0,bits);
    reverse(all(res));
    return res;
}

vector<int> minterms;
vector<row1> table1;
vector<row2> table2;
vector<row3> table3;

bool is_match(row1 a, row1 b){
    int mismatch = 0;
    for (int i = 0; i < variables; ++i) {
        if(a.bin_rep[i] != b.bin_rep[i]) mismatch++;
    }
    return mismatch == 1;
}

string get_bin_rep(row1 a, row1 b){
    int mismatch = 0;
    string res(variables,'_');
    for (int i = 0; i < variables; ++i) {
        if(a.bin_rep[i] == b.bin_rep[i]) res[i] = a.bin_rep[i];
    }
    return res;
}



bool is_match(row2 a, row2 b){
    int mismatch = 0;
    for (int i = 0; i < variables; ++i) {
        if(a.bin_rep[i] != b.bin_rep[i]) mismatch++;
    }
    return mismatch == 1;
}

string get_bin_rep(row2 a, row2 b){
    int mismatch = 0;
    string res(variables,'_');
    for (int i = 0; i < variables; ++i) {
        if(a.bin_rep[i] == b.bin_rep[i]) res[i] = a.bin_rep[i];
    }
    return res;
}

void test(int tc){

    // take minterms input
    int in;
    while(cin >> in) minterms.push_back(in);
    sort(all(minterms));

    // generate first table
    for (int i = 0; i <= variables; ++i) {
        for (int j = 0; j < minterms.size(); ++j) {
            if(__builtin_popcount(minterms[j]) == i){
                // add this minterm to our table1
                row1 tmp;
                tmp.group_no = i;
                tmp.minterm = minterms[j];
                tmp.bin_rep = dec_to_bin(minterms[j],variables);
                table1.push_back(tmp);
            }
        }
    }


    // generate second table
    for (int i = 0; i < variables; ++i) {
        // match i with i+1 groups
        for (int j = 0; j < table1.size(); ++j) {
            if(table1[j].group_no == i){
                for (int k = 0; k < table1.size(); ++k) {
                    if(table1[k].group_no == i+1){
                        if(j == k) continue;
                        if(is_match(table1[j] , table1[k])){
                            row2 tmp;
                            tmp.group_no = i;
                            tmp.matches = {table1[j].minterm, table1[k].minterm};
                            tmp.bin_rep = get_bin_rep(table1[j] , table1[k]);
                            table2.push_back(tmp);
                            table1[j].has_pair = true;
                            table1[k].has_pair = true;
                        }
                    }
                }
            }
        }
    }

    // generate third table
    for (int i = 0; i < variables; ++i) {
        // match i with i+1 groups
        for (int j = 0; j < table2.size(); ++j) {
            if(table2[j].group_no == i){
                for (int k = 0; k < table2.size(); ++k) {
                    if(table2[k].group_no == i+1){
                        if(j == k) continue;
                        if(is_match(table2[j] , table2[k])){
                            row3 tmp;
                            tmp.group_no = i;
                            tmp.matches = make_tuple(table2[j].matches.first,table2[j].matches.second,table2[k].matches.first,table2[k].matches.second);
                            tmp.bin_rep = get_bin_rep(table2[j] , table2[k]);
                            table3.push_back(tmp);
                            table2[j].has_pair = true;
                            table2[k].has_pair = true;
                        }
                    }
                }
            }
        }
    }


    // print the first table
    sort(all(table1));
    cout << "Table #1:" close
    for (int i = 0; i < table1.size(); ++i) {
        if(i!=0 && table1[i-1].group_no != table1[i].group_no) cout close
        cout << table1[i].group_no << "\t " << table1[i].minterm << "\t " << table1[i].bin_rep << "\t " << table1[i].has_pair close
    }

    cout close
    cout close
    cout close

    // print the first table
    sort(all(table2));
    cout << "Table #2:" close
    for (int i = 0; i < table2.size(); ++i) {
        if(i!=0 && table2[i-1].group_no != table2[i].group_no) cout close
        cout << table2[i].group_no << "\t " << table2[i].matches.first << "-" << table2[i].matches.second << "\t " << table2[i].bin_rep << "\t " << table2[i].has_pair close
    }

    cout close
    cout close
    cout close

    // print the first table
    sort(all(table3));
    cout << "Table #3:" close
    for (int i = 0; i < table3.size(); ++i) {
        if(i!=0 && table3[i-1].group_no != table3[i].group_no) cout close
        int first, second, third, fourth;
        tie(first, second, third, fourth) = table3[i].matches;
        cout << table3[i].group_no << "\t " << first << "-" << second << "-" << third << "-" << fourth << "\t " << table3[i].bin_rep << "\t " << table3[i].has_pair close
    }

}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#ifdef necromancer
    freopen("../input.txt", "r", stdin);
//    freopen("../output.txt", "w", stdout);
//    freopen("../error.txt", "w", stderr);
#endif
    int testcase = 1;
//    cin >> testcase;
    for (int tc = 0; tc < testcase; tc++) {
        test(tc);
    }
}
