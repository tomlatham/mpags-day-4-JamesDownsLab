//
// Created by james on 08/11/2019.
//

#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"
#include "TransformChar.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

PlayfairCipher::PlayfairCipher(const std::string key) {
    setKey(key);
}

void PlayfairCipher::setKey(const std::string& key) {
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += alphabet_;

    // Make sure the key is uppercase
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
    std::cout << "Capitalised key : " + key_ << std::endl;

    // Remove non-alpha characters

    // Change J -> I

    // Store the coords of each letter

    // Store the playfair cipher key map
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

    // Change J -> I

    // If repeated characters in a digraph add an X or Q if XX

    // if the size of the input is odd, add a trailing Z

    // Loop over the input in Digraphs

    //  - Find the coords in the grid of each digraph

    //  - Apply the rules to these coords to get 'new' coords

    //  - Find the letter associated with the new coords

    // Return the text
}