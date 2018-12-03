// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#include "headers.h"

bool CheckSig(vector<unsigned char> vchSig, vector<unsigned char> vchPubKey, CScript scriptCode, const CTransaction& txTo, unsigned int nIn, int nHashType);


typedef vector<unsigned char> valtype;
static const valtype vchFalse(0);
static const valtype vchZero(0);
static const valtype vchTrue(1, 1);

//CBigNum代笔大数类，从openssl中继承而来
static const CBigNum bnZero(0);
static const CBigNum bnOne(1);
static const CBigNum bnFalse(0);
static const CBigNum bnTrue(1);

//vch如故是0，就返回false
bool CastToBool(const valtype& vch)
{
    return (CBigNum(vch) != bnZero);
}

//让两个vector<unsigned char> 尺寸相同
void MakeSameSize(valtype& vch1, valtype& vch2)
{
    // Lengthen the shorter one
    if (vch1.size() < vch2.size())
        vch1.resize(vch2.size(), 0);
    if (vch2.size() < vch1.size())
        vch2.resize(vch1.size(), 0);
}



//
// Script is a stack machine (like Forth) that evaluates a predicate
// returning a bool indicating valid or not.  There are no loops.
// 脚本就是一个栈， 来返回一个布尔值来表示有意义或没有意义
#define stacktop(i)  (stack.at(stack.size()+(i)))
#define altstacktop(i)  (altstack.at(altstack.size()+(i)))










/*
现在我们回到SignSignature()。在该函数的第12行之后，txin.scriptsig，即wtxNew的第nIn笔输入交易中的scriptSig部分，将插入一个签名。该签名可能是以下其中之一：

vchSig vchPubKey（脚本A的签名A）
vchSig（脚本B的签名B）
在下文当中，vchSig将被引用为<你的签名_vchSig>，vchPubKey则为<你的公钥_vchPubKey>，以强调它们分别是你本人的签名和公钥。
*/


/*
EvalScript()带有3个参数，分别为：

第一个参数为txin.scriptSig + CScript(OP_CODESEPARATOR) + txout.scriptPubKey。它有可能是：
验证情形A：<你的签名_vchSig> <你的公钥_vchPubKey> OP_CODESEPARATOR OP_DUP OP_HASH160 <你的地址160位哈希> OP_EQUALVERIFY OP_CHECKSIG，即签名A + OP_CODESEPARATOR + 脚本A。
验证情形B：<你的签名_vchSig> OP_CODESEPARATOR <你的公钥_vchPubKey> OP_CHECKSIG，即签名B + OP_CODESEPARATOR + 脚本B。
第二个参数为新创建的交易txTo，即CreateTransaction()中的wtxNew。
第三个参数为nIn，即将被验证的交易在txTo输入交易列表中的位置。
*/
/*
该函数依次执行所传入脚本中包含的指令。所返回的结果为布尔值true或false。它通过一个while循环（第13行）依次提取脚本中的指令。在循环里，根据当前指令的操作符，执行过程会进入相应的分支并执行指令。以下是该函数的源码：
*/

