//TODO odwracanie macierzy, sprawdzanie rzedu, jadro i obraz
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

vector<vector<double>> matrix = {};
int i_dim = 0;
int j_dim = 0;
int matrix_sign = 1;


vector<double> add(vector<double> v, vector<double> u);
vector<double> scalar_mul(vector<double> v, double x);
void list_matrix();
void list_matrix(vector<vector<double>> m);
void create_matrix();
void gauss();
vector<vector<double>> gauss(vector<vector<double>> m);
void determinant();
void save(vector<vector<double>> m);
vector<vector<double>> cleanup_matrix(vector<vector<double>> m);

int main(){
    create_matrix();
    for(;;){
        cout << "1. List the matrix in memory\n2. Gauss\n3. Determinant\n0. Type in new matrix\n";
        char inp;
        cout << ">";
        cin >> inp;
        cout << "\n";
        switch (inp)
        {
        case '1':
            list_matrix();
            break;
        case '2':
            gauss();
            break;
        case '3':
            determinant();
            break;
        case '0':
            create_matrix();
            break;
        default:
            break;
        }
        cout << "\n";
    }
    return 0;
}

vector<double> add(vector<double> v, vector<double> u){
    for(int i = 0; i < v.size();i++){
        v[i] += u[i];
    }
    return v;
}

vector<double> scalar_mul(vector<double> v, double x){
    for (int i = 0; i < v.size();i++){
        v[i] *= x;
    }
    return v;
}

void list_matrix(){
    for(vector<double> row : matrix){
        for(double element : row){
            cout << element << " ";
        }
        cout << "\n";
    }
}

void list_matrix(vector<vector<double>> m){
    for(vector<double> row : m){
        for(double element : row){
            cout << element << " ";
        }
        cout << "\n";
    }
}

void create_matrix(){
    cout << "Type in matrix dimensions: IxJ \n";
    cout << "I > ";
    cin >> i_dim;
    cout << "J > ";
    cin >> j_dim;
    system("CLS");
    vector<vector<double>> m = {};
    for(int i = 0; i < i_dim;i++){
        cout << "row " << i+1 << "\n";
        vector<double> row = {};
        for(int j = 0; j < j_dim;j++){
            cout << "> ";
            double temp = 0.0;
            cin >> temp;
            row.push_back(temp);
        }
        m.push_back(row);
        system("CLS");
    }
    matrix = m;
}

void gauss() {
    vector<vector<double>> m = matrix;

    int place = i_dim - 1;
    for (int i = 0; i < (i_dim - 1); i++) {
        for (int j = i_dim - 1; j > i; j--) {
            if (m[i][i] == 0) {
                vector<double> temp = m[i];
                m[i] = m[place];
                m[place] = temp;
                place -= 1;
            }
            double ratio = m[j][i] / m[i][i];
            m[j] = add(scalar_mul(m[i], ratio * -1), m[j]);
        }
        place = i_dim - 1;
    }
    m = cleanup_matrix(m);
    list_matrix(m);
}

//void gauss(){
//    vector<vector<double>> m = matrix;
//
//
//    for(int i = 0;i<(i_dim - 1);i++){
//        for(int j = i_dim - 1; j > i; j--){ 
//            double ratio = m[j][i]/m[i][i];
//            m[j] = add(scalar_mul(m[i],ratio*-1),m[j]);
//        }
//    }
//    list_matrix(m);
//}

vector<vector<double>> gauss(vector<vector<double>> m){ //used to calculate the determinant, changes matrix_sign accordingly

    int place = i_dim - 1;
    for (int i = 0; i < (i_dim - 1); i++) {
        for (int j = i_dim - 1; j > i; j--) {
            if (m[i][i] == 0) {
                vector<double> temp = m[i];
                m[i] = m[place];
                m[place] = temp;
                place -= 1;
                matrix_sign *= -1;
            }
            double ratio = m[j][i] / m[i][i];
            m[j] = add(scalar_mul(m[i], ratio * -1), m[j]);
        }
        place = i_dim - 1;
    }
    m = cleanup_matrix(m);
    return m;
}

void determinant(){
    vector<vector<double>> m = gauss(matrix);
    double det = 1.0;
    for(int i = 0;i<i_dim;i++){
        det *= m[i][i];
    }
    cout << "Determinant equals: " << det * matrix_sign<< "\n";
    matrix_sign = 1;
    
}

void save(vector<vector<double>> m){
    matrix = m;
}

vector<vector<double>> cleanup_matrix(vector<vector<double>> m) {
    for (int i = 0; i < i_dim; i++) {
        for (int j = 0; j < j_dim; j++) {
            if (isnan(m[i][j])) {
                m[i][j] = 0;
            }
        }
    }
    return m;
}
