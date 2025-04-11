#include <iostream>
#include <dirent.h>
#include <sstream>
#include <functional>

using namespace std;

typedef function<int(stringstream &in, stringstream &out)> CommandFun;

class Command {
private:
    CommandFun fun;
public:
    void set_fun(CommandFun &&_fun) {
        fun = _fun;
    }
    Command &operator | (Command &&o) {
        auto prev = fun;
        fun = [prev, o](stringstream &in, stringstream &out) -> int {
            prev(in, out);
            in.str(out.str());
            out.str("");
            return o(in, out);
        };
        return *this;
    }
    int operator() (stringstream &in, stringstream &out) const {
        return fun(in, out);
    }
};

Command muestra_contenido_de(const string &a_carpeta) {
    Command detached;
    detached.set_fun([a_carpeta](stringstream &in, stringstream &out) -> int {
        DIR *carpeta;
        struct dirent *archivo;
        carpeta = opendir(a_carpeta.c_str());
        if (carpeta != NULL) {
            while ((archivo = readdir(carpeta)))
                out << archivo->d_name << '\n';
            closedir(carpeta);
        } else {
            perror("Error al abrir el directorio");
        }
        return 0;
    });
    return detached;
}

Command busca_nombre(const string &expr) {
    Command detached;
    detached.set_fun([expr](stringstream &in, stringstream &out) -> int {
        string filename;
        while (getline(in, filename)) {
            if (filename.contains(expr)) {
                out << filename << "\n";
            }
        }
        return 0;
    });
    return detached;
}

int main() {
    stringstream out, in;
    (muestra_contenido_de(".") | busca_nombre("o"))(in, out);
    string line;
    while (getline(out, line)) {
        cout << line << "\n";
    }
}