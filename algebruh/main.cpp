#include <iostream>
#include <string>
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
vector<vector<double>> matrix_container(int x, int y);
vector<vector<double>> create_id(int x, int y);
void transpose();
vector<vector<double>> flip_180(vector<vector<double>> m);
vector<vector<double>> transpose(vector<vector<double>> m);
void gauss();
vector<vector<double>> gauss_for_determinant(vector<vector<double>> m);
void determinant();
double determinant(vector<vector<double>> m);
vector<vector<vector<double>>> gauss_for_inversion(vector<vector<double>> m, vector<vector<double>> inv_m);
int inverse_matrix();
void save(vector<vector<double>> m);
vector<vector<double>> cleanup_matrix(vector<vector<double>> m);
vector<int64_t> to_fraction(double n);

int main(){
    create_matrix();
    //matrix = { {1 ,2, 4, 5, 8, 9}, {7, 6, 5, 3, 2, 5},{ 2, 4, 8, 5, 7, 8 },{6, 2, 5, 1, 2, 3 },{4, 5, 7, 8, 5, 9 },{6, 4, 1, 0, 2, 0} };
    for(;;){
        cout << "1. List the matrix in memory\n2. Gauss\n3. Determinant\n4. Transpose\n5. Invert matrix\n0. Type in new matrix\n";
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
        case '4':
            transpose();
            break;
        case '5':
            inverse_matrix();
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
    system("CLS");
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

vector<vector<double>> matrix_container(int x, int y) { //dokoncz
    vector<vector<double>> m = {};
    for (int i = 0; i < x; i++) {
        vector<double> row = {};
        for (int j = 0; j < y; j++) {
            row.push_back(0);
        }
        m.push_back(row);
    }
    return m; //do zmiany
}

vector<vector<double>> create_id(int x, int y) {
    vector<vector<double>> m = matrix_container(x,y);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (i == j) {
                m[i][j] = 1;
            }
        }
    }
    return m;
}

void transpose() {
    int x = i_dim;
    int y = j_dim;
    vector<vector<double>> trans_m = matrix_container(y,x);
    for (int i = 0; i < i_dim; i++) {
        for (int j = 0; j < j_dim; j++) {
            trans_m[j][i] = matrix[i][j];
        }
    }
    list_matrix(trans_m);
}

vector<vector<double>> flip_180(vector<vector<double>> m) {
    vector<vector<double>> flip_m = matrix_container(i_dim,j_dim);
    for (int i = 0; i < i_dim; i++) {
        for (int j = 0; j < j_dim; j++) {
            int x = i_dim - 1 - i;
            int y = j_dim - 1- j;
            flip_m[x][y] = m[i][j];
        }
    }
    return flip_m;
}

vector<vector<double>> transpose(vector<vector<double>> m) {
    vector<vector<double>> trans_m = m;
    for (int i = 0; i < i_dim; i++) {
        for (int j = 0; j < j_dim; j++) {
            trans_m[i][j] = m[j][i];
        }
    }
    return trans_m;
}

void gauss() {
    vector<vector<double>> m = matrix;


    for (int i = 0; i < (i_dim - 1); i++) {
        for (int j = i + 1; j <= (i_dim - 1); j++) {
            int swap_row_id = -1;
            if (m[i][i] == 0) {
                for (int k = i; k < i_dim - 1; k++) {
                    if (m[k][i] != 0) {
                        swap_row_id = k;
                        break;
                    }
                }
                if (swap_row_id != -1) {
                    vector<double> temp = m[i];
                    m[i] = m[swap_row_id];
                    m[swap_row_id] = temp;
                }
            }
            double ratio = m[j][i] / m[i][i];
            m[j] = add(scalar_mul(m[i], ratio * -1), m[j]);
        }

    }
    m = cleanup_matrix(m);
    list_matrix(m);
}

vector<vector<double>> gauss_for_determinant(vector<vector<double>> m){ //used to calculate the determinant, changes matrix_sign accordingly    
    for (int i = 0; i < (i_dim - 1); i++) {
        for (int j = i + 1; j <= (i_dim - 1); j++) {
            int swap_row_id = -1;
            if (m[i][i] == 0) {
                for (int k = i; k < i_dim - 1; k++) {
                    if (m[k][i] != 0) {
                        swap_row_id = k;
                        break;
                    }
                }
                if (swap_row_id != -1) {
                    vector<double> temp = m[i];
                    m[i] = m[swap_row_id];
                    m[swap_row_id] = temp;
                    matrix_sign *= -1;
                }
            }
            double ratio = m[j][i] / m[i][i];
            m[j] = add(scalar_mul(m[i], ratio * -1), m[j]);
        }

    }
    m = cleanup_matrix(m);
    return m;
}

