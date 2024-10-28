#!/bin/bash

# Colores para OK y KO
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sin color

# Ruta del ejecutable
EXEC="./RPN"

# Tests y resultados esperados
declare -a tests=(
    "8 9 * 9 - 9 - 9 - 4 - 1 +"  # Esperado: 42
    "7 7 * 7 -"                  # Esperado: 42
    "1 2 * 2 / 2 * 2 4 - +"      # Esperado: 0
    "(1 + 1)"                    # Esperado: Invalid Arguments
    "3 5 + 7 -"                  # Esperado: 1
    "5 5 * 5 25 / -"             # Esperado: 0
    "10 2 / 3 +"                 # Esperado: 8
    "5 3 -"                      # Esperado: 2
    "15 5 / 2 * 3 -"             # Esperado: 3
)
declare -a expected=(
    "42"
    "42"
    "0"
    "Invalid Arguments"
    "1"
    "25"
    "8"
    "2"
    "3"
)

# Ejecutar los tests
echo -e "${GREEN}Starting tests...${NC}"
for i in "${!tests[@]}"; do
    output=$($EXEC "${tests[$i]}")
    if [ "$output" == "${expected[$i]}" ]; then
        echo -e "Test $((i+1)): ${tests[$i]} -> ${GREEN}OK${NC} (Expected: ${expected[$i]})"
    else
        echo -e "Test $((i+1)): ${tests[$i]} -> ${RED}KO${NC} (Expected: ${expected[$i]}, Got: $output)"
    fi
done

echo -e "${GREEN}All tests completed.${NC}"
