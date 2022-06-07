# easy_encrypt_cpp

<b>Latest update partially untested.</b>
- Freed variables
- Added GCM support
- Added 192 bit encryption for all algorithms
- Created AESData class and functions

Easy one line function calls for AES Encryption, SHA hashes, MD5 hashes, RSA Public Key encryption with Private Key decryption, key generation, encoding and other utilities using the OpenSSL 3 library.<br><br>This branch differs from the 'past' branch due to the fact that it has been cleaned up and that most of the Hex and Base64 functions take the string type. This is for data with multiple null terminator characters (string type is not terminated by `'\0'` like char array strings). To create a string from a char array with multiple `'\0'` characters call the arrToStr utility function.

# the EasyEncrypt class

The source code for the EasyEncrypt class is available in this repo and contains five inner classes: AES, AESData, SHA, MD5, PublicKey (with KeyPair), Random and Utils.<br><br>
AES includes GCM-256/192/128 for key, iv (96 bits preferred), additional authenticated data (optional: pass empty string), and tag verification encryption/decryption. Plus CBC-256/192/128 for key + iv encryption/decrypiton as well as EBC-256/192/128 for key only encryption/decryption. AES uses PKCS#7 padding. SHA contains the SHA hashing algorithms in both 256 bit and 512 bit as well as an HMAC 256 & 512 bit hash function that accepts a key of any length. MD5 contains one function to get the 128 bit MD5 result of the input.
<br><br>Each of the AES and one way hash functions have inner classes for easy use with Hex/Base64 parameters and return types. During <b>encryption</b> (encrypt == true), input data is recognized as regular characters. During <b>decryption</b> (encrypt == false), input data is recognized the same as the return type (base64 or hex) of the encryption call. PublicKey consists of functions that support Public Key encryption and Private Key decryption plus a KeyPair class to create new Public and Private keys. If you do not wish to use a password for the private key, simply pass NULL for the password param. 
<br><br>There are multiple utility functions that support encryption, decryption, and the hashing of data as well as encoding functions to convert between bytes, hex, and base64 as well as hex->base64 & base64->hex. Secure random functions are also available for use to generate keys, ivs, and random numbers.
<br><br>
GCM encryption/decryption requires use of the AESData class. You can either call one of the constructors or use the "create" functions for standard use with the encoding you prefer. If you're not using additional authenticated data, you can either pass NULL or use the constructor or "create" function that does not have the aad parameter. If you're decrypting data and already have the tag value, you will need to use one of the "set" functions for the tag value.<br><br><b>Using the AESData function calculates the key and iv size based on your input.</b><br>Make sure your input is the appropriate size for what you're encrypting or decrypting. There are no checks for this within the functions. 256 bit encryption requires a 32 byte (256 bit) key and 16 byte (128 bit) IV. 192 requires a 24 byte key and 16 byte IV. 128 requires a 16 byte key and IV. Additional Authenticated Data in GCM can be any length. The tag length used within the GCM functions is a set 16 bytes.<br><br>
There are multiple set functions for the AESData class that support already encoded data or raw data from a char array (which gets encoded by the function). After encryption/decryption you can access the objects values to get the plaintext or encrypted data, check if the tag verifies, and change encryption direction (encrypt or decrypt). The encoded GCM functions return the updated AESData object.<br><br>
All algorithms in this class have the regular char array types available for optional use. In the header they are above the Hex & Base64 class definitions and are static functions returning a char pointer (char*). These do not accept hex or base64 encoding and must be raw char arrays. They also return a char array with the size available by passing an int pointer (int*) that gets updated after encryption/decryption. All of the encoded functions use the char* returning functions along with the utility (Utils) functions. Advanced usage is supported by both the char* returning functions and use of the utility functions.<br><br>
Public Key encryption and Private Key decryption is available using the PublicKey class. It uses the RSA algorithm with your desired bit size. You can create a new key pair using the inner KeyPair class. Please note that this key pair is saved into a variable and will not be created on the file system. If you need a copy on the file system, just use the get function and create + write to your file. <b>The encoded functions accept only the original Base64 private and public keys with the appropriate start and end line</b>. There is no need to remove the first and last lines and encode/decode the file. The <b>input data</b> that you're decrypting with the encoded functions will need to be in either Base64 or Hex and the encryption function will return a Base64 or Hex value. This is not true if you decide to use the char* returning functions for advanced usage.
