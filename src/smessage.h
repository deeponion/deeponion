// Copyright (c) 2019 The DeepOnion developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SEC_MESSAGE_H
#define SEC_MESSAGE_H

#include <support/allocators/secure.h>
#include <string.h>
#include <vector>

const unsigned int SMS_CRYPTO_KEY_SIZE = 32;
const unsigned int SMS_CRYPTO_IV_SIZE = 16;

class SecMsgCrypter
{
private:
    std::vector<unsigned char, secure_allocator<unsigned char>> chKey;
    std::vector<unsigned char, secure_allocator<unsigned char>> chIV;
    bool fKeySet;
public:

    SecMsgCrypter()
    {
        fKeySet = false;
        chKey.resize(SMS_CRYPTO_KEY_SIZE);
        chIV.resize(SMS_CRYPTO_IV_SIZE);
    }

    ~SecMsgCrypter()
    {
        // clean key
        memory_cleanse(chKey.data(), chKey.size());
        memory_cleanse(chIV.data(), chIV.size());
        fKeySet = false;
    }
    bool SetKey(const std::vector<uint8_t> &vchNewKey, const uint8_t *chNewIV);
    bool SetKey(const uint8_t *chNewKey, const uint8_t *chNewIV);
    bool Encrypt(const uint8_t *chPlaintext, uint32_t nPlain, std::vector<uint8_t> &vchCiphertext) const;
    bool Decrypt(const uint8_t *chCiphertext, uint32_t nCipher, std::vector<uint8_t> &vchPlaintext) const;
};


#endif // SEC_MESSAGE_H
