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
    const std::string alphabet_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    /// Use a typedef for improved clarity
    using PlayfairCoord = std::pair<size_t,size_t>;

    /// Key_map, char: (column, row)
    std::map<char,PlayfairCoord> letterToCoordMap_;

    /// Keymap., (column, row): char
    std::map<PlayfairCoord,char> coordToLetterMap_;

    /**
     * \brief Set the key for the cipher
     * \param key string used to generate digraph
     */
    void setKey(const std::string &key);

    /**
     * \brief Implement rules to setup input text
     * \param inputText
     * \return string with repeated letters in digraphs fixed and Z's appended to odd length strings
     */
    std::string setupInputText(const std::string &inputText) const;
};


#endif //MPAGSCIPHER_PLAYFAIRCIPHER_HPP
