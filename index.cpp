#include <iostream>
#include <mysql.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cuenta {
public:
    string numero_cuenta;
    string nombre_titular;
    string tipo;
    double saldo;

    Cuenta(string nombre, string tipo, double saldo_inicial) {
        this->nombre_titular = nombre;
        this->tipo = tipo;
        this->saldo = saldo_inicial;
        this->numero_cuenta = generarNumeroCuenta();
    }

    string generarNumeroCuenta() {
        srand(time(nullptr));
        string numero = "";
        for (int i = 0; i < 10; i++) {
            numero += to_string(rand() % 10);
        }
        return numero;
    }

    bool guardarEnDB(MYSQL* conn) {
        string query = "INSERT INTO cuentas (numero_cuenta, nombre_titular, tipo, saldo) VALUES ('"
            + numero_cuenta + "', '"
            + nombre_titular + "', '"
            + tipo + "', "
            + to_string(saldo) + ")";

        if (mysql_query(conn, query.c_str())) {
            cout << "Error al guardar: " << mysql_error(conn) << "\n";
            return false;
        }

        cout << "\n=== Cuenta Creada Exitosamente ===\n";
        cout << "Numero de cuenta : " << numero_cuenta << "\n";
        cout << "Titular          : " << nombre_titular << "\n";
        cout << "Tipo             : " << tipo << "\n";
        cout << "Saldo inicial    : Q" << saldo << "\n";
        cout << "==================================\n";
        return true;
    }
};

// crearCuenta va FUERA de la clase
void crearCuenta(MYSQL* conn) {
    string nombre, tipo;
    double saldo;

    cin.ignore();
    cout << "\nNombre del titular: ";
    getline(cin, nombre);

    cout << "Tipo de cuenta (ahorro/monetaria): ";
    cin >> tipo;

    cout << "Saldo inicial: Q";
    cin >> saldo;

    Cuenta* cuenta = new Cuenta(nombre, tipo, saldo);
    cuenta->guardarEnDB(conn);
    delete cuenta;
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "localhost", "root", "1234", "banco", 3306, nullptr, 0)) {
        cout << "Error de conexion: " << mysql_error(conn) << "\n";
        return 1;
    }

    int opcion;

    do {
        cout << "\n=== Sistema Bancario ===\n";
        cout << "1. Crear cuenta\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearCuenta(conn);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 0);

    mysql_close(conn);
    return 0;
}