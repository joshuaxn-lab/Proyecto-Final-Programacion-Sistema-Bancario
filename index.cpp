#include <iostream>
#include <mysql.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Transaccion {
    string numero_cuenta;
    string tipo;
    double monto;
};

struct Transferencia {
    string origen;
    string destino;
    double monto;
};


class Cuenta {

private:
    string numero;
    string nombre;
    string tipo;
    double saldo;

public:

    Cuenta(string n, string nom, string t, double s) {
        numero = n;
        nombre = nom;
        tipo = t;
        saldo = s;
    }

    string getNumero() { return numero; }
    string getNombre() { return nombre; }
    string getTipo() { return tipo; }
    double getSaldo() { return saldo; }
};

MYSQL* conn;

void conectar() {

    conn = mysql_init(NULL);

    conn = mysql_real_connect(
        conn,
        "localhost",
        "root",
        "1234",
        "banco",
        3306,
        NULL,
        0
    );

    if(conn)
        cout << "Conexion OK\n";
    else
        cout << "Error conexion\n";
}

string generarNumeroCuenta() {

    string numero;

    for(int i = 0; i < 10; i++) {
        numero += to_string(rand() % 10);
    }

    return numero;
}

void crearCuenta() {

    string nombre, tipo, correo;
    double saldo;

    cin.ignore();

    cout << "Nombre: " <<endl;
    getline(cin, nombre);

    cout << "Correo: " <<endl;
    getline(cin, correo);

    cout << "Tipo (ahorro/monetaria): " <<endl;
    cin >> tipo;

    cout << "Saldo inicial:Q " <<endl;
    cin >> saldo;

    string numero = generarNumeroCuenta();

    Cuenta* c = new Cuenta(numero, nombre, tipo, saldo);

    string query =
    "INSERT INTO cuentas(numero_cuenta,nombre_titular,tipo,saldo,correo_electronico) VALUES('"
    + c->getNumero() + "','" + c->getNombre() + "','" + c->getTipo() + "',"
    + to_string(c->getSaldo()) + ",'" + correo + "')";

    mysql_query(conn, query.c_str());

    cout<<"CUENTA CREADA EXISTOSAMENTE: "<<endl;
    cout << "Cuenta creada\n";
    cout << "Numero: " << c->getNumero() << endl;

    delete c;
}

void depositar() {

    string numero;
    double monto;

    cin.ignore();

    cout << "\nCuenta: ";
    getline(cin, numero);

    cout << "Monto: ";
    cin >> monto;

    string q =
    "UPDATE cuentas SET saldo = saldo + " + to_string(monto)
    + " WHERE numero_cuenta = '" + numero + "'";

    mysql_query(conn, q.c_str());

    Transaccion t;
    t.numero_cuenta = numero;
    t.tipo = "deposito";
    t.monto = monto;

    string ins =
    "INSERT INTO transacciones(numero_cuenta,tipo,monto) VALUES('"
    + t.numero_cuenta + "','" + t.tipo + "'," + to_string(t.monto) + ")";

    mysql_query(conn, ins.c_str());

    cout<<"DEPOSITO SE REALIZO EXISTOSAMENTE: "<<endl;

}

void retirar() {

    string numero;
    double monto;

    cin.ignore();

    cout << "\nCuenta: ";
    getline(cin, numero);

    cout << "Monto: ";
    cin >> monto;

    string buscar =
    "SELECT tipo,saldo FROM cuentas WHERE numero_cuenta = '" + numero + "'";

    mysql_query(conn, buscar.c_str());

    MYSQL_RES* res = mysql_store_result(conn);

    if(mysql_num_rows(res) == 0) {
        cout << "Cuenta no existe\n";
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);

    string tipo = row[0];
    double saldo = atof(row[1]);

    double comision = 0;

    if(tipo == "ahorro") {
        comision = monto * 0.02;
    }

    double total = monto + comision;

    if(total > saldo) {
        cout << "Saldo insuficiente\n";
        return;
    }

    string q =
    "UPDATE cuentas SET saldo = saldo - " + to_string(total)
    + " WHERE numero_cuenta = '" + numero + "'";

    mysql_query(conn, q.c_str());

    Transaccion t;
    t.numero_cuenta = numero;
    t.tipo = "retiro";
    t.monto = monto;

    string ins =
    "INSERT INTO transacciones(numero_cuenta,tipo,monto) VALUES('"
    + t.numero_cuenta + "','" + t.tipo + "'," + to_string(t.monto) + ")";

    mysql_query(conn, ins.c_str());

    cout<<"EL RETIRO SE REALIZO EXISTOSAMENTE: "<<endl;

    if(comision > 0)
        cout << "Comision: Q" << comision << endl;
}