bool EvalScript(const CScript& script, const CTransaction& txTo, unsigned int nIn, int nHashType,
                vector<vector<unsigned char> >* pvStackRet)
{
    CAutoBN_CTX pctx;
    CScript::const_iterator pc = script.begin();
    CScript::const_iterator pend = script.end();
    CScript::const_iterator pbegincodehash = script.begin();
    vector<bool> vfExec;
    vector<valtype> stack;
    vector<valtype> altstack;
    if (pvStackRet)
        pvStackRet->clear();


    while (pc < pend)
    {
        //count是来数false在这些里面出现了多少次，若果没出现就是0，fExec就是true
        bool fExec = !count(vfExec.begin(), vfExec.end(), false);

        //
        // Read instruction
        //
        //执行指令，opcodetype
        opcodetype opcode;
        valtype vchPushValue;
        if (!script.GetOp(pc, opcode, vchPushValue))
            return false;

        if (fExec && opcode <= OP_PUSHDATA4)
            stack.push_back(vchPushValue);
        else if (fExec || (OP_IF <= opcode && opcode <= OP_ENDIF))
        switch (opcode)
        {
            //
            // Push value
            //
            case OP_1NEGATE:
            case OP_1:
            case OP_2:
            case OP_3:
            case OP_4:
            case OP_5:
            case OP_6:
            case OP_7:
            case OP_8:
            case OP_9:
            case OP_10:
            case OP_11:
            case OP_12:
            case OP_13:
            case OP_14:
            case OP_15:
            case OP_16:
            {
                // ( -- value)
                CBigNum bn((int)opcode - (int)(OP_1 - 1));
                stack.push_back(bn.getvch());
            }
            break;


            //
            // Control
            //
            case OP_NOP:
            break;

            case OP_VER:
            {
                CBigNum bn(VERSION);
                stack.push_back(bn.getvch());
            }
            break;

            case OP_IF:
            case OP_NOTIF:
            case OP_VERIF:
            case OP_VERNOTIF:
            {
                // <expression> if [statements] [else [statements]] endif
                bool fValue = false;
                if (fExec)
                {
                    if (stack.size() < 1)
                        return false;
                    valtype& vch = stacktop(-1);
                    if (opcode == OP_VERIF || opcode == OP_VERNOTIF)
                        fValue = (CBigNum(VERSION) >= CBigNum(vch));
                    else
                        fValue = CastToBool(vch);
                    if (opcode == OP_NOTIF || opcode == OP_VERNOTIF)
                        fValue = !fValue;
                    stack.pop_back();
                }
                vfExec.push_back(fValue);
            }
            break;

            case OP_ELSE:
            {
                if (vfExec.empty())
                    return false;
                vfExec.back() = !vfExec.back();
            }
            break;

            case OP_ENDIF:
            {
                if (vfExec.empty())
                    return false;
                vfExec.pop_back();
            }
            break;

            case OP_VERIFY:
            {
                // (true -- ) or
                // (false -- false) and return
                if (stack.size() < 1)
                    return false;
                bool fValue = CastToBool(stacktop(-1));
                if (fValue)
                    stack.pop_back();
                else
                    pc = pend;
            }
            break;

            case OP_RETURN:
            {
                pc = pend;
            }
            break;


            //
            // Stack ops
            //
            case OP_TOALTSTACK:
            {
                if (stack.size() < 1)
                    return false;
                altstack.push_back(stacktop(-1));
                stack.pop_back();
            }
            break;

            case OP_FROMALTSTACK:
            {
                if (altstack.size() < 1)
                    return false;
                stack.push_back(altstacktop(-1));
                altstack.pop_back();
            }
            break;

            case OP_2DROP:
            {
                // (x1 x2 -- )
                stack.pop_back();
                stack.pop_back();
            }
            break;

            case OP_2DUP:
            {
                // (x1 x2 -- x1 x2 x1 x2)
                if (stack.size() < 2)
                    return false;
                valtype vch1 = stacktop(-2);
                valtype vch2 = stacktop(-1);
                stack.push_back(vch1);
                stack.push_back(vch2);
            }
            break;

            case OP_3DUP:
            {
                // (x1 x2 x3 -- x1 x2 x3 x1 x2 x3)
                if (stack.size() < 3)
                    return false;
                valtype vch1 = stacktop(-3);
                valtype vch2 = stacktop(-2);
                valtype vch3 = stacktop(-1);
                stack.push_back(vch1);
                stack.push_back(vch2);
                stack.push_back(vch3);
            }
            break;

            case OP_2OVER:
            {
                // (x1 x2 x3 x4 -- x1 x2 x3 x4 x1 x2)
                if (stack.size() < 4)
                    return false;
                valtype vch1 = stacktop(-4);
                valtype vch2 = stacktop(-3);
                stack.push_back(vch1);
                stack.push_back(vch2);
            }
            break;

            case OP_2ROT:
            {
                // (x1 x2 x3 x4 x5 x6 -- x3 x4 x5 x6 x1 x2)
                if (stack.size() < 6)
                    return false;
                valtype vch1 = stacktop(-6);
                valtype vch2 = stacktop(-5);
                stack.erase(stack.end()-6, stack.end()-4);
                stack.push_back(vch1);
                stack.push_back(vch2);
            }
            break;

            case OP_2SWAP:
            {
                // (x1 x2 x3 x4 -- x3 x4 x1 x2)
                if (stack.size() < 4)
                    return false;
                swap(stacktop(-4), stacktop(-2));
                swap(stacktop(-3), stacktop(-1));
            }
            break;

            case OP_IFDUP:
            {
                // (x - 0 | x x)
                if (stack.size() < 1)
                    return false;
                valtype vch = stacktop(-1);
                if (CastToBool(vch))
                    stack.push_back(vch);
            }
            break;

            case OP_DEPTH:
            {
                // -- stacksize
                CBigNum bn(stack.size());
                stack.push_back(bn.getvch());
            }
            break;

            case OP_DROP:
            {
                // (x -- )
                if (stack.size() < 1)
                    return false;
                stack.pop_back();
            }
            break;

            case OP_DUP:
            {
                // (x -- x x)
                if (stack.size() < 1)
                    return false;
                valtype vch = stacktop(-1);
                stack.push_back(vch);
            }
            break;

            case OP_NIP:
            {
                // (x1 x2 -- x2)
                if (stack.size() < 2)
                    return false;
                stack.erase(stack.end() - 2);
            }
            break;

            case OP_OVER:
            {
                // (x1 x2 -- x1 x2 x1)
                if (stack.size() < 2)
                    return false;
                valtype vch = stacktop(-2);
                stack.push_back(vch);
            }
            break;

            case OP_PICK:
            case OP_ROLL:
            {
                // (xn ... x2 x1 x0 n - xn ... x2 x1 x0 xn)
                // (xn ... x2 x1 x0 n - ... x2 x1 x0 xn)
                if (stack.size() < 2)
                    return false;
                int n = CBigNum(stacktop(-1)).getint();
                stack.pop_back();
                if (n < 0 || n >= stack.size())
                    return false;
                valtype vch = stacktop(-n-1);
                if (opcode == OP_ROLL)
                    stack.erase(stack.end()-n-1);
                stack.push_back(vch);
            }
            break;

            case OP_ROT:
            {
                // (x1 x2 x3 -- x2 x3 x1)
                //  x2 x1 x3  after first swap
                //  x2 x3 x1  after second swap
                if (stack.size() < 3)
                    return false;
                swap(stacktop(-3), stacktop(-2));
                swap(stacktop(-2), stacktop(-1));
            }
            break;

            case OP_SWAP:
            {
                // (x1 x2 -- x2 x1)
                if (stack.size() < 2)
                    return false;
                swap(stacktop(-2), stacktop(-1));
            }
            break;

            case OP_TUCK:
            {
                // (x1 x2 -- x2 x1 x2)
                if (stack.size() < 2)
                    return false;
                valtype vch = stacktop(-1);
                stack.insert(stack.end()-2, vch);
            }
            break;


            //
            // Splice ops
            //
            case OP_CAT:
            {
                // (x1 x2 -- out)
                if (stack.size() < 2)
                    return false;
                valtype& vch1 = stacktop(-2);
                valtype& vch2 = stacktop(-1);
                vch1.insert(vch1.end(), vch2.begin(), vch2.end());
                stack.pop_back();
            }
            break;

            case OP_SUBSTR:
            {
                // (in begin size -- out)
                if (stack.size() < 3)
                    return false;
                valtype& vch = stacktop(-3);
                int nBegin = CBigNum(stacktop(-2)).getint();
                int nEnd = nBegin + CBigNum(stacktop(-1)).getint();
                if (nBegin < 0 || nEnd < nBegin)
                    return false;
                if (nBegin > vch.size())
                    nBegin = vch.size();
                if (nEnd > vch.size())
                    nEnd = vch.size();
                vch.erase(vch.begin() + nEnd, vch.end());
                vch.erase(vch.begin(), vch.begin() + nBegin);
                stack.pop_back();
                stack.pop_back();
            }
            break;

            case OP_LEFT:
            case OP_RIGHT:
            {
                // (in size -- out)
                if (stack.size() < 2)
                    return false;
                valtype& vch = stacktop(-2);
                int nSize = CBigNum(stacktop(-1)).getint();
                if (nSize < 0)
                    return false;
                if (nSize > vch.size())
                    nSize = vch.size();
                if (opcode == OP_LEFT)
                    vch.erase(vch.begin() + nSize, vch.end());
                else
                    vch.erase(vch.begin(), vch.end() - nSize);
                stack.pop_back();
            }
            break;

            case OP_SIZE:
            {
                // (in -- in size)
                if (stack.size() < 1)
                    return false;
                CBigNum bn(stacktop(-1).size());
                stack.push_back(bn.getvch());
            }
            break;


            //
            // Bitwise logic
            //
            case OP_INVERT:
            {
                // (in - out)
                if (stack.size() < 1)
                    return false;
                valtype& vch = stacktop(-1);
                for (int i = 0; i < vch.size(); i++)
                    vch[i] = ~vch[i];
            }
            break;

            case OP_AND:
            case OP_OR:
            case OP_XOR:
            {
                // (x1 x2 - out)
                if (stack.size() < 2)
                    return false;
                valtype& vch1 = stacktop(-2);
                valtype& vch2 = stacktop(-1);
                MakeSameSize(vch1, vch2);
                if (opcode == OP_AND)
                {
                    for (int i = 0; i < vch1.size(); i++)
                        vch1[i] &= vch2[i];
                }
                else if (opcode == OP_OR)
                {
                    for (int i = 0; i < vch1.size(); i++)
                        vch1[i] |= vch2[i];
                }
                else if (opcode == OP_XOR)
                {
                    for (int i = 0; i < vch1.size(); i++)
                        vch1[i] ^= vch2[i];
                }
                stack.pop_back();
            }
            break;

            case OP_EQUAL:
            case OP_EQUALVERIFY:
            //case OP_NOTEQUAL: // use OP_NUMNOTEQUAL
            {
                // (x1 x2 - bool)
                if (stack.size() < 2)
                    return false;
                valtype& vch1 = stacktop(-2);
                valtype& vch2 = stacktop(-1);
                bool fEqual = (vch1 == vch2);
                // OP_NOTEQUAL is disabled because it would be too easy to say
                // something like n != 1 and have some wiseguy pass in 1 with extra
                // zero bytes after it (numerically, 0x01 == 0x0001 == 0x000001)
                //if (opcode == OP_NOTEQUAL)
                //    fEqual = !fEqual;
                stack.pop_back();
                stack.pop_back();
                stack.push_back(fEqual ? vchTrue : vchFalse);
                if (opcode == OP_EQUALVERIFY)
                {
                    if (fEqual)
                        stack.pop_back();
                    else
                        pc = pend;
                }
            }
            break;


            //
            // Numeric
            //
            case OP_1ADD:
            case OP_1SUB:
            case OP_2MUL:
            case OP_2DIV:
            case OP_NEGATE:
            case OP_ABS:
            case OP_NOT:
            case OP_0NOTEQUAL:
            {
                // (in -- out)
                if (stack.size() < 1)
                    return false;
                CBigNum bn(stacktop(-1));
                switch (opcode)
                {
                case OP_1ADD:       bn += bnOne; break;
                case OP_1SUB:       bn -= bnOne; break;
                case OP_2MUL:       bn <<= 1; break;
                case OP_2DIV:       bn >>= 1; break;
                case OP_NEGATE:     bn = -bn; break;
                case OP_ABS:        if (bn < bnZero) bn = -bn; break;
                case OP_NOT:        bn = (bn == bnZero); break;
                case OP_0NOTEQUAL:  bn = (bn != bnZero); break;
                }
                stack.pop_back();
                stack.push_back(bn.getvch());
            }
            break;

            case OP_ADD:
            case OP_SUB:
            case OP_MUL:
            case OP_DIV:
            case OP_MOD:
            case OP_LSHIFT:
            case OP_RSHIFT:
            case OP_BOOLAND:
            case OP_BOOLOR:
            case OP_NUMEQUAL:
            case OP_NUMEQUALVERIFY:
            case OP_NUMNOTEQUAL:
            case OP_LESSTHAN:
            case OP_GREATERTHAN:
            case OP_LESSTHANOREQUAL:
            case OP_GREATERTHANOREQUAL:
            case OP_MIN:
            case OP_MAX:
            {
                // (x1 x2 -- out)
                if (stack.size() < 2)
                    return false;
                CBigNum bn1(stacktop(-2));
                CBigNum bn2(stacktop(-1));
                CBigNum bn;
                switch (opcode)
                {
                case OP_ADD:
                    bn = bn1 + bn2;
                    break;

                case OP_SUB:
                    bn = bn1 - bn2;
                    break;

                case OP_MUL:
                    if (!BN_mul(&bn, &bn1, &bn2, pctx))
                        return false;
                    break;

                case OP_DIV:
                    if (!BN_div(&bn, NULL, &bn1, &bn2, pctx))
                        return false;
                    break;

                case OP_MOD:
                    if (!BN_mod(&bn, &bn1, &bn2, pctx))
                        return false;
                    break;

                case OP_LSHIFT:
                    if (bn2 < bnZero)
                        return false;
                    bn = bn1 << bn2.getulong();
                    break;

                case OP_RSHIFT:
                    if (bn2 < bnZero)
                        return false;
                    bn = bn1 >> bn2.getulong();
                    break;

                case OP_BOOLAND:             bn = (bn1 != bnZero && bn2 != bnZero); break;
                case OP_BOOLOR:              bn = (bn1 != bnZero || bn2 != bnZero); break;
                case OP_NUMEQUAL:            bn = (bn1 == bn2); break;
                case OP_NUMEQUALVERIFY:      bn = (bn1 == bn2); break;
                case OP_NUMNOTEQUAL:         bn = (bn1 != bn2); break;
                case OP_LESSTHAN:            bn = (bn1 < bn2); break;
                case OP_GREATERTHAN:         bn = (bn1 > bn2); break;
                case OP_LESSTHANOREQUAL:     bn = (bn1 <= bn2); break;
                case OP_GREATERTHANOREQUAL:  bn = (bn1 >= bn2); break;
                case OP_MIN:                 bn = (bn1 < bn2 ? bn1 : bn2); break;
                case OP_MAX:                 bn = (bn1 > bn2 ? bn1 : bn2); break;
                }
                stack.pop_back();
                stack.pop_back();
                stack.push_back(bn.getvch());

                if (opcode == OP_NUMEQUALVERIFY)
                {
                    if (CastToBool(stacktop(-1)))
                        stack.pop_back();
                    else
                        pc = pend;
                }
            }
            break;

            case OP_WITHIN:
            {
                // (x min max -- out)
                if (stack.size() < 3)
                    return false;
                CBigNum bn1(stacktop(-3));
                CBigNum bn2(stacktop(-2));
                CBigNum bn3(stacktop(-1));
                bool fValue = (bn2 <= bn1 && bn1 < bn3);
                stack.pop_back();
                stack.pop_back();
                stack.pop_back();
                stack.push_back(fValue ? vchTrue : vchFalse);
            }
            break;


            //
            // Crypto
            //
            case OP_RIPEMD160:
            case OP_SHA1:
            case OP_SHA256:
            case OP_HASH160:
            case OP_HASH256:
            {
                // (in -- hash)
                if (stack.size() < 1)
                    return false;
                valtype& vch = stacktop(-1);
                valtype vchHash(opcode == OP_RIPEMD160 || opcode == OP_SHA1 || opcode == OP_HASH160 ? 20 : 32);
                if (opcode == OP_RIPEMD160)
                    RIPEMD160(&vch[0], vch.size(), &vchHash[0]);
                else if (opcode == OP_SHA1)
                    SHA1(&vch[0], vch.size(), &vchHash[0]);
                else if (opcode == OP_SHA256)
                    SHA256(&vch[0], vch.size(), &vchHash[0]);
                else if (opcode == OP_HASH160)
                {
                    uint160 hash160 = Hash160(vch);
                    memcpy(&vchHash[0], &hash160, sizeof(hash160));
                }
                else if (opcode == OP_HASH256)
                {
                    uint256 hash = Hash(vch.begin(), vch.end());
                    memcpy(&vchHash[0], &hash, sizeof(hash));
                }
                stack.pop_back();
                stack.push_back(vchHash);
            }
            break;

            case OP_CODESEPARATOR:
            {
                // Hash starts after the code separator
                pbegincodehash = pc;
            }
            break;

            case OP_CHECKSIG:
            case OP_CHECKSIGVERIFY:
            {
                // (sig pubkey -- bool)
                if (stack.size() < 2)
                    return false;

                valtype& vchSig    = stacktop(-2);
                valtype& vchPubKey = stacktop(-1);

                ////// debug print
                //PrintHex(vchSig.begin(), vchSig.end(), "sig: %s\n");
                //PrintHex(vchPubKey.begin(), vchPubKey.end(), "pubkey: %s\n");

                // Subset of script starting at the most recent codeseparator
                CScript scriptCode(pbegincodehash, pend);

                // Drop the signature, since there's no way for a signature to sign itself
                scriptCode.FindAndDelete(CScript(vchSig));

                bool fSuccess = CheckSig(vchSig, vchPubKey, scriptCode, txTo, nIn, nHashType);

                stack.pop_back();
                stack.pop_back();
                stack.push_back(fSuccess ? vchTrue : vchFalse);
                if (opcode == OP_CHECKSIGVERIFY)
                {
                    if (fSuccess)
                        stack.pop_back();
                    else
                        pc = pend;
                }
            }
            break;

            case OP_CHECKMULTISIG:
            case OP_CHECKMULTISIGVERIFY:
            {
                // ([sig ...] num_of_signatures [pubkey ...] num_of_pubkeys -- bool)

                int i = 1;
                if (stack.size() < i)
                    return false;

                int nKeysCount = CBigNum(stacktop(-i)).getint();
                if (nKeysCount < 0)
                    return false;
                int ikey = ++i;
                i += nKeysCount;
                if (stack.size() < i)
                    return false;

                int nSigsCount = CBigNum(stacktop(-i)).getint();
                if (nSigsCount < 0 || nSigsCount > nKeysCount)
                    return false;
                int isig = ++i;
                i += nSigsCount;
                if (stack.size() < i)
                    return false;

                // Subset of script starting at the most recent codeseparator
                CScript scriptCode(pbegincodehash, pend);

                // Drop the signatures, since there's no way for a signature to sign itself
                for (int i = 0; i < nSigsCount; i++)
                {
                    valtype& vchSig = stacktop(-isig-i);
                    scriptCode.FindAndDelete(CScript(vchSig));
                }

                bool fSuccess = true;
                while (fSuccess && nSigsCount > 0)
                {
                    valtype& vchSig    = stacktop(-isig);
                    valtype& vchPubKey = stacktop(-ikey);

                    // Check signature
                    if (CheckSig(vchSig, vchPubKey, scriptCode, txTo, nIn, nHashType))
                    {
                        isig++;
                        nSigsCount--;
                    }
                    ikey++;
                    nKeysCount--;

                    // If there are more signatures left than keys left,
                    // then too many signatures have failed
                    if (nSigsCount > nKeysCount)
                        fSuccess = false;
                }

                while (i-- > 0)
                    stack.pop_back();
                stack.push_back(fSuccess ? vchTrue : vchFalse);

                if (opcode == OP_CHECKMULTISIGVERIFY)
                {
                    if (fSuccess)
                        stack.pop_back();
                    else
                        pc = pend;
                }
            }
            break;

            default:
                return false;
        }
    }


    if (pvStackRet)
        *pvStackRet = stack;
    return (stack.empty() ? false : CastToBool(stack.back()));
}

