#ifndef __JD_DEFINE
#define __JD_DEFINE

#define _JD_BEGIN namespace jd {
#define _JD_END }
#define _JD jd::
#define _USING_JD using namespace jd;

#define safe_delete(x) { delete x; x = nullptr; } 

#include <utility>
#include <cstdlib>


#endif // !__JD_DEFINE