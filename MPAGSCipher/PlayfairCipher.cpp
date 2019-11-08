//
// Created by james on 08/11/2019.
//

#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"
#include "TransformChar.hpp"

#include <iostream>
#include <algorithm>


PlayfairCipher::PlayfairCipher(const std::string& key) {
    setKey(key);
}

void PlayfairCipher::setKey(const std::string& key) {
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += alphabet_;

    // Make sure the key is uppercase
    std::transform(
            key_.begin(),
            key_.end(),
            key_.begin(),
            ::toupper
    );
    std::cout << "Capitalised key : " + key_ << std::endl;

    // Remove non-alpha characters
    auto iterNonAlpha = std::remove_if(
            key_.begin(),
            key_.end(),
            [] (char i) {return !std::isalpha(i);});
    key_.erase(iterNonAlpha, key_.end());
    std::cout << "Non-alpha characters removed : " + key_ << std::endl;

    // Change J -> I
    std::transform(
            key_.begin(),
            key_.end(),
            key_.begin(),
            [] (char i) {
                if (i == 'J'){
                    return 'I';
                }
                else {
                    return i;
                }
            }
    );
    std::cout << "J's turned to I's : " + key_ << std::endl;

    // Remove duplicated letters
    std::string encountered_characters{};
    auto iterDuplicated = std::remove_if(
            key_.begin(),
            key_.end(),
            [&] (char c) {
                if (encountered_characters.find(c) == std::string::npos){
                    encountered_characters += c;
                    return false;
                }
                else {
                    return true;
                }
            }
    );
    key_.erase(iterDuplicated, key_.end());
    std::cout << "Repeats removed : " + key_ << std::endl;

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