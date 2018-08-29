// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2017 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_KEY0_H
#define BITCOIN_KEY0_H

#include <pubkey.h>
#include <serialize.h>
#include <uint256.h>

#include <stdexcept>
#include <vector>

#include <openssl/ec.h> // for EC_KEY definition - DeepOnion: Ported

class key_error : public std::runtime_error
{
public:
    explicit key_error(const std::string& str) : std::runtime_error(str) {}
};


/** An encapsulated private key. */
class CKey0
{
protected:
	// DeepOnion: Port for PoS
	EC_KEY* pkey;
    bool fSet;
    bool fCompressedPubKey;

public:
    /**
     * secp256k1:
     */
    static const unsigned int PRIVATE_KEY_SIZE            = 279;
    static const unsigned int COMPRESSED_PRIVATE_KEY_SIZE = 214;
    /**
     * see www.keylength.com
     * script supports up to 75 for single byte push
     */
    static_assert(
        PRIVATE_KEY_SIZE >= COMPRESSED_PRIVATE_KEY_SIZE,
        "COMPRESSED_PRIVATE_KEY_SIZE is larger than PRIVATE_KEY_SIZE");

private:
    //! Whether this private key is valid. We check for correctness when modifying the key
    //! data, so fValid should always correspond to the actual state.
    bool fValid;

    //! Whether the public key corresponding to this private key is (to be) compressed.
    bool fCompressed;

 
public:
    //! Construct an invalid private key.
    CKey0() : pkey(NULL), fSet(false), fCompressedPubKey(false), fValid(false), fCompressed(false)
    {}

    ~CKey0();

    //! Check whether this private key is valid.
    bool IsValid() const { return fValid; }

    //! Check whether the public key corresponding to this private key is (to be) compressed.
    bool IsCompressed() const { return fCompressed; }

    // DeepOnion: Ported for PoS Signature checking.
    bool SetPubKey(const CPubKey& vchPubKey);
    bool Verify(uint256 hash, const std::vector<unsigned char>& vchSig);
    void Reset();

};


#endif // BITCOIN_KEY0_H
