#include <iostream>
#include <cstdlib>
#include "Cliente.h"
#include "Fecha.h"
#include "Pago.h"
#include "Prestamo.h"
using namespace std;


#define TAM 5

Cliente* agregarCliente() {
    int idCl;
    string n, a;
    Cliente* cl;
    cout << "Digite el id del cliente: \n";
    cin >> idCl;
    cout << "Digite el nombre del cliente: \n";
    cin >> n;
    cout << "Digite el apellido del cliente: \n";
    cin >> a;
    cl = new Cliente(idCl, n, a);
    return cl;
}

Prestamo* agregarPrestamo(Cliente* cl) {
    int noPres, d, m, a;
    float montApro;
    Fecha* fechApro = NULL;
    Prestamo* pres;
    cout << "Digite el numero del prestamo:\n";
    cin >> noPres;
    cout << "Digite la fecha de aprobacion (dd/mm/aa) : \n";
    cin >> d;
    cin >> m;
    cin >> a;
    fechApro = new Fecha(d, m, a);
    cout << "Digite el monto aprobado :\n";
    cin >> montApro;
    pres = new Prestamo(noPres, cl, fechApro, montApro);
    return pres;
}

Cliente* buscarCliente(Cliente* lst[], int cont, int db) {
    bool encontrado = false;
    int contador = 0;
    Cliente* cl = NULL;
    while (contador < cont && !encontrado) {
        if (lst[contador]->getIdCliente() == db) {
            encontrado = true;
            cl = lst[contador];
        } else {
            contador++;
        }
    }
    return cl;
}

Prestamo* buscarPrestamo(Prestamo* lst[], int cont, int db) {
    bool encontrado = false;
    int contador = 0;
    Prestamo* pres = NULL;
    while (contador < cont && !encontrado) {
        if (lst[contador]->getNumeroPrestamo() == db) {
            encontrado = true;
            pres = lst[contador];
        } else {
            contador++;
        }
    }
    return pres;
}

void registrarPago(Prestamo* pres) {
    int d, m, a;
    Fecha* fecPag;
    float montPag;
    Pago* pg;
    cout << "Digite la fecha de pago (dd/mm/aa) : \n";
    cin >> d >> m >> a;
    fecPag = new Fecha(d, m, a);
    cout << "Digite el monto del pago: \n";
    cin >> montPag;
    pg = new Pago(fecPag, montPag);
    pres->HacerPago(pg);
}

void verDetalles(Prestamo* pres) {
    cout << "\nEl numero: " << pres->getNumeroPrestamo() << endl;
    cout << "Cliente: " << pres->getCliente()->getNombre() << " " << pres->getCliente()->getApellido() << endl;
    cout << "Fecha de aprobacion: ";
    pres->getFechaAprobacion()->MostrarFecha();
    cout << "Monto Aprobado: " << pres->getMontoAprobado() << endl;
    cout << "Saldo Pendiente: " << pres->getSaldoPendiente() << endl;
    if (pres->getContPagos() == 0) {
        cout << "No tiene pagos registrados\n";
    } else {
        Pago** lista = pres->getLstPagos();
        for (int i = 0; i < pres->getContPagos(); i++) {
            cout <<"\nNo:" << (i + 1) <<endl;
            cout << "Fecha de pago:";
            lista[i]->getFechaPago()->MostrarFecha();
            cout << "Saldo ingresado:" << lista[i]->getMontoPago() << endl;
        }
    }
}


int menu() {
    int op;
    cout << "MENU DE OPCIONES\n";
    cout << "1. Agregar clientes a la lista\n";
    cout << "2. Agregar prestamos a la lista\n";
    cout << "3. Hacer pagos de prestamos\n";
    cout << "4. Mostrar lista de clientes\n";
    cout << "5. Mostrar lista de prestamos\n";
    cout << "6. Mostrar detalles prestamo\n";
    cout << "7. Salir\n";
    cout << "Digite la opcion : ";
    cin >> op;
    return op;
}


int main() {
    Cliente* lstCliente[TAM];
    Prestamo* lstPrestamo[TAM];
    Cliente* cl = NULL;
    Prestamo* pres = NULL;
    int opc, contCln = 0, contPres = 0, idCl, idPres;

    do {
        system("cls");
        opc = menu();
        switch (opc) {
        case 1:
            ///Agregar clientes a la lista
            if (contCln < TAM) {
                lstCliente[contCln] = agregarCliente();
                contCln++;
                cout << "El cliente se agrego con exito\n";
            } else {
                cout << "La lista de clientes esta llena\n";
            }
            break;

        case 2:
            ///Agregar prestamos a la lista
            if (contPres < TAM) {
                cout << "Digite el id del cliente:\n";
                cin >> idCl;
                cl = buscarCliente(lstCliente, contCln, idCl);
                if (cl) {
                    lstPrestamo[contPres] = agregarPrestamo(cl);
                    contPres++;
                    cout << "El prestamo se agrego con exito\n";
                } else {
                    cout << "El cliente no existe, no se pudo agregar el prestamo\n";
                }
            } else {
                cout << "La lista esta llena\n";
            }
            break;

        case 3:
            ///Hacer pago de prestamos
            cout << "Digite el numero de prestamo\n";
            cin >> idPres;
            pres = buscarPrestamo(lstPrestamo, contPres, idPres);
            if (pres) {
                registrarPago(pres);
                cout << "El pago se registro con exito\n";
            } else {
                cout << "El prestamo no existe, no se pudo registrar el pago\n";
            }
            break;

        case 4:
            ///Mostrar lista de clientes
            if (contCln == 0) {
                cout << "La lista esta vacia\n";
            } else {
                cout << "Id\tNombre\tApellido\n";
                for (int i = 0; i < contCln; i++) {
                    cout << lstCliente[i]->getIdCliente() << "\t";
                    cout << lstCliente[i]->getNombre() << "\t";
                    cout << lstCliente[i]->getApellido() << "\n";
                }
            }
            break;

        case 5:
            ///Mostrar lista de prestamos
            if(contPres == 0){
                cout << "La lista está vacía\n";
            }else{
                for(int i = 0; i < contPres; i++){

                    cout << "\nNo:" << lstPrestamo[i]->getNumeroPrestamo() << "\n";
                    cout << "Cliente:" << lstPrestamo[i]->getCliente()->getNombre() << " " << lstPrestamo[i]->getCliente()->getApellido() << "\n";
                    cout << "Fecha de aprobacion: ";
                    lstPrestamo[i]->getFechaAprobacion()->MostrarFecha();
                    cout << "Monto:" << lstPrestamo[i]->getMontoAprobado() << "\n";
                    cout << "Saldo:" << lstPrestamo[i]->getSaldoPendiente() << endl;
                }
            }
            break;

        case 6:
            ///Mostrar detalles prestamos
            cout << "Digite el numero de prestamo\n";
            cin >> idPres;
            pres = buscarPrestamo(lstPrestamo, contPres, idPres);
            if(pres){
                verDetalles(pres);
            }else{
                cout << "El prestamo no existe, no se puede visualizar los detalles\n";
            }
            break;

        case 7:
            cout << "Saliendo del programa\n";
            break;

        default:
            cout << "Error, opcion no esta definida\n";
            break;
       }
        system("pause");

    } while(opc != 7);

    return 0;
}
