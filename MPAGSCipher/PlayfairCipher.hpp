//
// Created by james on 08/11/2019.
//

#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <map>
#include "CipherMode.hpp"


/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
public:
    /**
     * Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit PlayfairCipher(const std::string& key);

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string &inputText, const CipherMode cipherMode) const;

private:
    /// The cipher key used to generate the digraph
    std::string key_{""};

    /// Alphabet appended to
    std::string alphabet_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    /// Key_map, char: (column, row)
    std::map<char, std::pair <int, int>> letterToCoordMap_;

    /// Keymap., (column, row): char
    std::map<std::pair <int, int>, char> coordToLetterMap_;

    /**
     * \brief Set the key for the cipher
     * \param key string used to generate digraph
     */
    void setKey(const std::string &key);

    std::string setupInputText(const std::string &inputText) const;
};


#endif //MPAGSCIPHER_PLAYFAIRCIPHER_HPP