/*
以下是关于该函数的一些重要部分：

1.迭代器pc总是指向下一个将要读取的字节。
2.stack是该函数用于操作的主栈。所有从输入脚本中提取的操作数将被压入这个栈当中。所有的通过存放在该栈里的操作数上应用操作符产生的结果也将被压回这个栈。
3.如果script.GetOp(pc, opcode, vchPushValue)返回为true（第21行），opcode将包含提取出的操作符，而vchPushValue将包括操作数，如果有的话。
4.在第23行，如果opcode小于或等于78（OP_PUSHDATA4的代码值），则vchPushValue中的数据被压入stack，位于第24行。（现在不要管布尔变量fExec，我将会在后面提到）。所以，如果opcode是位于1与75之间的值，即UNKNOWN_OPCODE，vchPushValue中的数据将被压入stack。对于opcode值0，76，77，78同样如此。所以，比特币脚本语言对短操作数进行了优化：对于小于或等于75字节的操作数，你只需要首先压入数据的大小，接着数据本身至CScript中。解释器将正确处理它。对于长的操作数，你必须首先压入一个OP_PUSHDATA#操作符。
5.操作符OP_1NEGATE和OP_1与OP_16之间的操作符首先将它们所对应的数据值压入stack（第51行）。因此，OP_1NEGATE（代码值79）将-1压入stack，+OP_2（代码值82）将2压入stack，以此类推。这与push_int64()处理输入数据的方式是一致的。
EvalScript()的结构简单而清晰：script.GetOP()从script（第21行）提取一个指令。取决于所提取的操作符opcode，每种情况分别在switch(opcode)语句（第26行）中的某一分支执行。只有含有变量fExec的代码（第23与25行）令人有些疑惑。下面让我们更进一步了解它们。
嵌套OP_IF
变量fExec在每次循环的开始被赋予一个新值（第15行）。如果容器vfExec包含至少一个false，它的值为false。否则，如果vfExec的每一个条目均为true，则它的值为true。
容器vfExec是一个用来记录在一个嵌套OP_IF语句中当前指令位置的栈。这个位置决定当前指令是否被执行。
在任何时候，vfExec中的条目表示当前指令在嵌套OP_IF语句当中的位置。例如，[true, false]意味着当前指令位于内层语句的false分支，同时位于外层语句的true分支。这便市为什么当vfExec中包含至少一个false时，整个便为false。因为任何vfExec的false表示当前指令在嵌套OP_IF语句当中的某个false分支上，因此不会被执行。

若干switch分支
1.OP_EQUALVERIFY分支非常简单（第106至107行），它从stack中弹出两个值并进行比较（第113至114行）。
2.哈希操作符被放在了一起（第137-141行）。操作符OP_RIPEMD160、OP_SHA1与OP_HASH160的输出大小为160位，OP_SHA256和OP_HASH256为256位。将要哈希的数据从stack顶部取出（第146行），结果被放回stack（第165行）。
3.OP_CHECKSIG分支更有意思（第174至175行）。该分支检查交易txTo（第二个参数）的签名部分。我现在用我在第一章所提到的例子中的脚本A和B解释一下该操作符是怎样被执行验证签名的。


执行OP_CHECKSIG
现在我用中的验证案例A与B说明：
验证案例A：<你的签名_vchSig> <你的公钥_vchPubKey> OP_CODESEPARATOR OP_DUP OP_HASH160 <你的地址_hash160> OP_EQUALVERIFY OP__CHECKSIG，例如签名A + OP_CODESEPARATOR + 脚本A。
验证案例B：<你的签名_vchSig> OP_CODESEPARATOR <你的公钥_vchPubKey> OP__CHECKSIG，例如签名B + OP_CODESEPARATOR + 脚本B。
我将会讲解验证案例B，你可以自己推出验证案例A。
首先，注意签名B + OP_CODESEPARATOR + 脚本B被作为第一个参数script传入至函数EvalScript()。
第一个被读入的指令是 <你的公钥_vchPubKey> ，它是一个类型为vector <unsigned char>的签名。因此，它将被压入stack，位于第24行。
第二个被读入的指令是OP_CODESEPARATOR。在第171行，一个本地变量pegincodehash被赋予值pc，指向下一个将被读取的指令，即 <你的公钥_vchPubKey>。
第三个被读入的指令是 <你的公钥_vchPubKey>，它是一个256位的公钥，并将会被压入stack，位于第24行。
第四个被读入的指令是OP__CHECKSIG。执行将进入OP__CHECKSIG分支（第174至175行）。
在第180行，<你的签名_vchSig>从stack中被提出，即vchSig = stacktop(-2)。
在第181行，<你的公钥_vchPubKey>从stack中被提出，即vchPubKey = stacktop(-1)。
第188行对scriptCode没有任何影响，因为它不包含任何签名。
第189行，函数CheckSig()以参数CheckSig(vchSig, vchPubKey, scriptCode, txTo, nIn, nHashType)被调用。下面是该函数的源代码。
*/
#undef top













