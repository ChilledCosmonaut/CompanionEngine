import os
import sys

from codeGenerators.keywords import generate_enums


def main():

    if len(sys.argv) < 2:
        sys.stderr.write('Output path not provided.\n')
        sys.exit(1)

    output_folder = os.path.join(sys.argv[1], 'gen')
    os.makedirs(output_folder, exist_ok=True)

    asset_header = os.path.join(output_folder, 'Assets.h')
    # source = os.path.join(output_folder, 'source.cpp')
    generate_enums(asset_header)


if __name__ == '__main__':
    main()
