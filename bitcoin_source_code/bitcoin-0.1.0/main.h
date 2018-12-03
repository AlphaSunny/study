// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

/*
每个节点均保存有一个区块链副本。区块链由相互连接的区块（CBlock实例）所构成。
每个区块包含多笔交易（CTransaction实例）。为了存储、搜索、读取在内存与磁盘中的区块和交易信息，
比特币引入了一些访问类。它们包括：CBlockIndex和CDiskBlockIndex用于索引区块，CDiskTxPos和CTxIndex用于索引交易。

*/


class COutPoint;
class CInPoint;
class CDiskTxPos;
class CCoinBase;
class CTxIn;
class CTxOut;					 //交易中的
class CTransaction;               //一个交易
class CBlock;                   //一个区块
class CBlockIndex;
class CWalletTx;
class CKeyItem;

static const unsigned int MAX_SIZE = 0x02000000;
static const int64 COIN = 100000000;
static const int64 CENT = 1000000;
static const int COINBASE_MATURITY = 100;             //都是静态内部链接

static const CBigNum bnProofOfWorkLimit(~uint256(0) >> 32);     //~代表非的意思，意味着~uint256(0) 将所有0做非处理，即2^256-1，也就是256位最大的整数，而>>32 即代表移32位，/2^32,来显示难度





//extern 保证主要是为了几个文件之间共享，c++语言支持分离式编译
//为了将程序分为许多文件，则需要在文件中共享代码，例如一个文件的代码可能需要另一个文件中中定义的变量。

extern CCriticalSection cs_main;
extern map<uint256, CBlockIndex*> mapBlockIndex;
extern const uint256 hashGenesisBlock;                 //最初的block
extern CBlockIndex* pindexGenesisBlock;
extern int nBestHeight;
extern uint256 hashBestChain;
extern CBlockIndex* pindexBest;
extern unsigned int nTransactionsUpdated;
extern string strSetDataDir;
extern int nDropMessagesTest;

// Settings
extern int fGenerateBitcoins;
extern int64 nTransactionFee;
extern CAddress addrIncoming;







string GetAppDir();
bool CheckDiskSpace(int64 nAdditionalBytes=0);
FILE* OpenBlockFile(unsigned int nFile, unsigned int nBlockPos, const char* pszMode="rb");
FILE* AppendBlockFile(unsigned int& nFileRet);
bool AddKey(const CKey& key);
vector<unsigned char> GenerateNewKey();
bool AddToWallet(const CWalletTx& wtxIn);
void ReacceptWalletTransactions();
void RelayWalletTransactions();
bool LoadBlockIndex(bool fAllowNew=true);
void PrintBlockTree();
bool BitcoinMiner();
bool ProcessMessages(CNode* pfrom);
bool ProcessMessage(CNode* pfrom, string strCommand, CDataStream& vRecv);
bool SendMessages(CNode* pto);
int64 GetBalance();
bool CreateTransaction(CScript scriptPubKey, int64 nValue, CWalletTx& txNew, int64& nFeeRequiredRet);
bool CommitTransactionSpent(const CWalletTx& wtxNew);
bool SendMoney(CScript scriptPubKey, int64 nValue, CWalletTx& wtxNew);









/*
CDiskTxPos与CTxIndex
这两个类用来索引交易。
*/

/*
CDiskTxPos中的nFile，nBlockPos和nTxPos分别是区块数据文件的序号，区块在区块数据文件当中的位置和交易在区块数据中的位置。因此，CDiskTxPos包含了从区块数据文件中找到某笔交易的全部信息。
*/

class CDiskTxPos                                          //交易在磁盘中的位置
{
public:
    unsigned int nFile;
    unsigned int nBlockPos;
    unsigned int nTxPos;

    CDiskTxPos()
    {
        SetNull();
    }

    CDiskTxPos(unsigned int nFileIn, unsigned int nBlockPosIn, unsigned int nTxPosIn)
    {
        nFile = nFileIn;
        nBlockPos = nBlockPosIn;
        nTxPos = nTxPosIn;
    }

    IMPLEMENT_SERIALIZE( READWRITE(FLATDATA(*this)); )
    void SetNull() { nFile = -1; nBlockPos = 0; nTxPos = 0; }
    bool IsNull() const { return (nFile == -1); }

    friend bool operator==(const CDiskTxPos& a, const CDiskTxPos& b)
    {
        return (a.nFile     == b.nFile &&
                a.nBlockPos == b.nBlockPos &&
                a.nTxPos    == b.nTxPos);
    }

    friend bool operator!=(const CDiskTxPos& a, const CDiskTxPos& b)
    {
        return !(a == b);
    }

    string ToString() const
    {
        if (IsNull())
            return strprintf("null");
        else
            return strprintf("(nFile=%d, nBlockPos=%d, nTxPos=%d)", nFile, nBlockPos, nTxPos);
    }

    void print() const
    {
        printf("%s", ToString().c_str());
    }
};




class CInPoint
{
public:
    CTransaction* ptx;
    unsigned int n;

    CInPoint() { SetNull(); }
    CInPoint(CTransaction* ptxIn, unsigned int nIn) { ptx = ptxIn; n = nIn; }
    void SetNull() { ptx = NULL; n = -1; }
    bool IsNull() const { return (ptx == NULL && n == -1); }       
};