uint256 SignatureHash(CScript scriptCode, const CTransaction& txTo, unsigned int nIn, int nHashType)
/* txTo是将要被签署的交易。它同时也是CreateTransaction()中的wtxNew对象。它的输入
//交易列表中的第nln项,txTo.vin[nIn],是该函数将要起作用的目标
scriptCode是scriptPrereq+txout.scriptPubKey,其中txout是SignSignature()中定义
的来源交易txFrom()中的输出交易。由于此时scriptPrereq为空，scriptCode事实上是来源交易
txFrom中的输出交易列表当中被txTo作为输入交易引用的那笔的脚本代码。txout.scriptPubKey
有可能包含两类脚本：
脚本A：OP_DUP OP_HASH160 <你地址的160位哈希> OP_EQUALVERIFY OP_CECKSIG。该脚本将来源交易txFrom中的币发送给你，
其中<你地址的160位哈希>是你的比特币地址。
脚本B：<你的公钥> OP_CHECKSIG。该脚本将剩余的币退还至来源交易txFrom的发起人。由于你创建的新交易txTo/wtxNew将会花费来自txFrom的币，
你必须同时也是txFrom的创建者。换句话讲，当你在创建txFrom的时候，你其实是在花费之前别人发送给你的币。因此，<你的公钥>即是txFrom创建者的公钥，也是你自己的公钥。
*/

