// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

/*
比特币带有一个基于栈的脚本语言。每笔交易的输出部分都嵌有一段脚本。要想花费一笔交易中所携带的币，
接收方必须提供他的公钥，以使脚本能够成功执行。
*/


class CTransaction;



/*
比特币脚本语言定义了一组操作符，例如OP_FALSE，OP_RIPEMD160，OP_HASH256等等。操作符作用于栈里面的数据。
在使用操作符对栈当中的数据进行操作之后，输出的数据将被再次压回栈中。该脚本语言中包含两种不同类型的对象：操作符与操作数。
操作符位于enum opcodetype，每一条对应一个操作符。操作数则是操作符的输入数据。它们的类型为valtype，
由一个unsigned char容器构成（typedef vector<unsigned char> valtype）。一个操作符与它的操作数，如果有的话，合起来称为一条指令。
*/

enum
{
    SIGHASH_ALL = 1,                    //默认签名哈希的类型，对除了scriptSigs外的整个交易进行签名，阻止他人修改签名的内容。
    SIGHASH_NONE = 2,                    //一种哈希签名的类型，只对输入进行签名，允许任何人对输出进行修改
    SIGHASH_SINGLE = 3,               //一种签名哈希的类型，只对具有相同索引的input和output进行签名，允许修改其它input和output
    SIGHASH_ANYONECANPAY = 0x80,    //一种哈希签名的类型，它修改其他类型哈希签名的行为
};



enum opcodetype
{
    // push value
    OP_0=0,
    OP_FALSE=OP_0,
    OP_PUSHDATA1=76,
    OP_PUSHDATA2,
    OP_PUSHDATA4,
    OP_1NEGATE,
    OP_RESERVED,
    OP_1,
    OP_TRUE=OP_1,
    OP_2,
    OP_3,
    OP_4,
    OP_5,
    OP_6,
    OP_7,
    OP_8,
    OP_9,
    OP_10,
    OP_11,
    OP_12,
    OP_13,
    OP_14,
    OP_15,
    OP_16,

    // control
    OP_NOP,
    OP_VER,
    OP_IF,
    OP_NOTIF,
    OP_VERIF,
    OP_VERNOTIF,
    OP_ELSE,
    OP_ENDIF,
    OP_VERIFY,
    OP_RETURN,

    // stack ops
    OP_TOALTSTACK,
    OP_FROMALTSTACK,
    OP_2DROP,
    OP_2DUP,
    OP_3DUP,
    OP_2OVER,
    OP_2ROT,
    OP_2SWAP,
    OP_IFDUP,
    OP_DEPTH,
    OP_DROP,
    OP_DUP,
    OP_NIP,
    OP_OVER,
    OP_PICK,
    OP_ROLL,
    OP_ROT,
    OP_SWAP,
    OP_TUCK,

    // splice ops
    OP_CAT,
    OP_SUBSTR,
    OP_LEFT,
    OP_RIGHT,
    OP_SIZE,

    // bit logic
    OP_INVERT,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_EQUAL,
    OP_EQUALVERIFY,
    OP_RESERVED1,
    OP_RESERVED2,

    // numeric
    OP_1ADD,
    OP_1SUB,
    OP_2MUL,
    OP_2DIV,
    OP_NEGATE,
    OP_ABS,
    OP_NOT,
    OP_0NOTEQUAL,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_LSHIFT,
    OP_RSHIFT,

    OP_BOOLAND,
    OP_BOOLOR,
    OP_NUMEQUAL,
    OP_NUMEQUALVERIFY,
    OP_NUMNOTEQUAL,
    OP_LESSTHAN,
    OP_GREATERTHAN,
    OP_LESSTHANOREQUAL,
    OP_GREATERTHANOREQUAL,
    OP_MIN,
    OP_MAX,

    OP_WITHIN,

    // crypto
    OP_RIPEMD160,
    OP_SHA1,
    OP_SHA256,
    OP_HASH160,
    OP_HASH256,
    OP_CODESEPARATOR,
    OP_CHECKSIG,
    OP_CHECKSIGVERIFY,
    OP_CHECKMULTISIG,
    OP_CHECKMULTISIGVERIFY,


    // multi-byte opcodes
    OP_SINGLEBYTE_END = 0xF0,
    OP_DOUBLEBYTE_BEGIN = 0xF000,

    // template matching params
    OP_PUBKEY,
    OP_PUBKEYHASH,



