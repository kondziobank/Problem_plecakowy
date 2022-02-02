#include <stdio.h>
#include <stdlib.h>

int algorytm_dynamiczny(const int C, const int n, const int *w, const int *p)
{
    //dynamiczna alokacja pamieci
    int **DP = malloc(sizeof(int*) * (n+1));
    for(int i = 0; i <= n; i++){
        DP[i] = malloc(sizeof(int) * (C+1));
        DP[i][0] = 0;
    }
    for(int i = 0; i <= C; i++)
        DP[0][i] = 0;

    //algorytm dynamiczny
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= C; j++){

            DP[i][j] = DP[i-1][j];
            if(w[i-1] <= j && DP[i][j] < p[i-1] + DP[i-1][j - w[i-1]])
                DP[i][j] = p[i-1] + DP[i-1][j - w[i-1]];
        }
    }

    //zwolnienie pamieci zaalokowanej dynamicznie
    int wynik = DP[n][C];
    for(int i = 0; i <= n; i++)
        free(DP[i]);
    free(DP);

    return wynik;
}

int brute_force(const int C, const int n, const int *w, const int *p){

    //liczba kombinacji
    int zapis = 0;
    int permutacje = (1 << n);

    //sprawdz wszystkie kombinacje
    for(int i = 0; i <= permutacje; i++){

        int suma_wagi = 0;
        int suma_zysku = 0;

        //oblicz wartosc pojedynczego zestawu
        for(int j = 0; j < n; j++)
            if(i & (1 << j)){
                suma_wagi += w[j];
                suma_zysku += p[j];
            }

        //sprawdz czy jest najlepszy
        if(suma_wagi <= C && suma_zysku > zapis)
            zapis = suma_zysku;
    }

    return zapis;
}

int main(){

    int n, C, *w, *p;

    //wczytaj liste przedmiotow z pliku
    FILE *input = fopen("przedmioty.txt", "r");
    fscanf(input, "%d%d", &n, &C);

    w = malloc(sizeof(int) * n);
    p = malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++)
        fscanf(input, "%d%d", p + i, w + i);

    fclose(input);

    //algorytm dynamiczny
    printf("Algorytm dynamiczny: %d\n", algorytm_dynamiczny(C, n, w, p));

    //algorytm brute force
    printf("Algorytm brute force: %d\n", brute_force(C, n, w, p));

    //zwolnienie pamieci zaalokowanej dynamicznie
    free(w);
    free(p);

    return 0;
}