/*
我们在此停留片刻，来思考一下脚本A和脚本B。你有可能会问，这些脚本是从哪来的。中本聪在创造比特币的时候为比特币添加了一套脚本语言系统，
所以比特币中的交易都是由脚本代码完成的。该脚本系统其实也是后来智能合约的雏形。脚本A来自第29行，位于方法CSendDialog::OnButtonSend()，脚本B则来自第44行，位于方法CreateTransaction()。

1.当用户发起一笔交易时，比特币客户端会调用CSendDialog::OnButtonSend()方法并将脚本A添加至txFrom中的一笔输出交易中。
由于该输出交易的收款方为你本人，从而脚本中的<收款人地址160位哈希>，就是<你的地址160位哈希>。
2.如果txFrom是你本人创建的，则脚本B会被添加至CreateTransaction()中txFrom的某一笔输出交易。在这里，第44行位于CreateTransaction()中的公钥vchPubKey是你本人的公钥。

*/
{
    if (nIn >= txTo.vin.size())
    {
        printf("ERROR: SignatureHash() : nIn=%d out of range\n", nIn);
        return 1;
    }
    CTransaction txTmp(txTo);   //首先将txTo拷贝至txTemp

    // In case concatenating two scripts ends up with two codeseparators,
    // or an extra one at the end, this prevents all those possible incompatibilities.
    scriptCode.FindAndDelete(CScript(OP_CODESEPARATOR));  //qing

    // Blank out other inputs' signatures
    //接着清空除了txTmp.vin[nIn]之外的txTmp.vin中每一笔输入交易的scriptSig，该输入交易的scriptSig被设为scriptCode
    for (int i = 0; i < txTmp.vin.size(); i++)
        txTmp.vin[i].scriptSig = CScript();
    txTmp.vin[nIn].scriptSig = scriptCode;




//-----------------------------------------------------------------------------------
/*
enum
{
    SIGHASH_ALL = 1,                    //默认签名哈希的类型，对除了scriptSigs外的整个交易进行签名，阻止他人修改签名的内容。
    SIGHASH_NONE = 2,                    //一种哈希签名的类型，只对输入进行签名，允许任何人对输出进行修改
    SIGHASH_SINGLE = 3,               //一种签名哈希的类型，只对具有相同索引的input和output进行签名，允许修改其它input和output
    SIGHASH_ANYONECANPAY = 0x80,    //一种哈希签名的类型，它修改其他类型哈希签名的行为
}; 这个迭代中分四个值

*/
    // Blank out some of the outputs
    if ((nHashType & 0x1f) == SIGHASH_NONE)
    {
        // Wildcard payee
        txTmp.vout.clear();

        // Let the others update at will
        for (int i = 0; i < txTmp.vin.size(); i++)
            if (i != nIn)
                txTmp.vin[i].nSequence = 0;
    }
    else if ((nHashType & 0x1f) == SIGHASH_SINGLE)
    {
        // Only lockin the txout payee at same index as txin
        unsigned int nOut = nIn;
        if (nOut >= txTmp.vout.size())
        {
            printf("ERROR: SignatureHash() : nOut=%d out of range\n", nOut);
            return 1;
        }
        txTmp.vout.resize(nOut+1);
        for (int i = 0; i < nOut; i++)
            txTmp.vout[i].SetNull();

        // Let the others update at will
        for (int i = 0; i < txTmp.vin.size(); i++)
            if (i != nIn)
                txTmp.vin[i].nSequence = 0;
    }

    // Blank out other inputs completely, not recommended for open transactions
    if (nHashType & SIGHASH_ANYONECANPAY)
    {
        txTmp.vin[0] = txTmp.vin[nIn];
        txTmp.vin.resize(1);
    }


    //默认的，如果上面的if不成立，直接进行
    // Serialize and hash
    // txTmp和nHashType变成序列化后的类型CDataStream对象。该类型包括一个装有数据的字符容器类型。
    //所返回的哈希值是Hash()方法在计算序列化后的数据所得到的。
    CDataStream ss(SER_GETHASH);
    ss.reserve(10000);
    ss << txTmp << nHashType;
    return Hash(ss.begin(), ss.end());
}
/*
总结：
一笔交易可以包含多笔输入交易。SignatureHash()取其中一笔作为目标。它通过以下步骤生成哈希：
1.清空除了目标交易之外的所有输入交易。
2.复制来源交易中被目标交易作为输入交易引用的那笔输出交易的脚本至目标交易的输入交易列表中。
3.为修改后的交易生成哈希值。
*/