    OP_INVALIDOPCODE = 0xFFFF,
};
/*
这里共有106个操作符，加上OP_FALSE与OP_TRUE，它们分别是OP_0与OP_1的假名。操作符代码并不是连贯的。
从OP_PUSHDATA = 76 = 0x4C开始，代码逐渐递增至OP_CHECKMULTISIGVERIFY = 175 = 0xAF。
接下来，代码的值为OP_SINGLEBYTE_END = 0xF0。在它之后的是OP_DOUBLEBYTE_BEGIN = 0xF000。
所有在它后面的代码值占用两个字节。
*/









//将opcode转换成一个字符串返回
inline const char* GetOpName(opcodetype opcode)
{
    switch (opcode)
    {
    // push value
    case OP_0                      : return "0";
    case OP_PUSHDATA1              : return "OP_PUSHDATA1";
    case OP_PUSHDATA2              : return "OP_PUSHDATA2";
    case OP_PUSHDATA4              : return "OP_PUSHDATA4";
    case OP_1NEGATE                : return "-1";
    case OP_RESERVED               : return "OP_RESERVED";
    case OP_1                      : return "1";
    case OP_2                      : return "2";
    case OP_3                      : return "3";
    case OP_4                      : return "4";
    case OP_5                      : return "5";
    case OP_6                      : return "6";
    case OP_7                      : return "7";
    case OP_8                      : return "8";
    case OP_9                      : return "9";
    case OP_10                     : return "10";
    case OP_11                     : return "11";
    case OP_12                     : return "12";
    case OP_13                     : return "13";
    case OP_14                     : return "14";
    case OP_15                     : return "15";
    case OP_16                     : return "16";

    // control
    case OP_NOP                    : return "OP_NOP";
    case OP_VER                    : return "OP_VER";
    case OP_IF                     : return "OP_IF";
    case OP_NOTIF                  : return "OP_NOTIF";
    case OP_VERIF                  : return "OP_VERIF";
    case OP_VERNOTIF               : return "OP_VERNOTIF";
    case OP_ELSE                   : return "OP_ELSE";
    case OP_ENDIF                  : return "OP_ENDIF";
    case OP_VERIFY                 : return "OP_VERIFY";
    case OP_RETURN                 : return "OP_RETURN";

    // stack ops
    case OP_TOALTSTACK             : return "OP_TOALTSTACK";
    case OP_FROMALTSTACK           : return "OP_FROMALTSTACK";
    case OP_2DROP                  : return "OP_2DROP";
    case OP_2DUP                   : return "OP_2DUP";
    case OP_3DUP                   : return "OP_3DUP";
    case OP_2OVER                  : return "OP_2OVER";
    case OP_2ROT                   : return "OP_2ROT";
    case OP_2SWAP                  : return "OP_2SWAP";
    case OP_IFDUP                  : return "OP_IFDUP";
    case OP_DEPTH                  : return "OP_DEPTH";
    case OP_DROP                   : return "OP_DROP";
    case OP_DUP                    : return "OP_DUP";
    case OP_NIP                    : return "OP_NIP";
    case OP_OVER                   : return "OP_OVER";
    case OP_PICK                   : return "OP_PICK";
    case OP_ROLL                   : return "OP_ROLL";
    case OP_ROT                    : return "OP_ROT";
    case OP_SWAP                   : return "OP_SWAP";
    case OP_TUCK                   : return "OP_TUCK";

    // splice ops
    case OP_CAT                    : return "OP_CAT";
    case OP_SUBSTR                 : return "OP_SUBSTR";
    case OP_LEFT                   : return "OP_LEFT";
    case OP_RIGHT                  : return "OP_RIGHT";
    case OP_SIZE                   : return "OP_SIZE";

    // bit logic
    case OP_INVERT                 : return "OP_INVERT";
    case OP_AND                    : return "OP_AND";
    case OP_OR                     : return "OP_OR";
    case OP_XOR                    : return "OP_XOR";
    case OP_EQUAL                  : return "OP_EQUAL";
    case OP_EQUALVERIFY            : return "OP_EQUALVERIFY";
    case OP_RESERVED1              : return "OP_RESERVED1";
    case OP_RESERVED2              : return "OP_RESERVED2";

    // numeric
    case OP_1ADD                   : return "OP_1ADD";
    case OP_1SUB                   : return "OP_1SUB";
    case OP_2MUL                   : return "OP_2MUL";
    case OP_2DIV                   : return "OP_2DIV";
    case OP_NEGATE                 : return "OP_NEGATE";
    case OP_ABS                    : return "OP_ABS";
    case OP_NOT                    : return "OP_NOT";
    case OP_0NOTEQUAL              : return "OP_0NOTEQUAL";
    case OP_ADD                    : return "OP_ADD";
    case OP_SUB                    : return "OP_SUB";
    case OP_MUL                    : return "OP_MUL";
    case OP_DIV                    : return "OP_DIV";
    case OP_MOD                    : return "OP_MOD";
    case OP_LSHIFT                 : return "OP_LSHIFT";
    case OP_RSHIFT                 : return "OP_RSHIFT";
    case OP_BOOLAND                : return "OP_BOOLAND";
    case OP_BOOLOR                 : return "OP_BOOLOR";
    case OP_NUMEQUAL               : return "OP_NUMEQUAL";
    case OP_NUMEQUALVERIFY         : return "OP_NUMEQUALVERIFY";
    case OP_NUMNOTEQUAL            : return "OP_NUMNOTEQUAL";
    case OP_LESSTHAN               : return "OP_LESSTHAN";
    case OP_GREATERTHAN            : return "OP_GREATERTHAN";
    case OP_LESSTHANOREQUAL        : return "OP_LESSTHANOREQUAL";
    case OP_GREATERTHANOREQUAL     : return "OP_GREATERTHANOREQUAL";
    case OP_MIN                    : return "OP_MIN";
    case OP_MAX                    : return "OP_MAX";
    case OP_WITHIN                 : return "OP_WITHIN";

    // crypto
    case OP_RIPEMD160              : return "OP_RIPEMD160";
    case OP_SHA1                   : return "OP_SHA1";
    case OP_SHA256                 : return "OP_SHA256";
    case OP_HASH160                : return "OP_HASH160";
    case OP_HASH256                : return "OP_HASH256";
    case OP_CODESEPARATOR          : return "OP_CODESEPARATOR";
    case OP_CHECKSIG               : return "OP_CHECKSIG";
    case OP_CHECKSIGVERIFY         : return "OP_CHECKSIGVERIFY";
    case OP_CHECKMULTISIG          : return "OP_CHECKMULTISIG";
    case OP_CHECKMULTISIGVERIFY    : return "OP_CHECKMULTISIGVERIFY";



    // multi-byte opcodes
    case OP_SINGLEBYTE_END         : return "OP_SINGLEBYTE_END";
    case OP_DOUBLEBYTE_BEGIN       : return "OP_DOUBLEBYTE_BEGIN";
    case OP_PUBKEY                 : return "OP_PUBKEY";
    case OP_PUBKEYHASH             : return "OP_PUBKEYHASH";



    case OP_INVALIDOPCODE          : return "OP_INVALIDOPCODE";
    default:
        return "UNKNOWN_OPCODE";
    }
};




