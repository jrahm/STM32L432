#ifndef COMMON__H
#define COMMON__H

/* Define __IO to be volatile if it's not already. */
#ifndef __IO
#define __IO volatile
#endif

#define bool int

#define PACKED __attribute__((packed))

#endif /* COMMON_H */
