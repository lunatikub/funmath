#ifndef ANT_LANGTON_H_
# define ANT_LANGTON_H_

#include <stdint.h>

#define __LR (0)     /* Left  rotation */
#define __RR (1)     /* rigth rotation */

#define __U (0)      /* Looking up    */
#define __D (1)      /* Looking down  */
#define __L (2)      /* Looking left  */
#define __R (3)      /* Looking rigth */

enum {
    __WHITE = 0,
    __BLACK,
    __RED,
    __GREEN,
    __BLUE,
    __SKY,
    __PURPLE,
    __GREY,
    __YELLOW,
    __DRED,
    __DGREEN,
};

typedef struct {
    uint32_t rotation;
    uint32_t color;
} ant_trans_t;;

#endif /* !ANT_LANGTON_H_ */
