//
// Created by james on 08/11/2019.
//

#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

PlayfairCipher::PlayfairCipher(const std::string key) {
    setKey(key);
}

void PlayfairCipher::setKey(const std::string& key) {
    key_ = key;
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {
    switch (cipherMode) {
        case CipherMode::Encrypt : {
            return inputText + "Encrypted";
        }
        case CipherMode::Decrypt : {
            return inputText + "Decrypted";
        }
    }
    return "";
}