void transferir() {

    string origen, destino, correo;
    double monto;

    cin.ignore();

    cout << "\nOrigen: ";
    getline(cin, origen);

    cout << "Destino: ";
    getline(cin, destino);

    cout << "Correo receptor: ";
    getline(cin, correo);

    cout << "Monto: ";
    cin >> monto;

    string debito =
    "UPDATE cuentas SET saldo = saldo - " + to_string(monto)
    + " WHERE numero_cuenta = '" + origen + "'";

    string credito =
    "UPDATE cuentas SET saldo = saldo + " + to_string(monto)
    + " WHERE numero_cuenta = '" + destino + "'";

    mysql_query(conn, debito.c_str());
    mysql_query(conn, credito.c_str());

    Transferencia tf;
    tf.origen = origen;
    tf.destino = destino;
    tf.monto = monto;

    string ins =
    "INSERT INTO transferencias(cuenta_origen,cuenta_destino,monto,estado,correo_receptor) VALUES('"
    + tf.origen + "','" + tf.destino + "',"
    + to_string(tf.monto) + ",'completada','" + correo + "')";

    mysql_query(conn, ins.c_str());

    string t1 =
    "INSERT INTO transacciones(numero_cuenta,tipo,monto) VALUES('"
    + origen + "','transferencia_enviada'," + to_string(monto) + ")";

    string t2 =
    "INSERT INTO transacciones(numero_cuenta,tipo,monto) VALUES('"
    + destino + "','transferencia_recibida'," + to_string(monto) + ")";

    mysql_query(conn, t1.c_str());
    mysql_query(conn, t2.c_str());

        cout<<"LA TRANSFERENCIA SE REALIZO EXISTOSAMENTE: "<<endl;
}

void historialCuenta() {

    string numero;

    cin.ignore();

    cout << "\nCuenta: ";
    getline(cin, numero);

    string q =
    "SELECT tipo,monto,fecha FROM transacciones WHERE numero_cuenta = '"
    + numero + "' ORDER BY fecha DESC";

    mysql_query(conn, q.c_str());

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "===== HISTORIAL CUENTA ====="<<endl;;

    while((row = mysql_fetch_row(res))) {

        cout << row[0] << " | Q" << row[1] << " | " << row[2] << endl;
    }

    mysql_free_result(res);
}

void historialGeneral() {

    string q =
    "SELECT numero_cuenta,tipo,monto,fecha FROM transacciones ORDER BY fecha DESC LIMIT 10";

    mysql_query(conn, q.c_str());

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "==== HISTORIAL GENERAL ====="<<endl;;

    while((row = mysql_fetch_row(res))) {

        cout << row[0] << " | "
             << row[1] << " | Q"
             << row[2] << " | "
             << row[3] << endl;
    }

    mysql_free_result(res);
}

int main() {

    srand(time(NULL));

    conectar();

    int op;

    do {

        cout << "\n===== BANCO ====="<<endl;
        cout << "1. Crear cuenta"<<endl;
        cout << "2. Depositar"<<endl;
        cout << "3. Retirar"<<endl;
        cout << "4. Transferir"<<endl;
        cout << "5. Historial cuenta"<<endl;;
        cout << "6. Historial general"<<endl;;
        cout << "7. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {

            case 1: crearCuenta(); break;
            case 2: depositar(); break;
            case 3: retirar(); break;
            case 4: transferir(); break;
            case 5: historialCuenta(); break;
            case 6: historialGeneral(); break;
            case 7: cout << "Saliendo del programa"<<endl;; break;
            default: cout << "La opcion no existe"<<endl; break;
        }

    } while(op != 7);

    mysql_close(conn);

    return 0;
}