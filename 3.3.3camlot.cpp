/*
ID: messifo2
PROG: camelot
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <assert.h>
#include <cstdlib>

using namespace std;

typedef pair<int,int> PII; 

int rows,cols;
int kings[2];
bool vis[31][31];
vector<pair<int,int> > knights;

int dist[31][31][31][31];

int moves[8][2] = {{-2,1},{-1,2},{1,2},{2,1},
                 {2,-1}, {1,-2}, {-1,-2},{-2,-1}} ;
int ans;

void get_shortest_path(int x_pos, int y_pos) {
    queue<PII> q;
    q.push(PII(x_pos,y_pos));
    dist[x_pos][y_pos][x_pos][y_pos] = 0;
    while(!q.empty()) {
        PII cur = q.front();
        q.pop();
        for(int i = 0; i < 8; i++) {
            int new_i = cur.first + moves[i][0];
            int new_j = cur.second + moves[i][1];
            if(new_i >= 1 && new_i <=rows && new_j >= 1
                && new_j <= cols) {
                if(dist[x_pos][y_pos][new_i][new_j] == -1) {
                    dist[x_pos][y_pos][new_i][new_j] = 
                    dist[x_pos][y_pos][cur.first][cur.second] + 1;
                    q.push(PII(new_i,new_j));
                }
            }
        }
    }
}

// int abs(int i) {
//     return ( i > 0 ? i : (-i));
// }

int get_dist(int i, int j, int ii, int jj) {
    return max(abs(i-ii),abs(ii-jj));
}
void solve() {
    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= cols; j++) {
            int tmp_ans = 0;
            for(int k = 0; k < knights.size(); k++) {
                int tmp_i = knights[k].first;
                int tmp_j = knights[k].second;
                tmp_ans += dist[i][j][tmp_i][tmp_j];
            }
            // cout << "i = " << i << " j = " << j << " ans = " << tmp_ans << endl;
            if(tmp_ans > ans) continue;
            int king_cost = get_dist(i,j,kings[0],kings[1]);
            for(int ii = 1; ii <= rows; ii++) {
                for(int jj = 1; jj <= cols; jj++) {
                    int base_cost = get_dist(i,j,ii,jj);
                    // if(base_cost > king_cost ) continue;
                    for(int kk = 0; kk < knights.size(); kk++) {
                        int tmp_i = knights[kk].first;
                        int tmp_j = knights[kk].second;
                        int tmp_king_cost = base_cost + dist[ii][jj][i][j]
                        + dist[ii][jj][tmp_i][tmp_j] - dist[tmp_i][tmp_j][i][j];
                        king_cost = min(king_cost, tmp_king_cost);
                    }
                }
            }
            ans = min(ans, tmp_ans + king_cost);
        }
    }

}

int main()
{
    freopen("camelot.in","r",stdin);
    freopen("camelot.out","w",stdout);
    int i,j;
    cin >> rows >> cols;
    char row_num;
    int col_num;
    bool count_knight = false;
    while(scanf("%c",&row_num) != EOF) {
    	if(row_num >= 'A' && row_num <= 'Z'){
    		scanf("%d",&col_num);
    		if(count_knight == false) {
    			kings[0] = (1+row_num-'A');
    			kings[1] = col_num;
    			count_knight = true;
    		}
    		else{
    			knights.push_back(pair<int,int>((int)(1+row_num-'A'),col_num));
    		}
    	} 
    }
    memset(dist,-1,sizeof(dist));
    for(i = 1 ; i <= rows; i++) {
        for(j = 1; j <= cols; j++) {
            get_shortest_path(i,j);
        }
    }
    ans = 100000000;
    solve();
    cout << ans << endl;
    return 0;
}
