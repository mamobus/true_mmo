#pragma once
#define _DEBUG_
#ifdef _DEBUG_
#define prind(...) printf(__VA__ARGS__)
#define print printf("File %s\nLine: %d\n\n", __FILE__, __LINE__);
#else
#define print(...)  
#endif
