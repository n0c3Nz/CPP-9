#!/bin/bash

# Verificar si el usuario proporcionó un argumento
if [ $# -ne 1 ]; then
    echo "Uso: $0 <número de líneas>"
    exit 1
fi

# Número de líneas que el usuario quiere generar
num_lines=$1

# Nombre del archivo de salida
output_file="purchases.csv"

# Generar el archivo CSV con encabezado
echo "date | value" > $output_file

# Función para generar una fecha aleatoria
generate_random_date() {
    year=$((RANDOM % 24 + 2000))  # Año entre 2000 y 2023
    month=$((RANDOM % 12 + 1))    # Mes entre 1 y 12
    day=$((RANDOM % 28 + 1))      # Día entre 1 y 28 para evitar problemas con meses de distinta longitud
    printf "%04d-%02d-%02d" $year $month $day
}

# Generar las líneas de datos aleatorios
for ((i=1; i<=num_lines; i++)); do
    random_date=$(generate_random_date)
    random_value=$((RANDOM % 100 + 1))  # Valor aleatorio entre 1 y 100
    echo "$random_date | $random_value" >> $output_file
done

echo "Archivo $output_file generado con $num_lines líneas."
