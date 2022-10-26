# from typing import Optional, Dict
import os

from codeGenerators.cppbuilder import CppBuilder

path = "D:\\UniStuff(Secondary)\\GameLab3\\code\\assets"


# KEYWORDS = {
#     'hello',
#     'hell',
#     'helium',
#     'help',
#     'apple',
#     'orange',
#     'ornament',
#     'application',
#     'apply',
#     'test',
#     'testing',
#     'testify',
#     'tomorrow',
#     'today',
#     'something',
# }
#
#
# class RadixNode:
#     def __init__(self, value: Optional[str] = None) -> None:
#         self.value: Optional[str] = value
#         self.leaf: bool = False
#         self.children: Dict[str, RadixNode] = {}
#
#     def add_keyword(self, word: str) -> None:
#         char = word[0]
#         word = word[1:]
#         child = self.children.get(char)
#         if child is None:
#             child = RadixNode(char)
#             self.children[char] = child
#
#         if len(word) > 0:
#             child.add_keyword(word)
#         else:
#             child.leaf = True
#
#
# def generate_keywords(header_file: str, source_file: str) -> None:
#     print("Test")
#     # Create the Radix Tree that begins from a 'root' node
#     root = RadixNode()
#     for keyword in KEYWORDS:
#         root.add_keyword(keyword)
#
#     # Generate the header file
#     header = CppBuilder()
#     header.write_line('#pragma once')
#     header.write_line()
#     header.write_line('bool is_keyword(const char* keyword);')
#     header.save(header_file)
#
#     # Generate the source file. We use a single-letter variable for the
#     # builder, specifically to make code alignment more readable.
#     s = CppBuilder()
#
#     def write_node_rec(node: RadixNode) -> None:
#         if len(node.children) == 1:
#             # Only one child - if the next character doesn't match,
#             # then NO keyword will match and we can exit.
#             n = list(node.children.values())[0]
#             with s.block("if (*cursor != '{}')".format(n.value),
#                          inline=True, newline=False):
#                 s.write_code('return false')
#             s.write_code('++cursor')
#             write_node_rec(n)
#         elif len(node.children) > 1:
#             # Multiple children - if the next character doesn't match
#             # either child, then NO keyword will match and we can exit.
#             with s.block('switch (*cursor++)'):
#                 for n in sorted(node.children.values(), key=lambda x: x.value):
#                     with s.case("'{}'".format(n.value)):
#                         write_node_rec(n)
#                 with s.label('default'):
#                     s.write_code('return false')
#         else:
#             # Leaf case - if the next character is not the end of the
#             # word, it means that our word is longer than the keyword
#             s.write_code("return *cursor == '\\0'")
#
#     with s.block('bool is_keyword(const char* keyword)'):
#         s.write_code('char *cursor = const_cast<char*>(keyword)')
#         s.write_line()
#         write_node_rec(root)
#
#     s.save(source_file)

def add_enum(file: CppBuilder, enum_list: list, enum_name: str):
    file.write_line("enum " + enum_name + " {")

    enum_string = ""

    for index, enum_qualifier in enumerate(enum_list):
        if index != 0:
            enum_string += "\n"

        enum_string += enum_qualifier.replace(".\\", "").replace(".", "$").replace("\\", "$") + ", "

    file.write_line(enum_string)
    file.write_line("};")


def generate_enums(header_file: str):
    header = CppBuilder()
    header.write_line('#pragma once')
    header.write_line("")
    header.write_line("#include <string>")
    header.write_line("")
    header.write_line("namespace assets {")
    header.indent()

    shaders = list()
    models = list()
    sounds = list()
    materials = list()
    images = list()

    for currentDir, sub_directories, contained_files in os.walk(path):
        print("Looking for assets in:\n", currentDir)

        current_relative = os.path.relpath(currentDir, path)

        for file in contained_files:
            if file.endswith(".glsl"):
                shaders.append(os.path.join(current_relative, file))
            if file.endswith(".mtl"):
                materials.append(os.path.join(current_relative, file))
            if file.endswith((".jpg", ".png")):
                images.append(os.path.join(current_relative, file))
            if file.endswith((".obj", ".fbx")):
                models.append(os.path.join(current_relative, file))
            if file.endswith((".wav", ".mp3")):
                sounds.append(os.path.join(current_relative, file))

    add_enum(header, shaders, "Shaders")
    header.write_line("")
    add_enum(header, models, "Models")
    header.write_line("")
    add_enum(header, sounds, "Sounds")
    header.write_line("")
    add_enum(header, materials, "Materials")
    header.write_line("")
    add_enum(header, images, "Images")

    header.write_line()

    header.write_code(
        "class AssetTranslator {\n" +
        "public:\n" +
        "static std::string TranslateShader(Shaders shader) {\n" +
        "return shaderDict[shader];\n" +
        "}\n\n" +
        "static std::string TranslateModel(Models model) {\n" +
        "return modelDict[model];\n" +
        "}\n\n" +
        "static std::string TranslateSound(Sounds sound) {\n" +
        "return soundDict[sound];\n" +
        "}\n\n" +
        "static std::string TranslateMaterial(Materials material) {\n" +
        "return materialDict[material];\n" +
        "}\n\n" +
        "static std::string TranslateImage(Images image) {\n" +
        "return imageDict[image];\n" +
        "}\n\n" +
        "private:\n" +
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
        "};\n")

    header.write_line("}")

    header.save(header_file)


if __name__ == "__main__":
    generate_enums("../Test.h")