class COutPoint
//任何一笔交易都由一个256为uint256哈希作为其唯一识别。若要引用一笔来源交易TxSource当中某个
//某个特性的输出交易，我们需要两个信息：TxSource的哈希，和该输出交易在输出交易当中的位置n
//这两种信息构成CoutPoint类。一个COutPoint对象指向来源交易的某一笔输出交易TxSource.vout[n]
//如果该比输出交易被另一笔交易Tx的位置i的输入交易所引用，例如Tx.vin[i].prevout, 我们将其
//称为Tx的第i笔输入交易花费了TxSource中的第n比输出交易
{
public:
    uint256 hash;
    unsigned int n;

    COutPoint() { SetNull(); }
    COutPoint(uint256 hashIn, unsigned int nIn) { hash = hashIn; n = nIn; }
    IMPLEMENT_SERIALIZE( READWRITE(FLATDATA(*this)); )
    void SetNull() { hash = 0; n = -1; }                          //如果是空的话，设置hash值=-0，和n的值=0
    bool IsNull() const { return (hash == 0 && n == -1); }

    friend bool operator<(const COutPoint& a, const COutPoint& b)       //重写<，首先比较hash值的小
    {
        return (a.hash < b.hash || (a.hash == b.hash && a.n < b.n));
    }

    friend bool operator==(const COutPoint& a, const COutPoint& b)           //重写符号 ==
    {
        return (a.hash == b.hash && a.n == b.n);
    }

    friend bool operator!=(const COutPoint& a, const COutPoint& b)     //重写operator !=
    {
        return !(a == b);
    }

    string ToString() const
    {
        return strprintf("COutPoint(%s, %d)", hash.ToString().substr(0,6).c_str(), n);
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }
};




//
// An input of a transaction.  It contains the location of the previous
// transaction's output that it claims and a signature that matches the
// output's public key.
//交易的输入，包括当前输入对应前一笔交易的输出的位置，以及花费前一笔输出需要的签名脚本
 //CScriptWitness是用来支持隔离见证时使用的。
class CTxIn
{
public:
    COutPoint prevout;					//本类是交易的输入，所有COutPoint代表输出的位置
    CScript scriptSig;                   //用来解锁的脚本
    unsigned int nSequence;                //序列号

    CTxIn()
    {
        nSequence = UINT_MAX;                 //构造函数，UINT_MAX是unsigned int 的最大值
    }

    explicit CTxIn(COutPoint prevoutIn, CScript scriptSigIn=CScript(), unsigned int nSequenceIn=UINT_MAX)   // 禁用隐式转换，构造函数必须明确使用当前形式
    {
        prevout = prevoutIn;
        scriptSig = scriptSigIn;
        nSequence = nSequenceIn;
    }

    CTxIn(uint256 hashPrevTx, unsigned int nOut, CScript scriptSigIn=CScript(), unsigned int nSequenceIn=UINT_MAX)
    {
        prevout = COutPoint(hashPrevTx, nOut);
        scriptSig = scriptSigIn;
        nSequence = nSequenceIn;
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(prevout);
        READWRITE(scriptSig);
        READWRITE(nSequence);
    )

    bool IsFinal() const
    {
        return (nSequence == UINT_MAX);
    }

    friend bool operator==(const CTxIn& a, const CTxIn& b)
    {
        return (a.prevout   == b.prevout &&
                a.scriptSig == b.scriptSig &&
                a.nSequence == b.nSequence);
    }

    friend bool operator!=(const CTxIn& a, const CTxIn& b)
    {
        return !(a == b);
    }

    string ToString() const
    {
        string str;
        str += strprintf("CTxIn(");
        str += prevout.ToString();
        if (prevout.IsNull())        //如果是coinbase代表这是开采出来给矿工的奖励，所以是没有Coutpoint prevout是没有的
            str += strprintf(", coinbase %s", HexStr(scriptSig.begin(), scriptSig.end(), false).c_str());
        else
            str += strprintf(", scriptSig=%s", scriptSig.ToString().substr(0,24).c_str());
        if (nSequence != UINT_MAX)
            str += strprintf(", nSequence=%u", nSequence);
        str += ")";
        return str;
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }

    bool IsMine() const;
    int64 GetDebit() const;           //来得到借方账目
};




//
// An output of a transaction.  It contains the public key that the next input
// must be able to sign with to claim it.
//一个交易的输出，包含了公共钥匙，代表交易的输入必须出示来认领它
class CTxOut
{
public:
    int64 nValue;                                   //输出金额
    CScript scriptPubKey;                  			//锁定脚本，也是公共钥匙

public:
    CTxOut()
    {
        SetNull();
    }

    CTxOut(int64 nValueIn, CScript scriptPubKeyIn)
    {
        nValue = nValueIn;
        scriptPubKey = scriptPubKeyIn;
    }

    IMPLEMENT_SERIALIZE                                  //？？
    (
        READWRITE(nValue);
        READWRITE(scriptPubKey);
    )

    void SetNull()                                              //设置空
    {
        nValue = -1;
        scriptPubKey.clear();
    }

    bool IsNull()                                                  //判断是否为空
    {
        return (nValue == -1);
    }

    uint256 GetHash() const                            //得到这个交易得hash值
    {
        return SerializeHash(*this);
    }

	//决定了在该成员函数中，任意修改它所在的类的成员的操作都是不允许的（因为隐含了对this指针的const引用）；
	//唯一的例外是对于 mutable修饰的成员。
    bool IsMine() const                           //这个交易是否被mine                             
    {
        return ::IsMine(scriptPubKey);
    }

    int64 GetCredit() const
    {
        if (IsMine())
            return nValue;
        return 0;
    }

    friend bool operator==(const CTxOut& a, const CTxOut& b)         //重载了运算符 ==， 必须值相等和公共钥匙都必须相等
    {
        return (a.nValue       == b.nValue &&
                a.scriptPubKey == b.scriptPubKey);
    }

    friend bool operator!=(const CTxOut& a, const CTxOut& b)           //重载！=
    {
        return !(a == b);
    }

    string ToString() const                                    //定义toString
    {
        if (scriptPubKey.size() < 6)
            return "CTxOut(error)";
        return strprintf("CTxOut(nValue=%I64d.%08I64d, scriptPubKey=%s)", nValue / COIN, nValue % COIN, scriptPubKey.ToString().substr(0,24).c_str());
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }
};




//
// The basic transaction that is broadcasted on the network and contained in
// blocks.  A transaction can contain multiple inputs and outputs.
//
class CTransaction
{
public:
    int nVersion;
    vector<CTxIn> vin;                          //输入交易
    vector<CTxOut> vout;						//输出交易
    int nLockTime;


    CTransaction()
    {
        SetNull();
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(vin);
        READWRITE(vout);
        READWRITE(nLockTime);
    )