inline string ValueString(const vector<unsigned char>& vch)
{
    if (vch.size() <= 4)
        return strprintf("%d", CBigNum(vch).getint());
    else
        return HexNumStr(vch.begin(), vch.end());
        //return string("(") + HexStr(vch.begin(), vch.end()) + string(")");
}

//将vstack中每一个vector<unsigned char>& vch加到string中，形成  76 A9 14 89 AB CD EF AB BA AB BA AB BA AB BA AB BA AB BA AB BA AB BA   88 AC
inline string StackString(const vector<vector<unsigned char> >& vStack)
{
    string str;
    foreach(const vector<unsigned char>& vch, vStack)
    {
        if (!str.empty())
            str += " ";
        str += ValueString(vch);
    }
    return str;
}








//unsigned char为无符号整形 占8位，即1个字节，能表示的数据范围是0~255
//CScript类包含一个将被解析并执行的脚本。一个脚本只不过是一个字符流，
//所以CScript只不过是一个vector<unsigned char>。
//脚本通过重载操作符<<被插入到CScript当中。它接受多种输入类型
//（不要与比特币脚本中的操作符搞混）。
class CScript : public vector<unsigned char>
{
protected:
    CScript& push_int64(int64 n)
    {
        if (n == -1 || (n >= 1 && n <= 16))
        {
            push_back(n + (OP_1 - 1));
        }
        else
        {
            CBigNum bn(n);
            *this << bn.getvch();
        }
        return (*this);
    }

