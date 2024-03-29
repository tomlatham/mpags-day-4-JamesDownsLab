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

    // Remove non-alpha characters
    auto iterNonAlpha = std::remove_if(
            key_.begin(),
            key_.end(),
            [] (char i) {return !std::isalpha(i);});
    key_.erase(iterNonAlpha, key_.end());

    // Change J -> I
    std::transform(
            key_.begin(),
            key_.end(),
            key_.begin(),
            [] (char i) { return (i == 'J') ? 'I' : i;}
    );

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

    // Store the coords of each letter in a map
    for (size_t i{0}; i<key_.size(); i++){
        Point coord = {i%5, i/5}; // x is row, y is column
        letterToCoordMap_.insert(std::pair <char, Point> {key_[i], coord});
        coordToLetterMap_[coord] = key_[i];
    }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {
    std::string outputText;
    switch (cipherMode) {
        case CipherMode::Encrypt : {
            outputText = setupInputText(inputText);
            break;
        }
        case CipherMode::Decrypt : {
            outputText = inputText;
            break;
        }
    }

    std::string digraph{"AA"};
    // Loop over the input in Digraphs
    for (size_t i{0}; i<outputText.size(); i+=2) {
        std::copy(outputText.begin()+i, outputText.begin()+i+2, digraph.begin());

        Point first_coord = (*letterToCoordMap_.find(digraph[0])).second;
        Point second_coord = (*letterToCoordMap_.find(digraph[1])).second;

        //  - Apply the rules to these coords to get new coords
        if (first_coord.y == second_coord.y){
            // same row
            if (cipherMode==CipherMode::Encrypt) {
                first_coord.x = (first_coord.x + 1) % 5;
                second_coord.x = (second_coord.x + 1) % 5;
            }
            else {
                first_coord.x = (first_coord.x - 1 + 5) % 5; // add 5 to prevent underflow
                second_coord.x = (second_coord.x - 1 + 5) % 5; // add 5 to prevent underflow
            }
        }
        else if (first_coord.x == second_coord.x) {
            // same column
            if (cipherMode == CipherMode::Encrypt) {
                first_coord.y = (first_coord.y + 1) % 5;
                second_coord.y = (second_coord.y + 1) % 5;
            }
            else {
                first_coord.y = (first_coord.y - 1 + 5) % 5;
                second_coord.y = (second_coord.y -1 + 5) % 5;
            }
        }
        else {
            // coords make opposite corners of rectangle
            // swap the x-coordinates
            std::swap(first_coord.x, second_coord.x);
        }

        //  - Find the letter associated with the new coords
        digraph[0] = (*coordToLetterMap_.find(first_coord)).second;
        digraph[1] = (*coordToLetterMap_.find(second_coord)).second;
        outputText.replace(outputText.begin()+i, outputText.begin()+i+2, digraph);
    }
    // Return the text
    return outputText;
}

std::string PlayfairCipher::setupInputText(const std::string& inputText) const {
    std::string outputText {inputText};
    // Change J -> I
    std::transform(
            outputText.begin(),
            outputText.end(),
            outputText.begin(),
            [] (char i) { return (i == 'J') ? 'I' : i;}
    );

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

    // if the size of the input is odd, add a trailing Z
    if (outputText.size() % 2 != 0){
        outputText += "Z";
    }

    return outputText;
}