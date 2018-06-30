// CYK Algorithm

#include <bits/stdc++.h>
using namespace std;

ifstream in("date.in");

const int NMax = 310;
const int cuvMax = 1010;

int n, cnt, nrCuvinte;
string s, ss, start;

bool DP[NMax][NMax][110];
vector< string > cuvinte(cuvMax);
vector< pair< string, string > > productiiUnitate;
vector< pair< string, pair< string, string > > > productii;
unordered_map< string, int > uMap;

int main() {
    
    in >> n; in.get();

    for(int i = 1; i <= n; ++i) {
        getline(in, s);

        int nrTermeni = 0;
        for(auto it: s) {
            if(it == ' ') {
                nrTermeni++;
            }
        }

        if(nrTermeni == 1) {
            string lhs = "", rhs = "";

            int i = 0;
            for(i = 0; s[i] != ' '; ++i) {
                lhs += s[i];
            }
            for(++i; s[i]; ++i) {
                rhs += s[i];
            }
            
            productiiUnitate.push_back(make_pair(lhs, rhs));
            if(uMap[lhs] == 0) {
                uMap[lhs] = ++cnt;
            }
        } else {
            string lhs = "", mid = "", rhs = "";

            int i = 0;
            for(i = 0; s[i] != ' '; ++i) {
                lhs += s[i];
            }
            for(++i; s[i] != ' '; ++i) {
                mid += s[i];
            }
            for(++i; s[i]; ++i) {
                rhs += s[i];
            }

            productii.push_back(make_pair(lhs, make_pair(mid, rhs)));

            if(uMap[lhs] == 0) {
                uMap[lhs] = ++cnt;
            }
            if(uMap[mid] == 0) {
                uMap[mid] = ++cnt;
            }
            if(uMap[rhs] == 0) {
                uMap[rhs] = ++cnt;
            }
        }
    }

    in >> start; in.get();
    
    getline(in, ss);

    for(int i = 0; i < (int)ss.size(); ++i) {
        if(ss[i] == ' ') {
            nrCuvinte++;
            continue;
        }

        cuvinte[nrCuvinte] += ss[i];
    }
    nrCuvinte++;
    
    for(int i = 0; i < nrCuvinte; ++i) {
        for(auto prod: productiiUnitate) {
            if(prod.second == cuvinte[i]) {
                DP[1][i][uMap[prod.first]] = true;
            }
        }
    }

    for(int i = 2; i <= nrCuvinte; ++i) {
        for(int j = 0; j < nrCuvinte - i + 1; ++j) {
            for(int k = 1; k < i; ++k) {
                for(auto prod: productii) {
                    DP[i][j][uMap[prod.first]] |= (DP[k][j][uMap[prod.second.first]] && DP[i - k][j + k][uMap[prod.second.second]]);
                }
            }
        }
    }

    if(DP[nrCuvinte][0][uMap[start]] == true) {
        cout << "Propozitie ce apartine limbajului.\n";
    } else {
        cout << "Propozitia nu este acceptata de limbaj.\n";
    }
    
    in.close();

    return 0;
}
