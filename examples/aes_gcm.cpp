//
// Created by ryanfitzgerald on 6/6/22.
//

#include <iostream>
#include "EasyEncrypt.h"

int main() {

    //Creating a HEX key and iv (256 bit & 128 bit == 256 bit encryption)
    std::string hex_key = EasyEncrypt::Random::secureEncoded(EasyEncrypt::HEX, 32);
    std::string hex_iv = EasyEncrypt::Random::secureEncoded(EasyEncrypt::HEX, 16);

    //Getting some Additional Authenticated Data (random bytes) [optional]
    std::string hex_aad = EasyEncrypt::Random::secureEncoded(EasyEncrypt::HEX, 16);

    //GCM encoded Encryption/Decryption requires the use of
    //the AESData class

    //Creating an AESData object using the constructor that has an aad parameter
    //algorithm_t algorithm, encode_t encoding, std::string key, std::string iv, std::string aad, bool encrypt
    EasyEncrypt::AESData *aes_obj1 = new EasyEncrypt::AESData(EasyEncrypt::algorithm_t::GCM, EasyEncrypt::encode_t::HEX,
                                                              hex_key, hex_iv, hex_aad, true);

    //Setting the plaintext
    aes_obj1->plaintext = "My Encrypted Message";

    //Encrypting and storing the result in the same AESData object
    *aes_obj1 = EasyEncrypt::AES::Hex::gcm(*aes_obj1);

    //Printing the encrypted result encoded as a hex string
    std::cout << "Encrypted Result 1: " << aes_obj1->encrypted << std::endl;

    //Printing the encrypted result encoded as a hex string
    std::cout << "Tag Value: " << aes_obj1->tag << std::endl;

    //Setting the do_encrypt variable to false
    //** this step is not required if you keep a copy of the AESData object
    //   after encryption, the do_encrypt variable is changed to false.
    aes_obj1->do_encrypt = false;

    //Decrypting and storing the result in the same AESData object
    *aes_obj1 = EasyEncrypt::AES::Hex::gcm(*aes_obj1);

    //Printing the encrypted result encoded as a hex string
    std::cout << "Decrypted Result 1: " << aes_obj1->plaintext << std::endl;

    //checking to see if tag is verified
    std::cout << "Tag Verifies: " << ((aes_obj1->tag_verifies) ? "Yes" : "No") << std::endl;

    /*
     * --------------------------------------------------------------------------------
     */

    //Additional Authenticated Data is optional
    //This example uses none by setting the aad to an empty string
    //alternatively, you can call the constructor that doesn't have an aad parameter.

    std::string input = "My Other Encrypted Message";

    //Creating an AESData object using the gcm_gcm_hex_create;
    //std::string input, std::string key, std::string iv,  std::string aad, bool encrypt
    EasyEncrypt::AESData* aes_obj2 = EasyEncrypt::AESData::gcm_hex_create(input, hex_key,
                                                                hex_iv, "", true);

    //encrypting and storing in a new object
    EasyEncrypt::AESData gcm_res = EasyEncrypt::AES::Hex::gcm(*aes_obj2);

    //Printing the encrypted result encoded as a hex string
    std::cout << "Encrypted Result 2: " << gcm_res.encrypted << std::endl;

    //Setting the object to decryption
    //** this step is not required if you keep a copy of the AESData object
    //   after encryption, the do_encrypt variable is changed to false.
    gcm_res.do_encrypt = false;

    //Decrypting and storing in previously created result object
    gcm_res = EasyEncrypt::AES::Hex::gcm(gcm_res);

    //Printing the encrypted result encoded as a hex string
    std::cout << "Decrypted Result 2 " << gcm_res.plaintext << std::endl;

    //checking to see if tag is verified
    std::cout << "Tag Verifies: " << ((gcm_res.tag_verifies) ? "Yes" : "No") << std::endl;

    return 0;

}
