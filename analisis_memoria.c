#include <stdio.h>
#include <math.h>
#include <stdint.h>

// Constantes del sistema
#define VIRTUAL_ADDRESS_BITS 36
#define PAGE_SIZE 1      // 1 página por entrada
#define TLB_ACCESS_TIME 8 // 8ns
#define MEMORY_ACCESS_TIME 70 // 70ns
#define TLB_HIT_RATE 0.90 // 90% de aciertos

// Estructura para almacenar los campos de una dirección virtual
typedef struct {
    uint64_t level1_index;
    uint64_t level2_index;
    uint64_t level3_index;
    uint64_t offset;
} VirtualAddress;

// Función para calcular los bits necesarios para cada campo
void calculateBitFields(void) {
    int total_pages = 8;  // 8 páginas por tabla
    int bits_per_level = (int)log2(total_pages);
    int offset_bits = (int)log2(PAGE_SIZE);
    
    printf("\nCálculo de campos de bits:\n");
    printf("Bits para cada nivel de tabla: %d\n", bits_per_level);
    printf("Bits para offset: %d\n", offset_bits);
    
    // Mostrar rangos de bits para cada campo
    int current_position = VIRTUAL_ADDRESS_BITS - 1;
    
    printf("\nRangos de bits en la dirección virtual de %d bits:\n", VIRTUAL_ADDRESS_BITS);
    printf("Nivel 1: bits %d-%d\n", current_position - bits_per_level + 1, current_position);
    current_position -= bits_per_level;
    
    printf("Nivel 2: bits %d-%d\n", current_position - bits_per_level + 1, current_position);
    current_position -= bits_per_level;
    
    printf("Nivel 3: bits %d-%d\n", current_position - bits_per_level + 1, current_position);
    current_position -= bits_per_level;
    
    printf("Offset: bits %d-%d\n", 0, current_position);
}

// Función para calcular el tiempo medio de acceso a memoria
void calculateAverageAccessTime(void) {
    // Tiempo con acierto en TLB
    float tlb_hit_time = TLB_ACCESS_TIME + MEMORY_ACCESS_TIME;
    
    // Tiempo con fallo en TLB (necesita acceder a las tablas de páginas)
    float tlb_miss_time = TLB_ACCESS_TIME + (3 * MEMORY_ACCESS_TIME) + MEMORY_ACCESS_TIME;
    
    // Tiempo medio considerando la tasa de aciertos
    float average_time = (TLB_HIT_RATE * tlb_hit_time) + 
                        ((1 - TLB_HIT_RATE) * tlb_miss_time);
    
    printf("\nCálculo de tiempos de acceso:\n");
    printf("Tiempo con acierto en TLB: %.2f ns\n", tlb_hit_time);
    printf("Tiempo con fallo en TLB: %.2f ns\n", tlb_miss_time);
    printf("Tiempo medio de acceso: %.2f ns\n", average_time);
}

int main() {
    printf("Análisis del Sistema de Memoria Virtual\n");
    printf("=======================================\n");
    
    // Calcular y mostrar la descomposición de campos de bits
    calculateBitFields();
    
    // Calcular y mostrar los tiempos de acceso
    calculateAverageAccessTime();
    
    return 0;
}
