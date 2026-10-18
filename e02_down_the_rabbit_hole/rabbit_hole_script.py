import base64
import urllib.parse

# Keep a log of each layer encoded by writing to file
def log_layer(layer_num, encoding_type, content):

    header = f"\n=========== {layer_num} Layer ({encoding_type}) ===========\n"
    
    # Print the header and the first 500 characters
    print(header + content[:500] + "\n...")
    
    # Append the full content to a single log file
    with open("all_layers_log.txt", "a", encoding="utf-8") as out_file:
        out_file.write(header + content[:500] + "\n...")


# Stored ASCII text
ascii_text = []

# Read input file
with open("challenge.txt", "r", encoding="utf-8") as f:

    # one line at a time
    for line in f:

        # Split line into space-separated chunks of 8-bit digits
        for chunk in line.split():

            # Filter out non-binary characters or non-valid length chunks
            if len(chunk) == 8 and all(c in '01' for c in chunk):
                number = int(chunk, 2)
                character = chr(number)
                ascii_text.append(character)


#  =========== 1st Layer ===========

# Strip out unneeded characters from decoded first layer
first_layer = "".join(ascii_text)
log_layer("1st", "Binary", first_layer)


#  =========== 2nd Layer ===========

# Decode from Base64, first stripping initial text
initial_second_layer = first_layer.split("\n\n")[-1].strip()
second_layer_bytes = base64.b64decode(initial_second_layer)
second_layer = second_layer_bytes.decode("utf-8")

log_layer("2nd", "Base64", second_layer)  


#  =========== 3rd Layer ===========

# Decode from Hex, stripping initial text
initial_third_layer = second_layer.split("\n\n")[-1].strip()
third_layer_bytes = bytes.fromhex(initial_third_layer)
third_layer = third_layer_bytes.decode("utf-8")

log_layer("3rd", "Hex", third_layer)


#  =========== 4th Layer ===========

initial_fourth_layer = third_layer.split("\n\n")[-1].strip()

# Remove all newline char, spaces, and append '=' to make exact multiple of 8
initial_fourth_layer = initial_fourth_layer.replace("\n", "")
initial_fourth_layer = initial_fourth_layer.replace(" ", "")

while len(initial_fourth_layer) % 8 != 0:
    initial_fourth_layer += "=" 

fourth_layer_bytes = base64.b32decode(initial_fourth_layer)
fourth_layer = fourth_layer_bytes.decode("utf-8")

log_layer("4th", "Base32", fourth_layer)


#  =========== 5th Layer ===========

initial_fifth_layer = fourth_layer.split("\n\n")[-1].strip()
fifth_layer_bytes = base64.b64decode(initial_fifth_layer)
fifth_layer = fifth_layer_bytes.decode("utf-8")

log_layer("5th", "Base64", fifth_layer)


#  =========== 6th Layer ===========

# Again, Base64...
initial_sixth_layer = fifth_layer.split("\n\n")[-1].strip()
sixth_layer_bytes = base64.b64decode(initial_sixth_layer)
sixth_layer = sixth_layer_bytes.decode("utf-8")

log_layer("6th", "Base64", sixth_layer)


#  =========== 7th Layer ===========

# No need to write to file - printing to terminal is manegeable now
initial_seventh_layer = sixth_layer.split("\n\n")[-1].strip()
seventh_layer_bytes = bytes.fromhex(initial_seventh_layer)
seventh_layer = seventh_layer_bytes.decode("utf-8")

log_layer("7th", "Hex", seventh_layer)


# =========== 8th Layer ============

initial_eighth_layer = seventh_layer.split("\n\n")[-1].strip()
ascii_text_eighth = []

# Its binary again...
for chunk in initial_eighth_layer.split():
    if len(chunk) < 8:
        break
    number = int(chunk, 2)
    character = chr(number)
    ascii_text_eighth.append(character)

eighth_layer = "".join(ascii_text_eighth)

log_layer("8th", "Binary ASCII", eighth_layer)


# =========== 9th Layer ============
initial_ninth_layer = eighth_layer.split("\n\n")[-1].strip()
ninth_layer_bytes = base64.b64decode(initial_ninth_layer)
ninth_layer = ninth_layer_bytes.decode("utf-8")

log_layer("9th", "Base64", ninth_layer)


# =========== 10th Layer ============
initial_tenth_layer = ninth_layer.split("\n\n")[-1].strip()
tenth_layer = urllib.parse.unquote(initial_tenth_layer)

log_layer("10th", "URL Encoding", tenth_layer)


# =========== 11th Layer ============
initial_eleventh_layer = tenth_layer.split("\n\n")[-1].strip()
eleventh_layer_bytes = initial_eleventh_layer.encode("utf-8")
eleventh_layer = eleventh_layer_bytes.decode("unicode_escape")

log_layer("11th", "Unicode", eleventh_layer)

# Save final result to HTML file
with open("down_rabbit_hole_flag.html", "w", encoding="utf-8") as out_flag:
    out_flag.write(eleventh_layer)

print("\nQR code HTML saved to 'down_rabbit_hole_flag.html'\n")