    CScript& push_uint64(uint64 n)
    {
        if (n == -1 || (n >= 1 && n <= 16))
        {
            push_back(n + (OP_1 - 1));
        }
        else
        {
            CBigNum bn(n);
            *this << bn.getvch();
        }
        return (*this);
    }

public:
    CScript() { }
    CScript(const CScript& b) : vector<unsigned char>(b.begin(), b.end()) { }
    CScript(const_iterator pbegin, const_iterator pend) : vector<unsigned char>(pbegin, pend) { }
	
//_MSC_VER是微软C/C++编译器——cl.exe编译代码时预定义的一个宏。
//需要针对cl编写代码时， 可以使用该宏进行条件编译。	
#ifndef _MSC_VER
    CScript(const unsigned char* pbegin, const unsigned char* pend) : vector<unsigned char>(pbegin, pend) { }
#endif

    CScript& operator+=(const CScript& b)
    {
        insert(end(), b.begin(), b.end());
        return *this;
    }

    friend CScript operator+(const CScript& a, const CScript& b)
    {
        CScript ret = a;
        ret += b;
        return (ret);
    }


    explicit CScript(char b)           { operator<<(b); }
    explicit CScript(short b)          { operator<<(b); }
    explicit CScript(int b)            { operator<<(b); }
    explicit CScript(long b)           { operator<<(b); }
    explicit CScript(int64 b)          { operator<<(b); }
    explicit CScript(unsigned char b)  { operator<<(b); }
    explicit CScript(unsigned int b)   { operator<<(b); }
    explicit CScript(unsigned short b) { operator<<(b); }
    explicit CScript(unsigned long b)  { operator<<(b); }
    explicit CScript(uint64 b)         { operator<<(b); }

    explicit CScript(opcodetype b)     { operator<<(b); }
    explicit CScript(const uint256& b) { operator<<(b); }
    explicit CScript(const CBigNum& b) { operator<<(b); }
    explicit CScript(const vector<unsigned char>& b) { operator<<(b); }


    CScript& operator<<(char b)           { return (push_int64(b)); }
    CScript& operator<<(short b)          { return (push_int64(b)); }
    CScript& operator<<(int b)            { return (push_int64(b)); }
    CScript& operator<<(long b)           { return (push_int64(b)); }
    CScript& operator<<(int64 b)          { return (push_int64(b)); }
    CScript& operator<<(unsigned char b)  { return (push_uint64(b)); }
    CScript& operator<<(unsigned int b)   { return (push_uint64(b)); }
    CScript& operator<<(unsigned short b) { return (push_uint64(b)); }
    CScript& operator<<(unsigned long b)  { return (push_uint64(b)); }
    CScript& operator<<(uint64 b)         { return (push_uint64(b)); }

    CScript& operator<<(opcodetype opcode)
    {
        if (opcode <= OP_SINGLEBYTE_END)
        {
            insert(end(), (unsigned char)opcode);
        }
        else
        {
            assert(opcode >= OP_DOUBLEBYTE_BEGIN);
            insert(end(), (unsigned char)(opcode >> 8));
            insert(end(), (unsigned char)(opcode & 0xFF));
        }
        return (*this);
    }

    CScript& operator<<(const uint160& b)
    {
        insert(end(), sizeof(b));
        insert(end(), (unsigned char*)&b, (unsigned char*)&b + sizeof(b));
        return (*this);
    }

    CScript& operator<<(const uint256& b)
    {
        insert(end(), sizeof(b));
        insert(end(), (unsigned char*)&b, (unsigned char*)&b + sizeof(b));
        return (*this);
    }

    CScript& operator<<(const CBigNum& b)
    {
        *this << b.getvch();
        return (*this);
    }

    CScript& operator<<(const vector<unsigned char>& b)
    {
        if (b.size() < OP_PUSHDATA1)
        {
            insert(end(), (unsigned char)b.size());
        }
        else if (b.size() <= 0xff)
        {
            insert(end(), OP_PUSHDATA1);
            insert(end(), (unsigned char)b.size());
        }
        else
        {
            insert(end(), OP_PUSHDATA2);
            unsigned short nSize = b.size();
            insert(end(), (unsigned char*)&nSize, (unsigned char*)&nSize + sizeof(nSize));
        }
        insert(end(), b.begin(), b.end());
        return (*this);
    }

