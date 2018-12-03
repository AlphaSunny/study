// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#ifdef _MSC_VER
#pragma warning(disable:4786)                           //阻止 4786，4804，4717号错误
#pragma warning(disable:4804)
#pragma warning(disable:4717)
#endif
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0400
#define WIN32_LEAN_AND_MEAN 1

//wxwidgets的库
#include <wx/wx.h>                              
#include <wx/clipbrd.h>
#include <wx/snglinst.h>


#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>

//c的库
#include <stdio.h>
#include <stdlib.h>

#include <io.h>        //这个库包括了低级的io流
#include <math.h>
#include <limits.h>
#include <float.h>
#include <assert.h>
#include <process.h>
#include <malloc.h>

//c++库
#include <memory>
#define BOUNDSCHECK 1
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>

//一些boost库
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/array.hpp>
#pragma hdrstop
using namespace std;
using namespace boost;


//包括这个源码中的所有的头文件
#include "serialize.h"
#include "uint256.h"
#include "util.h"
#include "key.h"
#include "bignum.h"
#include "base58.h"
#include "script.h"
#include "db.h"
#include "net.h"
#include "irc.h"
#include "main.h"
#include "market.h"
#include "uibase.h"
#include "ui.h"
