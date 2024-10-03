#include <iostream>

double sqRoot(double n){
    const double E = 1E-15;
    double x = 1;
    double nx, val, ab_val;

    while(true){
        nx = (x + n / x) / 2;
        val = x - nx;

        if(val<0){
            ab_val = nx - x;
        }
        else{
            ab_val = (x-nx);
        }
        if(ab_val < E){ 
            break;
        }

        x=nx;
    }

    return x;
}

int main() {
    std::cout << sqRoot(14);
    return 0;
}