    void SetNull()
    {
        nVersion = 1;
        vin.clear();
        vout.clear();
        nLockTime = 0;
    }

    bool IsNull() const
    {
        return (vin.empty() && vout.empty());
    }

    uint256 GetHash() const
    {
        return SerializeHash(*this);                //得到这个交易的哈希值
    }

    bool IsFinal() const
    {
        if (nLockTime == 0 || nLockTime < nBestHeight)
            return true;
        foreach(const CTxIn& txin, vin)
            if (!txin.IsFinal())
                return false;
        return true;
    }

    bool IsNewerThan(const CTransaction& old) const          //判断这个交易是不是就交易的新版本,注意在整个过程中，我们只检查了vin
    {
        if (vin.size() != old.vin.size())                   //如果输入交易的尺寸不等于老的输出交易的尺寸，返回否
            return false;
        for (int i = 0; i < vin.size(); i++)               //如果输入交易代表的 每个单笔输出交易prevout不同的话，返回否
            if (vin[i].prevout != old.vin[i].prevout)
                return false;

        bool fNewer = false;
        unsigned int nLowest = UINT_MAX;                             //最大的UINT的值
        for (int i = 0; i < vin.size(); i++)
        {
            if (vin[i].nSequence != old.vin[i].nSequence)
            {
                if (vin[i].nSequence <= nLowest)
                {
                    fNewer = false;
                    nLowest = vin[i].nSequence;
                }
                if (old.vin[i].nSequence < nLowest)
                {
                    fNewer = true;
                    nLowest = old.vin[i].nSequence;
                }
            }
        }
        return fNewer;
    }

    bool IsCoinBase() const                       //判断这个值是不是coinbase交易，在于，这个交易的vin是不是只有一个，而且这个vin的preout 是空的
    {
        return (vin.size() == 1 && vin[0].prevout.IsNull());
    }

    bool CheckTransaction() const
    {
        // Basic checks that don't depend on any context
        if (vin.empty() || vout.empty())
            return error("CTransaction::CheckTransaction() : vin or vout empty");

        // Check for negative values
        foreach(const CTxOut& txout, vout)
            if (txout.nValue < 0)
                return error("CTransaction::CheckTransaction() : txout.nValue negative");

        if (IsCoinBase())
        {
            if (vin[0].scriptSig.size() < 2 || vin[0].scriptSig.size() > 100)
                return error("CTransaction::CheckTransaction() : coinbase script size");
        }
        else
        {
            foreach(const CTxIn& txin, vin)
                if (txin.prevout.IsNull())
                    return error("CTransaction::CheckTransaction() : prevout is null");
        }

        return true;
    }

    bool IsMine() const
    {
        foreach(const CTxOut& txout, vout)
            if (txout.IsMine())
                return true;
        return false;
    }


    //Debit是借的意思，Credit是贷的意思，没有什么特别具体含义，只是一种符号而已，好比加和减。
    int64 GetDebit() const                          //这个代表这个交易中所有txin的值
    {
        int64 nDebit = 0;
        foreach(const CTxIn& txin, vin)
            nDebit += txin.GetDebit();
        return nDebit;
    }

    int64 GetCredit() const                     //代表所有credit即txout中的值     
    {
        int64 nCredit = 0;
        foreach(const CTxOut& txout, vout)
            nCredit += txout.GetCredit();
        return nCredit;
    }

    int64 GetValueOut() const
    {
        int64 nValueOut = 0;
        foreach(const CTxOut& txout, vout)
        {
            if (txout.nValue < 0)
                throw runtime_error("CTransaction::GetValueOut() : negative value");
            nValueOut += txout.nValue;
        }
        return nValueOut;
    }

    int64 GetMinFee(bool fDiscount=false) const                 //得到最小交易费用的代码
    {
        // Base fee is 1 cent per kilobyte     
        unsigned int nBytes = ::GetSerializeSize(*this, SER_NETWORK);
        int64 nMinFee = (1 + (int64)nBytes / 1000) * CENT;   //每kilobyte的基准费用是1cent

        // First 100 transactions in a block are free   前100个交易是免费的
        if (fDiscount && nBytes < 10000)
            nMinFee = 0;

        // To limit dust spam, require a 0.01 fee if any output is less than 0.01
        if (nMinFee < CENT)                                //txout的nMinFee都至少为Cent    
            foreach(const CTxOut& txout, vout)
                if (txout.nValue < CENT)
                    nMinFee = CENT;

        return nMinFee;
    }



    bool ReadFromDisk(CDiskTxPos pos, FILE** pfileRet=NULL)               //从磁盘中来读取这个交易
    {
        CAutoFile filein = OpenBlockFile(pos.nFile, 0, pfileRet ? "rb+" : "rb");
        if (!filein)
            return error("CTransaction::ReadFromDisk() : OpenBlockFile failed");

        // Read transaction
        if (fseek(filein, pos.nTxPos, SEEK_SET) != 0)
            return error("CTransaction::ReadFromDisk() : fseek failed");
        filein >> *this;

        // Return file pointer
        if (pfileRet)
        {
            if (fseek(filein, pos.nTxPos, SEEK_SET) != 0)
                return error("CTransaction::ReadFromDisk() : second fseek failed");
            *pfileRet = filein.release();
        }
        return true;
    }


    friend bool operator==(const CTransaction& a, const CTransaction& b)
    {
        return (a.nVersion  == b.nVersion &&
                a.vin       == b.vin &&
                a.vout      == b.vout &&
                a.nLockTime == b.nLockTime);
    }

    friend bool operator!=(const CTransaction& a, const CTransaction& b)
    {
        return !(a == b);
    }


    string ToString() const
    {
        string str;
        str += strprintf("CTransaction(hash=%s, ver=%d, vin.size=%d, vout.size=%d, nLockTime=%d)\n",
            GetHash().ToString().substr(0,6).c_str(),
            nVersion,
            vin.size(),
            vout.size(),
            nLockTime);
        for (int i = 0; i < vin.size(); i++)
            str += "    " + vin[i].ToString() + "\n";
        for (int i = 0; i < vout.size(); i++)
            str += "    " + vout[i].ToString() + "\n";
        return str;
    }

