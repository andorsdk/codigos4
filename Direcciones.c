#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#define PAGE_SIZE 4096 // 4 KBytes
#define VIRTUAL_BITS 32 // 2^32 bytes de espacio virtual
#define PHYSICAL_BITS 28 // 2^28 bytes de memoria física

// Estructura para la tabla de páginas
typedef struct {
    int bit_presencia;
    int bit_modificado;
    int marco_pagina;
} PageTableEntry;

// Tabla de páginas del ejercicio
PageTableEntry page_table[] = {
    {1, 0, 1},
    {0, 0, 8},
    {1, 0, 14},
    {1, 0, 5},
    {1, 0, 7},
    {0, 0, 25},
    {0, 1, 16}
};

// Función para mostrar el formato de la dirección virtual
void mostrarFormatoDireccionVirtual() {
    int bits_offset = log2(PAGE_SIZE);
    int bits_pagina = VIRTUAL_BITS - bits_offset;
    
    printf("\na) Formato de la dirección virtual:\n");
    printf("Total de bits: %d\n", VIRTUAL_BITS);
    printf("- Bits para número de página: %d bits (bits %d-%d)\n", 
           bits_pagina, bits_offset, VIRTUAL_BITS-1);
    printf("- Bits para desplazamiento: %d bits (bits 0-%d)\n", 
           bits_offset, bits_offset-1);
}

// Función para convertir dirección virtual a física
void convertirDireccionVirtual(uint32_t dir_virtual) {
    int bits_offset = log2(PAGE_SIZE);
    uint32_t mascara_offset = PAGE_SIZE - 1;
    uint32_t offset = dir_virtual & mascara_offset;
    uint32_t num_pagina = dir_virtual >> bits_offset;
    
    printf("\nb) Conversión de dirección virtual 0x%08X:\n", dir_virtual);
    printf("Número de página: %d\n", num_pagina);
    printf("Desplazamiento: %d\n", offset);
    
    if (num_pagina < sizeof(page_table)/sizeof(PageTableEntry)) {
        if (page_table[num_pagina].bit_presencia) {
            uint32_t dir_fisica = (page_table[num_pagina].marco_pagina * PAGE_SIZE) + offset;
            printf("Dirección física: 0x%08X\n", dir_fisica);
        } else {
            printf("¡Fallo de página! La página no está en memoria física.\n");
        }
    } else {
        printf("Error: Número de página fuera de rango\n");
    }
}

// Función para calcular el tamaño del espacio de direcciones virtual
void calcularTamanoEspacioVirtual() {
    int num_paginas = sizeof(page_table)/sizeof(PageTableEntry);
    int tamano_bytes = num_paginas * PAGE_SIZE;
    
    printf("\nc) Tamaño del espacio de direcciones virtual:\n");
    printf("Número de páginas: %d\n", num_paginas);
    printf("Tamaño por página: %d bytes\n", PAGE_SIZE);
    printf("Tamaño total: %d bytes (%.2f KB)\n", 
           tamano_bytes, tamano_bytes/1024.0);
}

int main() {
    printf("Análisis de Sistema de Memoria Virtual\n");
    printf("=====================================\n");
    
    // a) Mostrar formato de dirección virtual
    mostrarFormatoDireccionVirtual();
    
    // b) Convertir dirección virtual específica
    convertirDireccionVirtual(0x000005B3);
    
    // c) Calcular tamaño del espacio de direcciones
    calcularTamanoEspacioVirtual();
    
    return 0;
}