bool CheckSig(vector<unsigned char> vchSig, vector<unsigned char> vchPubKey, CScript scriptCode,
              const CTransaction& txTo, unsigned int nIn, int nHashType)
{
    CKey key;
    if (!key.SetPubKey(vchPubKey))
        return false;

    // Hash type is one byte tacked on to the end of the signature
    if (vchSig.empty())
        return false;
    if (nHashType == 0)
        nHashType = vchSig.back();
    else if (nHashType != vchSig.back())
        return false;
    vchSig.pop_back();

    if (key.Verify(SignatureHash(scriptCode, txTo, nIn, nHashType), vchSig))
        return true;

    return false;
}
/*
我们来研究下这个函数：

1.它的第一个参数vchSIg是<你的签名_vchSig>。
2.第二个参数vchPubKey是<你的公钥_vchPubKey>。
3.第三个参数scriptCode是<你的公钥_vchPubKey> OP_CHECKSIG。
函数CkeckSig()调用函数SignatureHash(scriptCode，txTo，nIn，nHashType）位于第15行。如果你比较我在第一章里介绍过的函数SignatureHash()，你会发现二者的输入参数完全相同。所以你会得到完全相同的哈希码。
接着回到继续执行验证案例B：
1.位于第190至191行，stack最顶端的两个项目，例如<你的签名_vchSig>和<你的公钥_vchPubKey>将被弹出。
2.位于第192行，CheckSig()的返回值，为true，将会被压入stack。因此stack现在仅包含一个true，意味着脚本执行成功。

*/






