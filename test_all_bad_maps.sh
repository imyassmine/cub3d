#!/bin/bash

# Script pour tester toutes les bad maps avec Valgrind
echo "=========================================="
echo "Testing all bad maps with Valgrind"
echo "=========================================="

BAD_MAPS_DIR="maps/bad"
PASSED=0
FAILED=0
LEAK_FOUND=0

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

for map_file in "$BAD_MAPS_DIR"/*; do
    if [ -f "$map_file" ]; then
        filename=$(basename "$map_file")
        echo -n "Testing $filename... "
        
        # Exécuter valgrind et capturer la sortie
        valgrind_output=$(./val.sh "$map_file" 2>&1)
        
        # Vérifier s'il y a des fuites mémoire
        if echo "$valgrind_output" | grep -q "All heap blocks were freed -- no leaks are possible"; then
            echo -e "${GREEN}✓ PASS (No leaks)${NC}"
            ((PASSED++))
        elif echo "$valgrind_output" | grep -q "definitely lost: 0 bytes" && echo "$valgrind_output" | grep -q "indirectly lost: 0 bytes"; then
            echo -e "${YELLOW}⚠ PASS (Only reachable memory)${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL (Memory leaks detected)${NC}"
            ((FAILED++))
            ((LEAK_FOUND++))
            echo "  Details:"
            echo "$valgrind_output" | grep -E "(definitely lost|indirectly lost|possibly lost)" | head -3
        fi
    fi
done

echo ""
echo "=========================================="
echo "RESULTS SUMMARY:"
echo "=========================================="
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"

if [ $LEAK_FOUND -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed! No memory leaks detected.${NC}"
    exit 0
else
    echo -e "${RED}❌ $LEAK_FOUND test(s) failed with memory leaks.${NC}"
    exit 1
fi
