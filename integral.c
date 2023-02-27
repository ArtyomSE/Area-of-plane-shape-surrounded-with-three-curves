#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define eps1_0 0.0001           //Значение эпсилон для вычисления корня
#define eps2_0 0.0001           //Значение эпсилон для вычисления определённого интеграла
#define a0 -4.1                 //Левая граница отрезка
#define b0 -0.3                 //Правая граница отрезка

typedef double afunc(double);

//Счётчик числа итераций, потребовавшихся на приближенное решение уравнения
int count;

double root(afunc *, afunc *, double, double, double, afunc *, afunc *);

double integral(afunc *, double, double, double);

double f1(double);
 
double f2(double);

double f3(double);

double f_1(double);

double f_2(double);

double f_3(double);

int main(int argc, char **argv) {
    if (argc == 1) {
        double x1 = root(f1, f3, a0, b0, eps1_0, f_1, f_3);
        double x2 = root(f2, f3, a0, b0, eps1_0, f_2, f_3);
        double x3 = root(f1, f2, a0, b0, eps1_0, f_1, f_2);
        double I1 = integral(f1, x1, x3, eps2_0);
        double I2 = integral(f2, x2, x3, eps2_0);
        double I3 = integral(f3, x1, x2, eps2_0);
        printf("Площадь фигуры = %lf\n", I1 - I2 - I3);
    } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("-h --help (вывод доступных ключей)\n"
        "-r --root (вывод абсцисс точек пересечения функций f1, f2, f3)\n"
        "-i --iterations\n (вывод определённых интегралов функций f1, f2, f3 с пределами, "
        "равными абсциссам точек перессечения функций друг с другом)"
        "-R --test-root (вывод результатов проверки работы функции root)\n"
        "-I --test-integral (вывод результатов проверки работы функции integral)\n");
    } else if (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-r") == 0) {
        printf("Точка пересечений функций f1 и f2: %lf\n", root(f1, f2, a0, b0, eps1_0, f_1, f_2));
        printf("Точка пересечений функций f1 и f3: %lf\n", root(f1, f3, a0, b0, eps1_0, f_1, f_3));
        printf("Точка пересечений функций f2 и f3: %lf\n", root(f2, f3, a0, b0, eps1_0, f_2, f_3));
    } else if (strcmp(argv[1], "--iterations") == 0 || strcmp(argv[1], "-i") == 0) {
        root(f1, f2, a0, b0, eps1_0, f_1, f_2);
        printf("Количество итераций, потребовавшихся на приближенное решение уравнения f1 = f2: %d\n", count);
        root(f1, f3, a0, b0, eps1_0, f_1, f_3);
        printf("Количество итераций, потребовавшихся на приближенное решение уравнения f1 = f3: %d\n", count);
        root(f2, f3, a0, b0, eps1_0, f_2, f_3);
        printf("Количество итераций, потребовавшихся на приближенное решение уравнения f2 = f3: %d\n", count);
    } else if (strcmp(argv[1], "--test-root") == 0 || strcmp(argv[1], "-R") == 0) {
        int f_num1, f_num2;
        double a, b, eps1, res;
        sscanf(*(argv + 2), "%d:%d:%lf:%lf:%lf:%lf", &f_num1, &f_num2, &a, &b, &eps1, &res);
        afunc *F1 = NULL, *F2 = NULL, *F_1 = NULL, *F_2 = NULL;
        switch (f_num1) {
            case 1:
                F1 = f1;
                F_1 = f_1;
                break;
            case 2:
                F1 = f2;
                F_1 = f_2;
                break;
            case 3:
                F1 = f3;
                F_1 = f_3;
                break;
            default: printf("Недопустимый номер функции\n");
        }
        switch (f_num2) {
            case 1:
                F2 = f1;
                F_2 = f_1;
                break;
            case 2:
                F2 = f2;
                F_2 = f_2;
                break;
            case 3:
                F2 = f3;
                F_2 = f_3;
                break;
            default: printf("Недопустимый номер функции\n");
        }
        double answer = root(F1, F2, a, b, eps1, F_1, F_2);
        if (fabs(answer - res) < eps1) {
            printf("Корень посчитан верно\n");
        } else {
            printf("Корень посчитан неверно\n");
        }
        printf("Абсолютная ошибка = %lf\n", answer - res);
        printf("Относительная ошибка = %lf\n", (answer - res) / res);
    } else if (strcmp(argv[1], "--test-integral") == 0 || strcmp(argv[1], "-I") == 0) {
        int f_num;
        double a, b, eps2, res;
        sscanf(*(argv + 2), "%d:%lf:%lf:%lf:%lf", &f_num, &a, &b, &eps2, &res);
        afunc *F = NULL;
        if(f_num == 1) {
            F = f1;
        } else if (f_num == 2) {
            F = f2;
        } else if(f_num == 3) {
            F = f3;
        }
        double answer = integral(F, a, b, eps2);
        if(fabs(answer - res) < eps2) {
            printf("Интеграл посчитан верно\n");
        } else {
            printf("Интеграл посчитан неверно\n");
        }
        printf("Абсолютная ошибка = %lf\n", answer - res);
        printf("Относительная ошибка = %lf\n", (answer - res) / res);
    }

    return 0;
}

double root(afunc *f, afunc *g, double a, double b, double eps1, afunc *f_, afunc *g_) {
    double Fa = f(a) - g(a);
    double Fb = f(b) - g(b);
    double Fab = f((a + b) / 2) - g((a + b) / 2);
    count = 0;
    if(Fa * Fb <= 0) {
        double d;
        // if F'(x) * F"(x) > 0:
        if ((Fa < 0 && Fab <= (Fa + Fb) / 2) || (Fa > 0 && Fab > (Fa + Fb) / 2)) {
            d = b;
            double Fd = f(d) - g(d);
            double F_d = f_(d) - g_(d);
            double Fde = f(d - eps1) - g(d - eps1);
            while (Fd * Fde >= 0) {
                d = d - Fd / F_d;
                Fd = f(d) - g(d);
                F_d = f_(d) - g_(d);
                Fde = f(d - eps1) - g(d - eps1);
                ++count;
            }
        } else {
            d = a;
            double Fd = f(d) - g(d);
            double F_d = f_(d) - g_(d);
            double Fde = f(d - eps1) - g(d - eps1);
            while (Fd * Fde >= 0) {
                d = d - Fd / F_d;
                Fd = f(d) - g(d);
                F_d = f_(d) - g_(d);
                Fde = f(d - eps1) - g(d - eps1);
                ++count;
            }
        }
        return d;
    } else {
        printf("На отрезке [a; b] корней нет\n");
        return 0;
    }
}

double integral(afunc *f, double a, double b, double eps2) {
    double In, F, f_n;
    double n0 = 20;
    double I2n = 0;
    double h = (b - a) / n0;
    I2n += 0.5 * f(a);
    for (int i = 1; i < n0; i++) {
        I2n += f(a + i * h);
    }
    f_n = f(a + n0 * h);
    I2n += 0.5 * f_n;
    F = I2n + 0.5 * f_n;
    I2n *= h;
    do {
        In = I2n;
        I2n = F;
        n0 *= 2;
        h = (b - a) / n0;
        for (int i = 1; i < n0; i++) {
            if(i % 2 != 0) {
                I2n += f(a + i * h);
            }
        }
        f_n = f(a + n0 * h);
        I2n -= 0.5 * f(a + n0 * h);
        F = I2n + 0.5 * f_n;
        I2n *= h;
    } while (fabs(In - I2n) / 3 >= eps2);
    return I2n;
}
