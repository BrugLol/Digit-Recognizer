#include <iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <queue>


using namespace std;

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

class neuron {
public:
    double weights[25];
    double bias = -2;


    neuron() {
        for (int ind = 0; ind < 25; ind++) {
            weights[ind] = 0;
        }
    }

    double calc(vector<vector <double>>& board) {
        double sum = 0;

        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {

                int index = y * 5 + x; //Turns board positions into valid index

                sum += board[y][x] * weights[index];
            }
        }

        sum += bias;
        return sigmoid(sum);
    }

    void train(vector<vector <double>>& nBoard, double target, double lr) {
        double error;
        
        error = target - calc(nBoard);

        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                int i = y * 5 + x;

                weights[i] += error * nBoard[y][x] * lr;
                
            }
        }


        bias += lr * error;
    }
    
};

void BFSBoard(vector<vector <int>> board, vector<vector <double>>& nBoard) {
    vector<vector <int>> DistanceBoard = board;
    queue<pair<int, int>> q;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            if (DistanceBoard[y][x] == 1)
            {

                DistanceBoard[y][x] = 0;
                q.push({y, x});
            }
            else
            {
                DistanceBoard[y][x] = 5;
            }
        }
    }

    while (!q.empty())
    {
        pair<int, int> current = q.front();

        int y = current.first;
        int x = current.second;

        q.pop();

        int dy[] = {+1, -1, 0, 0};
        int dx[] = {0, 0, +1, -1};

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 5 && ny >= 0 && nx < 5 && nx >= 0 && DistanceBoard[ny][nx] == 5)
            {
                DistanceBoard[ny][nx] = DistanceBoard[y][x] + 1;

                q.push({ny, nx});
            }
        }
    }

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {

            nBoard[y][x] = 1.0 / (1.0 + DistanceBoard[y][x]);
        }
    }

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            cout << nBoard[y][x] << " ";
        }
        cout << "\n";
    }
}

void epoch(vector<neuron>& n, vector<vector<vector<double>>>& allNoiseBoards) {
    for (int digit = 0; digit < 10; digit++) {
        for (int neuronId = 0; neuronId < 10; neuronId++) {
            double target = (neuronId == digit) ? 1.0 : 0.0;
            n[neuronId].train(allNoiseBoards[digit], target, 0.1);
        }
    }
}


int main() {


    vector<neuron> n(10);

    vector<vector <int>> board {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0}
    }; //Initiates board

    vector<vector <double>> NoiseBoard(5, vector<double>(5));
    BFSBoard(board, NoiseBoard);

    vector<vector<vector<int>>> digitBoards(10);

    digitBoards[0] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    digitBoards[1] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };

    digitBoards[2] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };

    digitBoards[3] = {
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0}
    };

    digitBoards[4] = {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };

    digitBoards[5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0}
    };

    digitBoards[6] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    digitBoards[7] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0}
    };

    digitBoards[8] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    digitBoards[9] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    vector<vector<vector<double>>> allNoiseBoards(10, vector<vector<double>>(5, vector<double>(5)));

    for (int d = 0; d < 10; d++) {
        BFSBoard(digitBoards[d], allNoiseBoards[d]);
    }

    for (int e = 0; e < 5000; e++) {
        epoch(n, allNoiseBoards);
    }

    int best = -1;
    double bestScore = -1;

    cout << "\n\n";
    cout << "================================  RESULTS ===============================\n";

    for (int i = 0; i < 10; i++) {
        double result = n[i].calc(NoiseBoard);
        cout << "  digit " << i << ": " << result << "\n";
        if (result > bestScore) { bestScore = result; best = i;}
    }

    cout << "best=" << best << ": confidence=" << bestScore << endl;

    

    //End
    std::cin.get();
    std::cin.ignore();
    return 0;
}