    CScript& operator<<(const CScript& b)
    {
        // I'm not sure if this should push the script or concatenate scripts.
        // If there's ever a use for pushing a script onto a script, delete this member fn
        assert(("warning: pushing a CScript onto a CScript with << is probably not intended, use + to concatenate", false));
        return (*this);
    }

    //
    bool GetOp(iterator& pc, opcodetype& opcodeRet, vector<unsigned char>& vchRet)
    {
         // This is why people hate C++
         const_iterator pc2 = pc;
         bool fRet = GetOp(pc2, opcodeRet, vchRet);
         pc = begin() + (pc2 - begin());
         return fRet;
    }




/*
该函数从pc中读取一个指令（如果必须，一个操作符或操作数），并将它们分别放入opcodeRet和vchRet。迭代器pc指向CScript的内部存储中将要读取数据的位置。
以下是该函数的用途：
1.它区分单字节与双字节的操作符。如果第一个字节大于0xF0（第14行），则下一个字节将被提取，
并将这两个字节合并成一个双字节操作符（第16、17行）。这便是为什么双字节操作符中最高有效字节首先被压入。
所有的双字节操作符的第一个字节均大于0xF0，而所有单字节操作符的第一个字节均小于0xF0。
2.在第20行，如果第一个字节小于或等于78（OP_PUSHDATA4的代码值），则根据值的大小，该函数有4种不同情况：
如果代码值是76（OP_PUSHDATA1的代码值），它读取接下来一个字节作为数据的大小至nSize（第27行），接着读取nSize个字节至vchRet（第46行）。所以，假设nSize = 100，则读取接下来100个字节至vchRet。
如果代码值是77（OP_PUSHDATA2的代码值），它读取接下来两个字节作为数据的大小（第34行），接着读取数据本身至vchRet（第46行）。
如果代码值是78（OP_PUSHDATA4的代码值），它读取接下来四个字节作为数据的大小（第41行），接着读取数据本身至vchRet（第46行）。
否则，如果代码值位于0与75之间（包括两者），该值被当作数据的大小（第22行）。该函数将读取相同大小的字节至vchRet（第46行）。
你或许会奇怪这样将会返回哪种操作符。返回的操作符代码是提取出的一个位于0与75之间的代码，其实是UNKNOWN_OPCODE（除了0之外，表示OP_0或OP_FALSE）。这不会引起任何问题，
当你了解在指令执行过程当中如处理UNKNOWN_OPCODE的之后就会明白。
*/
    bool GetOp(const_iterator& pc, opcodetype& opcodeRet, vector<unsigned char>& vchRet) const
    {
        opcodeRet = OP_INVALIDOPCODE;
        vchRet.clear();
        if (pc >= end())
            return false;

        // Read instruction
        unsigned int opcode = *pc++;
        if (opcode >= OP_SINGLEBYTE_END)
        {
            if (pc + 1 > end())
                return false;
            opcode <<= 8;
            opcode |= *pc++;
        }

        // Immediate operand
        if (opcode <= OP_PUSHDATA4)
        {
            unsigned int nSize = opcode;
            if (opcode == OP_PUSHDATA1)
            {
                if (pc + 1 > end())
                    return false;
                nSize = *pc++;
            }
            else if (opcode == OP_PUSHDATA2)
            {
                if (pc + 2 > end())
                    return false;
                nSize = 0;
                memcpy(&nSize, &pc[0], 2);
                pc += 2;
            }
            else if (opcode == OP_PUSHDATA4)
            {
                if (pc + 4 > end())
                    return false;
                memcpy(&nSize, &pc[0], 4);
                pc += 4;
            }
            if (pc + nSize > end())
                return false;
            vchRet.assign(pc, pc + nSize);
            pc += nSize;
        }

        opcodeRet = (opcodetype)opcode;
        return true;
    }








    void FindAndDelete(const CScript& b)
    {
        iterator pc = begin();
        opcodetype opcode;
        vector<unsigned char> vchPushValue;
        int count = 0;
        do
        {
            while (end() - pc >= b.size() && memcmp(&pc[0], &b[0], b.size()) == 0)
            {
                erase(pc, pc + b.size());
                count++;
            }
        }
        while (GetOp(pc, opcode, vchPushValue));
        //printf("FindAndDeleted deleted %d items\n", count); /// debug
    }