    void print() const
    {
        printf("%s", ToString().c_str());
    }



    bool DisconnectInputs(CTxDB& txdb);
    bool ConnectInputs(CTxDB& txdb, map<uint256, CTxIndex>& mapTestPool, CDiskTxPos posThisTx, int nHeight, int64& nFees, bool fBlock, bool fMiner, int64 nMinFee=0);
    bool ClientConnectInputs();

    bool AcceptTransaction(CTxDB& txdb, bool fCheckInputs=true, bool* pfMissingInputs=NULL);

    bool AcceptTransaction(bool fCheckInputs=true, bool* pfMissingInputs=NULL)
    {
        CTxDB txdb("r");
        return AcceptTransaction(txdb, fCheckInputs, pfMissingInputs);
    }

protected:
    bool AddToMemoryPool();
public:
    bool RemoveFromMemoryPool();
};





/*
我们一起检查另外两个由CTransaction衍生的重要的类：CMerkleTx与CWallet。
*/
/*
CTransaction的实例被收集并生成一个CBlock。对于指定的CTransaction实例，它的梅克尔分支，和它在CBlock的vector<CTranaction> vtx字段中的位置，可以用于查找该实例是否被包含在这个CBlock里面。这便是为什么CMerkleTx包含另外两个字段：一个梅克尔分支vMerkleBranch，和一个位置索引nIndex。一个CMerkleTx实例携带有这两个字段使其能方便地被验证是否属于一个区块。

uint256 hashBlock是该交易所在CBlock的哈希。
*/
//
// A transaction with a merkle branch linking it to the block chain
//
class CMerkleTx : public CTransaction
{
public:
    uint256 hashBlock;
    vector<uint256> vMerkleBranch;
    int nIndex;

    // memory only
    mutable bool fMerkleVerified;


    CMerkleTx()
    {
        Init();
    }

    CMerkleTx(const CTransaction& txIn) : CTransaction(txIn)
    {
        Init();
    }

    void Init()
    {
        hashBlock = 0;
        nIndex = -1;
        fMerkleVerified = false;
    }

    int64 GetCredit() const
    {
        // Must wait until coinbase is safely deep enough in the chain before valuing it
        if (IsCoinBase() && GetBlocksToMaturity() > 0)
            return 0;
        return CTransaction::GetCredit();
    }

    IMPLEMENT_SERIALIZE
    (
        nSerSize += SerReadWrite(s, *(CTransaction*)this, nType, nVersion, ser_action);
        nVersion = this->nVersion;
        READWRITE(hashBlock);
        READWRITE(vMerkleBranch);
        READWRITE(nIndex);
    )


    int SetMerkleBranch(const CBlock* pblock=NULL);
    int GetDepthInMainChain() const;
    bool IsInMainChain() const { return GetDepthInMainChain() > 0; }
    int GetBlocksToMaturity() const;
    bool AcceptTransaction(CTxDB& txdb, bool fCheckInputs=true);
    bool AcceptTransaction() { CTxDB txdb("r"); return AcceptTransaction(txdb); }
};




//
// A transaction with a bunch of additional info that only the owner cares
// about.  It includes any unrecorded transactions needed to link it back
// to the block chain.
//

/*
CWalletTx进一步延伸CMerkleTx，包括了关于“只有（该笔交易的）拥有者关心”的信息。这些成员字段将被提及，当我们在代码当中遇到它们的时候。

class CWalletTx : public CMerkleTx
*/
class CWalletTx : public CMerkleTx
{
public:
    vector<CMerkleTx> vtxPrev;
    map<string, string> mapValue;
    vector<pair<string, string> > vOrderForm;
    unsigned int fTimeReceivedIsTxTime;
    unsigned int nTimeReceived;  // time received by this node
    char fFromMe;
    char fSpent;
    //// probably need to sign the order info so know it came from payer

    // memory only
    mutable unsigned int nTimeDisplayed;


    CWalletTx()
    {
        Init();
    }

    CWalletTx(const CMerkleTx& txIn) : CMerkleTx(txIn)
    {
        Init();
    }

    CWalletTx(const CTransaction& txIn) : CMerkleTx(txIn)
    {
        Init();
    }

    void Init()
    {
        fTimeReceivedIsTxTime = false;
        nTimeReceived = 0;
        fFromMe = false;
        fSpent = false;
        nTimeDisplayed = 0;
    }

    IMPLEMENT_SERIALIZE
    (
        nSerSize += SerReadWrite(s, *(CMerkleTx*)this, nType, nVersion, ser_action);
        nVersion = this->nVersion;
        READWRITE(vtxPrev);
        READWRITE(mapValue);
        READWRITE(vOrderForm);
        READWRITE(fTimeReceivedIsTxTime);
        READWRITE(nTimeReceived);
        READWRITE(fFromMe);
        READWRITE(fSpent);
    )

    bool WriteToDisk()
    {
        return CWalletDB().WriteTx(GetHash(), *this);
    }


    int64 GetTxTime() const;

    void AddSupportingTransactions(CTxDB& txdb);

    bool AcceptWalletTransaction(CTxDB& txdb, bool fCheckInputs=true);
    bool AcceptWalletTransaction() { CTxDB txdb("r"); return AcceptWalletTransaction(txdb); }

    void RelayWalletTransaction(CTxDB& txdb);
    void RelayWalletTransaction() { CTxDB txdb("r"); RelayWalletTransaction(txdb); }
};




//
// A txdb record that contains the disk location of a transaction and the
// locations of transactions that spend its outputs.  vSpent is really only
// used as a flag, but having the location is very helpful for debugging.
//代表一个交易的磁盘位置和花费了这个交易输出的交易的磁盘为位置，vspent只是当作一个标志来使用，但是对于debug很有帮助。

