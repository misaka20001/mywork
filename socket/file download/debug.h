#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define   DEBUG_PRNF(_x_) \
do{ \
printf("%s(%d): ", __FILE__, __LINE__); \
printf _x_; \
}while(0)

#endif // DEBUG_H_INCLUDED
