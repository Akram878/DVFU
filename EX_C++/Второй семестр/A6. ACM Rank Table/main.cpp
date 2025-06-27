#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Submission {
    int time;
    int result;
};

struct Team {
    int id;
    int solved = 0;
    int total_time = 0;
    map<int, vector<Submission>> submissions;
};


void sort_submissions(vector<Submission>& runs) {
    int n = runs.size();
    for (int i = 0; i < n; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (runs[j].time < runs[min_idx].time)
                min_idx = j;
        }
        swap(runs[i], runs[min_idx]);
    }
}


void sort_teams(vector<Team>& teams) {
    int n = teams.size();
    for (int i = 0; i < n; ++i) {
        int best = i;
        for (int j = i + 1; j < n; ++j) {
            if (teams[j].solved > teams[best].solved) {
                best = j;
            } else if (teams[j].solved == teams[best].solved) {
                if (teams[j].total_time < teams[best].total_time) {
                    best = j;
                } else if (teams[j].total_time == teams[best].total_time && teams[j].id < teams[best].id) {
                    best = j;
                }
            }
        }
        swap(teams[i], teams[best]);
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int C, N;
    fin >> C >> N;

    vector<Team> teams(C);
    for (int i = 0; i < C; ++i) {
        teams[i].id = i + 1;
    }

    for (int i = 0; i < N; ++i) {
        int ci, pi, ti, ri;
        fin >> ci >> pi >> ti >> ri;
        teams[ci - 1].submissions[pi].push_back({ti, ri});
    }

    for (int i = 0; i < C; ++i) {
        for (auto& entry : teams[i].submissions) {
            vector<Submission>& runs = entry.second;

            sort_submissions(runs);  // فرز يدوي للمحاولات حسب الوقت

            int penalty = 0;
            for (Submission run : runs) {
                if (run.result == 1) {
                    teams[i].solved += 1;
                    teams[i].total_time += run.time + penalty;
                    break;
                } else {
                    penalty += 20 * 60;
                }
            }
        }
    }

    sort_teams(teams);

    for (int i = 0; i < C; ++i) {
        fout << teams[i].id;
        if (i < C - 1) fout << " ";
    }
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}
