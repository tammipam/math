#include "s21_math.h"

// вычисляет абсолютное значение целого числа
long int s21_abs(int x) {
  if (x < 0)
    x *= -1;
  return x;
}

// вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(long double x) {
  if (x < 0)
    x *= -1;
  return x;
}

// функция delete проверяет на принадлежность к области определения
double delete (double x) {
  while (x > s21_PI || x < -s21_PI) {
    x += x > s21_PI ? -2 * s21_PI : 2 * s21_PI;
  }
  return x;
}

// вычисляет синус
long double s21_sin(double x) {
  x = delete (x);
  long double result = x, y = x;
  long double i = 1.;
  while (s21_fabs(result) > s21_EPS) {
    result = -1 * result * x * x / (2 * i * (2 * i + 1));
    i += 1.;
    y += result;
  }
  return y;
}

// вычисляет косинус, используется формула приведения
long double s21_cos(double x) {
  x = delete (x);
  return s21_sin((s21_PI / 2.0) - x);
}

// вычисляет тангенс
long double s21_tan(double x) {
  x = delete (x);
  return s21_sin(x)/s21_cos(x);
}

// вычисляет арксинус
long double s21_asin(double x) {
  long double result = x, y = x;
  long double i = 1;
  while (s21_fabs(result) > s21_EPS) {
    if (x < -1 || x > 1) {
      y = s21_NAN;
      break;
    }
    if (x == 1 || x == -1) {
      y = s21_PI / 2 * x;
      break;
    }
    result *=
        x * x * (2 * i - 1) * (2 * i) * (2 * i - 1) / ((2 * i + 1) * 4 * i * i);
    i += 1;
    y += result;
  }
  return y;
}

// вычисляет арккосинус через формулу арксин+арккос=пи/2
long double s21_acos(double x) {
  if (x <= 1 && x >= -1) {
    x = s21_PI / 2. - s21_asin(x);
  } else {
    x = s21_NAN;
  }
  return x;
}

// вычисляет арктангенс
long double s21_atan(double x) {
    long double y = 0;
    y = (x < 1 && x > -1) ? common(x): y;
    y =  x == 1 ? s21_PI / 4: x == -1 ? s21_NPI / 4: x == 0 ? 0: y;
    y = x > 1 ? s21_PI / 2 - common(1 / x): x < -1 ? s21_NPI/2 - common(1 / x): y;
    return y;
}

// проверяет включение в область определения арктангенса
long double common(double x) {
  long double result = x, y = x, i = 1;
  while (s21_fabs(result) > s21_EPS) {
    result = -1 * result * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1;
    y += result;
  }
  return y;
}

// возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x) {
  int i;
  double y = x < 0 ? -x : x;
  for (i = 0; i < y; i++) {
  }
  return x < 0 ? -i + 1 : i;
}

// возвращает значение e, возведенное в заданную степень
long double s21_exp(double x) {
  long double result = 1, y = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(result) > s21_EPS) {
    result *= x / i;
    i += 1;
    y += result;
    if (y > s21_MAX_double) {
      y = s21_INF;
      break;
    }
  }
  y = flag == 1 ? y > s21_MAX_double ? 0 : 1. / y : y;
  return y = y > s21_MAX_double ? s21_INF : y;
}

// возвращает ближайшее целое число, не превышающее заданное значение
long double s21_floor(double x) {
  int i;
  double y = x < 0 ? -x : x;
  for (i = 0; i < y; i++) {
  }
  return x < 0 ? -i : x == 0 ? 0 : i - 1;
}

// остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y) {
  long double result = s21_fabs(x);
  y = s21_fabs(y);
  int i = 1;
  while (result > y) {
    result = s21_fabs(x) - y * i;
    i++;
  }
  return x < 0 ? -result : result;
}

// вычисляет натуральный логарифм
long double s21_log(double x) {
  long double y;
  return y = (x > 0 && x < 2) ? log_0_2(x) : log_other(x);
}

// возводит число в заданную степень
long double s21_pow(double base, double exp) {
  long double result;
  result = s21_exp(exp * s21_log(base));
  return result;
}

// вычисляет квадратный корень
long double s21_sqrt(double x) {
  long double result = 4, y = 0;
  while (s21_fabs(result - y) > s21_EPS) {
    if (x < 0) {
      result = s21_N_NAN;
      break;
    }
    y = result;
    result = (y + x / y) / 2;
  }
  return result;
}

// вычисляет десятичный логарифм
long double log_0_2(double x) {
  x--;
  long double result = x, y = x;
  long double i = 2;
  while (s21_fabs(result) > s21_EPS) {
    result *= -x * (i - 1) / i;
    i += 1;
    y += result;
  }
  return y;
}

// вычисляет остальные логарифмы по формуле
long double log_other(double x) {
  struct aboba zena;
  algorithm(x, &zena);
  x = zena.mantisa * zena.sign / 10;
  long double result;
  result = x < 0    ? s21_N_NAN
           : x == 0 ? s21_NINF
                    : log_0_2(x) + (zena.e + 1) * s21_LN10;
  return result;
}

// переводит значения с помощью структуры
void algorithm(double x, struct aboba *zena) {
  long double i = 1;
  int es = 0;
  zena->sign = x < 0 ? -1 : 1;
  x *= zena->sign;
  if (x >= 10) {
    while (x >= 10) {
      x /= 10.;
      i *= 10;
      es++;
    }
  } else if (x < 1 && x > 0) {
    while (x < 1) {
      x *= 10;
      i /= 10;
      es--;
    }
  }
  zena->mantisa = x;
  zena->pow = i;
  zena->e = es;
}