/*
第一个参数scriptPubKey可能包含脚本A也可能是脚本B。再一次说明，它是SignSignature()中来源交易txFrom的输出脚本。
 
第二个参数用来存放输出交易。它是一个容器对，每个对由一个脚本运算符（opcodetype类型）和脚本操作元（valtype类型）构成。

该函数第8-10行首先定义两个模板：
1.模板A：OP_DUP OP_HASH160 OP_PUBKEYHASH OP_EQUALVERIFY OP_CHECKSIG。
2.模板B：OP_PUBKEY OP_CHECKSIG。

很明显，模板A、模板B与脚本A、脚本B相对应。为了便于对比，以下是脚本A和B的内容：
1.脚本A：OP_DUP OP_HASH160 <你的地址160位哈希> OP_EQUALVERIFY OP_CHECKSIG。
2.脚本B：<你的公钥> OP_CHECKSIG。

该函数的作用是将scriptPubKey与两个模板相比较：
1.如果输入脚本为脚本A，则将模板A中的OP_PUBKEYHASH与脚本A中的<你的地址160位哈希>配对，并将该对放入vSolutionRet。
2.如果输入脚本为脚本B，则从模板B中提取运算符OP_PUBKEY，和从脚本B中提取运算元<你的公钥>，将二者配对并放入vSolutionRet。
3.如果输入脚本与两个模板均不匹配，则返回false。
*/
bool Solver(const CScript& scriptPubKey, vector<pair<opcodetype, valtype> >& vSolutionRet)
{
    // Templates
    static vector<CScript> vTemplates;
    if (vTemplates.empty())
    {
        // Standard tx, sender provides pubkey, receiver adds signature
        vTemplates.push_back(CScript() << OP_PUBKEY << OP_CHECKSIG);

        // Short account number tx, sender provides hash of pubkey, receiver provides signature and pubkey
        vTemplates.push_back(CScript() << OP_DUP << OP_HASH160 << OP_PUBKEYHASH << OP_EQUALVERIFY << OP_CHECKSIG);
    }

    // Scan templates
    const CScript& script1 = scriptPubKey;
    foreach(const CScript& script2, vTemplates)
    {
        vSolutionRet.clear();
        opcodetype opcode1, opcode2;
        vector<unsigned char> vch1, vch2;

        // Compare
        CScript::const_iterator pc1 = script1.begin();
        CScript::const_iterator pc2 = script2.begin();
        loop
        {
            bool f1 = script1.GetOp(pc1, opcode1, vch1);
            bool f2 = script2.GetOp(pc2, opcode2, vch2);
            if (!f1 && !f2)
            {
                // Success
                reverse(vSolutionRet.begin(), vSolutionRet.end());
                return true;
            }
            else if (f1 != f2)
            {
                break;
            }
            else if (opcode2 == OP_PUBKEY)
            {
                if (vch1.size() <= sizeof(uint256))
                    break;
                vSolutionRet.push_back(make_pair(opcode2, vch1));
            }
            else if (opcode2 == OP_PUBKEYHASH)
            {
                if (vch1.size() != sizeof(uint160))
                    break;
                vSolutionRet.push_back(make_pair(opcode2, vch1));
            }
            else if (opcode1 != opcode2)
            {
                break;
            }
        }
    }

    vSolutionRet.clear();
    return false;
}








//Solver()在SignSignature()中紧接着SignatureHash()被执行。它是真正用来为SignatureHash（）返回
//哈希值生成签名的函数

//四个参数的详解
//1.scriptPubKey位于第10行的调用函数SignSignature()将txOut.scriptPubKey，  ???
//来源交易txFrom的输出脚本，作为输入值传入第一个参数scriptPubKey。记住它可能包含脚本A或者脚本B。
//2.hash 是由SignatureHash（）生成的哈希值
//3.nHashType 的值为 SIGHASH_ALL ???
//4第四个参数是该函数的返回值，即调用函数SignSIgnature()中位于第12行的txin.scriptSig。记住txin是新生成的交易wtxNew
//（在调用函数SignSignature()中作为txTo引用）位于第nIn的输入交易。因此，wtxNew第nIn笔输入交易的scriptSig将存放该函数返回的签名。


/*
我们回到有4个参数的Solver()并继续对该函数的分析。现在我们清楚了该函数的工作原理。它会在两个分支中选择一个执行，
取决于从vSolutionRet得到的对来自脚本A还是脚本B。如果来自脚本A，item.first  == OP_PUBKEYHASH；如果来自脚本B，item.first  == OP_PUBKEY。

item.first  == OP_PUBKEY（脚本B）。在该情形下，item.second包含<你的公钥>。全局变量mapKeys将你的全部公钥映射至与之对应的私钥。
如果mapKeys当中没有该公钥，则报错（第16行）。否则，用从mapKeys中提取出的私钥签署新生成的交易wtxNew的哈希值，
其中哈希值作为第2个被传入的参数（CKey::Sign(mapKeys[vchPubKey], hash, vchSig)，第23行），再将结果放入vchSig，
接着将其序列化成scriptSigRet（scriptSigRet << vchSig，第24行）并返回。

item.first  == OP_PUBKEYHASH（脚本A）。在该情形下，item.second包含<你的地址160位哈希>。
该比特币地址将被用于从位于第23行的全局映射mapPubKeys中找到其所对应的公钥。
全局映射mapPubKeys将你的地址与生成它们的公钥建立一一对应关系（查看函数AddKey()）。
接着，通过该公钥从mapKeys中找到所对应的私钥，并用该私钥签署第二个参数hash。
签名和公钥将一同被序列化至scriptSigRet并返回（scriptSig << vchSig << vchPubkey，第24行）。
*/
bool Solver(const CScript& scriptPubKey, uint256 hash, int nHashType, CScript& scriptSigRet)
{
    scriptSigRet.clear();

    vector<pair<opcodetype, valtype> > vSolution;
    if (!Solver(scriptPubKey, vSolution))
        return false;

    // Compile solution
    CRITICAL_BLOCK(cs_mapKeys)
    {
        foreach(PAIRTYPE(opcodetype, valtype)& item, vSolution)
        {
            if (item.first == OP_PUBKEY)
            {
                // Sign
                const valtype& vchPubKey = item.second;
                if (!mapKeys.count(vchPubKey))
                    return false;
                if (hash != 0)
                {
                    vector<unsigned char> vchSig;
                    if (!CKey::Sign(mapKeys[vchPubKey], hash, vchSig))
                        return false;
                    vchSig.push_back((unsigned char)nHashType);
                    scriptSigRet << vchSig;
                }
            }
            else if (item.first == OP_PUBKEYHASH)
            {
                // Sign and give pubkey
                map<uint160, valtype>::iterator mi = mapPubKeys.find(uint160(item.second));
                if (mi == mapPubKeys.end())
                    return false;
                const vector<unsigned char>& vchPubKey = (*mi).second;
                if (!mapKeys.count(vchPubKey))
                    return false;
                if (hash != 0)
                {
                    vector<unsigned char> vchSig;
                    if (!CKey::Sign(mapKeys[vchPubKey], hash, vchSig))
                        return false;
                    vchSig.push_back((unsigned char)nHashType);
                    scriptSigRet << vchSig << vchPubKey;
                }
            }
        }
    }

    return true;
}


