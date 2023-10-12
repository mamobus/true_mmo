#pragma once
#define _DEBUG_
#ifdef _DEBUG_
#define prind(...) printf(__VA__ARGS__)
#define print printf("Line: %d\n", __LINE__);
#define ass(...) assert(__VA__ARGS__)
#else
#define print(...)  
#define ass(...)  
#endif
