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
            [] (char i) { return (i == 'J') ? 'I' : i;}
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
    for (size_t i{0}; i<key_.size(); i++){
        std::pair <int, int> coord{i%5, i/5}; // x is row, y is column
        letterToCoordMap_[key_[i]] = coord;
        coordToLetterMap_[coord] = key_[i];
    }

    // Print the maps to test the output
    for ( auto p: letterToCoordMap_) {
        std::cout << p.first << ": (" << p.second.first << "," << p.second.second << ")" << std::endl;
    }
    for ( auto p: coordToLetterMap_) {
        std::cout << "(" << p.first.first << "," << p.first.second << ") : " << p.second << std::endl;
    }
    // Store the playfair cipher key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {
    switch (cipherMode) {
        case CipherMode::Encrypt : {
            std::cout << "Encryption mode" << std::endl;
            break;
        }
        case CipherMode::Decrypt : {
            std::cout << "Decryption mode" << std::endl;
            break;
        }
    }


    std::string outputText {inputText};
    // Change J -> I
    std::transform(
            outputText.begin(),
            outputText.end(),
            outputText.begin(),
            [] (char i) { return (i == 'J') ? 'I' : i;}
    );
    std::cout << "J's in inputText turned to I's : "<< outputText << std::endl;

    // If repeated characters in a digraph add an X or Q if XX
    for (size_t i{0}; i<outputText.size(); i+=2){
        if (outputText[i] == outputText[i+1]){
            if (outputText[i] == 'X'){
                outputText.insert(i+1, "Q");
            }
            else {
                outputText.insert(i+1, "X");
            }
        }
    }
    std::cout << "Repeated characters managed : " << outputText << std::endl;

    // if the size of the input is odd, add a trailing Z
    if (outputText.size() % 2 != 0){
        outputText += "Z";
    }
    std::cout << "Odd inputs are appended with a Z : " << outputText << std::endl;

    // Loop over the input in Digraphs

    //  - Find the coords in the grid of each digraph

    //  - Apply the rules to these coords to get 'new' coords

    //  - Find the letter associated with the new coords

    // Return the text
    return outputText;
}