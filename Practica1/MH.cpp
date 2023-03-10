
#include <iostream>
#include <list>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------------------------------*/
//Source: www.rookieslab.com - Ravi Ojha
vector<int> extended_euclid_gcd(int a, int b) {
    // Returns a vector `result` of size 3 where:
    // Referring to the equation ax + by = gcd(a, b)
    //     result[0] is gcd(a, b)
    //     result[1] is x
    //     result[2] is y 
    
    int s = 0; int old_s = 1;
    int t = 1; int old_t = 0;
    int r = b; int old_r = a;

    while(r != 0) {
        int quotient = old_r/r;
        // We are overriding the value of r, before that we store it's current
        // value in temp variable, later we assign it to old_r
        int temp = r;
        r = old_r - quotient*r;
        old_r = temp;

        // We treat s and t in the same manner we treated r
        temp = s;
        s = old_s - quotient*s;
        old_s = temp;

        temp = t;
        t = old_t - quotient*t;
        old_t = temp;
    }
    vector<int> result;
    result.push_back(old_r);
    result.push_back(old_s);
    result.push_back(old_t);
    return result;
}

int modulo_multiplicative_inverse(int A, int M) {
    // Assumes that A and M are co-prime
    // Returns multiplicative modulo inverse of A under M
    
    // Find gcd using Extended Euclid's Algorithm
    vector<int> v = extended_euclid_gcd(A, M);
    int gcd = v[0];
    int x = v[1];
    int y = v[2]; // We don't really need this though

    // In case x is negative, we handle it by adding extra M
    // Because we know that multiplicative inverse of A in range M lies
    // in the range [0, M-1]
    if(x < 0) {
        x += M;
    }
    
    return x;
}

/*----------------------------------------------------------------------------*/

std::vector<int> calcular_V(std::vector<int> m, int w, int N){
    std::vector<int> solucion;
    int valor;
    int w_inversa = modulo_multiplicative_inverse(w, N);

    for (unsigned int i=0; i< m.size(); i++){
        valor = (m[i] * w_inversa) % N;
        solucion.push_back(valor);
    }

    return solucion;
}

std::vector<int> calcular_A(std::vector<int> e, int w, int N){
    std::vector<int> solucion_A;
    int valor;

    for (unsigned int i=0; i< e.size(); i++){
        valor = (e[i] * w) % N;
        solucion_A.push_back(valor);
    }

    return solucion_A;
}

std::vector<int> cifrar(string M, std::vector<int> e, int N, int w, std::map<char, std::vector<int>> cod_bin){
    
    int tmp;
    std::vector<int> res;
    std::vector<int> a = calcular_A(e, w, N);

    for (unsigned int i=0; i<M.size(); i++){

        tmp = 0;
        for (unsigned int j=0; j< a.size(); j++){
            tmp += (cod_bin[(M[i])])[j] * a[j] ;
        }
        res.push_back(tmp);
        
    }

    return res;
}

std::list<std::list<int>> descifrar (std::vector<int> e, std::vector<int> m, int w, int N) {
    //Declaramos el resultado y variables
    std::list<std::list<int>> M;
    int n = e.size();
    std::list<int> tmp;

    std::vector<int> v = calcular_V(m, w, N);

    //Desciframos usando el problema de la mochila
    for (unsigned int i=0; i<v.size(); i++){
        int restante = v[i];
        for (unsigned int j=0; j<n; j++){
            if (e[n-1-j] <= restante){
                tmp.push_front(1);
                restante = restante - e[n-1-j];
            } else {
                tmp.push_front(0);
            }
        }
        M.push_back(tmp);
        tmp.clear();
    }
    return M;
}

void mostrar_msg(std::list<std::list<int>> M, std::map<char, std::vector<int>> cod_bin){

    for (auto i : M){
        std::vector<int> tmp{ std::begin(i), std::end(i) };
        for (auto e : cod_bin){
            if (e.second == tmp){
                cout<<e.first;
            }
        }
    }

    cout <<"\n";
    
}

int main(){
    
    std::vector<int> e = {2, 3, 7, 15, 31};
    std::map<char, std::vector<int> > cod_bin;
    int N = 61;
    int w = 17;

    cod_bin['A'] = {0, 0, 0, 0, 1};
    cod_bin['B'] = {0, 0, 0, 1, 0};
    cod_bin['C'] = {0, 0, 0, 1, 1};
    cod_bin['D'] = {0, 0, 1, 0, 0};
    cod_bin['E'] = {0, 0, 1, 0, 1};
    cod_bin['F'] = {0, 0, 1, 1, 0};
    cod_bin['G'] = {0, 0, 1, 1, 1};
    cod_bin['H'] = {0, 1, 0, 0, 0};
    cod_bin['I'] = {0, 1, 0, 0, 1};
    cod_bin['J'] = {0, 1, 0, 1, 0};
    cod_bin['K'] = {0, 1, 0, 1, 1};
    cod_bin['L'] = {0, 1, 1, 0, 0};
    cod_bin['M'] = {0, 1, 1, 0, 1};
    cod_bin['N'] = {0, 1, 1, 1, 0};
    cod_bin['O'] = {0, 1, 1, 1, 1};
    cod_bin['P'] = {1, 0, 0, 0, 0};
    cod_bin['Q'] = {1, 0, 0, 0, 1};
    cod_bin['R'] = {1, 0, 0, 1, 0};
    cod_bin['S'] = {1, 0, 0, 1, 1};
    cod_bin['T'] = {1, 0, 1, 0, 0};
    cod_bin['U'] = {1, 0, 1, 0, 1};
    cod_bin['V'] = {1, 0, 1, 1, 0};
    cod_bin['W'] = {1, 0, 1, 1, 1};
    cod_bin['X'] = {1, 1, 0, 0, 0};
    cod_bin['Y'] = {1, 1, 0, 0, 1};
    cod_bin['Z'] = {1, 1, 0, 1, 0};
    cod_bin[' '] = {1, 1, 0, 1, 1};

    string msg = "ESE TELEFONO PARECE CARPINTERO PORQUE ASERIN";

    std::vector<int> m = cifrar(msg, e, N, w, cod_bin);

    std::list<std::list<int>> M = descifrar(e, m, w, N);

    mostrar_msg(M, cod_bin);
}




