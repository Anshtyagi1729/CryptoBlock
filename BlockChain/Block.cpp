#include "Block.h"
#include "sha256.h"
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
Block::Block(uint32_t nIndexIn,const string&sDataIn):_nIndex(nIndexIn),_sData(sDataIn){
    _nNonce=-1;
    _tTime=time(nullptr);
}
string Block::GetHash() {
    return _sHash;
}
/*the blockchain tech was made for bitcurrency so when bitcoin is transferred teh transaction is written into a block on the blockchain written
by node ont the network ,a node is another computer  which is running the bitcoin software and since the network is peer to peer it could be any
one around the world this process is called mining as the owner of the node is awarded a mining each time they successfully create block on the
blockchain  a miner must create a cryptographic hash of the block they want to add to the blockchain that matches the requirements for a valid hash at that time; this is achieved by counting the number of zeros at the beginning of the hash, if the number of zeros is equal to or greater than the difficulty level set by the network that block is valid.*/
void Block::MineBlock(uint32_t _nDifficulty)
{
    char cstr[_nDifficulty+1];
    for (uint32_t i=0;i<_nDifficulty;++i)
    {
        cstr[i]='0';
    }
    cstr[_nDifficulty]='\0';
    string str(cstr);
    do
    {
        _nNonce++;
        _sHash=_CalculateHash();
    } while (_sHash.substr(0,_nDifficulty)!=str);
    cout<<"Block mined:"<<_sHash<<endl;
}
inline string Block::_CalculateHash() const {
    stringstream ss;    
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;

    return sha256(ss.str());
}