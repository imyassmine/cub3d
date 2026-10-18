#!/bin/bash

# Script pour tester Cub3D avec Valgrind
# Usage: ./val.sh [chemin_vers_le_fichier_map]

MAP_FILE=${1:-"maps/good/test_map.cub"}

# Créer le fichier de suppressions pour MLX/X11
cat > mlx_suppressions.supp << 'EOF'
{
   MLX_Image_Creation
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:calloc
   fun:mlx_int_new_xshm_image
   fun:mlx_new_image
}

{
   X11_Shared_Memory
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:calloc
   fun:XShmCreateImage
}

{
   MLX_XPM_Parsing
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:calloc
   ...
   fun:mlx_xpm_file_to_image
}

{
   X11_Display_Resources
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:malloc
   obj:/usr/lib/x86_64-linux-gnu/libX11.so*
}

{
   X11_Extension_Resources
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:malloc
   obj:/usr/lib/x86_64-linux-gnu/libXext.so*
}
EOF

echo "Test valgrind avec le fichier: $MAP_FILE"
echo "=========================================="
echo "Note: Les fuites MLX/X11 sont supprimées du rapport"
echo ""

valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --trace-children=yes \
    --track-fds=yes \
    --suppressions=mlx_suppressions.supp \
    ./cub3d "$MAP_FILE"

# Nettoyer le fichier temporaire
rm -f mlx_suppressions.supp