/*
一个CTxIndex是一个数据库记录“包含有一笔交易和花费这笔交易输出的交易在磁盘的位置”。一笔交易可以很容易地找到它的来源交易（参见第一章），但反过来不行。vector<CDiskTxPos> vSpent包含所有由CDiskTxPos pos指向的某笔交易作为来源交易的交易的位置，例如所有花费CDiskTxPos pos指向的交易的交易。
*/
class CTxIndex
{
public:
    CDiskTxPos pos;
    vector<CDiskTxPos> vSpent;

    CTxIndex()
    {
        SetNull();
    }

    CTxIndex(const CDiskTxPos& posIn, unsigned int nOutputs)
    {
        pos = posIn;
        vSpent.resize(nOutputs);
    }

    IMPLEMENT_SERIALIZE
    (
        if (!(nType & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(pos);
        READWRITE(vSpent);
    )

    void SetNull()
    {
        pos.SetNull();
        vSpent.clear();
    }

    bool IsNull()
    {
        return pos.IsNull();
    }

    friend bool operator==(const CTxIndex& a, const CTxIndex& b)
    {
        if (a.pos != b.pos || a.vSpent.size() != b.vSpent.size())
            return false;
        for (int i = 0; i < a.vSpent.size(); i++)
            if (a.vSpent[i] != b.vSpent[i])
                return false;
        return true;
    }

    friend bool operator!=(const CTxIndex& a, const CTxIndex& b)
    {
        return !(a == b);
    }
};





//
// Nodes collect new transactions into a block, hash them into a hash tree,
// and scan through nonce values to make the block's hash satisfy proof-of-work
// requirements.  When they solve the proof-of-work, they broadcast the block
// to everyone and the block is added to the block chain.  The first transaction
// in the block is a special one that creates a new coin owned by the creator
// of the block.
//
// Blocks are appended to blk0001.dat files on disk.  Their location on disk
// is indexed by CBlockIndex objects in memory.
//

/*
这里有几点注意：

一个区块包含若干笔交易，并存放于vector<CTransaction> vtx。
一个区块的哈希，由函数GetHash()生成，是通过计算区块的块头（block-header）而不是整个区块数据所得到。更具体讲，哈希由成员变量nVersion到nNonce生成，而并不包括交易容器vtx。
成员变量uint256 hashMerkleRoot是块头的一部分。它由成员函数BuildMerkleTree()生成，该函数将所有交易vtx作为输入参数，并最终生成一个256位哈希hashMerkleRoot。
uint256 hashPrevBlock是当前区块之前的区块哈希，被包括在块头当中。因此，一个区块的哈希与它在区块链当中先前区块的哈希有关。
*/
class CBlock
{
public:
    // header
    int nVersion;
    uint256 hashPrevBlock;                              //上一个区块的哈希值
    uint256 hashMerkleRoot;
    unsigned int nTime;                                    //ntime is Unix timestamp of the block
    unsigned int nBits;                               	//nBits is the current target
    unsigned int nNonce;                                  //挖出来的nonce值

    // network and disk
    vector<CTransaction> vtx;                          //Cblock中包含着CTransaction,CTransaction中包含着CTxIn和CTxOut

    // memory only
    mutable vector<uint256> vMerkleTree;           //树形对交易产生hash值，最上面的就是该merkle tree顶端的hash值


    CBlock()
    {
        SetNull();                                       //将这个block设置为空
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(hashPrevBlock);
        READWRITE(hashMerkleRoot);
        READWRITE(nTime);
        READWRITE(nBits);
        READWRITE(nNonce);

        // ConnectBlock depends on vtx being last so it can calculate offset
        if (!(nType & (SER_GETHASH|SER_BLOCKHEADERONLY)))
            READWRITE(vtx);
        else if (fRead)
            const_cast<CBlock*>(this)->vtx.clear();
    )

    void SetNull()
    {
        nVersion = 1;
        hashPrevBlock = 0;
        hashMerkleRoot = 0;
        nTime = 0;
        nBits = 0;
        nNonce = 0;
        vtx.clear();
        vMerkleTree.clear();
    }

    bool IsNull() const
    {
        return (nBits == 0);
    }

    uint256 GetHash() const
    {
        return Hash(BEGIN(nVersion), END(nNonce));
    }


/*
BuildMerkleTree()建立一个梅克尔树并返回树根。该树的每个节点，包括叶节点和中间节点，均为一个uint256哈希值。该树被扁平化并放置在vector<uint256> vMerkleTree中。为了扁平化梅克尔树，该函数首先将第0层的叶节点放入vMerkleTree，接着将第1层的中间结点紧接着放在它们之后，向上重复该过程直到到达根结点。

位于第25行的变量j用于索引vMerkleTree的起始位置来放入树每一层的第一个节点。变量nSize是每层的节点个数。从第0层开始，nSize=vtx.size()，并且j=0。

最外层的for循环访问树的每一层。每层节点个数是上一层的一半（nSize=(nSize+1)/2，第26行）。里面的for循环依次访问某一层的每对节点，指针i每一步增量为2。节点对（i和i2）的哈希附加在容器vMerkleTree，其中i2=i+1。当i到达最后一对节点，i=nSize-1当nSize为奇数，或者i=nSize-2当nSize为偶数。在前者情形，最后一个节点（i2=i=nSize-1）则与其自身的复制组成节点对。
*/
    uint256 BuildMerkleTree() const
    {
        vMerkleTree.clear();
        foreach(const CTransaction& tx, vtx)
            vMerkleTree.push_back(tx.GetHash());
        int j = 0;
        for (int nSize = vtx.size(); nSize > 1; nSize = (nSize + 1) / 2)
        {
            for (int i = 0; i < nSize; i += 2)
            {
                int i2 = min(i+1, nSize-1);
                vMerkleTree.push_back(Hash(BEGIN(vMerkleTree[j+i]),  END(vMerkleTree[j+i]),
                                           BEGIN(vMerkleTree[j+i2]), END(vMerkleTree[j+i2])));
            }
            j += nSize;
        }
        return (vMerkleTree.empty() ? 0 : vMerkleTree.back());
    }




/*
CBlock::GetMerkleBranch()
该函数返回一个梅克尔树分支。整个梅克尔树已被扁平化至容器vMerkleTree。参数nIndex指向容器vMerkleTree[nIndex]的那个节点。它的取值从0到vtx.size()。因此，nIndex永远指向一个叶节点，为某笔交易的哈希。

返回的梅克尔树分支包含了所有从vMerkleTre[nIndex]到树根所伴随的节点。回忆建立梅克尔树的过程，每一层的节点两两相配，成为下一层的节点。在第0层，若nIndex为偶数，则与节点vMerkleTree[nIndex]伴随的节点是vMerkleTree[nIndex+1]；若nIndex为奇数，则伴随节点为vMerkleTree[nIndex-1]。为了简化，我们把vMerkleTree[nIndex]称作节点A0，其伴随节点为B0。A0与B0相结合并生成另一个位于第1层节点A1。在第1层，A1的伴随节点为B1，两者配对并生成位于第2层的节点A2。重复该过程，直到到达梅克尔树根。节点[A0, A1, A2, ...]形成一条从A0到根节点的路径，它们的伴随节点[B0, B1, ...]则构成所返回的梅克尔分支。

为了找到伴随节点，该函数遍历树的每一层（第4行）。在每一层，指针nIndex比它前一层的值减半。因此，nIndex永远指向路径节点[A0, A1, A2, ...]。另一个指针i设为min(nIndex^1, nSize-1)，位于第46行。或运算符^1翻转nIndex最后一位，而不修改其他位。这将保证i永远指向nIndex所指向节点的伴随节点，例如节点[B0, B1, B2, ...]。

你可能会问，梅克尔树的作用是什么。它可以快速地验证一笔交易是否被包括在一个区块当中。下面我们将会介绍。
*/

    vector<uint256> GetMerkleBranch(int nIndex) const
    {
        if (vMerkleTree.empty())
            BuildMerkleTree();
        vector<uint256> vMerkleBranch;
        int j = 0;
        for (int nSize = vtx.size(); nSize > 1; nSize = (nSize + 1) / 2)
        {
            int i = min(nIndex^1, nSize-1);
            vMerkleBranch.push_back(vMerkleTree[j+i]);
            nIndex >>= 1;
            j += nSize;
        }
        return vMerkleBranch;
    }




/*
CBlock::CheckMerkleBranch()
这个函数接受它的第一个参数hash，用它检查第二个参数vMerkleBranch，并返回一个生成的梅克尔树根。如果所返回的树根与hashMerkleRoot相同，则hash所指向交易的哈希被包括在该CBlock当中。第三个参数nIndex是第一个参数在vMerkleTree当中的位置；它与GetMerkleBranch()的唯一参数是相同的。

因此，若需要检查一笔交易是否被包括在一个CBlock里，则仅需生成该笔交易的哈希并调用该函数，验证返回值是否与hashMerkleroot相同。
*/
    static uint256 CheckMerkleBranch(uint256 hash, const vector<uint256>& vMerkleBranch, int nIndex)
    {
        if (nIndex == -1)
            return 0;
        foreach(const uint256& otherside, vMerkleBranch)
        {
            if (nIndex & 1)
                hash = Hash(BEGIN(otherside), END(otherside), BEGIN(hash), END(hash));
            else
                hash = Hash(BEGIN(hash), END(hash), BEGIN(otherside), END(otherside));
            nIndex >>= 1;
        }
        return hash;
    }





/*
WriteToDisk将一个CBlock写入磁盘。在第80行，它调用AppendBlockFile()。
AppendBlockFile()的第一个参数nFileRet用于存放返回值。分析AppendBlockFile()和OpenBlockFile()源码显示nFileRet是一系列数据文件，以“blk0001.data”，“blk0002.data”的形式命名。区块被保存在这些文件中。它们被称作区块数据文件。

返回WriteToDisk()，第三个参数nBlockPosRet是当前CBlock在区块数据文件中存放的起始位置。在Block::WriteToDisk()的第89行，nBlockRet被赋给返回值ftell()，其为区块数据文件的当前指针位置。在其后面，当前CBlock以序列化后的形式被存储在区块数据文件里（第92行）。

ReadFromDisk()可以很直观地被理解。
*/
    bool WriteToDisk(bool fWriteTransactions, unsigned int& nFileRet, unsigned int& nBlockPosRet)
    {
        // Open history file to append
        CAutoFile fileout = AppendBlockFile(nFileRet);
        if (!fileout)
            return error("CBlock::WriteToDisk() : AppendBlockFile failed");
        if (!fWriteTransactions)
            fileout.nType |= SER_BLOCKHEADERONLY;

        // Write index header
        unsigned int nSize = fileout.GetSerializeSize(*this);
        fileout << FLATDATA(pchMessageStart) << nSize;

        // Write block
        nBlockPosRet = ftell(fileout);
        if (nBlockPosRet == -1)
            return error("CBlock::WriteToDisk() : ftell failed");
        fileout << *this;

        return true;
    }

    bool ReadFromDisk(unsigned int nFile, unsigned int nBlockPos, bool fReadTransactions)
    {
        SetNull();

        // Open history file to read
        CAutoFile filein = OpenBlockFile(nFile, nBlockPos, "rb");
        if (!filein)
            return error("CBlock::ReadFromDisk() : OpenBlockFile failed");
        if (!fReadTransactions)
            filein.nType |= SER_BLOCKHEADERONLY;

        // Read block
        filein >> *this;

        // Check the header
        if (CBigNum().SetCompact(nBits) > bnProofOfWorkLimit)
            return error("CBlock::ReadFromDisk() : nBits errors in block header");
        if (GetHash() > CBigNum().SetCompact(nBits).getuint256())
            return error("CBlock::ReadFromDisk() : GetHash() errors in block header");

        return true;
    }








    void print() const
    {
        printf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%d)\n",
            GetHash().ToString().substr(0,14).c_str(),
            nVersion,
            hashPrevBlock.ToString().substr(0,14).c_str(),
            hashMerkleRoot.ToString().substr(0,6).c_str(),
            nTime, nBits, nNonce,
            vtx.size());
        for (int i = 0; i < vtx.size(); i++)
        {
            printf("  ");
            vtx[i].print();
        }
        printf("  vMerkleTree: ");
        for (int i = 0; i < vMerkleTree.size(); i++)
            printf("%s ", vMerkleTree[i].ToString().substr(0,6).c_str());
        printf("\n");
    }


