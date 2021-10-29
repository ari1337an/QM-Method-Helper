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
int variables; // QM Method for n variable

struct row{
    int group_no;
    vector<int> match_pairs;
    string bin_rep;
    bool has_pair = false;
    bool operator <(row other){
        if(group_no == other.group_no){
            if(match_pairs == other.match_pairs){
                return bin_rep < other.bin_rep;
            }else return match_pairs < other.match_pairs;
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

bool is_match(row a, row b){
    int mismatch = 0;
    for (int i = 0; i < variables; ++i) if(a.bin_rep[i] != b.bin_rep[i]) mismatch++;
    return mismatch == 1;
}

string get_bin_rep(row a, row b){
    int mismatch = 0;
    string res(variables,'_');
    for (int i = 0; i < variables; ++i) if(a.bin_rep[i] == b.bin_rep[i]) res[i] = a.bin_rep[i];
    return res;
}

string print_vec(vector<int> &a){
    string res;
    res = res + to_string(a[0]);
    for (int i = 1; i < a.size(); ++i) {
        res = res + "-" + to_string(a[i]);
    }
    return res;
}

void test(int tc){
    // take number of variables input
    cin >> variables;

    // Configure tables
    vector<int> minterms;
    vector<row> tables[variables];

    // take minterms input
    int in;
    while(cin >> in) minterms.push_back(in);
    sort(all(minterms));

    // Generate every table
    for (int table_no = 0; table_no < variables; ++table_no) { // generate the i-th table
        for (int group = 0; group <= variables; ++group) { // for every group
            if(table_no == 0){ // if generating first table
                for (int j = 0; j < minterms.size(); ++j) {
                    if(__builtin_popcount(minterms[j]) == group){
                        // add this minterm to our ith table
                        row tmp;
                        tmp.group_no = group;
                        tmp.match_pairs.push_back(minterms[j]);
                        tmp.bin_rep = dec_to_bin(minterms[j],variables);
                        tables[table_no].push_back(tmp);
                    }
                }
            }else{ // rest of the tables
                // match group with group+1 groups
                for (int j = 0; j < tables[table_no-1].size(); ++j) {
                    if(tables[table_no-1][j].group_no == group){
                        for (int k = 0; k < tables[table_no-1].size(); ++k) {
                            if(tables[table_no-1][k].group_no == group+1){
                                if(j == k) continue;
                                if(is_match(tables[table_no-1][j] , tables[table_no-1][k])){
                                    row tmp;
                                    tmp.group_no = group;
                                    tmp.match_pairs.insert(tmp.match_pairs.end(),all(tables[table_no-1][j].match_pairs));
                                    tmp.match_pairs.insert(tmp.match_pairs.end(),all(tables[table_no-1][k].match_pairs));
                                    tmp.bin_rep = get_bin_rep(tables[table_no-1][j] , tables[table_no-1][k]);
                                    tables[table_no].push_back(tmp);
                                    tables[table_no-1][j].has_pair = true;
                                    tables[table_no-1][k].has_pair = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int table_no = 0; table_no < variables; ++table_no) { // print ith table
        if(table_no != 0){
            cout close
            cout close
            cout close
        }
        sort(all(tables[table_no]));
        cout << "Table #" << table_no+1 << ":" close
        for (int i = 0; i < tables[table_no].size(); ++i) {
            if(i!=0 && tables[table_no][i-1].group_no != tables[table_no][i].group_no) cout close
            cout << tables[table_no][i].group_no << "\t " << print_vec(tables[table_no][i].match_pairs) << "\t " << tables[table_no][i].bin_rep << "\t " << tables[table_no][i].has_pair close
        }
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
