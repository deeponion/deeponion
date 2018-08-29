
#include <key0.h>

#include <arith_uint256.h>
#include <crypto/common.h>
#include <crypto/hmac_sha512.h>
#include <random.h>

#include <secp256k1.h>
#include <secp256k1_recovery.h>

// DeepOnion: Port PoS
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>


// DeepOnion: Porting for PoS
CKey0::~CKey0()
{
	if(pkey != NULL)
		EC_KEY_free(pkey);
}

// DeepOnion: Porting for PoS
void CKey0::Reset()
{
    fCompressedPubKey = false;
    if (pkey != NULL)
        EC_KEY_free(pkey);
    pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (pkey == NULL)
        throw key_error("CKey::Reset() : EC_KEY_new_by_curve_name failed");
    fSet = false;
}

// DeepOnion: Porting for PoS
bool CKey0::SetPubKey(const CPubKey& vchPubKey)
{
	Reset();
    const unsigned char* pbegin = vchPubKey.begin();
    if (o2i_ECPublicKey(&pkey, &pbegin, vchPubKey.size()))
    {
        fSet = true;
        if (vchPubKey.size() == 33)
        		fCompressedPubKey = true;
        return true;
    }
    pkey = NULL;
    Reset();
    return false;
}

// DeepOnion: Porting for PoS
bool CKey0::Verify(uint256 hash, const std::vector<unsigned char>& vchSigParam)
{
    // Prevent the problem described here: https://lists.linuxfoundation.org/pipermail/bitcoin-dev/2015-July/009697.html
    // by removing the extra length bytes
    std::vector<unsigned char> vchSig(vchSigParam.begin(), vchSigParam.end());
    if (vchSig.size() > 1 && vchSig[1] & 0x80)
    {
        unsigned char nLengthBytes = vchSig[1] & 0x7f;
        if (nLengthBytes > 4)
        {
            unsigned char nExtraBytes = nLengthBytes - 4;
            for (unsigned char i = 0; i < nExtraBytes; i++)
                if (vchSig[2 + i])
                    return false;
            vchSig.erase(vchSig.begin() + 2, vchSig.begin() + 2 + nExtraBytes);
            vchSig[1] = 0x80 | (nLengthBytes - nExtraBytes);
        }
    }

    if (vchSig.empty())
        return false;

    // New versions of OpenSSL will reject non-canonical DER signatures. de/re-serialize first.
    unsigned char *norm_der = NULL;
    ECDSA_SIG *norm_sig = ECDSA_SIG_new();
    const unsigned char* sigptr = &vchSig[0];
    assert(norm_sig);
    if (d2i_ECDSA_SIG(&norm_sig, &sigptr, vchSig.size()) == NULL)
    {
        /* As of OpenSSL 1.0.0p d2i_ECDSA_SIG frees and nulls the pointer on
         * error. But OpenSSL's own use of this function redundantly frees the
         * result. As ECDSA_SIG_free(NULL) is a no-op, and in the absence of a
         * clear contract for the function behaving the same way is more
         * conservative.
         */
        ECDSA_SIG_free(norm_sig);
        return false;
    }
    int derlen = i2d_ECDSA_SIG(norm_sig, &norm_der);
    ECDSA_SIG_free(norm_sig);
    if (derlen <= 0)
        return false;

    // -1 = error, 0 = bad sig, 1 = good
    bool ret = ECDSA_verify(0, (unsigned char*)&hash, sizeof(hash), norm_der, derlen, pkey) == 1;
    OPENSSL_free(norm_der);
    return ret;
}