    int64 GetBlockValue(int64 nFees) const;
    bool DisconnectBlock(CTxDB& txdb, CBlockIndex* pindex);
    bool ConnectBlock(CTxDB& txdb, CBlockIndex* pindex);
    bool ReadFromDisk(const CBlockIndex* blockindex, bool fReadTransactions);
    bool AddToBlockIndex(unsigned int nFile, unsigned int nBlockPos);
    bool CheckBlock() const;
    bool AcceptBlock();
};






//
// The block chain is a tree shaped structure starting with the
// genesis block at the root, with each block potentially having multiple
// candidates to be the next block.  pprev and pnext link a path through the
// main/longest chain.  A blockindex may have multiple pprev pointing back
// to it, but pnext will only point forward to the longest branch, or will
// be null if the block is not part of the longest chain.
//  区块链源码是一个树状的结构，树的顶端就是第一个区块，每个block都有可能同时有几个候选者作为下一个block
// pprev和pnext链接一个最长的链，一个block可能同时有几个pprev指向它，但是pnext只会指向最长的分支


/*
CBlockIndex与CDiskBlockIndex
在上面对CBlock::WriteToDisk()和CBlock::ReadFromDisk()的分析显示区块被保存在一系列区块数据文件当中。CBlockIndex将这些信息全部封装在一个单独类CBlockIndex。

*/



