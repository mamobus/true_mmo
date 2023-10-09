#pragma once

#ifdef _DEBUG_
#define print(...) printf(__VA__ARGS__)
#define ass(...) assert(__VA__ARGS__)
#else
#define print(...)  
#define ass(...)  
#endif