    //打印16位数
    void PrintHex() const
    {
        printf("CScript(%s)\n", HexStr(begin(), end()).c_str());
    }

    string ToString() const
    {
        string str;
        opcodetype opcode;
        vector<unsigned char> vch;
        const_iterator it = begin();
        while (GetOp(it, opcode, vch))
        {
            if (!str.empty())
                str += " ";
            if (opcode <= OP_PUSHDATA4)
                str += ValueString(vch);
            else
                str += GetOpName(opcode);
        }
        return str;
    }

    void print() const
    {
        printf("%s\n", ToString().c_str());
    }
};

/*
重载之后的CScript的<<操作符接受的类型为char，short，int，long，并隐性将它们转换为int64（又称为long long），并调用push_int64(int64 n)将它们放入CScript的内部存储当中（由于CScript延伸了vector<unsigned char>，它的内部存储即为后者。你可以将它看做一个unsigned char类型的动态数组。通过检查push_int64(int64 n)的主体部分，显示如果n为-1或位于1与16之间，n则被压入为n + (OP_1 – 1)，即n + (81 -1) = n + 80 (OP_1 = 0×51)。于是，如果n为-1，则以单字节值79被压入栈，即操作符代码值OP_1NEGATE。如果n位于1与16之间，则以单字节值81至96被压入栈，正是操作符代码值OP_1至OP_16。对于其他n的值，则将其以CBigNum对待。简而言之：

当n为-1时，n被看作为操作符OP_1NEGATE（79）。
当n为1-16之间的数字时，n被看作为OP_1（81）与OP_16（96）之间的一个操作符。
否则，n被当作CBigNum类型，并返回bn.getvch()的值，该值为一个字符类容器，并被压入内部存储（第12行）。我将在后面对CBigNum进行介绍。
重载后的操作符<<同样接受usigned版本的char，short，int，long和uint64作为输入类型。它们对应的重载函数与它们的signed版本的逻辑相同。
现在，我们来检查一下其他输入类型的操作符重载函数。

对于输入类型uint160，首先将数据的大小压入内部存储（第51行），接着是数据本身（第52行）。该过程同样被应用于输入类型uint256（第55行）。这两种类型被用于存放哈希码。

对于输入类型opcodetype，例如操作符类型，则将代码值直接压入内部存储当中（第39行）。如果代码值占用2个字节，它们将被先后压入（第44至45行）。注意最高有效字节首先被压入（第44行）。
所以代码0xF001将被压入为0xF001，而不是0x01F0。我将在接下来CScript::GetOp()中详细介绍为什么这么做很重要。

对于输入类型CBigNum，一个字符类容器用于表示被压入的big number类型（第63行）。这与push_int64()处理CBigNum的方式一致。

对于输入类型vector <unsigned char>，过程则更加复杂：
如果输入b的大小小于76（OP_PUSHDATA1的代码值），则b的大小将首先以单字节值被压入（第70行），接着是数据b本身（第83行）。
如果b的大小在76与255之间（包括两者），操作符OP_PUSHDATA1首先被压入（第74行），接着是b的大小以单字节值的形式（第75行），接着是数据b本身（第83行）。
否则，操作符OP_PUSHDATA2首先被压入（第2行），接着是b的大小以双字节（short）值的形式（第80至81行），接着是数据b本身（第83行）。
重载之后的操作符<<将指令压入CScript，函数CScript::GetOp()则将指令提取出CScript。

*/






bool EvalScript(const CScript& script, const CTransaction& txTo, unsigned int nIn, int nHashType=0,
                vector<vector<unsigned char> >* pvStackRet=NULL);
uint256 SignatureHash(CScript scriptCode, const CTransaction& txTo, unsigned int nIn, int nHashType);
bool IsMine(const CScript& scriptPubKey);
bool ExtractPubKey(const CScript& scriptPubKey, bool fMineOnly, vector<unsigned char>& vchPubKeyRet);  //从scriptpubkey中提取pubkey
bool ExtractHash160(const CScript& scriptPubKey, uint160& hash160Ret);     //从scriptpubeky中提取hash160
bool SignSignature(const CTransaction& txFrom, CTransaction& txTo, unsigned int nIn, int nHashType=SIGHASH_ALL, CScript scriptPrereq=CScript());  //对这个交易签名
bool VerifySignature(const CTransaction& txFrom, const CTransaction& txTo, unsigned int nIn, int nHashType=0);   //验证这个签名
