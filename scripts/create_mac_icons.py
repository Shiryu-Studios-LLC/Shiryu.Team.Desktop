import sys
import os
from PIL import Image, ImageDraw


def create_mac_button(color, size=16):
    img = Image.new("RGBA", (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)

    # Draw filled circle
    radius = size // 2 - 1
    center = size // 2
    draw.ellipse(
        [center - radius, center - radius, center + radius, center + radius], fill=color
    )

    return img


def create_icon_images():
    # macOS traffic light colors (close = red, minimize = yellow, maximize = green)
    close_color = (255, 95, 95, 255)  # Red
    minimize_color = (255, 203, 55, 255)  # Yellow
    maximize_color = (40, 205, 65, 255)  # Green

    close = create_mac_button(close_color)
    minimize = create_mac_button(minimize_color)
    maximize = create_mac_button(maximize_color)

    return close, minimize, maximize


def image_to_c_array(img, array_name):
    import io

    buf = io.BytesIO()
    img.save(buf, format="PNG")
    data = buf.getvalue()

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
    close, minimize, maximize = create_icon_images()

    close.save(
        "F:/ShiryuCore/Shiryu.Team.Desktop/ShiryuTeam/Platform/GUI/ShiryuTeam/Embed/mac_close.png"
    )
    minimize.save(
        "F:/ShiryuCore/Shiryu.Team.Desktop/ShiryuTeam/Platform/GUI/ShiryuTeam/Embed/mac_minimize.png"
    )
    maximize.save(
        "F:/ShiryuCore/Shiryu.Team.Desktop/ShiryuTeam/Platform/GUI/ShiryuTeam/Embed/mac_maximize.png"
    )

    for name, img in [
        ("mac_close", close),
        ("mac_minimize", minimize),
        ("mac_maximize", maximize),
    ]:
        result = image_to_c_array(img, f"g_{name}Icon")
        with open(
            f"F:/ShiryuCore/Shiryu.Team.Desktop/ShiryuTeam/Platform/GUI/ShiryuTeam/Embed/{name}.embed",
            "w",
        ) as f:
            f.write(result)

    print("Created macOS control icons")
