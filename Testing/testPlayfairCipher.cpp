//! Unit Tests for MPAGSCipher PLayfairCipher class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Playfair cipher encryption", "[playfair]"){
    PlayfairCipher pc{"playfair example"};
    REQUIRE(pc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "DMYRANVQCRHV");
}

TEST_CASE("Playfair cipher decryption", "[playfair]"){
    PlayfairCipher pc{"playfair example"};
    REQUIRE(pc.applyCipher("DMYRANVQCRHV", CipherMode::Decrypt) == "HELXLOWORLDZ");
}