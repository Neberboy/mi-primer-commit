#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100

typedef struct {
    int id;
    char nombre[50];
    int stock;
    float precio;
    float ganancias;
} Producto;

Producto productos[MAX_PRODUCTOS];
int total_productos = 0;

int existeID(int id) {
    for (int i = 0; i < total_productos; i++) {
        if (productos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void registrarProducto() {
    if (total_productos >= MAX_PRODUCTOS) {
        printf("\n*No se pueden registrar mas productos.\n");
        return;
    }
    
    Producto nuevo_producto;
    do {
        printf("\nIngrese ID del producto: ");
        scanf("%d", &nuevo_producto.id);
        getchar(); // Limpiar buffer
        if (existeID(nuevo_producto.id) != -1) {
            printf("*El ID ya existe. Intente con otro.\n");
        }
    } while (existeID(nuevo_producto.id) != -1);
    
    printf("Ingrese nombre del producto: ");
    fgets(nuevo_producto.nombre, 50, stdin);
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre, "\n")] = 0;
    
    do {
        printf("Ingrese cantidad en stock: ");
        scanf("%d", &nuevo_producto.stock);
        if (nuevo_producto.stock < 0) {
            printf("*El stock no puede ser negativo. Intente de nuevo.\n");
        }
    } while (nuevo_producto.stock < 0);
    
    do {
        printf("Ingrese precio unitario: ");
        scanf("%f", &nuevo_producto.precio);
        if (nuevo_producto.precio < 0) {
            printf("*El precio no puede ser negativo. Intente de nuevo.\n");
        }
    } while (nuevo_producto.precio < 0);
    
    nuevo_producto.ganancias = 0.0;
    productos[total_productos++] = nuevo_producto;
    printf("*Producto registrado con exito.\n");
}

void venderProducto() {
    int id, cantidad, indice;
    printf("\nIngrese el ID del producto a vender: ");
    scanf("%d", &id);
    
    indice = existeID(id);
    if (indice == -1) {
        printf("\n*El producto no existe.\n");
        return;
    }
    
    printf("Ingrese la cantidad a vender: ");
    scanf("%d", &cantidad);
    
    if (cantidad > productos[indice].stock) {
        printf("\n*Stock insuficiente.\n");
    } else {
        productos[indice].stock -= cantidad;
        productos[indice].ganancias += cantidad * productos[indice].precio;
        printf("*Venta realizada con exito.\n");
    }
}

void reabastecerProducto() {
    int id, cantidad, indice;
    printf("\nIngrese el ID del producto a reabastecer: ");
    scanf("%d", &id);
    
    indice = existeID(id);
    if (indice == -1) {
        printf("\n*El producto no existe.\n");
        return;
    }
    
    do {
        printf("Ingrese la cantidad a agregar al stock: ");
        scanf("%d", &cantidad);
        if (cantidad < 0) {
            printf("*La cantidad no puede ser negativa. Intente de nuevo.\n");
        }
    } while (cantidad < 0);
    
    productos[indice].stock += cantidad;
    printf("*Stock actualizado con exito.\n");
}

void consultarProductos() {
    if (total_productos == 0) {
        printf("\n*No hay productos registrados.\n");
        return;
    }
    for (int i = 0; i < total_productos; i++) {
        printf("\n--- Producto %d ---\n", i + 1);
        printf("ID: %d\n", productos[i].id);
        printf("Nombre: %s\n", productos[i].nombre);
        printf("Stock disponible: %d\n", productos[i].stock);
        printf("Precio unitario: %.2f\n", productos[i].precio);
        printf("Ganancias obtenidas: %.2f\n", productos[i].ganancias);
    }
}

int main() {
    int opcion;
    
    do {
        printf("\n---- Gestion de Datos Comerciales ----");
        printf("\n             -- Menu --");
        printf("\n1. Registrar Producto.");
        printf("\n2. Vender Producto.");
        printf("\n3. Reabastecer Producto.");
        printf("\n4. Consultar Informacion.");
        printf("\n5. Salir.");
        printf("\nSu opcion: ");
        scanf("%i", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                venderProducto();
                break;
            case 3:
                reabastecerProducto();
                break;
            case 4:
                consultarProductos();
                break;
            case 5:
                printf("\n*Saliendo del programa...\n");
                break;
            default:
                printf("\n*Por favor, elija una opcion valida.*\n");
        }
    } while (opcion != 5);

    return 0;
}