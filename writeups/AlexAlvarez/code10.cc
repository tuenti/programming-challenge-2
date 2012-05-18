ll toInt(string& s) {
    stringstream ss(s);
    ll x;
    ss >> x;
    return x;
}

int main() {
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        stack<BI> S;
        while (ss >> s) {
            if (isdigit(s[0])) { //Mete el numero en la pila
                BI x(s);
                S.push(x);
            }
            else if (s == "mirror") { //Cambia el signo del primero
                BI x;
                x = S.top();
                BI aux = -1;
                x *= aux;
                S.pop();
                S.push(x);
            }
            else if (s == "breadandfish") S.push(S.top()); //Replica el primero
            else if (s == "fire") S.pop(); //Hace pop
            else if (s == "dance") { //Hace swap a los dos primeros
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                S.push(a); S.push(b);
            }
            else if (s == "conquer") {
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                b %= a;
                S.push(b);
            }
            else if (s == "#") {
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                a *= b;
                S.push(a);
            }
            else if (s == "$") {
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                b -= a;
                S.push(b);
            }
            else if (s == "@") {
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                a += b;
                S.push(a);
            }
            else if (s == "&") { 
                BI a = S.top(); S.pop();
                BI b = S.top(); S.pop();
                b /= a;
                S.push(b);
            }
            else if (s == ".") {
                BI aux = S.top();
                cout << aux << endl;
                S.pop();
            }
        }
    }
}