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

void depositar(MYSQL* conn){

        string numero_cuenta;
        double monto;

        cin.ignore();

        cout<<"Numero de cuenta: ";
        getline(cin,numero_cuenta);

        string query ="SELECT * FROM cuentas WHERE numero_cuenta ='"+ numero_cuenta + "'";
        mysql_query(conn, query.c_str());
        MYSQL_RES* result = mysql_store_result(conn);

        if(mysql_num_rows(result) == 0){

               cout<<"Cuenta no encontrada";
               mysql_free_result(result);
               return;
        }

         mysql_free_result(result);

         cout<<"Monto a depositar: Q";
         cin>> monto;

         string update = "UPDATE  cuentas SET saldo = saldo + " + to_string(monto)
         + " WHERE numero_cuenta = '" + numero_cuenta + "'";

         if(mysql_query(conn, update.c_str())){
           cout<<"Error al depositar: "<<mysql_error(conn) << endl;
           return;
         }

         string transacciones = "INSERT INTO transacciones (numero_cuenta, tipo, monto) VALUES('"
        + numero_cuenta + "', 'deposito', " + to_string(monto )+ ")";

         mysql_query(conn, transacciones.c_str());

        cout<<"===== Deposito Exitoso ======="<<endl;
        cout<<"Cuenta : " <<numero_cuenta<<endl;
        cout<<"Monto : Q"<<monto<<endl;
        cout<<"================================";
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
        cout << "2.Depositar \n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearCuenta(conn);
                break;
            
                case 2:
                    depositar(conn);
                break;

            case 3:
                cout << "Saliendo\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 3);

    mysql_close(conn);
    return 0;
}