/*
除了nFile和nBlockPos，CBlockIndex还包括一份它所指向的区块头的副本（除了字段hashPrevBlock，可通过pprev->phashBlock访问）。这样可以使计算得到区块哈希不需要从区块数据文件中读取整个区块。

从注释的1-6行，我们可以知道pprev指向其在区块链中紧挨着的前一个区块索引，pnext则指向区块链中紧挨着的下一个区块索引。

如果你仔细注意的话，你会发现我提到的是“区块链中的区块索引”而不是“区块链中的区块”。这里有点让人头晕，毕竟区块链是由区块而不是区块索引构成的，不是吗？的确，区块链由区块所构成，但你也可以换一种说法：区块链由区块索引构成。这是一位区块的完整数据被保存在磁盘上的区块数据文件当中，而一个区块索引则通过区块的成员变量nFile和nBlockPos引用这个区块。指针pprev和pnext分别指向一个区块的前一个和下一个区块，以构成整个区块链。所以，区块索引与区块链同样具有意义。

尽管被称为区块链，比特币的区块链其实并不是线性结构，而是树状结构。这棵树的根节点是创世区块，被硬编码至源码当中。其他区块则在创世区块之上依次累积。在一个区块上累积两个或更多区块是合法的。当这种情况发生之后，区块链将产生一个分叉。一个区块链可能含有若干分叉，而分叉出来的分支则可能进一步分叉。

由于分叉的存在，多个区块索引的pprev字段可能指向同一个前任。这些区块索引每一个都开始一个分支，而这些分支都基于同一个前任区块。然而，前任区块的pnext字段只能指向开始最长一条分支的继任区块。从树根（创世区块）到最长分支的最后一个区块的路径被称为最长链，或最佳链，或这个区块链的主链。

指针phashBlock指向该区块的哈希，可以通过CBlockIndex内嵌的区块头现场计算。

nHeight是该区块在区块链中的高度。区块链由高度为0的区块开始，即创世区块。紧接着的区块高度为1，以此类推。

CBlockIndex实例仅保存在内存当中。若要将区块索引存入磁盘，衍生类CDiskBlockIndex在这里定义。

*/
class CBlockIndex
{
public:
    const uint256* phashBlock;
    CBlockIndex* pprev;
    CBlockIndex* pnext;
    unsigned int nFile;
    unsigned int nBlockPos;
    int nHeight;

    // block header
    int nVersion;
    uint256 hashMerkleRoot;
    unsigned int nTime;
    unsigned int nBits;
    unsigned int nNonce;


    CBlockIndex()
    {
        phashBlock = NULL;
        pprev = NULL;
        pnext = NULL;
        nFile = 0;
        nBlockPos = 0;
        nHeight = 0;

        nVersion       = 0;
        hashMerkleRoot = 0;
        nTime          = 0;
        nBits          = 0;
        nNonce         = 0;
    }

    CBlockIndex(unsigned int nFileIn, unsigned int nBlockPosIn, CBlock& block)
    {
        phashBlock = NULL;
        pprev = NULL;
        pnext = NULL;
        nFile = nFileIn;
        nBlockPos = nBlockPosIn;
        nHeight = 0;

        nVersion       = block.nVersion;
        hashMerkleRoot = block.hashMerkleRoot;
        nTime          = block.nTime;
        nBits          = block.nBits;
        nNonce         = block.nNonce;
    }

    uint256 GetBlockHash() const
    {
        return *phashBlock;
    }

    bool IsInMainChain() const
    {
        return (pnext || this == pindexBest);
    }

    bool EraseBlockFromDisk()
    {
        // Open history file
        CAutoFile fileout = OpenBlockFile(nFile, nBlockPos, "rb+");
        if (!fileout)
            return false;

        // Overwrite with empty null block
        CBlock block;
        block.SetNull();
        fileout << block;

        return true;
    }

    enum { nMedianTimeSpan=11 };

    int64 GetMedianTimePast() const
    {
        unsigned int pmedian[nMedianTimeSpan];
        unsigned int* pbegin = &pmedian[nMedianTimeSpan];
        unsigned int* pend = &pmedian[nMedianTimeSpan];

        const CBlockIndex* pindex = this;
        for (int i = 0; i < nMedianTimeSpan && pindex; i++, pindex = pindex->pprev)
            *(--pbegin) = pindex->nTime;

        sort(pbegin, pend);
        return pbegin[(pend - pbegin)/2];
    }