void determinant(){
    vector<vector<double>> m = gauss_for_determinant(matrix);
    double det = 1.0;
    for(int i = 0;i<i_dim;i++){
        det *= m[i][i];
    }
    cout << "Determinant equals: " << det * matrix_sign<< "\n";
    matrix_sign = 1;
}

double determinant(vector<vector<double>> m) {
    m = gauss_for_determinant(m);
    double det = 1.0;
    for (int i = 0; i < i_dim; i++) {
        det *= m[i][i];
    }
    det *= matrix_sign;
    matrix_sign = 1;
    return det;
}

vector<vector<vector<double>>> gauss_for_inversion(vector<vector<double>> m, vector<vector<double>> inv_m) {
    int place = i_dim - 1;
    for (int i = 0; i < (i_dim - 1); i++) {
        for (int j = i + 1; j <= (i_dim - 1); j++) {
            int swap_row_id = -1;
            if (m[i][i] == 0) {
                for (int k = i; k < i_dim - 1; k++) {
                    if (m[k][i] != 0) {
                        swap_row_id = k;
                        break;
                    }
                }
                if (swap_row_id != -1) {
                    vector<double> temp = m[i];
                    m[i] = m[swap_row_id];
                    m[swap_row_id] = temp;

                    vector<double> temp_inv = inv_m[i];
                    inv_m[i] = inv_m[swap_row_id];
                    inv_m[swap_row_id] = temp_inv;
                }
            }
            double ratio = m[j][i] / m[i][i];
            m[j] = add(scalar_mul(m[i], ratio * -1), m[j]);
            inv_m[j] = add(scalar_mul(inv_m[i], ratio * -1), inv_m[j]);
        }

    }
    m = cleanup_matrix(m);
    inv_m = cleanup_matrix(inv_m);
    m = flip_180(m);
    inv_m = flip_180(inv_m);

    vector<vector<vector<double>>> return_vec = { m,inv_m };
    return return_vec;
}

int inverse_matrix() {
    if (determinant(matrix) == 0) {
        cout << "Inverse matrix doesnt exist when the determinant equals 0\n";
        return -1;
    }
    vector<vector<double>> m = matrix;
    vector<vector<double>> inv_m = create_id(i_dim,j_dim);

    for (int i = 0; i < 2; i++) {
        vector<vector<vector<double>>> matrix_vector = gauss_for_inversion(m, inv_m);
        m = matrix_vector[0];
        inv_m = matrix_vector[1];
    }

    for (int i = 0; i < i_dim; i++) {
        for (int j = 0; j < j_dim; j++) {
            double ratio = 0.0;
            if (i == j) {
                ratio = 1.0 / m[i][j];
                m[i] = scalar_mul(m[i],ratio);
                inv_m[i] = scalar_mul(inv_m[i], ratio);
            }
        }
    }
    m = cleanup_matrix(m);
    inv_m = cleanup_matrix(inv_m);

    list_matrix(inv_m);
    return 0;
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

vector<int64_t> to_fraction(double n) {
    int iter = 1000;
    int sign = 1;
    if (n < 0) {
        sign = -1;
    }

    string n_str = to_string(n);
    string before_decimal_str = "";
    string after_decimal_str = "0";
    bool passed_dot = 0;

    for (int i = 0; i < n_str.length(); i++) {
        if (n_str[i] == '.') {
            passed_dot = 1;
        };
        if (!passed_dot) {
            before_decimal_str.push_back(n_str[i]);
        }
        else {
            after_decimal_str.push_back(n_str[i]);
        }
    }

    int64_t before_decimal = stoll(before_decimal_str);
    double after_decimal = stod(after_decimal_str);
    if (after_decimal == 0) {
        return { (int64_t)n,1 };
    }
    before_decimal = abs(before_decimal);

    int64_t a = 0; // 
    int64_t b = 1; // representing fraction: 0/1

    int64_t c = 1; // 
    int64_t d = 1;  // representing fraction: 1/1

    int64_t pivot_a = a + c;
    int64_t pivot_b = b + d;

    for (int i = 0; i < iter; i++) {
        pivot_a = a + c;
        pivot_b = b + d;
        double pivot = (double)pivot_a / pivot_b;
        if (after_decimal > pivot) {
            a = pivot_a;
            b = pivot_b;
        }
        else if (after_decimal < pivot) {
            c = pivot_a;
            d = pivot_b;
        }

    }

    return { sign * (pivot_a + before_decimal * pivot_b),pivot_b };
}
