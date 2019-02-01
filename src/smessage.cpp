// Copyright (c) 2017-2019 The DeepOnion Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "smessage.h"

#include <crypto/aes.h>

bool SecMsgCrypter::SetKey(const std::vector<uint8_t> &vchNewKey, const uint8_t *chNewIV)
{
    if (vchNewKey.size() != SMS_CRYPTO_KEY_SIZE)
        return false;

    return SetKey(&vchNewKey[0], chNewIV);
};

bool SecMsgCrypter::SetKey(const uint8_t *chNewKey, const uint8_t *chNewIV)
{
    memcpy(chKey.data(), chNewKey, chKey.size());
    memcpy(chIV.data(), chNewIV, chIV.size());

    fKeySet = true;
    return true;
};

bool SecMsgCrypter::Encrypt(const uint8_t *chPlaintext, uint32_t nPlain, std::vector<uint8_t> &vchCiphertext) const
{
    if (!fKeySet)
        return false;

    // max ciphertext len for a n bytes of plaintext is
    // n + AES_BLOCKSIZE bytes
    vchCiphertext.resize(nPlain + AES_BLOCKSIZE);

    AES256CBCEncrypt enc(chKey.data(), chIV.data(), true);
    size_t nLen = enc.Encrypt(&chPlaintext[0], nPlain, vchCiphertext.data());
    if(nLen < nPlain)
        return false;
    vchCiphertext.resize(nLen);

    return true;
};

bool SecMsgCrypter::Decrypt(const uint8_t *chCiphertext, uint32_t nCipher, std::vector<uint8_t> &vchPlaintext) const
{
    if (!fKeySet)
        return false;

    // plaintext will always be equal to or lesser than length of ciphertext
    int nLen=nCipher;// = chCiphertext.size();

    vchPlaintext.resize(nLen);

    AES256CBCDecrypt dec(chKey.data(), chIV.data(), true);
    nLen = dec.Decrypt(chCiphertext, nCipher, &vchPlaintext[0]);
    if(nLen == 0)
        return false;

    vchPlaintext.resize(nLen);
    return true;
};
