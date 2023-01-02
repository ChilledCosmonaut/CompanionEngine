import os
import sys

from codeGenerators.enumScanner import generate_enums

relative_asset_path = "..\\assets"


def main():

    if len(sys.argv) < 2:
        sys.stderr.write('Output path not provided.\n')
        sys.exit(1)

    if len(sys.argv) < 3:
        sys.stderr.write('Asset path not provided.\n')
        sys.exit(1)

    output_folder = sys.argv[1]
    asset_folder = os.path.join(sys.argv[2], relative_asset_path)
    os.makedirs(output_folder, exist_ok=True)

    asset_header = os.path.join(output_folder, 'Assets.h')
    generate_enums(asset_header, asset_folder)


if __name__ == '__main__':
    main()