    int64 GetMedianTime() const
    {
        const CBlockIndex* pindex = this;
        for (int i = 0; i < nMedianTimeSpan/2; i++)
        {
            if (!pindex->pnext)
                return nTime;
            pindex = pindex->pnext;
        }
        return pindex->GetMedianTimePast();
    }



    string ToString() const
    {
        return strprintf("CBlockIndex(nprev=%08x, pnext=%08x, nFile=%d, nBlockPos=%-6d nHeight=%d, merkle=%s, hashBlock=%s)",
            pprev, pnext, nFile, nBlockPos, nHeight,
            hashMerkleRoot.ToString().substr(0,6).c_str(),
            GetBlockHash().ToString().substr(0,14).c_str());
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }
};



//
// Used to marshal pointers into hashes for db storage.
//用来整理指针 来便于存储


/*
该类拥有另外两个成员变量：前任区块索引和继任区块索引的哈希，hashPrev和hashNext。不要将它们与CBlockIndex中的pprev和pnext搞混，后者是指向区块索引的指针，而前者则是区块的哈希。

CBlockIndex和CDiskBlockIndex本身均不带有哈希；它们永远用所指向区块的哈希辨识自己。从CDiskBlockIndex的构造器（第15行）可以总结出这点。在这个构造器里，hashPrev被赋值为pprev->GetBlockHash()，其中pprev是一个CBlockIndex的指针。如果你检查CBlockIndex的成员函数GetBlockHash，你可以看到它返回的是前任区块的哈希。对于CDiskBlockIndex，它的成员函数GetBlockHash()同样返回它所指向区块的哈希。

CBlockIndex没有序列化方法，而CDiskBlockIndex则通过宏IMPLEMENT_SERIALIZE实现序列化。这是因为后者需要保存在磁盘里，而前者只存在于内存当中。


*/
class CDiskBlockIndex : public CBlockIndex
{
public:
    uint256 hashPrev;
    uint256 hashNext;

    CDiskBlockIndex()
    {
        hashPrev = 0;
        hashNext = 0;
    }

    explicit CDiskBlockIndex(CBlockIndex* pindex) : CBlockIndex(*pindex)
    {
        hashPrev = (pprev ? pprev->GetBlockHash() : 0);
        hashNext = (pnext ? pnext->GetBlockHash() : 0);
    }

    IMPLEMENT_SERIALIZE
    (
        if (!(nType & SER_GETHASH))
            READWRITE(nVersion);

        READWRITE(hashNext);
        READWRITE(nFile);
        READWRITE(nBlockPos);
        READWRITE(nHeight);

        // block header
        READWRITE(this->nVersion);
        READWRITE(hashPrev);
        READWRITE(hashMerkleRoot);
        READWRITE(nTime);
        READWRITE(nBits);
        READWRITE(nNonce);
    )

    uint256 GetBlockHash() const
    {
        CBlock block;
        block.nVersion        = nVersion;
        block.hashPrevBlock   = hashPrev;
        block.hashMerkleRoot  = hashMerkleRoot;
        block.nTime           = nTime;
        block.nBits           = nBits;
        block.nNonce          = nNonce;
        return block.GetHash();
    }


    string ToString() const
    {
        string str = "CDiskBlockIndex(";
        str += CBlockIndex::ToString();
        str += strprintf("\n                hashBlock=%s, hashPrev=%s, hashNext=%s)",
            GetBlockHash().ToString().c_str(),
            hashPrev.ToString().substr(0,14).c_str(),
            hashNext.ToString().substr(0,14).c_str());
        return str;
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }
};








//
// Describes a place in the block chain to another node such that if the
// other node doesn't have the same branch, it can find a recent common trunk.
// The further back it is, the further before the fork it may be.
//给其他节点描述一个place如果其他节点没有一个相同的分支，让它可以找到一个正常的树干
class CBlockLocator
{
protected:
    vector<uint256> vHave;
public:

    CBlockLocator()
    {
    }

    explicit CBlockLocator(const CBlockIndex* pindex)
    {
        Set(pindex);
    }

    explicit CBlockLocator(uint256 hashBlock)
    {
        map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(hashBlock);
        if (mi != mapBlockIndex.end())
            Set((*mi).second);
    }

    IMPLEMENT_SERIALIZE
    (
        if (!(nType & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(vHave);
    )

    void Set(const CBlockIndex* pindex)
    {
        vHave.clear();
        int nStep = 1;
        while (pindex)
        {
            vHave.push_back(pindex->GetBlockHash());

            // Exponentially larger steps back
            for (int i = 0; pindex && i < nStep; i++)
                pindex = pindex->pprev;
            if (vHave.size() > 10)
                nStep *= 2;
        }
        vHave.push_back(hashGenesisBlock);
    }

    CBlockIndex* GetBlockIndex()
    {
        // Find the first block the caller has in the main chain
        foreach(const uint256& hash, vHave)
        {
            map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(hash);
            if (mi != mapBlockIndex.end())
            {
                CBlockIndex* pindex = (*mi).second;
                if (pindex->IsInMainChain())
                    return pindex;
            }
        }
        return pindexGenesisBlock;
    }

    uint256 GetBlockHash()
    {
        // Find the first block the caller has in the main chain
        foreach(const uint256& hash, vHave)
        {
            map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(hash);
            if (mi != mapBlockIndex.end())
            {
                CBlockIndex* pindex = (*mi).second;
                if (pindex->IsInMainChain())
                    return hash;
            }
        }
        return hashGenesisBlock;
    }

    int GetHeight()
    {
        CBlockIndex* pindex = GetBlockIndex();
        if (!pindex)
            return 0;
        return pindex->nHeight;
    }
};












extern map<uint256, CTransaction> mapTransactions;
extern map<uint256, CWalletTx> mapWallet;
extern vector<pair<uint256, bool> > vWalletUpdated;
extern CCriticalSection cs_mapWallet;
extern map<vector<unsigned char>, CPrivKey> mapKeys;
extern map<uint160, vector<unsigned char> > mapPubKeys;
extern CCriticalSection cs_mapKeys;
extern CKey keyUser;
