// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xc8;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xb3;
        vAlertPubKey = ParseHex("04ee242da332db74a1dd4e93379a060330bedcf312ffc427a6d493b2121135c6e7fec40dfa0b90351aa7d46cab6d24ca83ad711b8725bc287695a4e89cd6582b93");
        nDefaultPort = 61407;
        nRPCPort = 61408;
        bnProofOfWorkLimit = CBigNum().SetCompact(0x1e0fffff);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 48);
        
        const char* pszTimestamp = "BTC BLOCK# 000000000000000000142331a01ea23efb7ae9127bc4f82632857b9278d6ac25";
        std::vector<CTxIn> vin(1);
        std::vector<CTxOut> vout(1);
        CTransaction txNew(1, 1471793005, vin, vout, 0);

        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vin[0].scriptSig = CScript() << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << OP_DUP << OP_HASH160 << ParseHex("2f372d86441bdf927e63dbe980ef7898ccc19a91") << OP_EQUALVERIFY << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1471793005;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 746672;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xae7a50664a05dfce54b5a05ea97e0d6bfea43afdf6e40cbc1e52c77123eaa5b4"));
        assert(genesis.hashMerkleRoot == uint256("0x27d81118d8320a80f39a82de06b62144f15a63852056cedffefac9ab82c1408c"));

        vSeeds.push_back(CDNSSeedData("seed1", "185.92.220.214"));
        vSeeds.push_back(CDNSSeedData("seed1", "45.63.4.227"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(160);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(165);
        base58Prefixes[SECRET_KEY] =     list_of(288);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 10180;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xe3;
        pchMessageStart[3] = 0xd8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("046f4dfd34d771e76e3cc3ef575c9dba03bff876fcaedcf7d0dd12db27fb3ac703e66f5e9703fdba567e4a557a85b8ff4c070f277151b9b0f6f48f9f501c91ca84");
        nDefaultPort = 13305;
        nRPCPort = 13306;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 41542;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x5ebb7a3703fcc971da549c820923f4999d5ee1daa146ee3d3dc80ebb4c2d88ec"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(184);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(212);
        base58Prefixes[SECRET_KEY]     = list_of(189);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xe0;
        pchMessageStart[1] = 0xdb;
        pchMessageStart[2] = 0xdf;
        pchMessageStart[3] = 0xbe;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1471793005;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 3341;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x71f605b5442845490546e4736b07f5efb20b787ce14e6bb9a0d47fa2c9972c45"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
