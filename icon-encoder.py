from PIL import Image # image processing
from sys import exit # exit
from sys import argv # to get the name of the script
from blessed import Terminal # pretty colors
from os.path import isfile # check if a path is a valid file
import argparse # argument parser
import pathlib # better handling of file paths


def main():
    # used to print colors
    term = Terminal()
    # nice error message
    error = f"{term.bold(argv[0] + ":")} {term.bold_bright_red("error:")}"
    
    args = parse_args()

    size = (35, 35)

    output = ""

    for file in args.filename:
        try:
            image = Image.open(file)
        except FileNotFoundError:
            print(f"{error} input image does not exist at: {file.absolute()}")
            exit(1)

        if image.getcolors() is None or len(image.getcolors()) > 2:
            print(f"{error} cannot encode images with more than two colors")
            exit(1)
            
        # splits the filename from the extention
        name = file.name.split(".")[0]

        # appends bool name[size1][size2] to the array and adds it to the output
        output += f"bool {name}[{size[0]}][{size[1]}] = " + format(parse_image(image, size, args.invert))

    # formating creates extra newlines
    output = output.strip()

    # applies the template
    output = apply_template(output, args.template)

    # print if there is no alternet output set
    if args.output is None:
        print(output)
    else:
        with open(args.output, "w+") as file:
            file.write(output)
        
# makes the array not be a one line mess
def format(data: str) -> str:
    data = data.replace("[", "\n{")
    data = data.replace("]", "}")
    data += ";"
    data += "\n\n"

    return data

# applies the template if provided, else returns the input data
def apply_template(data: str, template: str|pathlib.Path) -> str:
    if type(template) is str:
        output = template.format(data)
        
    elif isinstance(template, pathlib.PurePath):
        with open(template, "r") as file:
            template = file.read()
            output = template % data
    else:
        output = data

    return output
    
# sorts colors based on their "brightness"
def sort_colors(colors: list[tuple[int, int, int]], invert: bool) -> list[tuple[int, int, int]]:
    # blank dict to hold the brightness as the key and the rgb as the value
    brightneses = {}
    
    for color in colors:
        r = color[0]
        g = color[1]
        b = color[2]

        # greyscales the color to get its brightness, formula from:
        # https://pillow.readthedocs.io/en/stable/reference/Image.html#PIL.Image.Image.convert
        brightness = r * 299/1000 + g * 587/1000 + b * 114/1000

        brightneses[brightness] = color
    
    # uses the standerd python sort function
    sorted_colors = sorted(brightneses.values(), reverse=invert)

    return sorted_colors
        


def parse_image(image: Image.Image, size: tuple[int], invert: bool) -> str:
    array = list(generate_array(size))

    # makes sure that the image is the same size as the array
    # the default resampling algorithem blends colors when resizing, so the image would not be
    # two colors, the nearest algorithem just uses the naive way of getting the nearest color
    image = image.resize(size, Image.Resampling.NEAREST)

    # the color rules only work in rgb
    image = image.convert('RGB')

    # turns the image into an array of data
    pixels = image.load()

    # the order of the colors is random, so they need to be sorted
    # the first subscript returns a tuple of the number of times it is used and the actual color
    # so it needs to be subscripted again
    color1 = image.getcolors()[0][1]
    color2 = image.getcolors()[1][1]

    # sorts the colors by their brightness, from high to low
    sorted_colors = sort_colors([color1, color2], invert)

    for i in range(size[0]):
        for j in range(size[1]):
            if pixels[i, j] == sorted_colors[0]:
                # i and j have to be fliped so that the image is not rotated 90 deg
                array[j][i] = 1
            elif pixels[i, j] == sorted_colors[1]:
                # i and j are also fliped here
                array[j][i] = 0

    return str(array)

def generate_array(dimentions: tuple[int]) -> str:
    if len(dimentions) < 1:
        return ""

    # gets appended to itself for each dimension
    loop = " for i in range({})]"
    
    placeholder = str(0)

    # the loop expresion does not generate the "[" so this addes them plus a placeholder
    output_generator = "[" * len(dimentions) + placeholder
    
    for i in range(len(dimentions)):
        # appends the loops with the number of times that they loop in reverse order
        output_generator += loop.format(dimentions[-len(dimentions)+i])
    
    # runs the generated code
    # exec does not take locals and globals from where it was called, so a context dict is
    # needed to act as a place to put the new set of locals and to retrive them later
    context = {}
    exec("output = " + output_generator, None, context)

    return context["output"]

def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Takes a two color image and returnes a 35x35 array representation of that image")

    parser.add_argument("filename", action="store", type=pathlib.Path, nargs="+",
    help="path of input image")

    parser.add_argument("--output", action="store", type=pathlib.Path, help="path of output file", required=False)

    # the lambda says that if the template is a valid file, the type shouldbe file, else it is str
    path_or_string = lambda text : pathlib.Path(text) if isfile(text) else text

    parser.add_argument("--template", action="store", type=path_or_string, help="a template to put the result into with c format syntax", required=False)

    parser.add_argument("--invert", action="store_true", help="Flips the 1's and 0's in the output")

    return parser.parse_args()

if __name__ == "__main__":
    main()