#!/bin/bash

INPUT_DIR="assets"
OUTPUT_DIR="resources_embedded"
HEADER_FILE="include/textures.h"

mkdir -p "$OUTPUT_DIR"
mkdir -p "$(dirname "$HEADER_FILE")"

# Vide le dossier précédent
rm -rf "$OUTPUT_DIR"/*
echo "// Auto-generated file - Do not edit manually" > "$HEADER_FILE"
echo "" >> "$HEADER_FILE"
echo "#ifndef TEXTURES_H" >> "$HEADER_FILE"
echo "#define TEXTURES_H" >> "$HEADER_FILE"
echo "" >> "$HEADER_FILE"

for file in "$INPUT_DIR"/*; do
    filename=$(basename "$file")
    varname=$(echo "$filename" | tr '.' '_' | tr '-' '_')
    output_file="$OUTPUT_DIR/${filename}.h"

    {
        echo "// Auto-generated file - Do not edit manually"
        echo ""
        # Remplace les noms générés par xxd par des noms propres et const
        xxd -i "$file" | \
        sed -E "s/unsigned char [^[]+/static const unsigned char ${varname}/" | \
        sed -E "s/unsigned int [^=]+=/static const unsigned int ${varname}_len =/"
    } > "$output_file"

    # Ajoute un include dans textures.h
    echo "#include \"../resources_embedded/${filename}.h\"" >> "$HEADER_FILE"
done

echo "" >> "$HEADER_FILE"
echo "#endif // TEXTURES_H" >> "$HEADER_FILE"
