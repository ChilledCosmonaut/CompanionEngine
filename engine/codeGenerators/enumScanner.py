# from typing import Optional, Dict
import os
from .cppbuilder import CppBuilder


def add_enum(file: CppBuilder, enum_list: list, enum_name: str):
    file.write_line("enum " + enum_name + " {")

    enum_string = ""

    for index, enum_qualifier in enumerate(enum_list):
        if index != 0:
            enum_string += "\n"

        enum_string += enum_qualifier.replace(".\\", "").replace(".", "$").replace("\\", "$") + ", "

    file.write_line(enum_string)

    if enum_name == "Shaders":
        file.write_line("LAST")

    file.write_line("};")


def generate_enums(header_file: str, scan_path: str):
    header = CppBuilder()
    header.write_line('#pragma once')
    header.write_line("")
    header.write_line("#include <string>")
    header.write_line("#include <filesystem>")
    header.write_line("")
    header.write_line("namespace assets {")
    header.indent()
    header.write_line("namespace fs = std::filesystem;")

    shaders = list()
    models = list()
    sounds = list()
    materials = list()
    images = list()
    fonts = list()

    for currentDir, sub_directories, contained_files in os.walk(scan_path):
        print("Looking for assets in: ", currentDir)

        current_relative = os.path.relpath(currentDir, scan_path)

        for file in contained_files:
            if file.endswith(".glsl"):
                shaders.append(os.path.join(current_relative, file))
            if file.endswith(".mtl"):
                materials.append(os.path.join(current_relative, file))
            if file.endswith((".jpg", ".png", ".tga")):
                images.append(os.path.join(current_relative, file))
            if file.endswith((".obj", ".fbx")):
                models.append(os.path.join(current_relative, file))
            if file.endswith((".wav", ".mp3")):
                sounds.append(os.path.join(current_relative, file))
            if file.endswith(".ttf"):
                fonts.append(os.path.join(current_relative, file))

    add_enum(header, shaders, "Shaders")
    header.write_line("")
    add_enum(header, models, "Models")
    header.write_line("")
    add_enum(header, sounds, "Sounds")
    header.write_line("")
    add_enum(header, materials, "Materials")
    header.write_line("")
    add_enum(header, images, "Images")
    header.write_line("")
    add_enum(header, fonts, "Fonts")

    header.write_line()

    header.write_code(
        "class AssetTranslator {\n" +
        "public:\n" +
        "static fs::path TranslateShader(Shaders shader) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", shaderDict[shader]);\n" +
        "}\n\n" +
        "static fs::path TranslateModel(Models model) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", modelDict[model]);\n" +
        "}\n\n" +
        "static fs::path TranslateSound(Sounds sound) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", soundDict[sound]);\n" +
        "}\n\n" +
        "static fs::path TranslateMaterial(Materials material) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", materialDict[material]);\n" +
        "}\n\n" +
        "static fs::path TranslateImage(Images image) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", imageDict[image]);\n" +
        "}\n\n" +
        "static fs::path TranslateFonts(Fonts fonts) {\n" +
        "return ResolveForSubdirectory(\"../../assets\", fontsDict[fonts]);\n" +
        "}\n\n" +
        "private:\n\n" +
        "static fs::path ResolveForSubdirectory(const fs::path &subdirectory, const fs::path &relativeAssetPath) {\n" +
        "return fs::weakly_canonical((subdirectory / relativeAssetPath).make_preferred());\n" +
        "}\n" +
        "static inline std::string shaderDict[] = {\n" +
        "\"" + "\",\n\"".join(shaders).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n\n" +
        "static inline std::string modelDict[] = {\n" +
        "\"" + "\",\n\"".join(models).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n\n" +
        "static inline std::string soundDict[] = {\n" +
        "\"" + "\",\n\"".join(sounds).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n\n" +
        "static inline std::string materialDict[] = {\n" +
        "\"" + "\",\n\"".join(materials).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n\n" +
        "static inline std::string imageDict[] = {\n" +
        "\"" + "\",\n\"".join(images).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n" +
        "static inline std::string fontsDict[] = {\n" +
        "\"" + "\",\n\"".join(fonts).replace(".\\", "").replace("\\", "\\\\") + "\"" +
        "};\n" +
        "};\n")

    header.write_line("}")

    header.save(header_file)


if __name__ == "__main__":
    generate_enums("../Test.h")
