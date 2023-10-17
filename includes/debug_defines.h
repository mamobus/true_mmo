#pragma once
#define _DEBUG_
#ifdef _DEBUG_
#define prind(...) printf(__VA__ARGS__)
#define print printf("Line: %d\n", __LINE__);
#else
#define print(...)  
#endif
