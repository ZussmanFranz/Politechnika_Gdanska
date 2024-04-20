#include <iostream>

const int MAX_ITEMS = 15;

int main() {

    for (int a = 0; a < 500; a++) {
        int n, P[MAX_ITEMS], W[MAX_ITEMS], C;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> P[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> W[i];
        }
        std::cin >> C;

        int bestProfit = 0;

        for (int item = 0; item < (1 << n); ++item) {
            int WeightAttempt = 0;
            int ProfitAttempt = 0;

            for (int i = 0; i < n; ++i) {
                if (item & (1 << i)) {
                    WeightAttempt += W[i];
                    ProfitAttempt += P[i];
                }
            }
            if (WeightAttempt <= C && ProfitAttempt > bestProfit) {
                bestProfit = ProfitAttempt;
            }
        }

        std::cout << bestProfit << "\n";
    }

    return 0;
}