bool IsMine(const CScript& scriptPubKey)
{
    CScript scriptSig;
    return Solver(scriptPubKey, 0, 0, scriptSig);
}


bool ExtractPubKey(const CScript& scriptPubKey, bool fMineOnly, vector<unsigned char>& vchPubKeyRet)
{
    vchPubKeyRet.clear();

    vector<pair<opcodetype, valtype> > vSolution;
    if (!Solver(scriptPubKey, vSolution))
        return false;

    CRITICAL_BLOCK(cs_mapKeys)
    {
        foreach(PAIRTYPE(opcodetype, valtype)& item, vSolution)
        {
            valtype vchPubKey;
            if (item.first == OP_PUBKEY)
            {
                vchPubKey = item.second;
            }
            else if (item.first == OP_PUBKEYHASH)
            {
                map<uint160, valtype>::iterator mi = mapPubKeys.find(uint160(item.second));
                if (mi == mapPubKeys.end())
                    continue;
                vchPubKey = (*mi).second;
            }
            if (!fMineOnly || mapKeys.count(vchPubKey))
            {
                vchPubKeyRet = vchPubKey;
                return true;
            }
        }
    }
    return false;
}


bool ExtractHash160(const CScript& scriptPubKey, uint160& hash160Ret)
{
    hash160Ret = 0;

    vector<pair<opcodetype, valtype> > vSolution;
    if (!Solver(scriptPubKey, vSolution))
        return false;

    foreach(PAIRTYPE(opcodetype, valtype)& item, vSolution)
    {
        if (item.first == OP_PUBKEYHASH)
        {
            hash160Ret = uint160(item.second);
            return true;
        }
    }
    return false;
}










//首先需要注意的是，该函数有5个参数，而CreateTransaction()只有3个。
//这是因为在script.h文件里，后两个参数已默认给出。
//三个参数
/*
1.txFrom是一个*pcoin对象。它是CreateTransaction()里setCoins中的所有币中的某一个。
它同时也是一笔来源交易。它的若干输出交易当中包含了新交易将要花费的币。因为sign是为一次输出交易签字
2.txTo是CreateTransaction()里的wtxNew对象。
它是将要花费来源交易txFrom的新交易。新交易需要被签署方可生效。
3.nIn是指向txTo中输入交易列表的索引位置。该输入交易列表包含一个对txFrom的输出交易列表的引用。
更准确地讲，txin=txTo.vin[nIn]（第4行）是txTo中的输入交易；
txout=txFrom.vout[txin.prev.out.n]（第6行）是txin所指向的txFrom中的输出交易。
*/
/*
以下是SignSignature()所做的工作：
1.调用SignatureHash()方法生成txTo的哈希值。
2.调用Solver()函数签署刚才生成的哈希。
3.调用EvalScript()来运行一小段脚本并检查签名是否合法。

*/
bool SignSignature(const CTransaction& txFrom, CTransaction& txTo, unsigned int nIn, int nHashType, CScript scriptPrereq)
{
    assert(nIn < txTo.vin.size());
    CTxIn& txin = txTo.vin[nIn];        //nIn是索引数，因为不止一个txto
    assert(txin.prevout.n < txFrom.vout.size());
    const CTxOut& txout = txFrom.vout[txin.prevout.n];

    // Leave out the signature from the hash, since a signature can't sign itself.
    // The checksig op will also drop the signatures from its hash.
    uint256 hash = SignatureHash(scriptPrereq + txout.scriptPubKey, txTo, nIn, nHashType);

    if (!Solver(txout.scriptPubKey, hash, nHashType, txin.scriptSig))
        return false;

    txin.scriptSig = scriptPrereq + txin.scriptSig;

    // Test solution
    // OP_CODESEPARATOR：All of the signature checking words will only match signatures 
    //to the data after the most recently-executed OP_CODESEPARATOR.
    if (scriptPrereq.empty())
        if (!EvalScript(txin.scriptSig + CScript(OP_CODESEPARATOR) + txout.scriptPubKey, txTo, nIn))
            return false;

    return true;
}






bool VerifySignature(const CTransaction& txFrom, const CTransaction& txTo, unsigned int nIn, int nHashType)
{
    assert(nIn < txTo.vin.size());
    const CTxIn& txin = txTo.vin[nIn];
    if (txin.prevout.n >= txFrom.vout.size())
        return false;
    const CTxOut& txout = txFrom.vout[txin.prevout.n];

    if (txin.prevout.hash != txFrom.GetHash())
        return false;

    return EvalScript(txin.scriptSig + CScript(OP_CODESEPARATOR) + txout.scriptPubKey, txTo, nIn, nHashType);
}
