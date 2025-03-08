#pragma once
#define __my_math__

double exp(double x, double eps = 1e-14);
double pow(double x, int n);
double ln(double x, double eps = 1e-18);
double ln_gr(double x, double eps = 1e-18);
double log(double base, double x, double eps = 1e-18);
double sqrt(double x, double eps = 1e-10);
double sin(double x, double eps = 1e-13);
double cos(double x, double eps = 1e-13);
double tg(double x, double eps = 1e-13);
double ctg(double x, double eps = 1e-13);
double sh(double x, double eps = 1e-13);
double ch(double x, double eps = 1e-13);