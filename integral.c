#include <emscripten.h>
#include <math.h>

#define EPSILON 0.0001
#define INCREMENT 100

double longAbs(double n) {
    if (n < 0) return -n;
    return n;
}

double f(double n) {
    return sin(n) + 1;
}

EMSCRIPTEN_KEEPALIVE
double integral(double lowerLimit, double upperLimit, double n) {
    double result1 = 0;
    double result2 = 0;

    while (longAbs(result2 - result1) > EPSILON || (!result1 && !result2)) {
        double perWidth = longAbs(upperLimit - lowerLimit) / n;
        double perHeight = (f(lowerLimit) + f(upperLimit)) / 2;
        double middleVariable;

        for (int i = 1; i < n; i++) {
            middleVariable = lowerLimit + i * perWidth;
            perHeight += f(middleVariable);
        }
        result1 = perWidth * perHeight;
        n += INCREMENT;
        perWidth = longAbs(upperLimit - lowerLimit) / n;
        perHeight = (f(lowerLimit) + f(upperLimit)) / 2;
        for (int i = 1; i < n; i++) {
            middleVariable = lowerLimit + i * perWidth;
            perHeight += f(middleVariable);
        }
        result2 = perWidth * perHeight;
        n += INCREMENT;
    }

    return result2;
}

EMSCRIPTEN_KEEPALIVE
int main() {
    for (double index = 2; index < 1003; index++) {
        integral(1, index, 10);
    }

    return 0;
}