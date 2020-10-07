

#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include <iostream>
#include <iomanip>

using namespace std;
int n, m, js, jl, jk, maxnum, maxline, flag=0;
double a[110][110], multi, ans[110], num;
const double EPS=1e-7;//精度处理

char alphabet[26];

void initAlphabet(){
    for(int i = 1; i <= 26; i++){
        alphabet[i] = 'a'+(i-1);
    }
}

void intputArr(){
    
    
    string delimiter = ",";
    
    cout << "请输入方程组个数：";
    cin >> n;
    
    string inputline;// = "1,2,3,4,5";;
    
    for(int i = 1; i <= n; i++){
        cout << "请输入第 " << i << " 方程以及和," << "共 " <<n+1<<" 个数," <<"以空格分隔:"<< endl;
        cin >> inputline;
        inputline.append(delimiter);
        size_t pos = 0;
        string token;
        
        // 列数比方程组个数大1
        int columnCount = 1;
        
        while ((pos = inputline.find(delimiter)) != string::npos) {
            token = inputline.substr(0, pos);
            if(token.length()==0) continue;
            a[i][columnCount++] = stod(token);
            inputline.erase(0, pos + delimiter.length());
        }
        if(n+2 != columnCount){
            cout << "输入的个数不符合, 请重新输入，期望个数为：" << n+1 << endl;
            i--;
            continue;
        }
    }
}

void printArr(){
    
    initAlphabet();
    
    cout << endl << "您输入的方程组为：" <<  endl;
    int row = n;
    int column = n + 1;
    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= column; j++){
            cout << a[i][j];
            if(j < column) cout << alphabet[j];
            if(j < column-1) cout << " + ";
            if(j == column-1) cout << " = ";
            
        }
        cout << endl;
    }
    cout << endl;
}

void yordan(){
    
    //从左到右枚举第i列(即枚举主元列)
    for(int i = 1; i <= n; i++) {
        maxnum=0;maxline=0;
        for(int j = i; j<=n; j++) {
            if(fabs(a[j][i]) > maxnum) {
                maxnum = fabs(a[j][i]);
                maxline = j;
            }
        }
        
        //寻找第i列中系数绝对值最大的一行
        //其与第i行交换，保证第i行第i列不为0（即保证主元系数不为0）；
        if(maxnum < EPS) {
            flag = 1;
            break;
        }
        //判断第i列上的系数是否全为0，若是，则方程无解或存在多解
        //直接特判flag=1输出"No Solution"
        
        swap(a[i], a[maxline]);
        
        for(int j = 1; j <= n; j++) {
            if(j != i) {
                if(a[j][i] == 0) continue;
                else multi= a[j][i] / a[i][i];
                for(int k = i; k <= n+1; k++) {
                    a[j][k] -= a[i][k] * multi;
                }
            }
        }
        //通过初等行变化(即减去第i行的某个倍数)，我们将除第i行的第i列都变成0；
    }
    
    if(flag == 1) {
        printf("No Solution");
        exit(0);
    }
    
    //直接算出答案
    for(int i = n; i >= 1; i--) {
        ans[i] = a[i][n+1] / a[i][i];
    }
    
    cout<< endl << "方程组的解为：" << endl;
    for(int i = 1; i <=n; i++){
        cout << alphabet[i] << " = " << setprecision(5) << ans[i] << endl;
    }
    cout << endl;
}


int main() {
    
    string flag = "";
    
    while(1) {
    
        intputArr();

        printArr();
        
        yordan();
        
        cout << "是否继续解方程组（y/n）：";
        cin >> flag;
        
        if(flag == "n"){
            break;
        }
        
    }
    
    return 0;
}
