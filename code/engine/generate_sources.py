import os
import sys

from codeGenerators.enumScanner import generate_enums

path = "D:\\UniStuff\\GameLab3\\code\\assets"


def main():

    if len(sys.argv) < 2:
        sys.stderr.write('Output path not provided.\n')
        sys.exit(1)

    output_folder = sys.argv[1]
    os.makedirs(output_folder, exist_ok=True)

    asset_header = os.path.join(output_folder, 'Assets.h')
    generate_enums(asset_header, path)


if __name__ == '__main__':
    main()
