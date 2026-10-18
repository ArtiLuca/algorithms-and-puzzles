import base64
import urllib.parse

with open("description.txt", "r", encoding="utf-8") as f:
    message = f.read()

print("\n" + message + "\n")

print("Base64: ")
print(message)

message = message.split("ciphertext: ")[-1].strip()
message_bytes = base64.b64decode(message)
message_text = message_bytes.decode("utf-8")

print("\nDecoded: ")
print(message_text)

# reverse encryption moving each hex pair 13 backwards
shifted_message = []
for c in message_text:

    # if Uppercase letter
    if 'A' <= c <= 'Z':
        # normalize
        normalized = ord(c) - 65
        # apply cipher
        shifted = (normalized + 13) % 26
        # convert to ASCII
        char = chr(shifted + 65)
        # append to result
        shifted_message.append(char)

    # if lowercase, analogous logic
    elif 'a' <= c <= 'z':
        normalized = ord(c) - 97
        shifted = (normalized + 13) % 26
        char = chr(shifted + 97)
        shifted_message.append(char)

    # if symbol or number, keep intact
    else:
        shifted_message.append(c)

# cleanup string
shifted_text = "".join(shifted_message)

print("\nApplying ROT-13 decryption algorithm: ")
print(shifted_text)

# URL Encoding
flag = urllib.parse.unquote(shifted_text)

print("\nFinal Flag: ")
print(flag)
