import base64

# Print the result of each decoding layer
def print_layer(layer_num, encoding_type, content):
    header = f"\n=========== {layer_num} Layer ({encoding_type}) ===========\n"
    print(header)
    print(content)


# Morse Code dictionary map
morse_dict = {
    '.-': 'A', '-...': 'B', '-.-.': 'C', '-..': 'D', '.': 'E',
    '..-.': 'F', '--.': 'G', '....': 'H', '..': 'I', '.---': 'J',
    '-.-': 'K', '.-..': 'L', '--': 'M', '-.': 'N', '---': 'O',
    '.--.': 'P', '--.-': 'Q', '.-.': 'R', '...': 'S', '-': 'T',
    '..-': 'U', '...-': 'V', '.--': 'W', '-..-': 'X', '-.--': 'Y',
    '--..': 'Z', '-----': '0', '.----': '1', '..---': '2',
    '...--': '3', '....-': '4', '.....': '5', '-....': '6',
    '--...': '7', '---..': '8', '----.': '9'
}


# Read file
with open('zero_one', 'r') as f:
    digits = f.read()

# Replace to 0s and 1s
digits = digits.replace('ZERO', '0').replace('ONE', '1')
# Remove any spaces or special characters
digits = digits.replace(' ', '').replace('\n', '').replace('\t', '')


# =========== Binary Layer ============

# Convert to ASCII text (8 digits per character)
message = ""
for i in range(0, len(digits), 8):
    chunk = digits[i : i+8]    
    if len(chunk) < 8:
        break
    number = int(chunk, 2)
    character = chr(number)
    message += character

print_layer("1st", "Binary", message)


# =========== Second Layer ============

# Decode from Base64 to normal string
decoded_bytes = base64.b64decode(message)
decoded_text = decoded_bytes.decode('utf-8')

print_layer("2nd", "Base64", decoded_text)


# =========== Third Layer ============

# Decode using morse code
flag = ""
for m in decoded_text.split():
    flag += morse_dict[m]

print_layer("3rd", "Morse Code", flag)