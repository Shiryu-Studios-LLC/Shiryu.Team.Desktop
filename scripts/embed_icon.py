import sys
import os


def png_to_c_array(png_path, array_name="g_Icon"):
    with open(png_path, "rb") as f:
        data = f.read()

    hex_lines = []
    for i in range(0, len(data), 16):
        chunk = data[i : i + 16]
        hex_str = ", ".join(f"0x{b:02x}" for b in chunk)
        hex_lines.append(hex_str)

    output = f"const uint8_t {array_name}[] = {{\n"
    output += ",\n".join(hex_lines)
    output += "\n};\n"

    return output


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python embed_icon.py <png_file> [array_name]")
        sys.exit(1)

    png_file = sys.argv[1]
    array_name = sys.argv[2] if len(sys.argv) > 2 else "g_ShiryuTeamIcon"

    if not os.path.exists(png_file):
        print(f"Error: File '{png_file}' not found")
        sys.exit(1)

    result = png_to_c_array(png_file, array_name)
    print(result)
