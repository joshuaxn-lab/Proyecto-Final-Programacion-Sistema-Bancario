 # Sistema Bancario en C++

## Requisitos
- MinGW (g++ 16.x.x) 
- MySQL Server 9.6
- MySQL Connector C++ 9.7
- VS Code con extensión C/C++

## Instalación

### 1. MinGW
- Descargar desde: https://github.com/niXman/mingw-builds-binaries/releases
- Extraer en `D:\mingw64`
- Agregar `D:\mingw64\bin` al PATH del sistema

### 2. MySQL Server
- Descargar desde: https://dev.mysql.com/downloads/mysql/
- Instalar con opciones por defecto

### 3. MySQL Connector C++ 9.7
- Descargar ZIP desde: https://dev.mysql.com/downloads/connector/cpp/
- Extraer en `D:\mysql-connector-c++-9.7.0-winx64`

### 4. Base de datos
- Abrir MySQL Workbench
- Ejecutar el archivo `banco.sql` incluido en el proyecto

### 5. Compilar
```cmd
g++ index.cpp -o programa.exe "-IC:\Program Files\MySQL\MySQL Server 9.6\include" "-LC:\Program Files\MySQL\MySQL Server 9.6\lib" -lmysql
```

### 6. Copiar DLLs necesarias
```cmd
copy "C:\Program Files\MySQL\MySQL Server 9.6\lib\libmysql.dll" .
copy "C:\Program Files\MySQL\MySQL Server 9.6\bin\libssl-3-x64.dll" .
copy "C:\Program Files\MySQL\MySQL Server 9.6\bin\libcrypto-3-x64.dll" .
copy "D:\mingw64\bin\libstdc++-6.dll" .
copy "D:\mingw64\bin\libgcc_s_seh-1.dll" .
copy "D:\mingw64\bin\libwinpthread-1.dll" .
```

### 7. Ejecutar
```cmd
.\programa.exe
```

## Contraseña MySQL
Cambiar en `index.cpp` línea de conexión:
```cpp
mysql_real_connect(conn, "localhost", "root", "1234", "banco", 3306, nullptr, 0)
```
